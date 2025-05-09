#include <wup/wup.h>


static u8 UICGood = 0;


void UIC_Init()
{
    WUP_DelayMS(5);
    u8 sync = UIC_Sync();
    if (sync != 0x2F && sync != 0x3F)
        return;

    UICGood = 1;
}

u8 UIC_IsGood()
{
    return UICGood;
}


u8 UIC_Sync()
{
    u8 buf = 0x7F;
    u8 ret = 0;

    SPI_Start(SPI_DEVICE_UIC, SPI_CLK_248KHZ);
    WUP_DelayMS(1);
    SPI_Write(&buf, 1);
    WUP_DelayMS(1);
    do
    {
        REG_SPI_CNT |= 0x40;
        WUP_DelayUS(60);
        REG_SPI_CNT &= ~0x40;
        ret = 0;
        SPI_Read(&ret, 1);
    }
    while (ret == 0);

    SPI_Finish();
    WUP_DelayUS(60);

    return ret;
}


void UIC_SendCommand(u8 cmd, u8* in_data, int in_len, u8* out_data, int out_len)
{
    SPI_Start(SPI_DEVICE_UIC, SPI_CLK_8MHZ);

    SPI_Write(&cmd, 1);
    if (in_data)
    {
        WUP_DelayUS(60);
        SPI_Write(in_data, in_len);
    }

    if (out_data)
    {
        // TODO: figure out what REG_SPI_CNT bit6 does
        REG_SPI_CNT |= 0x40;
        WUP_DelayUS(60);
        REG_SPI_CNT &= ~0x40;
        SPI_Read(out_data, out_len);
    }

    SPI_Finish();
}


void UIC_SetLED(u8 led, u8 val)
{
    if (!UICGood) return;

    u8 buf[2];
    buf[0] = led;
    buf[1] = val;

    UIC_SendCommand(0x08, buf, 2, NULL, 0);
}

void UIC_Shutdown()
{
    if (!UICGood) return;

    UIC_SendCommand(0x16, NULL, 0, NULL, 0);
}

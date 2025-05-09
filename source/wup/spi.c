#include <wup/wup.h>


void SPI_Init()
{
    // ???
    REG_SPI_CNT = 0x307;
    REG_SPI_UNK14 = (REG_SPI_UNK14 & ~0x8013) | 0x8010;
}


void SPI_Start(u32 device, u32 clock)
{
    REG_SPI_DEVICE_SEL = device & 0x3;
    REG_SPI_CLOCK = clock & 0x87FF;

    REG_SPI_CNT = (REG_SPI_CNT & ~SPI_CS_MASK) | SPI_CSMODE_MANUAL | SPI_CS_SELECT;
}

void SPI_Finish()
{
    REG_SPI_CNT = (REG_SPI_CNT & ~SPI_CS_MASK) | SPI_CSMODE_MANUAL | SPI_CS_RELEASE;
}


void SPI_Read(u8* buf, int len)
{
    REG_SPI_CNT = (REG_SPI_CNT & ~SPI_DIR_MASK) | SPI_DIR_READ;

    REG_SPI_READ_LEN = len;
    SPDMA_Transfer(0, buf, SPDMA_PERI_SPI, SPDMA_DIR_READ, len);
    SPDMA_Wait(0);

    REG_SPI_READ_LEN = 0;
}

void SPI_Write(u8* buf, int len)
{
    REG_SPI_CNT = (REG_SPI_CNT & ~SPI_DIR_MASK) | SPI_DIR_WRITE;

    REG_SPI_IRQ_ENABLE |= SPI_IRQ_WRITE;

    SPDMA_Transfer(0, buf, SPDMA_PERI_SPI, SPDMA_DIR_WRITE, len);
    SPDMA_Wait(0);

    while (!(REG_SPI_IRQ_STATUS & SPI_IRQ_WRITE));
    REG_SPI_IRQ_STATUS = SPI_IRQ_WRITE;
    REG_SPI_IRQ_ENABLE &= ~SPI_IRQ_WRITE;
}

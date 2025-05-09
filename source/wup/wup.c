#include <wup/wup.h>


void WUP_Init()
{
    REG_TIMER_TARGET(0) = 0xFFFFFFFF;
    REG_TIMER_CNT(0) = 0;

    DMA_Init();
    SPI_Init();
    UIC_Init();
    UART_Init();
}


void WUP_DelayUS(int us)
{
    u32 target = (us >> 1) - 1;

    REG_TIMER_CNT(0) = TIMER_ENABLE;
    while (REG_TIMER_VALUE(0) < target);
    REG_TIMER_CNT(0) = 0;
}

void WUP_DelayMS(int ms)
{
    u32 target = (ms * 500) - 1;

    REG_TIMER_CNT(0) = TIMER_ENABLE;
    while (REG_TIMER_VALUE(0) < target);
    REG_TIMER_CNT(0) = 0;
}

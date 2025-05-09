#include <wup/wup.h>


void DMA_Init()
{
    // enable DMA
    REG_DMA_CNT = 0x3;
}


void SPDMA_Transfer(u32 chan, const void* data, u32 peri, u32 dir, u32 len)
{
    if (chan > 1) return;

    SPDMA_Wait(chan);

    REG_SPDMA_CNT(chan) = dir | peri;
    REG_SPDMA_CHUNKLEN(chan) = 0;
    REG_SPDMA_MEMSTRIDE(chan) = 0;
    REG_SPDMA_LEN(chan) = len - 1;
    REG_SPDMA_MEMADDR(chan) = (u32)data;
    REG_SPDMA_START(chan) = SPDMA_START;
}

void SPDMA_Wait(u32 chan)
{
    if (chan > 1) return;

    while (REG_SPDMA_START(chan) & SPDMA_BUSY);
    REG_SPDMA_START(chan) = SPDMA_STOP;
}

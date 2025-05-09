#ifndef _DMA_H_
#define _DMA_H_

void DMA_Init();


// SPDMA: for transferring from/to peripherals

void SPDMA_Transfer(u32 chan, const void* data, u32 peri, u32 dir, u32 len);
void SPDMA_Wait(u32 chan);

#endif // _DMA_H_

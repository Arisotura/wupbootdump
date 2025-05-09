#ifndef _WUP_H_
#define _WUP_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "regs.h"

#include "dma.h"
#include "spi.h"
#include "uic.h"
#include "uart.h"

void WUP_Init();

void WUP_DelayUS(int us);
void WUP_DelayMS(int ms);

#endif // _WUP_H_

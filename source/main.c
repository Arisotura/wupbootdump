#include <wup/wup.h>


void main()
{
    UIC_SetLED(0, 255);

    for (int i = 0; i < 0x1000; i++)
        *(u8*)(0x200000+i) = *(vu8*)i;
    UART_Send((u8*)0x200000, 0x1000);

    UIC_SetLED(0, 0);
    //UIC_Shutdown();
	for (;;);
}




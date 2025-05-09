#ifndef _UIC_H_
#define _UIC_H_

void UIC_Init();

u8 UIC_Sync();
void UIC_SendCommand(u8 cmd, u8* in_data, int in_len, u8* out_data, int out_len);

void UIC_SetLED(u8 led, u8 val);
void UIC_Shutdown();

#endif

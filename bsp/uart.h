#ifndef __UART_H_
#define __UART_H_
#include "main.h"					  


extern int time_come;
void UART_Init(void);
void uartSendByte(unsigned char dat);
void UartSendString(unsigned char *s);
#endif

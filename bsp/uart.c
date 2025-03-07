#include "uart.h"
sfr AUXR = 0x8E;  // ¶¨Òå AUXR ¼Ä´æÆ÷

void UART_Init() {
    TMOD = 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    SCON = 0x50;
    ES = 1;
    EA = 1;

	TI=1;
}
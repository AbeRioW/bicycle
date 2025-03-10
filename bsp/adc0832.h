#ifndef __ADC0832_H_
#define __ADC0832_H_

#include <reg52.h>

//IO设置

sbit ADC_CLK = P2^0;
sbit ADC_DO = P2^1;
sbit ADC_DI = P2^2;
sbit ADC_CS = P2^3;

//函数或者变量声明
extern void delay1(void);
extern void ADC_setchn(unsigned char chn);
extern unsigned char ADC_getdate(void);
extern unsigned char ADC0832(unsigned char chn);

#endif

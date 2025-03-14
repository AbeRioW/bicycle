#ifndef __LCD_H_
#define __LCD_H_

#include<reg52.h>
#include<intrins.h>
#include "config.h"

/**********************************
PIN¿Ú¶¨Òå
**********************************/
#define LCD1602_DB P0

sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^6;
sbit LCD1602_RS=P2^5;

void InitLcd1602();
void LcdWriteCmd(uchar cmd);
void LcdWrite(uchar addr, uchar dat);				  
void LCD_TEST(void);
void LCDClear(void);
#endif

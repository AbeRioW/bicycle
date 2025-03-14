#ifndef __MAIN_H_
#define __MAIN_H_
				  
#include "reg52.h"			 
#include "lcd.h"
#include "ds3231.h"
#include "uart.h"
#include "stdio.h"
#include "adc0832.h"
#include "ui.h"
#include "config.h"
#include "DHT11.h"

sbit BEEP = P1^2;
sbit LED = P1^3;

sbit BUTTON_L = P1^4;
sbit BUTTON_M = P1^5;
sbit BUTTON_R = P1^6;
#endif

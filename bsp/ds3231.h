#ifndef __DS3231_H_
#define __DS3231_H_

#include "main.h"

/**********************************
		PIN口定义
**********************************/
//DS3221引脚
sbit SDA = P1^0;  // I2C 数据线
sbit SCL = P1^1;  // I2C 时钟线

#define DS3231_ADDRESS 0xd0   //ds3231的i2c地址					  

void DS3231_Write(unsigned char addr, unsigned char dat);
unsigned char DS3231_Read(unsigned char addr);

#endif

#ifndef __DS3231_H_
#define __DS3231_H_

#include "main.h"

/**********************************
		PIN�ڶ���
**********************************/
//DS3221����
sbit SDA = P1^0;  // I2C ������
sbit SCL = P1^1;  // I2C ʱ����

#define DS3231_ADDRESS 0xd0   //ds3231��i2c��ַ					  

void DS3231_Write(unsigned char addr, unsigned char dat);
unsigned char DS3231_Read(unsigned char addr);

#endif

#include "main.h"
unsigned char Disp[]="Test OK";

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main(void)
{
    int i=0;
    unsigned char second, minute, hour;
	InitLcd1602();
    UART_Init();
	ADC_init();
    timer0_init();

	 
    DS3231_Write(0x00, 0x00);  // 设置秒
    DS3231_Write(0x01, 0x30);  // 设置分钟
    DS3231_Write(0x02, 0x12);  // 设置小时

	DS3231_Write(0x03, 0x03);  // 设置week
	DS3231_Write(0x04, 0x01);  // 设置日
	DS3231_Write(0x05, 0x01);  // 设置月
	DS3231_Write(0x06, 0x17);  // 设置年

	while(1)
	{   
	      RH();
		  show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);
	      if(time_come)
		  {
		  	time_come=0;
			show_time();


		  }
	}				
}

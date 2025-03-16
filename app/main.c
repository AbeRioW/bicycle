#include "main.h"
unsigned char Disp[]="Test OK";
double dht_ban = 70;
double tem_ban = 40;

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main(void)
{
    int i=0;
	int fanzhuan = 0;
    unsigned char second, minute, hour;
	unsigned char adc_data;
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
	DS3231_Write(0x06, 0x24);  // 设置年

	while(1)
	{   
		   	if(BUTTON_M==0)
			{
			  		LCDClear();
			   		ui_setting();
			}
		   RH();
		  show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);		  
		  if((((double)U8RH_data_H+(double)U8RH_data_L/100)>dht_ban)||(((double)U8T_data_H+(double)U8T_data_H/100)>tem_ban))
		  {
		  	BEEP=0;
			LED=0;
			delay_ms(200);
			BEEP=1;
			LED=1;
		  }
	      if(time_come)
		  {
		    time_come=0;
		    fanzhuan = !fanzhuan;
			if(fanzhuan)
			{

			   show_time();

			}
			else
			{
               LCDClear();
			   adc_data = ADC0832();
			   LcdWrite(0x80,adc_data/10+0x30);
			   LcdWrite(0x80+1,adc_data%10+0x30);
			   LcdWrite(0x80+2,'B');
			   LcdWrite(0x80+3,'P');
			   LcdWrite(0x80+4,'M');
			}
		  }
	}				
}

#include "main.h"
unsigned char Disp[]="Test OK";

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main(void)
{
    int i=0;
    unsigned char second, minute, hour;
	InitLcd1602();
    UART_Init();
	ADC_init();
    timer0_init();

	 
    DS3231_Write(0x00, 0x00);  // ������
    DS3231_Write(0x01, 0x30);  // ���÷���
    DS3231_Write(0x02, 0x12);  // ����Сʱ

	DS3231_Write(0x03, 0x03);  // ����week
	DS3231_Write(0x04, 0x01);  // ������
	DS3231_Write(0x05, 0x01);  // ������
	DS3231_Write(0x06, 0x17);  // ������

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

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
	int fanzhuan = 0;
    unsigned char second, minute, hour;
	unsigned char adc_data;
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
			

		   	if(BUTTON_R==0)
			{
				delay_ms(2);
				if(BUTTON_R==0)
				{
			   		Lcd_show_string(1,0,"               ",16);
					Lcd_show_string(2,0,"               ",16);
					ui_setting();
				}				

			}
		   RH();
		  show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);		  

	      if(time_come)
		  {
		    time_come=0;
					   	if(BUTTON_R==0)
			{
				delay_ms(2);
				if(BUTTON_R==0)
				{
			   		Lcd_show_string(1,0,"               ",16);
					Lcd_show_string(2,0,"               ",16);
					ui_setting();
				}				

			}
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

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
    unsigned char second, minute, hour;
	unsigned char i;
//	LcdInit();
    UART_Init();
//    DS3231_Write(0x00, 0x00);  // ������
//    DS3231_Write(0x01, 0x30);  // ���÷���
//    DS3231_Write(0x02, 0x12);  // ����Сʱ

	while(1)
	{   
	   	printf("%x\r\n",ADC0832(0));
		Lcd1602_Delay1ms(1000);
	}				
}

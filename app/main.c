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
	InitLcd1602();
    UART_Init();
	ADC_init();
    
//    DS3231_Write(0x00, 0x00);  // ������
//    DS3231_Write(0x01, 0x30);  // ���÷���
//    DS3231_Write(0x02, 0x12);  // ����Сʱ

	while(1)
	{   
		  printf("%d\r\n",ADC0832(0));
		  delay_ms(1000);
	}				
}

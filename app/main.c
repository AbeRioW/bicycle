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
    unsigned char second, minute, hour;
	unsigned char i;
	LcdInit();
    UART_Init();
    DS3231_Write(0x00, 0x00);  // 设置秒
    DS3231_Write(0x01, 0x30);  // 设置分钟
    DS3231_Write(0x02, 0x12);  // 设置小时

	while(1)
	{   
	   	printf("%02x\r\n",DS3231_Read(0x00));
	    //printf("heool\r\n");
	      //  LcdWriteData(DS3231_Read(0x00));
	}				
}

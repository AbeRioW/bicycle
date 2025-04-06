#include "main.h"
#include "stdio.h"
unsigned char Disp[]="Test OK";
double dht_ban = 70;
double tem_ban = 40;

static int key1_position = 0;

void show_4data(void);
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
	Int0Init();
	 
//    DS3231_Write(0x00, 0x00);  // 设置秒
//    DS3231_Write(0x01, 0x30);  // 设置分钟
//    DS3231_Write(0x02, 0x12);  // 设置小时
//
//	DS3231_Write(0x03, 0x03);  // 设置week
//	DS3231_Write(0x04, 0x01);  // 设置日
//	DS3231_Write(0x05, 0x01);  // 设置月
//	DS3231_Write(0x06, 0x24);  // 设置年
	while(1)
	{   
		    if(time_come) //定时时间到显示时间
			{
				time_come=0;
				show_time();	
			}

			if(BUTTON_L==0)
			{
			    delay_ms(100);
				if(BUTTON_L==0)
				{
					key1_position++;
					switch(key1_position)
					{
				   		case 1:
					    	LCDClear();
							show_4data();
						break;
						case 2:
							handle_setting();
						break;
					}	
				}

			}
	}				
}

void show_4data(void)
{
	char show[20];
	unsigned char adc_data;
	float xinlv_v;
  while(1)
  {

	RH();
	show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);

	 adc_data = ADC0832();
	xinlv_v = (float)adc_data*5.0/255;
	sprintf(show,"heart rate:%0.1f",(5.0-xinlv_v)*100);
	UartSendString(show);

	sprintf(show,"%0.1fBPM",(5.0-xinlv_v)*100) ;
	Lcd_show_string(0,0,show,7);

	delay_ms(400);
	
	//假定一圈一个脉冲,车子的周长为1米
	//一秒内产生了多少给脉冲，相当于一秒钟内走了X*1(米)
	//那速度就是X米/秒
	//换算成公里 X*3.6
	if(time_come)
	{
		time_come=0;
		sprintf(show,"%.1fkm/h",(float)(speed_count)*3.6);
		Lcd_show_string(0,8,show,7);
		speed_count=0;


	}

  }


}
////		   if(BUTTON_M==0)
////			{
////			  		LCDClear();
////			   		ui_setting();
////			}
////		   RH();
////
////		  show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);		  
////		  if((((double)U8RH_data_H+(double)U8RH_data_L/100)>dht_ban)||(((double)U8T_data_H+(double)U8T_data_H/100)>tem_ban))
////		  {
////		  	BEEP=0;
////			LED=0;
////			delay_ms(200);
////			BEEP=1;
////			LED=1;
////		  }
//	      if(time_come)
//		  {
////		  	
//////		    time_come=0;
//////		    fanzhuan = !fanzhuan;
//////			if(fanzhuan)
//////			{
////
//			   show_time();
////
//			}
//////			else
//////			{
//////               LCDClear();
//////
//////			   adc_data = ADC0832();
//////			   sprintf(show,"heart rate:%02x",adc_data);
//////			   UartSendString(show);
//////			   LcdWrite(0x80,adc_data/10+0x30);
//////			   LcdWrite(0x80+1,adc_data%10+0x30);
//////			   LcdWrite(0x80+2,'B');
//////			   LcdWrite(0x80+3,'P');
//////			   LcdWrite(0x80+4,'M');
//////			}
////		  }



#include "main.h"
#include "stdio.h"
#Include "ui.h"
unsigned char Disp[]="Test OK";
double dht_ban = 70;
double tem_ban = 40;

int key1_position = 0;

void show_4data(void);
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
	Int0Init();
	 
//    DS3231_Write(0x00, 0x00);  // ������
//    DS3231_Write(0x01, 0x30);  // ���÷���
//    DS3231_Write(0x02, 0x12);  // ����Сʱ
//
//	DS3231_Write(0x03, 0x03);  // ����week
//	DS3231_Write(0x04, 0x01);  // ������
//	DS3231_Write(0x05, 0x01);  // ������
//	DS3231_Write(0x06, 0x24);  // ������

	while(1)
	{   
		    if(time_come) //��ʱʱ�䵽��ʾʱ��
			{
				time_come=0;
				show_time();	
			}

			if(BUTTON_L==0)
			{
			    delay_ms(100);
				if(BUTTON_L==0)
				{
					LCDClear();
					show_4data();
				}
			}
	}				
}



//	int speed_ban=60;
//int heart_ban = 80;
//int rh_ban = 60;
//int th_ban = 30;


void show_4data(void)
{
	char show[25];
	unsigned char adc_data;
	float xinlv_v;
  while(1)
  {

	RH();
	show_dht(U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_L);
//	printf("%d\r\n",U8RH_data_H);

//	sprintf(show,"rh:%02x.%02x th:%02x.%02x",U8RH_data_H,U8RH_data_L,U8T_data_H,U8T_data_H);
//		UartSendString(show);

	 adc_data = ADC0832(0);
	xinlv_v = (float)adc_data*5.0/255;
//	sprintf(show,"heart rate:%0.1f",(5.0-xinlv_v)*100);
//	UartSendString(show);

	sprintf(show,"%0.1fBPM",(5.0-xinlv_v)*100) ;
	Lcd_show_string(0,0,show,7);

	delay_ms(400);
	
	//�ٶ�һȦһ������,���ӵ��ܳ�Ϊ1��
	//һ���ڲ����˶��ٸ����壬�൱��һ����������X*1(��)
	//���ٶȾ���X��/��
	//����ɹ��� X*3.6
	if(time_come)
	{
		time_come=0;
		sprintf(show,"%.1fkm/h",(float)(speed_count)*3.6);
		Lcd_show_string(0,8,show,7);
		sprintf(show,"rh:%c%c th:%c%c\r\n",U8RH_data_H/10+0x30,U8RH_data_H%10+0x30,U8T_data_H/10+0x30,U8T_data_H%10+0x30);
		UartSendString(show);

		sprintf(show,"heart rate:%0.1f SPEED:%0.1fkm/h",(5.0-xinlv_v)*100,(float)(speed_count)*3.6);
//			sprintf(show,"SPEED:%0.1fkm/h",(float)(speed_count)*3.6);
			UartSendString(show);

	}

			if(BUTTON_L==0)
			{
			    delay_ms(100);
				if(BUTTON_L==0)
				{
//				    key1_position++; //	 key1_position==1��
					LCDClear();
					break;
				}
			}

	if((U8RH_data_H>rh_ban)||(5.0-xinlv_v)*100>heart_ban||U8T_data_H>th_ban||(float)(speed_count)*3.6>speed_ban)	  //���ⱨ��
	{
			LED=0;
			BEEP=0;
	}
	else
	{
			LED=1;
			BEEP=1;
	}

	speed_count=0;
  }

  handle_setting();


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



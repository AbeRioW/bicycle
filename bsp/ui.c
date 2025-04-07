#include "ui.h"
int speed_ban=60;
int heart_ban = 80;
int rh_ban = 60;
int th_ban = 30;
void show_time(void)
{
   	    unsigned char dat;
	    unsigned char second, minute, hour;
		unsigned char year, month, date,week;
		 Lcd_show_string(1,1,"Current Time",12);


		dat = DS3231_Read(0x06);
		year = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+0+0x40,year/10+0x30);
		LcdWrite(0x80+1+0x40,year%10+0x30);

		dat = DS3231_Read(0x05);
		month =	((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+2+0x40,month/10+0x30);
		LcdWrite(0x80+3+0x40,month%10+0x30);

		 dat = DS3231_Read(0x04);
		 date =	 ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+4+0x40,date/10+0x30);
		LcdWrite(0x80+5+0x40,date%10+0x30);

		//时间
		dat = DS3231_Read(0x02);
		hour = 	((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+7+0x40,hour/10+0x30);
		LcdWrite(0x80+8+0x40,hour%10+0x30);
		LcdWrite(0x80+9+0x40,':');


		dat = DS3231_Read(0x01);
	    minute = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+10+0x40,minute/10+0x30);
		LcdWrite(0x80+11+0x40,minute%10+0x30);
		LcdWrite(0x80+12+0x40,':');

		dat = DS3231_Read(0x00);
		second = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+13+0x40,second/10+0x30);
		LcdWrite(0x80+14+0x40,second%10+0x30);
}


void show_dht(unsigned char RH,unsigned char RL,unsigned char TH,unsigned char TL)
{
		LcdWrite(0x80+0x40,RH/10+0x30);
		LcdWrite(0x80+0x40+1,RH%10+0x30);
		LcdWrite(0x80+0x40+2,'.');
		LcdWrite(0x80+0x40+3,RL/10+0x30);
		LcdWrite(0x80+0x40+4,RL%10+0x30);
		LcdWrite(0x80+0x40+5,'%');
		LcdWrite(0x80+0x40+6,'R');
		LcdWrite(0x80+0x40+7,'H');

		LcdWrite(0x80+0x40+9,TH/10+0x30);
		LcdWrite(0x80+0x40+10,TH%10+0x30);
		LcdWrite(0x80+0x40+11,'.');
		LcdWrite(0x80+0x40+12,TL/10+0x30);
		LcdWrite(0x80+0x40+13,TL%10+0x30);
		LcdWrite(0x80+0x40+14,'C');
}


void handle_setting(void)
{
       	unsigned char dat_y,dat_month,dat_date,dat_hour,dat_minute,dat_second;
	    unsigned char second, minute, hour;
		unsigned char year, month, date,week;
		char data_chow[2]={0};
		int position=0;

	   Lcd_show_string(1,1,"Setting time",12);
		dat_y = DS3231_Read(0x06);
		year = ((dat_y&0x70)>>4)*10+(dat_y&0x0f);
		LcdWrite(0x80+0x40+0,year/10+0x30);
		LcdWrite(0x80+0x40+1,year%10+0x30);

		dat_month = DS3231_Read(0x05);
		month =	((dat_month&0x70)>>4)*10+(dat_month&0x0f);
		LcdWrite(0x80+0x40+2,month/10+0x30);
		LcdWrite(0x80+0x40+3,month%10+0x30);

		 dat_date = DS3231_Read(0x04);
		 date =	 ((dat_date&0x70)>>4)*10+(dat_date&0x0f);
		LcdWrite(0x80+0x40+4,date/10+0x30);
		LcdWrite(0x80+0x40+5,date%10+0x30);

		//时间

		dat_hour = DS3231_Read(0x02);
		hour = ((dat_hour&0x70)>>4)*10+(dat_hour&0x0f);
		LcdWrite(0x80+0x40+7,hour/10+0x30);
		LcdWrite(0x80+0x40+8,hour%10+0x30);
		LcdWrite(0x80+0x40+9,':');


		dat_minute = DS3231_Read(0x01);
	    minute = ((dat_minute&0x70)>>4)*10+(dat_minute&0x0f);
		LcdWrite(0x80+0x40+10,minute/10+0x30);
		LcdWrite(0x80+0x40+11,minute%10+0x30);
		LcdWrite(0x80+0x40+12,':');

		dat_second = DS3231_Read(0x00);
		second = ((dat_second&0x70)>>4)*10+(dat_second&0x0f);
		LcdWrite(0x80+0x40+13,second/10+0x30);
		LcdWrite(0x80+0x40+14,second%10+0x30);
	while(1)
	{
		 if(BUTTON_L ==0)			  //KEY1移动
		 {
		    delay_ms(100);
		    if(BUTTON_L ==0)
			{
				position++;
				if(position>5)
				{
					//把数据写到DS3221中
					DS3231_Write(0x06,dat_y);
					DS3231_Write(0x05,dat_month);
					DS3231_Write(0x04,dat_date);
					DS3231_Write(0x02,dat_hour);
					DS3231_Write(0x01,dat_minute);
					DS3231_Write(0x00,dat_second);
					 LCDClear();
					 break;
				}
			}

		 }

		 if(BUTTON_M==0)
		 {
		 	delay_ms(100);
		    if(BUTTON_M==0)
			{
			        switch(position)
					{
						case 0:	   //对年的设置
							dat_y=dat_y-1;
							if(dat_y<0)
							{
								dat_y=99;	
							}
				    		year = ((dat_y&0x70)>>4)*10+(dat_y&0x0f);
							LcdWrite(0x80+0x40+0,year/10+0x30);
							LcdWrite(0x80+0x40+1,year%10+0x30);	
						break;
						case 1:	  //对月的设置
							dat_month=dat_month-1;
							if(dat_month<1)
							{
								dat_month=12;	
							}
				    		month = ((dat_month&0x70)>>4)*10+(dat_month&0x0f);
							LcdWrite(0x80+0x40+2,month/10+0x30);
							LcdWrite(0x80+0x40+3,month%10+0x30);	
						break;
						case 2:	  //对日的设置
							dat_date=dat_date-1;
							if(dat_date<1)
							{
								dat_date=31;	
							}
				    		date = ((dat_date&0x70)>>4)*10+(dat_date&0x0f);
							LcdWrite(0x80+0x40+4,date/10+0x30);
							LcdWrite(0x80+0x40+5,date%10+0x30);	
						break;

						case 3:	  //对时的设置
							dat_hour=dat_hour-1;
							if(dat_hour<0)
							{
								dat_hour=23;	
							}
				    		hour = ((dat_hour&0x70)>>4)*10+(dat_hour&0x0f);
							LcdWrite(0x80+0x40+7,hour/10+0x30);
							LcdWrite(0x80+0x40+8,hour%10+0x30);	
						break;
						case 4:	  //对时的设置
							dat_minute=dat_minute-1;
							if(dat_minute<0)
							{
								dat_minute=59;	
							}
				    		minute = ((dat_minute&0x70)>>4)*10+(dat_minute&0x0f);
							LcdWrite(0x80+0x40+10,minute/10+0x30);
							LcdWrite(0x80+0x40+11,minute%10+0x30);	
						break;
						case 5:	  //对秒的设置
							dat_second=dat_second-1;
							if(dat_second<0)
							{
								dat_second=59;	
							}
				    		second = ((dat_second&0x70)>>4)*10+(dat_second&0x0f);
							LcdWrite(0x80+0x40+13,second/10+0x30);
							LcdWrite(0x80+0x40+14,second%10+0x30);	
						break;
					}

			}
		 }

		 if(BUTTON_R==0)
		 {
		 	delay_ms(100);
		    if(BUTTON_R==0)
			{
			    switch(position)
				{
					 case 0:	//对年的设置
					   	dat_y=dat_y+1;
						if(dat_y>99)
						{
							dat_y=0;	
						}
				    	year = ((dat_y&0x70)>>4)*10+(dat_y&0x0f);
						LcdWrite(0x80+0x40+0,year/10+0x30);
						LcdWrite(0x80+0x40+1,year%10+0x30);	
					 break;
					 case 1:	  //对月的设置
							dat_month=dat_month+1;
							if(dat_month>12)
							{
								dat_month=1;	
							}
				    		month = ((dat_month&0x70)>>4)*10+(dat_month&0x0f);
							LcdWrite(0x80+0x40+2,month/10+0x30);
							LcdWrite(0x80+0x40+3,month%10+0x30);	
						break;
						case 2:	  //对日的设置
							dat_date=dat_date+1;
							if(dat_date>31)
							{
								dat_date=1;	
							}
				    		date = ((dat_date&0x70)>>4)*10+(dat_date&0x0f);
							LcdWrite(0x80+0x40+4,date/10+0x30);
							LcdWrite(0x80+0x40+5,date%10+0x30);	
						break;
						case 3:	  //对时的设置
							dat_hour=dat_hour+1;
							if(dat_hour>23)
							{
								dat_hour=0;	
							}
				    		date = ((dat_hour&0x70)>>4)*10+(dat_hour&0x0f);
							LcdWrite(0x80+0x40+7,date/10+0x30);
							LcdWrite(0x80+0x40+8,date%10+0x30);	
						break;

						case 4:	  //对分的设置
							dat_minute=dat_minute+1;
							if(dat_minute>59)
							{
								dat_minute=0;	
							}
				    		minute = ((dat_minute&0x70)>>4)*10+(dat_minute&0x0f);
							LcdWrite(0x80+0x40+10,minute/10+0x30);
							LcdWrite(0x80+0x40+11,minute%10+0x30);	
						break;
						case 5:	  //对秒的设置
							dat_second=dat_second+1;
							if(dat_second>59)
							{
								dat_second=0;	
							}
				    		second = ((dat_second&0x70)>>4)*10+(dat_second&0x0f);
							LcdWrite(0x80+0x40+13,second/10+0x30);
							LcdWrite(0x80+0x40+14,second%10+0x30);	
						break;
				}

			}
		 }
	}

	ui_set_speed();
}

void ui_setting(void)
{
    int position=0;
	Lcd_show_string(1,1,"Setting Menu",12);
	Lcd_show_string(2,0,"L:Opt R:Sure",12);
	delay_ms(1000);
	while(1)
	{
		if(BUTTON_R==0)
		{
			LCDClear();
			return;
		}
		
		if(BUTTON_L==0)
		{
			LCDClear();
			handle_setting();
			return;
		}  
	}	
}

void ui_set_speed(void)
{
    LCDClear();
	Lcd_show_string(1,2,"Set Speed",9);
	while(1)
	{
		   	LcdWrite(0x80+0x40+5,speed_ban/10+0x30);
			LcdWrite(0x80+0x40+6,speed_ban%10+0x30);

			 if(BUTTON_M==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_M==0)
				 {
				 	speed_ban--;
					if(speed_ban<0)
					{
						speed_ban=99;
					}	
				 }
			 }

			 if(BUTTON_R==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_R==0)
				 {
				 	speed_ban++;
					if(speed_ban>99)
					{
						speed_ban=0;
					}	
				 }
			 }

			 if(BUTTON_L==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_L==0)
				 {
						LCDClear();
						break;	
				 }
			 }
	}

	ui_set_heart();

}

void ui_set_heart(void)
{
    LCDClear();
	BUTTON_L=1;
	Lcd_show_string(1,0,"Set Heart Rate",14);
	while(1)
	{
		   	LcdWrite(0x80+0x40+5,heart_ban/100+0x30);
			LcdWrite(0x80+0x40+6,(heart_ban/10)%10+0x30);
			LcdWrite(0x80+0x40+7,heart_ban%10+0x30);

			 if(BUTTON_M==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_M==0)
				 {
				 	heart_ban--;
					if(heart_ban<0)
					{
						heart_ban=180;
					}	
				 }
			 }

			 if(BUTTON_R==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_R==0)
				 {
				 	heart_ban++;
					if(heart_ban>180)
					{
						heart_ban=0;
					}	
				 }
			 }

			 if(BUTTON_L==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_L==0)
				 {
						LCDClear();
						break;	
				 }
			 }
	}

	ui_setting_rh();

}

void ui_setting_rh(void)
{
	int position=0;
    LCDClear();
	BUTTON_L=1;
	Lcd_show_string(1,3,"Set RH%TH",9);
	while(1)
	{
			Lcd_show_string(2,3,"RH:",3);
			LcdWrite(0x80+0x40+6,rh_ban/10+0x30);
			LcdWrite(0x80+0x40+7,rh_ban%10+0x30);

			Lcd_show_string(2,8,"TH:",3);
			LcdWrite(0x80+0x40+11,th_ban/10+0x30);
			LcdWrite(0x80+0x40+12,th_ban%10+0x30);

			 if(BUTTON_M==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_M==0)
				 {
				   if(position==0)
				   {
				 		rh_ban--;
						if(rh_ban<0)
						{
							rh_ban=99;
						}				   	
				   }

				   if(position==1)
				   {
				   		th_ban--;
						if(th_ban<0)
						{
							th_ban=99;
						}		
				   }
	
				 }
			 }

			 if(BUTTON_R==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_R==0)
				 {
				 	if(position==0)
					{
				 		rh_ban++;
						if(rh_ban>99)
						{
							rh_ban=0;
						}						
					}

					if(position==1)
					{
				 		th_ban++;
						if(th_ban>99)
						{
							th_ban=0;
						}							
					}
	
				 }
			 }

			 if(BUTTON_L==0)
			 {
			 	 delay_ms(100);
				 if(BUTTON_L==0)
				 {
						position++;
						if(position>1)
						{
							LCDClear();
							break;
						}
	
				 }
			 }
	}	
}




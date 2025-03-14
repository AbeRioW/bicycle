#include "ui.h"

void show_time(void)
{
   	    unsigned char dat;
	    unsigned char second, minute, hour;
		unsigned char year, month, date,week;

		dat = DS3231_Read(0x06);
		year = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+0,year/10+0x30);
		LcdWrite(0x80+1,year%10+0x30);

		dat = DS3231_Read(0x05);
		month =	((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+2,month/10+0x30);
		LcdWrite(0x80+3,month%10+0x30);

		 dat = DS3231_Read(0x04);
		 date =	 ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+4,date/10+0x30);
		LcdWrite(0x80+5,date%10+0x30);

		//Ê±¼ä

		dat = DS3231_Read(0x02);
		hour = 	((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+7,hour/10+0x30);
		LcdWrite(0x80+8,hour%10+0x30);
		LcdWrite(0x80+9,':');


		dat = DS3231_Read(0x01);
	    minute = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+10,minute/10+0x30);
		LcdWrite(0x80+11,minute%10+0x30);
		LcdWrite(0x80+12,':');

		dat = DS3231_Read(0x00);
		second = ((dat&0x70)>>4)*10+(dat&0x0f);
		LcdWrite(0x80+13,second/10+0x30);
		LcdWrite(0x80+14,second%10+0x30);
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

void ui_setting(void)
{
    int position=0;
//	Lcd_show_string(1,1,"Setting Menu",12);
//	Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
	while(1)
	{
		  if(BUTTON_M==0)
		  {
		  	 position++;
			 if(position==5)
			 {
			    position=0;
			 }
		  }

		  if(BUTTON_L==0)
		  {
		  	 position--;
			 if(position<0)
			 {
			    position=4;
			 }
		  }

		  if(BUTTON_R==0)
		  {
		  	switch(position)
			{
				case 0:
				    LCDClear();
					return;
				break;
				case 1:
					LCDClear();
				break;
				case 2:
					LCDClear();
				break;
				case 3:
					LCDClear();
				break;
				case 4:
					LCDClear();
				break;
			}	
		  }
		  else
		  {
		  	switch(position)
			{
				case 0:
				    LCDClear();
						Lcd_show_string(1,1,"Setting Menu",12);
						Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
					break;
				break;
				case 1:
					LCDClear();
						Lcd_show_string(1,1,"Setting Date",12);
						Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
				break;
				case 2:
					LCDClear();
					Lcd_show_string(1,1,"Setting %RH",11);
						Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
				break;
				case 3:

					LCDClear();
											Lcd_show_string(1,1,"Setting BPM",11);
						Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
				break;
				case 4:
					LCDClear();
							Lcd_show_string(1,1,"Setting KPH",11);
						Lcd_show_string(2,0,"L/M:Opt R:Sure",14);
				break;
			}	
		  }


	}	
}
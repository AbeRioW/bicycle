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

		//ʱ��

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

#include "lcd.h"

void LcdWaitReady()
{
    uchar sta;
    LCD1602_DB = 0xFF;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_E = 1;
        sta = LCD1602_DB; 
        LCD1602_E = 0;
    } while (sta & 0x80);
}

void LcdWriteCmd(uchar cmd)
{
    LcdWaitReady();
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    LCD1602_E = 1;
    LCD1602_E = 0;
}

void LcdWriteDat(uchar dat)
{
    LcdWaitReady();
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    LCD1602_E = 1;
    LCD1602_E = 0;
}

void InitLcd1602()
{
    LcdWriteCmd(0x38);   
	LcdWriteCmd(0x0C);  
	LcdWriteCmd(0x06); 
    LcdWriteCmd(0x01); 
}

void LCDClear(void)
{
	LcdWriteCmd(0x01); 
}


void LcdWrite(uchar addr, uchar dat)
{
    LcdWriteCmd(addr);
    LcdWriteDat(dat);
}

void Lcd_show_string(int row,int col,uchar *data_s,int size)
{
    int i;
	uchar addr = 0x80;
	if(row==2)
		addr+=0x40;

	for(i=0;i<size;i++)
	{
	   LcdWrite(addr+i+col,data_s[i]);
	}
}

void LCD_TEST(void)
{
	LcdWrite(0x80+3, '3');	 //0x80:first row addr,3:offset,
	LcdWrite(0x80+0x40+3, '4');	 //0x80+0x40:second row addr,3:offset,
	delay_ms(1000);
	LCDClear();
	LcdWrite(0x80+3, '5');	 //0x80:first row addr,3:offset,
	LcdWrite(0x80+0x40+3, '6');	 //0x80+0x40:second row addr,3:offset,
		delay_ms(1000);
		LCDClear();

}
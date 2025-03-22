#include "uart.h"

//定时器相关
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
unsigned int count;                         //1000 times counter
int time_come=0;


sbit TEST_LED = P1^0;               //work LED, flash once per second


//void UART_SER (void) interrupt 4     //串行中断服务程序
//{
//    unsigned char r_buf;
//    if(RI)                        //判断是接收中断产生
//    {
//        RI=0;                      //标志位清零
//        r_buf = SBUF;
//		if(r_buf=='C'||r_buf=='D')    
//		{
//		   	count=0;
//			memset(rec_data,0,11);
//			rec_data[0]=r_buf;
//		}
//		else
//		{
//			count+=1;
//			rec_data[count]=r_buf;				
//		}
//		if(rec_data[3]=='O')
//		{
//		   is_connected=1; 
//		}
//		if(rec_data[3]=='L')
//		{
//		  is_connected=0;  
//		}
//
//		if(r_buf=='\n')
//		{
//		   if(memcmp(rec_data,connect_data,8)==0)
//		   {
//		       is_connected=1;
//		   }
//
//		   if(memcmp(rec_data,close_data,8)==0)
//		   {
//		      is_connected=0;
//		   }
//		}
//    }
////    if(TI)  //如果是发送标志位，清零
////        TI=0;
//}

void UART_Init(void)	   //11.0592MHz,波特率为9600
{
    SCON  = 0x50;                // SCON: 模式 1, 8-bit UART, 使能接收
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
    TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz
    TL1 = TH1;
    TR1   = 1;                  // TR1:  timer 1 打开
    EA    = 1;                  //打开总中断
    ES    = 0;                  //先关闭串口中断
	TI    =1;
}


void uartSendByte(unsigned char dat)
{
    unsigned char time_out;
    time_out=0x00;
    SBUF = dat;              //将数据放入SBUF中
    while((!TI)&&(time_out<255))  //检测是否发送出去
    {
        time_out++;    //未发送出去 进行短暂延时
    }
    TI = 0;                        //清除ti标志
}



/*------------------------------------------------
                    发送一个字符串
------------------------------------------------*/
void UartSendString(unsigned char *s)
{
    while(*s!='\0')// \0 表示字符串结束标志，
        //通过检测是否字符串末尾
    {
        uartSendByte(*s);//发送一个字节
        s++;//指向下一个数据
    }
}





//定时器相关
void timer0_init(void)
{
	TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
    count = 0;                      //initial counter
}


/* Timer0 interrupt routine */
void tm0_isr() interrupt 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte
    if (count-- == 0)               //1ms * 1000 -> 1s
    {
        count = 1000;               //reset counter
        //TEST_LED = ! TEST_LED;      //work LED flash
		 time_come = 1;
		 
    }

}
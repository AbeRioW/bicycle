#include "uart.h"

//��ʱ�����
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
unsigned int count;                         //1000 times counter
int time_come=0;


sbit TEST_LED = P1^0;               //work LED, flash once per second


//void UART_SER (void) interrupt 4     //�����жϷ������
//{
//    unsigned char r_buf;
//    if(RI)                        //�ж��ǽ����жϲ���
//    {
//        RI=0;                      //��־λ����
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
////    if(TI)  //����Ƿ��ͱ�־λ������
////        TI=0;
//}

void UART_Init(void)	   //11.0592MHz,������Ϊ9600
{
    SCON  = 0x50;                // SCON: ģʽ 1, 8-bit UART, ʹ�ܽ���
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit ��װ
    TH1   = 0xFD;               // TH1:  ��װֵ 9600 ������ ���� 11.0592MHz
    TL1 = TH1;
    TR1   = 1;                  // TR1:  timer 1 ��
    EA    = 1;                  //�����ж�
    ES    = 0;                  //�ȹرմ����ж�
	TI    =1;
}


void uartSendByte(unsigned char dat)
{
    unsigned char time_out;
    time_out=0x00;
    SBUF = dat;              //�����ݷ���SBUF��
    while((!TI)&&(time_out<255))  //����Ƿ��ͳ�ȥ
    {
        time_out++;    //δ���ͳ�ȥ ���ж�����ʱ
    }
    TI = 0;                        //���ti��־
}



/*------------------------------------------------
                    ����һ���ַ���
------------------------------------------------*/
void UartSendString(unsigned char *s)
{
    while(*s!='\0')// \0 ��ʾ�ַ���������־��
        //ͨ������Ƿ��ַ���ĩβ
    {
        uartSendByte(*s);//����һ���ֽ�
        s++;//ָ����һ������
    }
}





//��ʱ�����
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
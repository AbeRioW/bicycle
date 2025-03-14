#include "adc0832.h"
#include <intrins.h>



void delay1(void)
{
    _nop_();
    _nop_();
}

void ADC_init(void)
{
     ADC_DI=1;//��ʼ��ͨ��ѡ��
    delay1();
    ADC_CS=0;//����/cs��
    delay1();
}

void ADC_setchn(unsigned char chn)
{
    if(chn==0)
        chn=2;
    if(chn==1)
        chn=3;
    
    ADC_CLK=1;//����clk��
    delay1();
     ADC_CLK=0;//����clk���γ��½���

    ADC_DI=(chn & 0x02)>>1;//ͨ��ѡ���λ
    delay1();
    ADC_CLK=1;//��
    delay1();
    ADC_CLK=0;//�½���2

    ADC_DI=(chn & 0x01);//ͨ��ѡ���λ
    delay1();
    ADC_CLK=1;//��
    delay1();
    ADC_CLK=0;//�½���3   

    ADC_DI=1;    //�����������
    delay1();
}

unsigned char ADC_getdate(void)
{
    unsigned char j=0,i=8,getdate[2]={0,0},temp=0;
    
    ADC_CLK=1;
    delay1();
    ADC_CLK=0;//�½���4
    delay1();

    for(i=0;i<7;i++)     //�������
    {
        getdate[0] |= ADC_DO;//������
        getdate[0] <<= 1;
        ADC_CLK=1;
        delay1();
        ADC_CLK=0;//�½���
        delay1();
    }

    getdate[0] |= ADC_DO;

    temp=ADC_DO;
    getdate[1] |= (temp<<7);
   
    ADC_CLK=1;
    delay1();
    ADC_CLK=0;
    delay1();
   
    for(i=0;i<7;i++)     //�������
    {
       
        getdate[1] >>= 1;
        temp=ADC_DO;
        getdate[1] |= (temp<<7);
       
        ADC_CLK=1;
        delay1();
        ADC_CLK=0;
        delay1();
    }

    ADC_CS=1;//����CS

    ADC_CLK=0;
    ADC_DO=1;//�������ݶΣ��ص���ʼ״̬
   
    if(getdate[0]==getdate[1])     //�ж����������ν��յ��Ƿ���ͬ
		return getdate[1];   
    else
        return 0;
}

//��ȡADC������
unsigned char ADC0832(unsigned char chn)
{
	unsigned char ADval=0;
   
	ADC_init();
	ADC_setchn(chn);
	ADval=ADC_getdate();
  
    return ADval;
}
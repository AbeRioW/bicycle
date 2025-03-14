#include "adc0832.h"
#include <intrins.h>



void delay1(void)
{
    _nop_();
    _nop_();
}

void ADC_init(void)
{
     ADC_DI=1;//初始化通道选择
    delay1();
    ADC_CS=0;//拉低/cs端
    delay1();
}

void ADC_setchn(unsigned char chn)
{
    if(chn==0)
        chn=2;
    if(chn==1)
        chn=3;
    
    ADC_CLK=1;//拉高clk端
    delay1();
     ADC_CLK=0;//拉低clk，形成下降沿

    ADC_DI=(chn & 0x02)>>1;//通道选择高位
    delay1();
    ADC_CLK=1;//高
    delay1();
    ADC_CLK=0;//下降沿2

    ADC_DI=(chn & 0x01);//通道选择低位
    delay1();
    ADC_CLK=1;//高
    delay1();
    ADC_CLK=0;//下降沿3   

    ADC_DI=1;    //控制命令结束
    delay1();
}

unsigned char ADC_getdate(void)
{
    unsigned char j=0,i=8,getdate[2]={0,0},temp=0;
    
    ADC_CLK=1;
    delay1();
    ADC_CLK=0;//下降沿4
    delay1();

    for(i=0;i<7;i++)     //正序接收
    {
        getdate[0] |= ADC_DO;//收数据
        getdate[0] <<= 1;
        ADC_CLK=1;
        delay1();
        ADC_CLK=0;//下降沿
        delay1();
    }

    getdate[0] |= ADC_DO;

    temp=ADC_DO;
    getdate[1] |= (temp<<7);
   
    ADC_CLK=1;
    delay1();
    ADC_CLK=0;
    delay1();
   
    for(i=0;i<7;i++)     //反序接收
    {
       
        getdate[1] >>= 1;
        temp=ADC_DO;
        getdate[1] |= (temp<<7);
       
        ADC_CLK=1;
        delay1();
        ADC_CLK=0;
        delay1();
    }

    ADC_CS=1;//拉高CS

    ADC_CLK=0;
    ADC_DO=1;//拉高数据段，回到初始状态
   
    if(getdate[0]==getdate[1])     //判断正反序两次接收的是否相同
		return getdate[1];   
    else
        return 0;
}

//获取ADC的数据
unsigned char ADC0832(unsigned char chn)
{
	unsigned char ADval=0;
   
	ADC_init();
	ADC_setchn(chn);
	ADval=ADC_getdate();
  
    return ADval;
}
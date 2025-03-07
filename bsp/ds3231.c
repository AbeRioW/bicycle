#include "ds3231.h"

static void I2C_Delay() {
    unsigned int i;
    for (i = 0; i < 10; i++);
}

static void I2C_Start() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    SDA = 0;
    I2C_Delay();
    SCL = 0;
}

static void I2C_Stop() {
    SDA = 0;
    SCL = 1;
    I2C_Delay();
    SDA = 1;
    I2C_Delay();
}

static void I2C_Ack() {
    SDA = 0;
    SCL = 1;
    I2C_Delay();
    SCL = 0;
    SDA = 1;
}

static void I2C_NoAck() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    SCL = 0;
}

static bit I2C_WaitAck() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    if (SDA) {
        SCL = 0;
        return 0;
    }
    SCL = 0;
    return 1;
}

static void I2C_SendByte(uchar dat) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        dat <<= 1;
        SCL = 1;
        I2C_Delay();
        SCL = 0;
    }
    I2C_WaitAck();
}

static unsigned char I2C_ReadByte() {
    unsigned char i, dat = 0;
    SDA = 1;
    for (i = 0; i < 8; i++) {
        SCL = 1;
        I2C_Delay();
        dat <<= 1;
        if (SDA) dat |= 0x01;
        SCL = 0;
        I2C_Delay();
    }
    return dat;
}

void DS3231_Write(unsigned char addr, unsigned char dat) {
    I2C_Start();
    I2C_SendByte(0xD0);  // DS3231 ��д��ַ
    I2C_SendByte(addr);  // �Ĵ�����ַ
    I2C_SendByte(dat);   // ����
    I2C_Stop();
}

unsigned char DS3231_Read(unsigned char addr) {
    unsigned char dat;
    I2C_Start();
    I2C_SendByte(0xD0);  // DS3231 ��д��ַ
    I2C_SendByte(addr);  // �Ĵ�����ַ
    I2C_Start();
    I2C_SendByte(0xD1);  // DS3231 �Ķ���ַ
    dat = I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    return dat;
}

//void main() {
//    unsigned char second, minute, hour;
//    DS3231_Write(0x00, 0x00);  // ������
//    DS3231_Write(0x01, 0x30);  // ���÷���
//    DS3231_Write(0x02, 0x12);  // ����Сʱ
//
//    while (1) {
//        second = DS3231_Read(0x00);
//        minute = DS3231_Read(0x01);
//        hour = DS3231_Read(0x02);
//        // �����ﴦ���ȡ��ʱ������
//    }
//}
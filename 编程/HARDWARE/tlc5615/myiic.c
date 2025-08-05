#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  



void tlc_5615(unsigned int buf)
{
	unsigned int a,c;
	c=buf;    
    CS_5615_L; delay_us(10);
	for(a=16;a>0;a--)  
	{
         
        if((c>>15)&0x01)
			DAT_5615_H;
        else
        	DAT_5615_L;				
        c=c<<1;
        CLK_5615_H;
		delay_us(10);
        CLK_5615_L;
        delay_us(10);				
  }
	CLK_5615_H;delay_us(10);
	CLK_5615_L;delay_us(10);
	CLK_5615_H;delay_us(10);
	CLK_5615_L;delay_us(10);
	CS_5615_H;delay_us(10);
}
//��ʼ��IIC
void TLC5615_IO_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
  //��ʹ������IO PORTAʱ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 















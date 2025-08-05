#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
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
//初始化IIC
void TLC5615_IO_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
  //先使能外设IO PORTA时钟 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 















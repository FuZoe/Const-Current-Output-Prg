#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

   	   		   
 

//IO²Ù×÷º¯Êý	 
#define CLK_5615_L                         GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define CLK_5615_H                         GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define DAT_5615_L                         GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define DAT_5615_H                         GPIO_SetBits(GPIOA,GPIO_Pin_5)



#define CS_5615_L                         GPIO_ResetBits(GPIOA,GPIO_Pin_3) 
#define CS_5615_H                         GPIO_SetBits(GPIOA,GPIO_Pin_3)


void TLC5615_IO_Init(void);
void tlc_5615(unsigned int buf); 

 
#endif

















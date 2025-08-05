#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 

#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//读取按键3
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//读取按键4


#define KEY4_ADD_PRES	4		//KEY4  
#define KEY3_MIN_PRES	3		//KEY3 
#define KEY2_10_PRES	2		//KEY2  
#define KEY1_ONOFF_PRES	1		//KEY1

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif

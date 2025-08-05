#include "key.h"
#include "delay.h"

//按键初始化函数 
//PA15和PC5 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//使能PORTB时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //PB3 PB4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return KEY1_ONOFF_PRES;
		else if(KEY2==0)return KEY2_10_PRES;
		else if(KEY3==0)return KEY3_MIN_PRES; 
		else if(KEY4==0)return KEY4_ADD_PRES; 
	}else if(KEY1==1&&KEY2==1&&KEY3==1&KEY4==1)key_up=1; 	     
	return 0;// 无按键按下
}

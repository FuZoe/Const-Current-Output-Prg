#include "stm32f10x.h"
#include "sys.h"
 #include "core.h"
#include "1602.h"
#include "timer.h"
#include "myiic.h"
#include "key.h"
#include "adc.h"
 

int  main(void)  
{  
	delay_init();	  //延时函数初始化	
	SystemInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	
	KEY_Init();
	LCD_init();
	
	TIM3_Int_Init(10,7200);//10Khz的计数频率，10为1ms

	TLC5615_IO_Init();
	Adc_Init();
//	tlc_5615(DA_Date);//TLC5615输出电压设置为零

	while (1)  
	{
		key_check();
		CC_Calc();
		
		if(DIS_FLAG==Ture)
			{
				DIS_FLAG=False;
				display();
			} 
	}	
}









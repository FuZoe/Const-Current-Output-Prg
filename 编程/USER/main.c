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
	delay_init();	  //��ʱ������ʼ��	
	SystemInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	
	KEY_Init();
	LCD_init();
	
	TIM3_Int_Init(10,7200);//10Khz�ļ���Ƶ�ʣ�10Ϊ1ms

	TLC5615_IO_Init();
	Adc_Init();
//	tlc_5615(DA_Date);//TLC5615�����ѹ����Ϊ��

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









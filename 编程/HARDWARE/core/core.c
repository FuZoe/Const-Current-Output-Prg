#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "core.h"
#include "1602.h"
#include "timer.h"
#include "key.h"
#include "adc.h"
#include "myiic.h"

Bool StartFlag=False;
u8 key=0;
u16 Set_data=1000;//单位0.01mA
u16 Real_data=0;


void key_check(void)
{
	key=KEY_Scan(0);
	switch(key)
	{
		case KEY1_ONOFF_PRES:
			if(StartFlag == False)
				StartFlag=Ture;
			else
				StartFlag=False;
			break;
		case KEY2_10_PRES:
			Set_data=1000;
			break;
		case KEY3_MIN_PRES:
			if(Set_data>0)
				Set_data-=100;
			break;
		case KEY4_ADD_PRES:
			if(Set_data<2000)
				Set_data+=100;
			break;
		default:;
	}
}

/*
函数名称: display
功能描述: 显示电流值和开关状态到LCD屏上
主要逻辑:
1. 显示电流值的整数部分和小数部分。
2. 根据开关状态显示 "on" 或 "off"。
参数: 无
返回值: 无
注：该函数在主函数中循环执行
*/
void display(void)
{
	//显示电流值大小
	u16 dis_value;
	dis_value=Set_data/100;
	LCD_write_cmd(0x80+0x40+12);
	LCD_write_data(LCD1602_Table[(dis_value/10)]);
	LCD_write_data(LCD1602_Table[(dis_value%10)]);
	
	dis_value=Real_data/10;
	LCD_write_cmd(0x80+0x40+2);
	LCD_write_data(LCD1602_Table[(dis_value/100)]);
	LCD_write_data(LCD1602_Table[(dis_value%100/10)]);
	LCD_write_cmd(0x80+0x40+5);
	LCD_write_data(LCD1602_Table[(dis_value%10)]);
	
	//刷新开关
	if(StartFlag==1)
	{
		LCD_write_string(11,1,"on ");		
	}
	else
	LCD_write_string(11,1,"off");		

}

#define VREF 3247		//单位MV
float Temp;
float ampGain=48; //电流放大倍数
float Rs=2; //电流采样电阻 单位欧姆
unsigned int  DA_Date=0;  //传入TLC5615的值
unsigned int  DA_init_Date=0;  //DAC初值
u16 value;


/*设定电流值与实际电流表值进行对比，对PWM进行增加或减少*/
void  CC_Calc(void)
{
	float mid;
	if(StartFlag == Ture)
	{
		value=Get_Adc_Average(ADC_CH0,SCN);
		Temp = value * VREF*100 /4095/ ampGain / Rs;//单位：0.01MA
		if(Temp < 0) Temp =0;
		Real_data =(u16)Temp;//单位：0.01mA
		
		DA_init_Date = 20*Set_data/100;
		if((Real_data<Set_data)&&((Set_data-Real_data)>1))
		{
			if(DA_Date<DAC_MAX_CMP)
				DA_Date++;	
			
		}

		else if((Real_data>Set_data)&&((Real_data-Set_data)>1))
		{
			if(DA_Date>0)
				DA_Date--;				
		}	
	}
	else
	{		
		DA_init_Date = 0;
		DA_Date = 0;
		Real_data = 0;
	}

	tlc_5615(DA_init_Date+DA_Date);
}

///*设定电流值与实际电流表值进行对比，对PWM进行增加或减少*/
//void  CC_Calc(void)
//{
//	ad_val=Get_Adc_Average(ADC_CH2,SCN);
//	Temp = ad_val * 3.295 /4095/ ampGain / Rs;//单位：A
//	Cur_Data = Temp*1000;//单位：mA
//	if((Cur_Data<Set_Data)&&((Set_Data-Cur_Data)>1))
//	{
//		if(((Set_Data-Cur_Data)>200)&&((PWM_MAX_CMP-PWM_Data)>210))
//		{
//			PWM_Data+=200;
//		}
//		else if(((Set_Data-Cur_Data)>100)&&((PWM_MAX_CMP-PWM_Data)>110))
//		{
//			PWM_Data+=100;			
//		}
//		else if((Set_Data-Cur_Data>50)&&((PWM_MAX_CMP-PWM_Data)>51))
//		{
//			PWM_Data+=50;	
//		}
//		else if(((Set_Data-Cur_Data)>10)&&((PWM_MAX_CMP-PWM_Data)>11))
//		{
//			PWM_Data+=10;			
//		}
//		else if(PWM_Data<PWM_MAX_CMP)
//			PWM_Data++;	
//	}
//	else if((Cur_Data>Set_Data)&&((Cur_Data-Set_Data)>1))
//	{
//		if(((Cur_Data-Set_Data)>200)&&((PWM_Data-1)>210))
//		{
//			PWM_Data-=200;
//		}
//		else if(((Cur_Data-Set_Data)>100)&&((PWM_Data-1)>110))
//		{
//			PWM_Data-=100;			
//		}
//		else if(((Cur_Data-Set_Data)>50)&&((PWM_Data-1)>51))
//		{
//			PWM_Data-=50;			
//		}
//		else if(((Cur_Data-Set_Data)>10)&&((PWM_Data-1)>11))
//		{
//			PWM_Data-=10;			
//		}
//		else if(PWM_Data>1)
//			PWM_Data--;				
//	}
//}
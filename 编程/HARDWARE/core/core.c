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
u16 Set_data=1000;//��λ0.01mA
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
��������: display
��������: ��ʾ����ֵ�Ϳ���״̬��LCD����
��Ҫ�߼�:
1. ��ʾ����ֵ���������ֺ�С�����֡�
2. ���ݿ���״̬��ʾ "on" �� "off"��
����: ��
����ֵ: ��
ע���ú�������������ѭ��ִ��
*/
void display(void)
{
	//��ʾ����ֵ��С
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
	
	//ˢ�¿���
	if(StartFlag==1)
	{
		LCD_write_string(11,1,"on ");		
	}
	else
	LCD_write_string(11,1,"off");		

}

#define VREF 3247		//��λMV
float Temp;
float ampGain=48; //�����Ŵ���
float Rs=2; //������������ ��λŷķ
unsigned int  DA_Date=0;  //����TLC5615��ֵ
unsigned int  DA_init_Date=0;  //DAC��ֵ
u16 value;


/*�趨����ֵ��ʵ�ʵ�����ֵ���жԱȣ���PWM�������ӻ����*/
void  CC_Calc(void)
{
	float mid;
	if(StartFlag == Ture)
	{
		value=Get_Adc_Average(ADC_CH0,SCN);
		Temp = value * VREF*100 /4095/ ampGain / Rs;//��λ��0.01MA
		if(Temp < 0) Temp =0;
		Real_data =(u16)Temp;//��λ��0.01mA
		
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

///*�趨����ֵ��ʵ�ʵ�����ֵ���жԱȣ���PWM�������ӻ����*/
//void  CC_Calc(void)
//{
//	ad_val=Get_Adc_Average(ADC_CH2,SCN);
//	Temp = ad_val * 3.295 /4095/ ampGain / Rs;//��λ��A
//	Cur_Data = Temp*1000;//��λ��mA
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
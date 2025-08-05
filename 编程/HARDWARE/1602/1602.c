#include "1602.h"
#include "delay.h"


#define DELAY_2N     1
//LCD1602��ʾ����
u8 LCD1602_Table[]="0123456789";
u8 DIS_TAB1[]={"    Start:off   "};
u8 DIS_TAB2[]={"R:--.-mA  S:--mA"};	


//==================================================
void LCD_init(void)
{
	u8 i=0;

	/*********************Һ��ʹ�õ�I/O�ڳ�ʼ��**************************/ 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	CLR_RW();			//��дλֱ�ӵ͵�ƽ��ֻд����

	/*********************Һ����ʼ��**************************/        
	delay (15000);  
	CLR_RS();
	LCD_Write_half_byte(0x3);                 
	delay (15000);
	LCD_Write_half_byte(0x3);
	delay (15000);
	LCD_Write_half_byte(0x3);
	LCD_Write_half_byte(0x2);


	LCD_write_cmd(0x28);          // 4bit��ʾģʽ,2��,5x7����
	delay (20000);  
	LCD_write_cmd(0x08);         // ��ʾ�ر� 
	delay (20000); 
	LCD_write_cmd(0x01);         // ��ʾ���� 
	delay (20000); 
	LCD_write_cmd(0x06);         // ��ʾ����ƶ����� 
	delay (20000);
	LCD_write_cmd(0x0C);         //��ʾ��,���أ�
	//LCD_write_cmd(0x0F);         // ��ʾ������꿪�������˸
	delay (20000);
	LCD_write_cmd(0x01);         //����
	LCD_write_cmd(0x80);
	for(i=0;i<16;i++)
	LCD_write_data(DIS_TAB1[i]);
	LCD_write_cmd(0x80+0x40);
	for(i=0;i<16;i++)
	LCD_write_data(DIS_TAB2[i]);
}
/*--------------------------------------------------
����˵����д���Һ��


---------------------------------------------------*/
void LCD_write_cmd(unsigned char cmd)
{
    CLR_RS();
    LCD_Write_half_byte(cmd >> 4);
    LCD_Write_half_byte(cmd);
    delay (10000);
}
/*--------------------------------------------------
����˵����д���ݵ�Һ��


---------------------------------------------------*/
void LCD_write_data(unsigned char w_data)
{
    SET_RS();
    LCD_Write_half_byte(w_data >> 4);
    LCD_Write_half_byte(w_data);
    delay (10000);
}

  /*--------------------------------------------------
����˵����д4bit��Һ��
--------------------------------------------------*/
 void LCD_Write_half_byte(unsigned char half_byte)
{  
	if (half_byte&0x01)
			LCD_D4_OUT=1;
	else
			LCD_D4_OUT=0;

	if (half_byte&0x02)
			LCD_D5_OUT=1;
	else
			LCD_D5_OUT=0;

	if (half_byte&0x04)
			LCD_D6_OUT=1;
	else
			LCD_D6_OUT=0;

	if (half_byte&0x08)
			LCD_D7_OUT=1;
	else
			LCD_D7_OUT=0;

    SET_EN();
    delay(3000);
    CLR_EN(); 
    delay(3000);
}	  
/*----------------------------------------------------
LCD_set_xy        : ����LCD��ʾ����ʼλ��
���������x��y    : ��ʾ�ַ�����λ�ã�X:1-16��Y:1-2                
-----------------------------------------------------*/
void LCD_set_xy( unsigned char x, unsigned char y )
{
    unsigned char address;
    if (y==1) 
    {
        address=0x80-1+x;
    }
    else 
    {
        address=0xc0-1+x;
    }
    LCD_write_cmd(address);
}
/*---------------------------------------------------
LCD_write_string  : Ӣ���ַ�����ʾ����
���������*s      ��Ӣ���ַ���ָ�룻
          X��Y    : ��ʾ�ַ�����λ��                
---------------------------------------------------*/
void LCD_write_string(unsigned char X,unsigned char Y,unsigned char *s)
{
    LCD_set_xy( X, Y );   
    while (*s) 
    {
        LCD_write_data(*s);
        s++;
    }
}

//========================================================
void delay(vu32 cnt)
{
  cnt <<= DELAY_2N;

  while (cnt--);
}
//========================================================




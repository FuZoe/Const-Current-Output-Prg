#include "1602.h"
#include "delay.h"


#define DELAY_2N     1
//LCD1602显示部分
u8 LCD1602_Table[]="0123456789";
u8 DIS_TAB1[]={"    Start:off   "};
u8 DIS_TAB2[]={"R:--.-mA  S:--mA"};	


//==================================================
void LCD_init(void)
{
	u8 i=0;

	/*********************液晶使用的I/O口初始化**************************/ 
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
	
	CLR_RW();			//读写位直接低电平，只写不读

	/*********************液晶初始化**************************/        
	delay (15000);  
	CLR_RS();
	LCD_Write_half_byte(0x3);                 
	delay (15000);
	LCD_Write_half_byte(0x3);
	delay (15000);
	LCD_Write_half_byte(0x3);
	LCD_Write_half_byte(0x2);


	LCD_write_cmd(0x28);          // 4bit显示模式,2行,5x7字体
	delay (20000);  
	LCD_write_cmd(0x08);         // 显示关闭 
	delay (20000); 
	LCD_write_cmd(0x01);         // 显示清屏 
	delay (20000); 
	LCD_write_cmd(0x06);         // 显示光标移动设置 
	delay (20000);
	LCD_write_cmd(0x0C);         //显示开,光标关，
	//LCD_write_cmd(0x0F);         // 显示开，光标开，光标闪烁
	delay (20000);
	LCD_write_cmd(0x01);         //清屏
	LCD_write_cmd(0x80);
	for(i=0;i<16;i++)
	LCD_write_data(DIS_TAB1[i]);
	LCD_write_cmd(0x80+0x40);
	for(i=0;i<16;i++)
	LCD_write_data(DIS_TAB2[i]);
}
/*--------------------------------------------------
函数说明：写命令到液晶


---------------------------------------------------*/
void LCD_write_cmd(unsigned char cmd)
{
    CLR_RS();
    LCD_Write_half_byte(cmd >> 4);
    LCD_Write_half_byte(cmd);
    delay (10000);
}
/*--------------------------------------------------
函数说明：写数据到液晶


---------------------------------------------------*/
void LCD_write_data(unsigned char w_data)
{
    SET_RS();
    LCD_Write_half_byte(w_data >> 4);
    LCD_Write_half_byte(w_data);
    delay (10000);
}

  /*--------------------------------------------------
函数说明：写4bit到液晶
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
LCD_set_xy        : 设置LCD显示的起始位置
输入参数：x、y    : 显示字符串的位置，X:1-16，Y:1-2                
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
LCD_write_string  : 英文字符串显示函数
输入参数：*s      ：英文字符串指针；
          X、Y    : 显示字符串的位置                
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




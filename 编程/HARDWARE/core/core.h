#ifndef __CORE_H
#define __CORE_H	 
#include "sys.h"

#define DAC_MAX_CMP 500
#define k 0.912
#define b 1.33

void  CC_Calc(void);
void key_check(void);
void display(void);


typedef enum{
Ture=1,
False=0
}Bool;

extern Bool StartFlag;

unsigned char Encoder(void); 
void Encoder_Init(void);
void display(void);
#endif




#ifndef __1602_H_
#define __1602_H_

#include    "reg51.h"

typedef unsigned char uchar;
typedef unsigned int  uint;	
typedef unsigned long  ulong;
typedef unsigned char u8;
typedef unsigned int  u16;	

void	Initialize_LCD(void);
void	Write_AC(u8 hang,u8 lie);
void	Write_DIS_Data(u8 DIS_Data);
void	ClearLine(u8 row);
u8		BIN_ASCII(u8 tmp);
void 	PutString(u8 row, u8 column, u8 *puts);
void	WriteChar(u8 row, u8 column, u8 dat);

#endif
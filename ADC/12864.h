#ifndef __12864_H_
#define __12864_H_

#include <STC15.h>
	


void	delay_1ms(u16 ms);
void	DisableHC595(void);
void	WriteDataLCD(u8 WDLCD);
void	WriteCommandLCD(u8 WCLCD,BuysC);
u8		ReadDataLCD(void);
u8		ReadStatusLCD(void);
void	LCDInit(void);
void	LCDClear(void);
void	LCDFlash(void);
void	DisplayOneChar(u8 X, u8 Y, u8 DData);
void	DisplayListChar(u8 X, u8 Y, u8 code *DData);
void	DisplayImage (u8 code *DData);

void DisplayListNum(u8 X, u8 Y, uchar i);

#endif
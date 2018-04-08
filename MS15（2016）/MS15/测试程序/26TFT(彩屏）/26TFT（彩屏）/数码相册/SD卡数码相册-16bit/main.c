#include "STC_NEW_8051.H"
//#include <REG52.H>
#include <intrins.h>
#include <absacc.h>
#include "define.h"
#include "sd.h"
#include "fat.h"
#include "LCD.c"

void PORT_init()
{
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
}
void main(void)
{
	//uchar i;
	uchar item=0;
	T_CS = 1; //关闭触摸IC 由于共用了SPI总线， 以免影响SD卡读取数据 数据冲突
 	PORT_init();
	LCD_Init();   //tft初始化	
	Pant(RED>>8 , RED );
	Pant(GREEN>>8 ,GREEN);
	Pant(BLUE>>8 ,GREEN);
	Pant(WHITE>>8 ,GREEN);
	Pant(BLACK>>8 ,GREEN);
	Pant(YELLOW>>8 ,GREEN); 
	SD_Reset();
	SD_Init();	  //让SD卡就绪
  
  	pArg=&Init_Arg_SD; //pArg是znFAT的“初始参数结构指针”，它所指向的结构体中记录了存储器及其文件系统的重要参数信息
                       //在切换存储设备时，不光要更改设备号，还要将pArg指向相应存储设备的“初始参数结构”
	Dev_No=SDCARD; 	   //设备号为SDCARD，znFAT中将其宏定义为 0
	FAT32_Init(); 	   //文件系统初始化，使用znFAT前必须进行初始化，初始化过程中将所使用的存储设备的文件系统的一些重要参数
               		   //记录到了pArg所指向的结构中，以备后面使用
	while(1)
	{
		while(!FAT32_Open_File(&FileInfo,"\\*.bmp",item++)) //依次播放SD卡根目录下的所有BMP文件
		{
			display_pic();
			//while(touch_INT);
		    //while(touch_INT);
		} 
		item=0;
	}
}

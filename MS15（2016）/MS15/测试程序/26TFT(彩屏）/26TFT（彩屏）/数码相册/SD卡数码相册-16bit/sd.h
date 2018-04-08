#ifndef __SD_H__
#define __SD_H__

#include "STC_NEW_8051.H"
//#include <REG52.H>

sbit SD_CS =P3^0;	//SD卡片选 	  输入
sbit SD_SI =P3^1;  //SD卡同步数据  输入
sbit SD_SCL=P3^2;  //SD卡同步时钟  输入
sbit SD_SO =P3^3;  //SD卡同步数据  输出

sbit T_CS =P3^6; //触摸IC和SD卡都是SPI协议通信  他们3条共用通信线   通过片选CS来切换 当前的工作设备


#define DELAY_TIME 2000 //SD卡的复位与初始化时SPI的延时参数，根据实际速率修改其值，否则会造成SD卡复位或初始化失败
#define TRY_TIME 200   //向SD卡写入命令之后，读取SD卡的回应次数，即读TRY_TIME次，如果在TRY_TIME次中读不到回应，产生超时错误，命令写入失败

//错误码定义
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0错误
#define INIT_CMD1_ERROR     0x02 //CMD1错误
#define WRITE_BLOCK_ERROR   0x03 //写块错误
#define READ_BLOCK_ERROR    0x04 //读块错误
//-------------------------------------------------------------

unsigned char SD_Reset();
unsigned char SD_Init();
unsigned char SD_Write_Sector(unsigned long addr,uchar *Buffer);
unsigned char SD_Read_Sector(unsigned long addr,uchar *buffer);

#endif
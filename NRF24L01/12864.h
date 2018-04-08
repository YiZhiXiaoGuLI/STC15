/**********************
名称：12864  4*8显示代码
作者：段博侃
日期：2013年8月25日
控制原理：
	直接按照原理图显示
	
	接线：
		sbit rs = P2^4;
		sbit rw = P2^5;
		sbit en = P2^6;
		sbit psb = P2^1;
		sbit rst = P2^3;
	引出函数有：
	初始化12864：init12864();
	清屏：clear()
	显示一个字符: display_onchar(uint x,uint y,uchar dat)
	显示一个字符串: display_string(uint x,uint y,uchar *s)
***********************/

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int

sbit rs = P2^4;
sbit rw = P2^5;
sbit en = P2^6;
sbit psb = P2^1;
sbit rst = P2^3;
#define dataport P0




//12864检测忙位
void check_busy()
{
	rs = 0;
	rw = 1;
	en = 1;
	dataport = 0xff;
	while((dataport&0x80) == 0x80);
	en = 0;

}
//16864写指令
void write_cmd(uchar cmd)
{
	check_busy();
	rs = 0;
	rw = 0;
	en = 1;
	dataport = cmd;
	delay_us(5);
	en = 0;
	delay_us(5);
}
//12864写数据
void write_dat(uchar dat)
{
	check_busy();
	rs = 1;
	rw = 0;
	en = 1;
	dataport = dat;
	delay_us(5);
	en = 0;
	delay_us(5);
}
//12864初始化函数
void init12864()
{
	delay_ms(40);
	psb = 1;			//设置工作方式为8位并口工作模式
	delay_ms(1);
	rst = 0;			//复位，低电平有效
	delay_ms(1);
	rst = 1;			//复位口置高
	delay_ms(10);
	write_cmd(0x30);
	delay_us(50);
	write_cmd(0x30);
	delay_us(20);
	write_cmd(0x0c);	//不显示光标
	delay_us(50);
	write_cmd(0x06);	//光标移动为后移一位
	delay_us(50);	
	write_cmd(0x01);	//清屏并设置初始地址为00H
	delay_ms(15);
}
//显示单个字符
void display_onchar(uint x,uint y,uchar dat)
{
	switch(y)
	{
		case 1:write_cmd(0x80+x);break;
		case 2:write_cmd(0x90+x);break;
		case 3:write_cmd(0x88+x);break;
		case 4:write_cmd(0x98+x);break;
		default: break;		
	}
	write_dat(dat);
}
//显示字符串
void display_string(uint x,uint y,uchar *s)
{
	switch(y)
	{
		case 1:write_cmd(0x80+x);break;
		case 2:write_cmd(0x90+x);break;
		case 3:write_cmd(0x88+x);break;
		case 4:write_cmd(0x98+x);break;
		default: break;		
	}
	 while(*s>0)
   { 
      write_dat(*s);
      s++;
      delay_us(50);
   }
}
//清屏函数
void clear()
{
	write_cmd(0x01);
	delay_ms(15);
}


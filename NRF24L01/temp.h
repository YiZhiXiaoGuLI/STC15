/**********************
名称：温度传感器显示代码
作者：段博侃
日期：2013年8月25日
控制原理：
	直接按照原理图显示
	
	接线：
		sbit DQ = P1^3;
	引出函数有：
	change();
	所得温度放在数组S中
			s[0]=(temp/100)+0x30; 
	    s[1]=(temp/10)%10+0x30;
	    s[2]='.';
	    s[3]=temp%10+0x30;
	使用时：
		change();
		display_onchar(3,3,s[0]);
		display_onchar(4,3,s[1]);
		display_onchar(5,3,s[2]);
		display_onchar(6,3,s[3]);
		display_onchar(7,3,'C');
***********************/
#include "reg52.h"
#include "delay.h"
#define uint unsigned int 
#define uchar unsigned char

sbit DQ = P1^3;
uint temp=0;
float f_temp = 0;
uchar s[4] = {0,0,0,0}; 
/******************************************************************/
/*                    18B20初始化                                 */
/******************************************************************/
void Init_DS18B20(void)
{
unsigned char x=0;
	DQ = 1;    //DQ复位
	delay_us(8);  //稍做延时
	DQ = 0;    //单片机将DQ拉低
	delay_us(80); //精确延时 大于 480us
	DQ = 1;    //拉高总线
	delay_us(10);
	x=DQ;      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	delay_us(5);
}

/******************************************************************/
/*                    读一个字节                                  */
/******************************************************************/
unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
{
	DQ = 0; // 给脉冲信号
	dat>>=1;
	DQ = 1; // 给脉冲信号
	if(DQ)
	dat|=0x80;
	delay_us(5);
}
 return dat;
}

/******************************************************************/
/*                 写一个字节                                     */
/******************************************************************/
void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
{
	DQ = 0;
	DQ = dat&0x01;//采样
	delay_us(5);
	DQ = 1;
	dat>>=1;
 }
	delay_us(5);
}

/******************************************************************/
/*                   读取温度                                     */
/******************************************************************/
unsigned int ReadTemperature(void)
{
	unsigned char a=0;
	unsigned int b=0;
	unsigned int t=0;
	
	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	delay_us(200);
	
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作 
	WriteOneChar(0xBE); //读取温度寄存器等（共可读9个寄存器） 前两个就是温度
	a=ReadOneChar();   //低位
	b=ReadOneChar();   //高位
	
	b<<=8;
	t=a+b;

	return(t);
}

/***************温度转化**********/
void change()
{
	uchar i = 0;	
	temp=ReadTemperature();
	if(temp&0x8000)
	{
		temp=~temp;  // 取反加1
		temp +=1;
	}
	f_temp=temp*0.0625;
 	temp=f_temp*10;
    s[0]=(temp/100)+0x30; 
    s[1]=(temp/10)%10+0x30;
    s[2]='.';
    s[3]=temp%10+0x30;

}



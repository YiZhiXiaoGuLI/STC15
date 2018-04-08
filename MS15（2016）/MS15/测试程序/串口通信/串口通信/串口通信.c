/**********************************************************************************************************/

/******************************* 串口通讯例程（参考宏晶官方例程）******************************************/
/*******************************        hiold.taobao.com       ********************************************/

/**********************************************************************************************************/


#include "reg51.h"
#include "intrins.h"

typedef unsigned char uchar;
typedef unsigned int uint;

#define FOSC 11059200L      //晶振频率
#define BAUD 115200           //波特率

sfr AUXR  = 0x8e;               //辅助寄存器

bit    busy,flag=0;
uchar  Redata;
uint   i=0,j=0;


void SendData(uchar dat);
void SendString(uchar *S);

void main()
{
	
    AUXR = 0x40;                //定时器1为1T模式
    SCON = 0x50;
    TMOD = 0x20;            //定时器1为8位自动装载模式
    TH1 = TL1 =(256 - (FOSC/32/BAUD));  //自动装载值
    TR1 = 1;                //打开定时器1
    ES = 1;                 //开串口中断
    EA = 1;                 //开总中断	 	
	SendString("这是从单片机发来的数据，现在你可以给单片机发送数据"); //向PC发送一条字符串
					
	while(1)
		{
			if(flag)
				{
					SBUF=Redata;
					flag=0;				
				}	
		}       
}

/*********************************************************************************************************
*************************************串口中断程序*********************************************************
*********************************************************************************************************/
void Uart_Isr() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
        Redata =SBUF;          //P0 show UART data
		flag=1;
     }

    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}

/*********************************************************************************************************
*************************************发送一个字节*********************************************************
*********************************************************************************************************/
void SendData(uchar dat)
{
    while (busy);           //等待前一字节发送完成
    busy = 1;
    SBUF = dat;             //送数据到串口缓冲区
}


/*********************************************************************************************************
*************************************字符串发送程序*******************************************************
*********************************************************************************************************/
void SendString(uchar *s)
{
    while (*s)              //检查是否字符串结尾
    {
        SendData(*s++);     //发送当前数据，获取下一数据
    }
}

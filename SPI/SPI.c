/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 互为主从的SPI查询方式举例---------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 如果要在文章中应用此代码,请在文章中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz


#include "reg51.h"

#define FOSC        11059200L
#define BAUD        (256 - FOSC / 32 / 115200)

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;

#define     URMD    0           //0:使用定时器2作为波特率发生器
                                //1:使用定时器1的模式0(16位自动重载模式)作为波特率发生器
                                //2:使用定时器1的模式2(8位自动重载模式)作为波特率发生器

sfr T2H   = 0xd6;               //定时器2高8位
sfr T2L   = 0xd7;               //定时器2低8位

sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xb1;
sfr P3M0 = 0xb2;
sfr P4M1 = 0xb3;
sfr P4M0 = 0xb4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sfr  AUXR       =   0x8e;       //辅助寄存器                              
sfr SPSTAT      =   0xcd;       //SPI状态寄存器                           
#define SPIF        0x80        //SPSTAT.7                                
#define WCOL        0x40        //SPSTAT.6                                
sfr SPCTL       =   0xce;       //SPI控制寄存器                           
#define SSIG        0x80        //SPCTL.7                                 
#define SPEN        0x40        //SPCTL.6                                 
#define DORD        0x20        //SPCTL.5                                 
#define MSTR        0x10        //SPCTL.4                                 
#define CPOL        0x08        //SPCTL.3                                 
#define CPHA        0x04        //SPCTL.2                                 
#define SPDHH       0x00        //CPU_CLK/4                               
#define SPDH        0x01        //CPU_CLK/16                              
#define SPDL        0x02        //CPU_CLK/64                              
#define SPDLL       0x03        //CPU_CLK/128                             
sfr SPDAT       =   0xcf;       //SPI数据寄存器                           
sbit SPISS      =   P1^1;       //SPI从机选择口, 连接到其它MCU的SS口
                                //当SPI为一主多从模式时,请使用主机的普通IO口连接到从机的SS口

void InitUart();
void InitSPI();
void SendUart(BYTE dat);        //发送数据到PC
BYTE RecvUart();                //从PC接收数据
BYTE SPISwap(BYTE dat);         //主机与从机之间交换数据

///////////////////////////////////////////////////////////

void main()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;

    InitUart();                 //初始化串口   
    InitSPI();                  //初始化SPI    

    while (1)
    {
        if (RI)
        {
            SPCTL = SPEN | MSTR; //设置为主机模式
            SendUart(SPISwap(RecvUart()));
            SPCTL = SPEN;       //重置为从机模式
        }
        if (SPSTAT & SPIF)
        {
            SPSTAT = SPIF | WCOL; //清除SPI状态位
            SPDAT = SPDAT;      //数据从接收缓冲区移到发送缓冲区
        }
    }
}

///////////////////////////////////////////////////////////

void InitUart()
{
    SCON = 0x5a;                //设置串口为8位可变波特率
#if URMD == 0
    T2L = 0xd8;                 //设置波特率重装值
    T2H = 0xff;                 //115200 bps(65536-18432000/4/115200)
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
#elif URMD == 1
    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = 0xd8;                 //设置波特率重装值
    TH1 = 0xff;                 //115200 bps(65536-18432000/4/115200)
    TR1 = 1;                    //定时器1开始启动
#else
    TMOD = 0x20;                //设置定时器1为8位自动重装载模式
    AUXR = 0x40;                //定时器1为1T模式
    TH1 = TL1 = 0xfb;           //115200 bps(256 - 18432000/32/115200)
    TR1 = 1;
#endif
}

///////////////////////////////////////////////////////////

void InitSPI()
{
    SPDAT = 0;                  //初始化SPI数据
    SPSTAT = SPIF | WCOL;       //清除SPI状态位
    SPCTL = SPEN;               //从机模式
}

///////////////////////////////////////////////////////////

void SendUart(BYTE dat)
{
    while (!TI);                //等待发送完成
    TI = 0;                     //清除发送标志
    SBUF = dat;                 //发送串口数据
}

///////////////////////////////////////////////////////////

BYTE RecvUart()
{
    while (!RI);                //等待串口数据接收完成
    RI = 0;                     //清除接收标志
    return SBUF;                //返回串口数据
}

///////////////////////////////////////////////////////////

BYTE SPISwap(BYTE dat)
{
    SPISS = 0;                  //拉低从机的SS
    SPDAT = dat;                //触发SPI发送数据
    while (!(SPSTAT & SPIF));   //等待发送完成
    SPSTAT = SPIF | WCOL;       //清除SPI状态位
    SPISS = 1;                  //拉高从机的SS
    return SPDAT;               //返回SPI数据
}


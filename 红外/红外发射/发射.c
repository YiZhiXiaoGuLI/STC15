
/*************  本程序功能说明  **************

用户可以在宏定义中改变MCU主时钟频率. 范围 8MHZ ~ 33MHZ.

红外接收程序。模拟市场上用量最大的NEC的编码。

用户可以在宏定义中指定用户码.

使用PCA2高速输出产生38KHZ载波, 1/3占空比, 每个38KHZ周期发射管发射9us,关闭16.3us.

使用开发板上的16个IO扫描按键, MCU不睡眠, 连续扫描按键.

当键按下, 第一帧为数据, 后面的帧为重复争,不带数据, 具体定义请自行参考NEC的编码资料.

键释放后, 停止发送.

******************************************/

#include    "intrins.h"
#include    "onewire.h"
#define     MAIN_Fosc       11059200L   //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

//sfr TH2  = 0xD6;
//sfr TL2  = 0xD7;
sfr IE2   = 0xAF;
sfr INT_CLKO = 0x8F;
sfr AUXR = 0x8E;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;

sfr ADC_CONTR = 0xBC;   //带AD系列
sfr ADC_RES   = 0xBD;   //带AD系列
sfr ADC_RESL  = 0xBE;   //带AD系列
sfr P1ASF = 0x9D;   //只写，模拟输入(AD或LVD)选择

sfr CCON = 0xD8;    //
sbit CCF0  = CCON^0;    //PCA 模块0中断标志，由硬件置位，必须由软件清0。
sbit CCF1  = CCON^1;    //PCA 模块1中断标志，由硬件置位，必须由软件清0。
sbit CCF2  = CCON^2;    //PCA 模块2中断标志，由硬件置位，必须由软件清0。
sbit CR    = CCON^6;    //1: 允许PCA计数器计数，必须由软件清0。
sbit CF    = CCON^7;    //PCA计数器溢出（CH，CL由FFFFH变为0000H）标志。PCA计数器溢出后由硬件置位，必须由软件清0。
sfr CMOD = 0xD9;    //
sfr CCAPM0 = 0xDA;  //PCA模块0的工作模式寄存器。
sfr CCAPM1 = 0xDB;  //PCA模块1的工作模式寄存器。
sfr CCAPM2 = 0xDC;  //PCA模块2的工作模式寄存器。
sfr CL     = 0xE9;  //
sfr CCAP0L = 0xEA;  //PCA模块0的捕捉/比较寄存器低8位。
sfr CCAP1L = 0xEB;  //PCA模块1的捕捉/比较寄存器低8位。
sfr CCAP2L = 0xEC;  //PCA模块2的捕捉/比较寄存器低8位。
sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;      //PCA模块0的捕捉/比较寄存器高8位。
sfr CCAP1H = 0xFB;      //PCA模块1的捕捉/比较寄存器高8位。
sfr CCAP2H = 0xFC;      //PCA模块2的捕捉/比较寄存器高8位。
sfr PCA_PWM0 = 0xF2;    //PCA模块0 PWM寄存器。
sfr PCA_PWM1 = 0xF3;    //PCA模块1 PWM寄存器。
sfr PCA_PWM2 = 0xF4;    //PCA模块2 PWM寄存器。

sbit PPCA   = IP^7;

sfr P4   = 0xC0;
sfr P5   = 0xC8;
sfr P6   = 0xE8;
sfr P7   = 0xF8;
sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;





/*************  IO口定义    **************/
sbit    P_HC595_SER   = P4^0;   //pin 14    SER     data input
sbit    P_HC595_RCLK  = P5^4;   //pin 12    RCLk    store (latch) clock
sbit    P_HC595_SRCLK = P4^3;   //pin 11    SRCLK   Shift data clock

/*************  IO键盘变量声明  **************/

u8  IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;   //行列键盘变量
u8  KeyHoldCnt; //键按下计时
u8  KeyCode;    //给用户使用的键码, 1~16有效


/*************  本地函数声明    **************/
void    delay_ms(u8 ms);
void    PCA_config(void);
void    IR_TxPulse(u16 pulse);
void    IR_TxSpace(u16 pulse);
void    IR_TxByte(u8 dat);

unsigned char read_wendu(void);



/********************** 主函数 ************************/
void main(void)
{
	  unsigned char temp;//温度
	
    P0M1 = 0;   P0M0 = 0;   //设置为准双向口
    P1M1 = 0;   P1M0 = 0;   //设置为准双向口
    P2M1 = 0;   P2M0 = 0;   //设置为准双向口
    P3M1 = 0;   P3M0 = 0;   //设置为准双向口
    P4M1 = 0;   P4M0 = 0;   //设置为准双向口
    P5M1 = 0;   P5M0 = 0;   //设置为准双向口
    P6M1 = 0;   P6M0 = 0;   //设置为准双向口
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
    

    
   // DisableHC595();     //禁止掉学习板上的HC595显示，省电

    while(1)
    {
        delay_ms(5);       //30ms
        //IO_KeyScan();
         //temp=read_wendu();
			   temp=25;
        if(temp != 0)        //检测到键码
        {
            TxTime = 0;
                                //一帧数据最小长度 = 9 + 4.5 + 0.5625 + 24 * 1.125 + 8 * 2.25 = 59.0625 ms
                                //一帧数据最大长度 = 9 + 4.5 + 0.5625 + 8 * 1.125 + 24 * 2.25 = 77.0625 ms
            IR_TxPulse(342);    //对应9ms，同步头       9ms
            IR_TxSpace(171);    //对应4.5ms，同步头间隔 4.5ms
            IR_TxPulse(21);     //开始发送数据          0.5625ms

            IR_TxByte(User_code%256);   //发用户码高字节
            IR_TxByte(User_code/256);   //发用户码低字节
            IR_TxByte(temp);         //发数据
            IR_TxByte(~temp);        //发数据反码
            
            if(TxTime < 56)     //一帧按最大77ms发送, 不够的话,补偿时间     108ms
            {
                TxTime = 56 - TxTime;
                TxTime = TxTime + TxTime / 8;
                delay_ms(TxTime);
            }
            delay_ms(31);

            while(IO_KeyState != 0) //键未释放
            {
                IR_TxPulse(342);    //对应9ms，   同步头        9ms
                IR_TxSpace(86);     //对应2.25ms，同步头间隔    2.25ms
                IR_TxPulse(21);     //开始发送数据              0.5625ms
                delay_ms(96);
//IO_KeyScan();
            }
            KeyCode = 0;
        }
    }
} 


/**********************************************/

//========================================================================
// 函数: void  delay_ms(unsigned char ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //13T per loop
     }while(--ms);
}




/************* 发送脉冲函数 **************/
void    IR_TxPulse(u16 pulse)
{
    tx_cnt = pulse;
    B_Space = 0;    //发脉冲
    CCAPM2 = 0x48 | 0x04 | 0x01;    //工作模式 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CR = 1;     //启动
    while(CR);
}

/************* 发送空闲函数 **************/
void    IR_TxSpace(u16 pulse)
{
    tx_cnt = pulse;
    B_Space = 1;    //空闲
    CCAPM2 = 0x48 | 0x01;   //工作模式 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CR = 1;     //启动
    while(CR);
}


/************* 发送一个字节函数 **************/
void    IR_TxByte(u8 dat)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 1)     IR_TxSpace(63), TxTime += 2;    //数据1对应 1.6875 + 0.5625 ms 
        else            IR_TxSpace(21), TxTime++;       //数据0对应 0.5625 + 0.5625 ms
        IR_TxPulse(21);         //脉冲都是0.5625ms
        dat >>= 1;              //下一个位
    }
}

//========================================================================
// 函数: void   PCA_config(void)
// 描述: PCA配置函数.
// 参数: None
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
void    PCA_config(void)
{
    AUXR1   = (AUXR1 & ~0x30) | 0x10;   //切换IO口, 0x00: P1.2 P1.1 P1.0 P3.7,  0x10: P3.4 P3.5 P3.6 P3.7, 0x20: P2.4 P2.5 P2.6 P2.7

    CCON = 0x00;    //清除所有中断标志
    CCAPM2  = 0x48+ 1;  //工作模式 + 允许中断 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CCAPM2 |= 0x04; //允许高速取反输出, 一般用在16位软件定时器
    PCA_Timer2 = 100;   //随便给一个小的初值
    CCAP2L = (u8)PCA_Timer2;            //将影射寄存器写入捕获寄存器，先写CCAPxL
    CCAP2H = (u8)(PCA_Timer2 >> 8); //后写CCAPxH

    PPCA = 1;   //高优先级中断
    CMOD  = (CMOD  & ~0xe0) | 0x08; //选择时钟源, 0x00: 12T, 0x02: 2T, 0x04: Timer0溢出, 0x06: ECI, 0x08: 1T, 0x0A: 4T, 0x0C: 6T, 0x0E: 8T
    CH = 0;
    CL = 0;
    CR = 0;
    tx_cnt = 2;
}

//========================================================================
// 函数: void   PCA_Handler (void) interrupt PCA_VECTOR
// 描述: PCA中断处理程序.
// 参数: None
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================

#define D_38K_DUTY  ((MAIN_Fosc * 26) / 1000000UL + MAIN_Fosc / 3000000UL)  /*  38KHZ周期时间   26.3us */
#define D_38K_OFF   ((MAIN_Fosc * 17) / 1000000UL + MAIN_Fosc / 3000000UL)  /* 发射管关闭时间   17.3us */
#define D_38K_ON    ((MAIN_Fosc * 9) / 1000000UL)                           /* 发射管导通时间   9us */

void    PCA_Handler (void) interrupt 7
{
    CCON = 0x40;    //清除所有中断标志,但不关CR
    if(!B_Space)    //发送载波
    {                               //发送脉冲，交替装载TH0值，溢出时自动重装
        if(P_IR_TX)
        {
            PCA_Timer2 += D_38K_OFF;    //装载高电平时间    17.3us
            if(--tx_cnt == 0)   CR = 0; //pulse has sent,   stop
        }
        else    PCA_Timer2 += D_38K_ON; //装载低电平时间    9us
    }
    else    //发送暂停时间
    {
        PCA_Timer2 += D_38K_DUTY;   //装载周期时间  26.3us
        if(--tx_cnt == 0)   CR = 0; //空闲时间
    }
    CCAP2L = (u8)PCA_Timer2;            //将影射寄存器写入捕获寄存器，先写CCAP0L
    CCAP2H = (u8)(PCA_Timer2 >> 8); //后写CCAP0H
}

//DS18B20??????:??  
unsigned char read_wendu(void)  
{  
    unsigned char low,high;  
  char temp;  
  Init_DS18B20();  
  Write_DS18B20(0xCC);//??ROM??  
  Write_DS18B20(0x44); //??????  
  Delay_OneWire(200);  
  Init_DS18B20();  
  Write_DS18B20(0xCC);  
  Write_DS18B20(0xBE); //?????  
  low = Read_DS18B20(); //???  
  high = Read_DS18B20(); //???  
  temp = high<<4;  
  temp |= (low>>4);  
  return temp;  
}  
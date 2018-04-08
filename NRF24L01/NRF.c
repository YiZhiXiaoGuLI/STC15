#include "reg52.h"
#include "intrins.h"
#include "12864.h"
#include "temp.h"


#define uchar unsigned char
#define uint unsigned int

uchar Rxstr1[4];
//****************************************NRF24L01端口定义***************************************
sbit 	MISO	=P3^7;
sbit 	MOSI	=P3^6;
sbit	SCK	  	=P3^5;
sbit	CSN		=P3^4;
sbit	CE	  	=P2^2; 
sbit	IRQ		=P3^3;

//******************************************************************************************
uint 	bdata sta;   				//NRF24L01状态标志
sbit	RX_DR	=sta^6;				
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
//*************************************NRF24L01**************************************************

#define TX_ADR_WIDTH    5   	// 本机地址宽度设置
#define RX_ADR_WIDTH    5   	// 接收方地址宽度设置

#define TX_PLOAD_WIDTH  5 		// 4 字节数据长度
#define RX_PLOAD_WIDTH  5		// 4 字节数据长度

uchar const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//本地地址
uchar const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//接收地址

//*****************************NRF24L01寄存器指令，详细请对照，Page18******************************

#define READ_REG        0x00  	// 读寄存器指令
#define WRITE_REG       0x20 	// 写寄存器指令
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留
//****************************SPI(nRF24L01)寄存器地址，详细请对照，Page18-24**********************

#define CONFIG          0x00   // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01   // 自动应答功能设置
#define EN_RXADDR       0x02   // 可用信道设置
#define SETUP_AW        0x03   // 收发地址宽度设置
#define SETUP_RETR      0x04   // 自动重发功能设置
#define RF_CH           0x05   // 工作频率设置
#define RF_SETUP        0x06   // 发射速率、功耗功能设置
#define STATUS          0x07   // 状态寄存器
#define OBSERVE_TX      0x08   // 发送监测功能
#define CD              0x09   // 地址检测           
#define RX_ADDR_P0      0x0A   // 频道0接收数据地址
#define RX_ADDR_P1      0x0B   // 频道1接收数据地址
#define RX_ADDR_P2      0x0C   // 频道2接收数据地址
#define RX_ADDR_P3      0x0D   // 频道3接收数据地址
#define RX_ADDR_P4      0x0E   // 频道4接收数据地址
#define RX_ADDR_P5      0x0F   // 频道5接收数据地址
#define TX_ADDR         0x10   // 发送地址寄存器
#define RX_PW_P0        0x11   // 接收频道0接收数据长度
#define RX_PW_P1        0x12   // 接收频道0接收数据长度
#define RX_PW_P2        0x13   // 接收频道0接收数据长度
#define RX_PW_P3        0x14   // 接收频道0接收数据长度
#define RX_PW_P4        0x15   // 接收频道0接收数据长度
#define RX_PW_P5        0x16   // 接收频道0接收数据长度
#define FIFO_STATUS     0x17   // FIFO栈入栈出状态寄存器设置
//************************************NRF24L01函数申明**********************************************

void inerDelay_us(unsigned char n);
void init_NRF24L01(void);
uint SPI_RW(uint uchars);
uchar SPI_Read(uchar reg);

void SetRX_Mode(void);
uint SPI_RW_Reg(uchar reg, uchar value);
uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars);
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);
/******************************************************************************************
/*延时函数
/******************************************************************************************/
void inerDelay_us(unsigned char n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi disable 
 	SCK=0;   // Spi clock line init high
	IRQ=1;
	//SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写本地地址
    //SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS1, TX_ADR_WIDTH);		
	//SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  频道0自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  允许接收地址只有频道0，如果需要多频道可以参考Page21 
	SPI_RW_Reg(WRITE_REG + SETUP_AW, 0x03); 
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00);
	SPI_RW_Reg(WRITE_REG + RF_CH, 1);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为4字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1Mkbps，发射功率为最大值0dB
	CE=1;
	inerDelay_us(200);
}
/****************************************************************************************************
/*函数：uint SPI_RW(uint uchar)
/*功能：NRF24L01的SPI写时序,详细看时序图，Page19
/****************************************************************************************************/
uint SPI_RW(uint uchars)
{
	uint bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (uchars & 0x80);         // output 'uchar', MSB to MOSI
		uchars = (uchars<< 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		uchars |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}
    return(uchars);           		  // return read uchar
}
/****************************************************************************************************
/*函数：uchar SPI_Read(uchar reg)
/*功能：NRF24L01的SPI时序,详细看时序图，Page19
/****************************************************************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication
	
	return(reg_val);        // return register value
}
/****************************************************************************************************/
/*功能：NRF24L01读写寄存器函数,
/****************************************************************************************************/
uint SPI_RW_Reg(uchar reg, uchar value)
{
	uint status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	
	return(status);            // return nRF24L01 status uchar
}
/****************************************************************************************************/
/*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
/****************************************************************************************************/
uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar
	
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status uchar
}
/*********************************************************************************************************
/*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
/*********************************************************************************************************/
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;            //SPI使能       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
	SPI_RW(*pBuf++);
	CSN = 1;           //关闭SPI
	return(status);    // 
}
/*函数：void SetRX_Mode(void)
/*功能：数据接收配置 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
	inerDelay_us(200);
}
/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char*rx_buf)
{
    unsigned char revale=0;
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	sta=SPI_Read(STATUS);	// 读取状态寄存其来判断数据接收状况
	if(sta&0x40)				// 判断是否接收到数据
	{		
	    CE=0; 			
	    SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;
		CE=1;
		CSN=0;
		SPI_RW(FLUSH_RX);
		CSN=1;
		//SPI_RW_Reg(WRITE_REG+STATUS,0XFF);			//读取数据完成标志
	}
	SPI_RW_Reg(WRITE_REG+STATUS,0XFF);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来其清除中断标志
	return revale;
}
/***********************************************************************************************************
/*函数：void nRF24L01_TxPacket(unsigned char * tx_buf)
/*功能：发送 tx_buf中数据
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy I模式	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // 装载接收端地址
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	CE=1;		 //置高CE，激发数据发送
	inerDelay_us(10);
}


void send( char *str)
{
	CSN=0;
	SPI_RW(FLUSH_RX);
	CSN=1;
  	nRF24L01_TxPacket(str);	// Transmit Tx buffer data
  	SPI_RW_Reg(WRITE_REG+STATUS,0XFF);	
}

void receive()
{
	SetRX_Mode();
	nRF24L01_RxPacket(Rxstr1);
}



void main()
{
	init12864();
	init_NRF24L01();
	while(1)
	{
		change();
		display_string(0,1,"本机温度：");
		display_onchar(0,2,s[0]);
		display_onchar(1,2,s[1]);
		display_onchar(2,2,s[2]);
		display_onchar(3,2,s[3]);
		display_onchar(4,2,'C');

		send(s);
		
		receive();
		
		display_string(0,3,"其他温度：");
		display_onchar(0,4,Rxstr1[0]);
		display_onchar(1,4,Rxstr1[1]);
		display_onchar(2,4,Rxstr1[2]);
		display_onchar(3,4,Rxstr1[3]);
		display_onchar(4,4,'C');
		
	
	}


}





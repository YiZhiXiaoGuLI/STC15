#include "reg52.h"
#include "intrins.h"
#include "12864.h"
#include "temp.h"


#define uchar unsigned char
#define uint unsigned int

uchar Rxstr1[4];
//****************************************NRF24L01�˿ڶ���***************************************
sbit 	MISO	=P3^7;
sbit 	MOSI	=P3^6;
sbit	SCK	  	=P3^5;
sbit	CSN		=P3^4;
sbit	CE	  	=P2^2; 
sbit	IRQ		=P3^3;

//******************************************************************************************
uint 	bdata sta;   				//NRF24L01״̬��־
sbit	RX_DR	=sta^6;				
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
//*************************************NRF24L01**************************************************

#define TX_ADR_WIDTH    5   	// ������ַ�������
#define RX_ADR_WIDTH    5   	// ���շ���ַ�������

#define TX_PLOAD_WIDTH  5 		// 4 �ֽ����ݳ���
#define RX_PLOAD_WIDTH  5		// 4 �ֽ����ݳ���

uchar const TX_ADDRESS[TX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���ص�ַ
uchar const RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//���յ�ַ

//*****************************NRF24L01�Ĵ���ָ���ϸ����գ�Page18******************************

#define READ_REG        0x00  	// ���Ĵ���ָ��
#define WRITE_REG       0x20 	// д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0  	// д��������ָ��
#define FLUSH_TX        0xE1 	// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NOP             0xFF  	// ����
//****************************SPI(nRF24L01)�Ĵ�����ַ����ϸ����գ�Page18-24**********************

#define CONFIG          0x00   // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01   // �Զ�Ӧ��������
#define EN_RXADDR       0x02   // �����ŵ�����
#define SETUP_AW        0x03   // �շ���ַ�������
#define SETUP_RETR      0x04   // �Զ��ط���������
#define RF_CH           0x05   // ����Ƶ������
#define RF_SETUP        0x06   // �������ʡ����Ĺ�������
#define STATUS          0x07   // ״̬�Ĵ���
#define OBSERVE_TX      0x08   // ���ͼ�⹦��
#define CD              0x09   // ��ַ���           
#define RX_ADDR_P0      0x0A   // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B   // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C   // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D   // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E   // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F   // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10   // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11   // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12   // ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13   // ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14   // ����Ƶ��0�������ݳ���
#define RX_PW_P4        0x15   // ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16   // ����Ƶ��0�������ݳ���
#define FIFO_STATUS     0x17   // FIFOջ��ջ��״̬�Ĵ�������
//************************************NRF24L01��������**********************************************

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
/*��ʱ����
/******************************************************************************************/
void inerDelay_us(unsigned char n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01��ʼ��
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi disable 
 	SCK=0;   // Spi clock line init high
	IRQ=1;
	//SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // д���ص�ַ
    //SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS1, TX_ADR_WIDTH);		
	//SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  Ƶ��0�Զ�	ACKӦ������	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  ������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21 
	SPI_RW_Reg(WRITE_REG + SETUP_AW, 0x03); 
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00);
	SPI_RW_Reg(WRITE_REG + RF_CH, 1);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//���÷�������Ϊ1Mkbps�����书��Ϊ���ֵ0dB
	CE=1;
	inerDelay_us(200);
}
/****************************************************************************************************
/*������uint SPI_RW(uint uchar)
/*���ܣ�NRF24L01��SPIдʱ��,��ϸ��ʱ��ͼ��Page19
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
/*������uchar SPI_Read(uchar reg)
/*���ܣ�NRF24L01��SPIʱ��,��ϸ��ʱ��ͼ��Page19
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
/*���ܣ�NRF24L01��д�Ĵ�������,
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
/*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
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
/*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
/*********************************************************************************************************/
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uint status,uchar_ctr;
	
	CSN = 0;            //SPIʹ��       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
	SPI_RW(*pBuf++);
	CSN = 1;           //�ر�SPI
	return(status);    // 
}
/*������void SetRX_Mode(void)
/*���ܣ����ݽ������� 
/****************************************************************************************************/
void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	CE = 1; 
	inerDelay_us(200);
}
/******************************************************************************************************/
/*������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char*rx_buf)
{
    unsigned char revale=0;
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	sta=SPI_Read(STATUS);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(sta&0x40)				// �ж��Ƿ���յ�����
	{		
	    CE=0; 			
	    SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;
		CE=1;
		CSN=0;
		SPI_RW(FLUSH_RX);
		CSN=1;
		//SPI_RW_Reg(WRITE_REG+STATUS,0XFF);			//��ȡ������ɱ�־
	}
	SPI_RW_Reg(WRITE_REG+STATUS,0XFF);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1��������жϱ�־
	return revale;
}
/***********************************************************************************************************
/*������void nRF24L01_TxPacket(unsigned char * tx_buf)
/*���ܣ����� tx_buf������
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy Iģʽ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // װ�ؽ��ն˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	CE=1;		 //�ø�CE���������ݷ���
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
		display_string(0,1,"�����¶ȣ�");
		display_onchar(0,2,s[0]);
		display_onchar(1,2,s[1]);
		display_onchar(2,2,s[2]);
		display_onchar(3,2,s[3]);
		display_onchar(4,2,'C');

		send(s);
		
		receive();
		
		display_string(0,3,"�����¶ȣ�");
		display_onchar(0,4,Rxstr1[0]);
		display_onchar(1,4,Rxstr1[1]);
		display_onchar(2,4,Rxstr1[2]);
		display_onchar(3,4,Rxstr1[3]);
		display_onchar(4,4,'C');
		
	
	}


}





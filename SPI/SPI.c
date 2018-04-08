/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 ϵ�� ��Ϊ���ӵ�SPI��ѯ��ʽ����---------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/* ���Ҫ��������Ӧ�ô˴���,����������ע��ʹ����STC�����ϼ�����        */
/*---------------------------------------------------------------------*/

//��ʾ����Keil������������ѡ��Intel��8058оƬ�ͺŽ��б���
//�����ر�˵��,����Ƶ��һ��Ϊ11.0592MHz


#include "reg51.h"

#define FOSC        11059200L
#define BAUD        (256 - FOSC / 32 / 115200)

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;

#define     URMD    0           //0:ʹ�ö�ʱ��2��Ϊ�����ʷ�����
                                //1:ʹ�ö�ʱ��1��ģʽ0(16λ�Զ�����ģʽ)��Ϊ�����ʷ�����
                                //2:ʹ�ö�ʱ��1��ģʽ2(8λ�Զ�����ģʽ)��Ϊ�����ʷ�����

sfr T2H   = 0xd6;               //��ʱ��2��8λ
sfr T2L   = 0xd7;               //��ʱ��2��8λ

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

sfr  AUXR       =   0x8e;       //�����Ĵ���                              
sfr SPSTAT      =   0xcd;       //SPI״̬�Ĵ���                           
#define SPIF        0x80        //SPSTAT.7                                
#define WCOL        0x40        //SPSTAT.6                                
sfr SPCTL       =   0xce;       //SPI���ƼĴ���                           
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
sfr SPDAT       =   0xcf;       //SPI���ݼĴ���                           
sbit SPISS      =   P1^1;       //SPI�ӻ�ѡ���, ���ӵ�����MCU��SS��
                                //��SPIΪһ�����ģʽʱ,��ʹ����������ͨIO�����ӵ��ӻ���SS��

void InitUart();
void InitSPI();
void SendUart(BYTE dat);        //�������ݵ�PC
BYTE RecvUart();                //��PC��������
BYTE SPISwap(BYTE dat);         //������ӻ�֮�佻������

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

    InitUart();                 //��ʼ������   
    InitSPI();                  //��ʼ��SPI    

    while (1)
    {
        if (RI)
        {
            SPCTL = SPEN | MSTR; //����Ϊ����ģʽ
            SendUart(SPISwap(RecvUart()));
            SPCTL = SPEN;       //����Ϊ�ӻ�ģʽ
        }
        if (SPSTAT & SPIF)
        {
            SPSTAT = SPIF | WCOL; //���SPI״̬λ
            SPDAT = SPDAT;      //���ݴӽ��ջ������Ƶ����ͻ�����
        }
    }
}

///////////////////////////////////////////////////////////

void InitUart()
{
    SCON = 0x5a;                //���ô���Ϊ8λ�ɱ䲨����
#if URMD == 0
    T2L = 0xd8;                 //���ò�������װֵ
    T2H = 0xff;                 //115200 bps(65536-18432000/4/115200)
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
#elif URMD == 1
    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
    TMOD = 0x00;                //��ʱ��1Ϊģʽ0(16λ�Զ�����)
    TL1 = 0xd8;                 //���ò�������װֵ
    TH1 = 0xff;                 //115200 bps(65536-18432000/4/115200)
    TR1 = 1;                    //��ʱ��1��ʼ����
#else
    TMOD = 0x20;                //���ö�ʱ��1Ϊ8λ�Զ���װ��ģʽ
    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
    TH1 = TL1 = 0xfb;           //115200 bps(256 - 18432000/32/115200)
    TR1 = 1;
#endif
}

///////////////////////////////////////////////////////////

void InitSPI()
{
    SPDAT = 0;                  //��ʼ��SPI����
    SPSTAT = SPIF | WCOL;       //���SPI״̬λ
    SPCTL = SPEN;               //�ӻ�ģʽ
}

///////////////////////////////////////////////////////////

void SendUart(BYTE dat)
{
    while (!TI);                //�ȴ��������
    TI = 0;                     //������ͱ�־
    SBUF = dat;                 //���ʹ�������
}

///////////////////////////////////////////////////////////

BYTE RecvUart()
{
    while (!RI);                //�ȴ��������ݽ������
    RI = 0;                     //������ձ�־
    return SBUF;                //���ش�������
}

///////////////////////////////////////////////////////////

BYTE SPISwap(BYTE dat)
{
    SPISS = 0;                  //���ʹӻ���SS
    SPDAT = dat;                //����SPI��������
    while (!(SPSTAT & SPIF));   //�ȴ��������
    SPSTAT = SPIF | WCOL;       //���SPI״̬λ
    SPISS = 1;                  //���ߴӻ���SS
    return SPDAT;               //����SPI����
}


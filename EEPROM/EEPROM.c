/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 ϵ�� �ڲ�EEPROM����--------------------------------*/
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
#include "intrins.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;

//-----------------------------------------------

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

sfr IAP_DATA    =   0xC2;           //IAP���ݼĴ���
sfr IAP_ADDRH   =   0xC3;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL   =   0xC4;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD     =   0xC5;           //IAP����Ĵ���
sfr IAP_TRIG    =   0xC6;           //IAP������Ĵ���
sfr IAP_CONTR   =   0xC7;           //IAP���ƼĴ���

#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//���Ե�ַ
#define IAP_ADDRESS 0x0400

void Delay(BYTE n);
void IapIdle();
BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);
void IapEraseSector(WORD addr);

void main()
{
    WORD i;

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

    P1 = 0xfe;                      //1111,1110 ϵͳOK
    Delay(10);                      //��ʱ
    IapEraseSector(IAP_ADDRESS);    //��������
    for (i=0; i<512; i++)           //����Ƿ�����ɹ�(ȫFF���)
    {
        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
            goto Error;             //�������,���˳�
    }
    P1 = 0xfc;                      //1111,1100 �����ɹ�
    Delay(10);                      //��ʱ
    for (i=0; i<512; i++)           //���512�ֽ�
    {
        IapProgramByte(IAP_ADDRESS+i, (BYTE)i);
    }
    P1 = 0xf8;                      //1111,1000 ������
    Delay(10);                      //��ʱ
    for (i=0; i<512; i++)           //У��512�ֽ�
    {
        if (IapReadByte(IAP_ADDRESS+i) != (BYTE)i)
            goto Error;             //���У�����,���˳�
    }
    P1 = 0xf0;                      //1111,0000 �������
    while (1);
Error:
    P1 &= 0x7f;                     //0xxx,xxxx IAP����ʧ��
    while (1);
}

/*----------------------------
�����ʱ
----------------------------*/
void Delay(BYTE n)
{
    WORD x;

    while (n--)
    {
        x = 0;
        while (++x);
    }
}

/*----------------------------
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //�������Ĵ���
    IAP_TRIG = 0;                   //��������Ĵ���
    IAP_ADDRH = 0x80;               //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}

/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //���ݻ�����

    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                      //�ر�IAP����

    return dat;                     //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

/*----------------------------
��������
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}


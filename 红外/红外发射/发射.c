
/*************  ��������˵��  **************

�û������ں궨���иı�MCU��ʱ��Ƶ��. ��Χ 8MHZ ~ 33MHZ.

������ճ���ģ���г�����������NEC�ı��롣

�û������ں궨����ָ���û���.

ʹ��PCA2�����������38KHZ�ز�, 1/3ռ�ձ�, ÿ��38KHZ���ڷ���ܷ���9us,�ر�16.3us.

ʹ�ÿ������ϵ�16��IOɨ�谴��, MCU��˯��, ����ɨ�谴��.

��������, ��һ֡Ϊ����, �����֡Ϊ�ظ���,��������, ���嶨�������вο�NEC�ı�������.

���ͷź�, ֹͣ����.

******************************************/

#include    "intrins.h"
#include    "onewire.h"
#define     MAIN_Fosc       11059200L   //������ʱ��

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

sfr ADC_CONTR = 0xBC;   //��ADϵ��
sfr ADC_RES   = 0xBD;   //��ADϵ��
sfr ADC_RESL  = 0xBE;   //��ADϵ��
sfr P1ASF = 0x9D;   //ֻд��ģ������(AD��LVD)ѡ��

sfr CCON = 0xD8;    //
sbit CCF0  = CCON^0;    //PCA ģ��0�жϱ�־����Ӳ����λ�������������0��
sbit CCF1  = CCON^1;    //PCA ģ��1�жϱ�־����Ӳ����λ�������������0��
sbit CCF2  = CCON^2;    //PCA ģ��2�жϱ�־����Ӳ����λ�������������0��
sbit CR    = CCON^6;    //1: ����PCA�����������������������0��
sbit CF    = CCON^7;    //PCA�����������CH��CL��FFFFH��Ϊ0000H����־��PCA�������������Ӳ����λ�������������0��
sfr CMOD = 0xD9;    //
sfr CCAPM0 = 0xDA;  //PCAģ��0�Ĺ���ģʽ�Ĵ�����
sfr CCAPM1 = 0xDB;  //PCAģ��1�Ĺ���ģʽ�Ĵ�����
sfr CCAPM2 = 0xDC;  //PCAģ��2�Ĺ���ģʽ�Ĵ�����
sfr CL     = 0xE9;  //
sfr CCAP0L = 0xEA;  //PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1L = 0xEB;  //PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP2L = 0xEC;  //PCAģ��2�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;      //PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1H = 0xFB;      //PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP2H = 0xFC;      //PCAģ��2�Ĳ�׽/�ȽϼĴ�����8λ��
sfr PCA_PWM0 = 0xF2;    //PCAģ��0 PWM�Ĵ�����
sfr PCA_PWM1 = 0xF3;    //PCAģ��1 PWM�Ĵ�����
sfr PCA_PWM2 = 0xF4;    //PCAģ��2 PWM�Ĵ�����

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





/*************  IO�ڶ���    **************/
sbit    P_HC595_SER   = P4^0;   //pin 14    SER     data input
sbit    P_HC595_RCLK  = P5^4;   //pin 12    RCLk    store (latch) clock
sbit    P_HC595_SRCLK = P4^3;   //pin 11    SRCLK   Shift data clock

/*************  IO���̱�������  **************/

u8  IO_KeyState, IO_KeyState1, IO_KeyHoldCnt;   //���м��̱���
u8  KeyHoldCnt; //�����¼�ʱ
u8  KeyCode;    //���û�ʹ�õļ���, 1~16��Ч


/*************  ���غ�������    **************/
void    delay_ms(u8 ms);
void    PCA_config(void);
void    IR_TxPulse(u16 pulse);
void    IR_TxSpace(u16 pulse);
void    IR_TxByte(u8 dat);

unsigned char read_wendu(void);



/********************** ������ ************************/
void main(void)
{
	  unsigned char temp;//�¶�
	
    P0M1 = 0;   P0M0 = 0;   //����Ϊ׼˫���
    P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
    P2M1 = 0;   P2M0 = 0;   //����Ϊ׼˫���
    P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
    P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
    P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
    P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
    

    
   // DisableHC595();     //��ֹ��ѧϰ���ϵ�HC595��ʾ��ʡ��

    while(1)
    {
        delay_ms(5);       //30ms
        //IO_KeyScan();
         //temp=read_wendu();
			   temp=25;
        if(temp != 0)        //��⵽����
        {
            TxTime = 0;
                                //һ֡������С���� = 9 + 4.5 + 0.5625 + 24 * 1.125 + 8 * 2.25 = 59.0625 ms
                                //һ֡������󳤶� = 9 + 4.5 + 0.5625 + 8 * 1.125 + 24 * 2.25 = 77.0625 ms
            IR_TxPulse(342);    //��Ӧ9ms��ͬ��ͷ       9ms
            IR_TxSpace(171);    //��Ӧ4.5ms��ͬ��ͷ��� 4.5ms
            IR_TxPulse(21);     //��ʼ��������          0.5625ms

            IR_TxByte(User_code%256);   //���û�����ֽ�
            IR_TxByte(User_code/256);   //���û�����ֽ�
            IR_TxByte(temp);         //������
            IR_TxByte(~temp);        //�����ݷ���
            
            if(TxTime < 56)     //һ֡�����77ms����, �����Ļ�,����ʱ��     108ms
            {
                TxTime = 56 - TxTime;
                TxTime = TxTime + TxTime / 8;
                delay_ms(TxTime);
            }
            delay_ms(31);

            while(IO_KeyState != 0) //��δ�ͷ�
            {
                IR_TxPulse(342);    //��Ӧ9ms��   ͬ��ͷ        9ms
                IR_TxSpace(86);     //��Ӧ2.25ms��ͬ��ͷ���    2.25ms
                IR_TxPulse(21);     //��ʼ��������              0.5625ms
                delay_ms(96);
//IO_KeyScan();
            }
            KeyCode = 0;
        }
    }
} 


/**********************************************/

//========================================================================
// ����: void  delay_ms(unsigned char ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
//========================================================================
void  delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 13000;
          while(--i)    ;   //13T per loop
     }while(--ms);
}




/************* �������庯�� **************/
void    IR_TxPulse(u16 pulse)
{
    tx_cnt = pulse;
    B_Space = 0;    //������
    CCAPM2 = 0x48 | 0x04 | 0x01;    //����ģʽ 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CR = 1;     //����
    while(CR);
}

/************* ���Ϳ��к��� **************/
void    IR_TxSpace(u16 pulse)
{
    tx_cnt = pulse;
    B_Space = 1;    //����
    CCAPM2 = 0x48 | 0x01;   //����ģʽ 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CR = 1;     //����
    while(CR);
}


/************* ����һ���ֽں��� **************/
void    IR_TxByte(u8 dat)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 1)     IR_TxSpace(63), TxTime += 2;    //����1��Ӧ 1.6875 + 0.5625 ms 
        else            IR_TxSpace(21), TxTime++;       //����0��Ӧ 0.5625 + 0.5625 ms
        IR_TxPulse(21);         //���嶼��0.5625ms
        dat >>= 1;              //��һ��λ
    }
}

//========================================================================
// ����: void   PCA_config(void)
// ����: PCA���ú���.
// ����: None
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void    PCA_config(void)
{
    AUXR1   = (AUXR1 & ~0x30) | 0x10;   //�л�IO��, 0x00: P1.2 P1.1 P1.0 P3.7,  0x10: P3.4 P3.5 P3.6 P3.7, 0x20: P2.4 P2.5 P2.6 P2.7

    CCON = 0x00;    //��������жϱ�־
    CCAPM2  = 0x48+ 1;  //����ģʽ + �����ж� 0x00: PCA_Mode_Capture,  0x42: PCA_Mode_PWM,  0x48: PCA_Mode_SoftTimer
    CCAPM2 |= 0x04; //�������ȡ�����, һ������16λ�����ʱ��
    PCA_Timer2 = 100;   //����һ��С�ĳ�ֵ
    CCAP2L = (u8)PCA_Timer2;            //��Ӱ��Ĵ���д�벶��Ĵ�������дCCAPxL
    CCAP2H = (u8)(PCA_Timer2 >> 8); //��дCCAPxH

    PPCA = 1;   //�����ȼ��ж�
    CMOD  = (CMOD  & ~0xe0) | 0x08; //ѡ��ʱ��Դ, 0x00: 12T, 0x02: 2T, 0x04: Timer0���, 0x06: ECI, 0x08: 1T, 0x0A: 4T, 0x0C: 6T, 0x0E: 8T
    CH = 0;
    CL = 0;
    CR = 0;
    tx_cnt = 2;
}

//========================================================================
// ����: void   PCA_Handler (void) interrupt PCA_VECTOR
// ����: PCA�жϴ������.
// ����: None
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================

#define D_38K_DUTY  ((MAIN_Fosc * 26) / 1000000UL + MAIN_Fosc / 3000000UL)  /*  38KHZ����ʱ��   26.3us */
#define D_38K_OFF   ((MAIN_Fosc * 17) / 1000000UL + MAIN_Fosc / 3000000UL)  /* ����ܹر�ʱ��   17.3us */
#define D_38K_ON    ((MAIN_Fosc * 9) / 1000000UL)                           /* ����ܵ�ͨʱ��   9us */

void    PCA_Handler (void) interrupt 7
{
    CCON = 0x40;    //��������жϱ�־,������CR
    if(!B_Space)    //�����ز�
    {                               //�������壬����װ��TH0ֵ�����ʱ�Զ���װ
        if(P_IR_TX)
        {
            PCA_Timer2 += D_38K_OFF;    //װ�ظߵ�ƽʱ��    17.3us
            if(--tx_cnt == 0)   CR = 0; //pulse has sent,   stop
        }
        else    PCA_Timer2 += D_38K_ON; //װ�ص͵�ƽʱ��    9us
    }
    else    //������ͣʱ��
    {
        PCA_Timer2 += D_38K_DUTY;   //װ������ʱ��  26.3us
        if(--tx_cnt == 0)   CR = 0; //����ʱ��
    }
    CCAP2L = (u8)PCA_Timer2;            //��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
    CCAP2H = (u8)(PCA_Timer2 >> 8); //��дCCAP0H
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
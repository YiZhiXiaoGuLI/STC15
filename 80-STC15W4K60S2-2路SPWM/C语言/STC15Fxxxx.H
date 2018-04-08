
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/



#ifndef	_STC15Fxxxx_H
#define	_STC15Fxxxx_H

#include <intrins.h>

/*  BYTE Registers  */
sfr P0   = 0x80;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr	S4CON = 0x84;
sfr	S4BUF = 0x85;
sfr PCON = 0x87;

sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr	AUXR = 0x8E;
sfr WAKE_CLKO = 0x8F;
sfr INT_CLKO = 0x8F;
sfr	AUXR2    = 0x8F;

sfr RL_TL0  = 0x8A;
sfr RL_TL1  = 0x8B;
sfr RL_TH0  = 0x8C;
sfr RL_TH1  = 0x8D;


sfr P1   = 0x90;
sfr P1M1 = 0x91;	//P1M1.n,P1M0.n 	=00--->Standard,	01--->push-pull		ʵ����1T�Ķ�һ��
sfr P1M0 = 0x92;	//					=10--->pure input,	11--->open drain
sfr P0M1 = 0x93;	//P0M1.n,P0M0.n 	=00--->Standard,	01--->push-pull
sfr P0M0 = 0x94;	//					=10--->pure input,	11--->open drain
sfr P2M1 = 0x95;	//P2M1.n,P2M0.n 	=00--->Standard,	01--->push-pull
sfr P2M0 = 0x96;	//					=10--->pure input,	11--->open drain
sfr CLK_DIV = 0x97;
sfr PCON2   = 0x97;

sfr SCON  = 0x98;
sfr SBUF  = 0x99;
sfr S2CON = 0x9A;	//
sfr S2BUF = 0x9B;	//
sfr P1ASF = 0x9D;	//ֻд��ģ������(AD��LVD)ѡ��

sfr P2    = 0xA0;
sfr BUS_SPEED = 0xA1;
sfr AUXR1 = 0xA2;
sfr P_SW1 = 0xA2;

sfr IE    = 0xA8;
sfr SADDR = 0xA9;
sfr WKTCL = 0xAA;	//���Ѷ�ʱ�����ֽ�
sfr WKTCH = 0xAB;	//���Ѷ�ʱ�����ֽ�
sfr	S3CON = 0xAC;
sfr S3BUF = 0xAD;
sfr IE2   = 0xAF;	//STC12C5A60S2ϵ��

sfr P3    = 0xB0;
sfr P3M1  = 0xB1;	//P3M1.n,P3M0.n 	=00--->Standard,	01--->push-pull
sfr P3M0  = 0xB2;	//					=10--->pure input,	11--->open drain
sfr P4M1  = 0xB3;	//P4M1.n,P4M0.n 	=00--->Standard,	01--->push-pull
sfr P4M0  = 0xB4;	//					=10--->pure input,	11--->open drain
sfr IP2   = 0xB5;	//STC12C5A60S2ϵ��
sfr IPH2  = 0xB6;	//STC12C5A60S2ϵ��
sfr IPH   = 0xB7;

sfr IP        = 0xB8;
sfr SADEN     = 0xB9;
sfr	P_SW2     = 0xBA;
sfr ADC_CONTR = 0xBC;	//��ADϵ��
sfr ADC_RES   = 0xBD;	//��ADϵ��
sfr ADC_RESL  = 0xBE;	//��ADϵ��

sfr P4        = 0xC0;
sfr WDT_CONTR = 0xC1;
sfr IAP_DATA  = 0xC2;
sfr IAP_ADDRH = 0xC3;
sfr IAP_ADDRL = 0xC4;
sfr IAP_CMD   = 0xC5;
sfr IAP_TRIG  = 0xC6;
sfr IAP_CONTR = 0xC7;

sfr ISP_DATA  = 0xC2;
sfr ISP_ADDRH = 0xC3;
sfr ISP_ADDRL = 0xC4;
sfr ISP_CMD   = 0xC5;
sfr ISP_TRIG  = 0xC6;
sfr ISP_CONTR = 0xC7;

sfr P5     = 0xC8;	//
sfr P5M1   = 0xC9;	//	P5M1.n,P5M0.n 	=00--->Standard,	01--->push-pull
sfr P5M0   = 0xCA;	//					=10--->pure input,	11--->open drain
sfr P6M1   = 0xCB;	//	P5M1.n,P5M0.n 	=00--->Standard,	01--->push-pull
sfr P6M0   = 0xCC;	//					=10--->pure input,	11--->open drain
sfr SPSTAT = 0xCD;	//
sfr SPCTL  = 0xCE;	//
sfr SPDAT  = 0xCF;	//

sfr PSW  = 0xD0;
sfr	T4T3M = 0xD1;
sfr	T4H  = 0xD2;
sfr	T4L  = 0xD3;
sfr	T3H  = 0xD4;
sfr	T3L  = 0xD5;
sfr	T2H  = 0xD6;
sfr	T2L  = 0xD7;

sfr	TH4  = 0xD2;
sfr	TL4  = 0xD3;
sfr	TH3  = 0xD4;
sfr	TL3  = 0xD5;
sfr	TH2  = 0xD6;
sfr	TL2  = 0xD7;

sfr	RL_T4H  = 0xD2;
sfr	RL_T4L  = 0xD3;
sfr	RL_T3H  = 0xD4;
sfr	RL_T3L  = 0xD5;
sfr	RL_T2H  = 0xD6;
sfr	RL_T2L  = 0xD7;

sfr CCON = 0xD8;	//
sfr CMOD = 0xD9;	//
sfr CCAPM0 = 0xDA;	//PCAģ��0�Ĺ���ģʽ�Ĵ�����
sfr CCAPM1 = 0xDB;	//PCAģ��1�Ĺ���ģʽ�Ĵ�����
sfr CCAPM2 = 0xDC;	//PCAģ��2�Ĺ���ģʽ�Ĵ�����

sfr ACC    = 0xE0;
sfr	P7M1   = 0xE1;
sfr	P7M0   = 0xE2;
sfr	CMPCR1 = 0xE6;
sfr	CMPCR2 = 0xE7;

sfr	P6     = 0xE8;
sfr CL     = 0xE9;	//
sfr CCAP0L = 0xEA;	//PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1L = 0xEB;	//PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP2L = 0xEC;	//PCAģ��2�Ĳ�׽/�ȽϼĴ�����8λ��

sfr B      = 0xF0;
sfr	PWMCFG   = 0xF1;	//PWM���üĴ���
sfr PCA_PWM0 = 0xF2;	//PCAģ��0 PWM�Ĵ�����
sfr PCA_PWM1 = 0xF3;	//PCAģ��1 PWM�Ĵ�����
sfr PCA_PWM2 = 0xF4;	//PCAģ��2 PWM�Ĵ�����
sfr	PWMCR    = 0xF5;	//PWM���ƼĴ���
sfr	PWMIF    = 0xF6;	//PWM�жϱ�־�Ĵ���
sfr	PWMFDCR  = 0xF7;	//PWM�ⲿ�쳣���ƼĴ���

sfr	P7     = 0xF8;
sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;		//PCAģ��0�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP1H = 0xFB;		//PCAģ��1�Ĳ�׽/�ȽϼĴ�����8λ��
sfr CCAP2H = 0xFC;		//PCAģ��2�Ĳ�׽/�ȽϼĴ�����8λ��

#define	PWMCH	0xFFF0	/* PWM���������ֽ�  */
#define	PWMCL	0xFFF1	/* PWM���������ֽ�  */
#define	PWMCKS	0xFFF2	/* PWMʱ��ѡ��      */

#define	PWM2T1H	0xFF00	/* PWM2T1�������ֽ� */
#define	PWM2T1L	0xFF01	/* PWM2T1�������ֽ� */
#define	PWM2T2H	0xFF02	/* PWM2T2�������ֽ� */
#define	PWM2T2L	0xFF03	/* PWM2T2�������ֽ� */
#define	PWM2CR	0xFF04	/* PWM2����         */

#define	PWM3T1H	0xFF10	/* PWM3T1�������ֽ� */
#define	PWM3T1L	0xFF11	/* PWM3T1�������ֽ� */
#define	PWM3T2H	0xFF12	/* PWM3T2�������ֽ� */
#define	PWM3T2L	0xFF13	/* PWM3T2�������ֽ� */
#define	PWM3CR	0xFF14	/* PWM3����         */

#define	PWM4T1H	0xFF20	/* PWM4T1�������ֽ� */
#define	PWM4T1L	0xFF21	/* PWM4T1�������ֽ� */
#define	PWM4T2H	0xFF22	/* PWM4T2�������ֽ� */
#define	PWM4T2L	0xFF23	/* PWM4T2�������ֽ� */
#define	PWM4CR	0xFF24	/* PWM4����         */

#define	PWM5T1H	0xFF30	/* PWM5T1�������ֽ� */
#define	PWM5T1L	0xFF31	/* PWM5T1�������ֽ� */
#define	PWM5T2H	0xFF32	/* PWM5T2�������ֽ� */
#define	PWM5T2L	0xFF33	/* PWM5T2�������ֽ� */
#define	PWM5CR	0xFF34	/* PWM5����         */

#define	PWM6T1H	0xFF40	/* PWM6T1�������ֽ� */
#define	PWM6T1L	0xFF41	/* PWM6T1�������ֽ� */
#define	PWM6T2H	0xFF42	/* PWM6T2�������ֽ� */
#define	PWM6T2L	0xFF43	/* PWM6T2�������ֽ� */
#define	PWM6CR	0xFF44	/* PWM6����         */

#define	PWM7T1H	0xFF50	/* PWM7T1�������ֽ� */
#define	PWM7T1L	0xFF51	/* PWM7T1�������ֽ� */
#define	PWM7T2H	0xFF52	/* PWM7T2�������ֽ� */
#define	PWM7T2L	0xFF53	/* PWM7T2�������ֽ� */
#define	PWM7CR	0xFF54	/* PWM7����         */

#define	PWM2_ID		0
#define	PWM3_ID		1
#define	PWM4_ID		2
#define	PWM5_ID		3
#define	PWM6_ID		4
#define	PWM7_ID		5

#define	PwmClk_1T	0
#define	PwmClk_2T	1
#define	PwmClk_3T	2
#define	PwmClk_4T	3
#define	PwmClk_5T	4
#define	PwmClk_6T	5
#define	PwmClk_7T	6
#define	PwmClk_8T	7
#define	PwmClk_9T	8
#define	PwmClk_10T	9
#define	PwmClk_11T	10
#define	PwmClk_12T	11
#define	PwmClk_13T	12
#define	PwmClk_14T	13
#define	PwmClk_15T	14
#define	PwmClk_16T	15
#define	PwmClk_T2	16

//                    7   6   5   4     3        2       1        0      Reset Value
//PWMnCR:  PWMn����   -   -   -   -   PWMn_PS  EPWMnI  ECnT2SI  ECnT1SI   0000,0000
#define	PWMn_PS_1		0x00	/* PWM�ܽ�ѡ��λ */
#define	PWMn_PS_2		0x08	/* PWM�ܽ�ѡ��λ */
#define	EPWMnI_Enable	0x04	/* ����PWM�ж�   */
#define	ECnT2SI_Enable	0x02	/* ����T2��תʱ�ж� */
#define	ECnT1SI_Enable	0x01	/* ����T1��תʱ�ж� */

#define	PWM2_P37	0x00
#define	PWM2_P27	0x08
#define	PWM3_P21	0x00
#define	PWM3_P45	0x08
#define	PWM4_P22	0x00
#define	PWM4_P44	0x08
#define	PWM5_P23	0x00
#define	PWM5_P42	0x08
#define	PWM6_P16	0x00
#define	PWM6_P07	0x08
#define	PWM7_P17	0x00
#define	PWM7_P06	0x08

#define	EAXSFR()		P_SW2 |=  0x80	/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
#define	EAXRAM()		P_SW2 &= ~0x80	/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */
#define	C2INI	0x01	/* PWM����˿ڵĳ�ʼ��ƽΪ�ߵ�ƽ */
#define	C3INI	0x02
#define	C4INI	0x04
#define	C5INI	0x08
#define	C6INI	0x10
#define	C7INI	0x20
#define	CBTADC	0x40	/* PWM����������ʱ�Զ�����ADCת������ע��ǰ��������PWM��ADC���뱻ʹ�ܣ���ENPWM==1����ADCON==1�� */

#define	ENPWM	0x80	/* ʹ��PWM���η�������PWM��������ʼ���� */
#define	ECBI	0x40	/* ʹ��PWM�����������ж� */
#define	ENC7O	0x20	/* ��ӦPWMͨ���Ķ˿�����ΪPWM����ڣ���PWM���η��������� */
#define	ENC6O	0x10
#define	ENC5O	0x08
#define	ENC4O	0x04
#define	ENC3O	0x02
#define	ENC2O	0x01
#define	PWM_Enable()	PWMCR |=  0x80	/* ʹ��PWM���η�������PWM��������ʼ���� */
#define	PWM_Disable()	PWMCR &= ~0x80	/* �ر�PWM���η����� */

#define	CBIF	0x40	/* PWM�����������жϱ�־λ */
#define	C7IF	0x20
#define	C6IF	0x10	/* ��nͨ����PWM�жϱ�־λ */
#define	C5IF	0x08
#define	C4IF	0x04
#define	C3IF	0x02
#define	C2IF	0x01

#define	ENFD		0x20	/* ʹ��PWM���ⲿ�쳣��⹦ */
#define	FLTFLIO		0x10	/* ����WM�ⲿ�쳣ʱ��PWM�����������������Ϊ��������ģʽ����ע��ֻ��ENCnO==1����Ӧ�Ķ˿ڲŻᱻǿ�����գ� */
#define	EFDI		0x08	/* ʹ��PWM�쳣����ж� */
#define	FDCMP		0x04	/* ���Ƚ���������ɵͱ��ʱ������PWM�쳣 */
#define	FDIO		0x02	/* ��P2.4�ĵ�ƽ�ɵͱ��ʱ������PWM�쳣 */
#define	FDIF		0x01	/* ������PWM�쳣���Ƚ���������ɵͱ�߻���P2.4�ĵ�ƽ�ɵͱ�ߣ�ʱ��Ӳ���Զ�����λ��1, ����λ�жϱ�־.��Ҫ������� */
#define	PWM_FaultDetect_Enable()	PWMFDCR |=  0x20		/* ʹ��PWM���ⲿ�쳣��⹦�� */
#define	PWM_FaultDetect_Disable()	PWMFDCR &= ~0x20		/* ��ֹPWM���ⲿ�쳣��⹦�� */


/*  BIT Registers  */
/*  PSW   */
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit F1   = PSW^1;
sbit P    = PSW^0;

/*  TCON  */
sbit TF1  = TCON^7;	//��ʱ��1����жϱ�־λ
sbit TR1  = TCON^6;	//��ʱ��1���п���λ
sbit TF0  = TCON^5;	//��ʱ��0����жϱ�־λ
sbit TR0  = TCON^4;	//��ʱ��0���п���λ
sbit IE1  = TCON^3;	//���ж�1��־λ
sbit IT1  = TCON^2;	//���ж�1�źŷ�ʽ����λ��1���½����жϣ�0�������½����жϡ�
sbit IE0  = TCON^1;	//���ж�0��־λ
sbit IT0  = TCON^0;	//���ж�0�źŷ�ʽ����λ��1���½����жϣ�0�������½����жϡ�

/*  P0  */
sbit  P00 = P0^0;
sbit  P01 = P0^1;
sbit  P02 = P0^2;
sbit  P03 = P0^3;
sbit  P04 = P0^4;
sbit  P05 = P0^5;
sbit  P06 = P0^6;
sbit  P07 = P0^7;

/*  P1  */
sbit  P10 = P1^0;
sbit  P11 = P1^1;
sbit  P12 = P1^2;
sbit  P13 = P1^3;
sbit  P14 = P1^4;
sbit  P15 = P1^5;
sbit  P16 = P1^6;
sbit  P17 = P1^7;

sbit  RXD2      = P1^0;
sbit  TXD2      = P1^1;
sbit  CCP1      = P1^0;
sbit  CCP0      = P1^1;
sbit  SPI_SS    = P1^2;
sbit  SPI_MOSI  = P1^3;
sbit  SPI_MISO  = P1^4;
sbit  SPI_SCLK  = P1^5;

sbit  SPI_SS_2    = P2^4;
sbit  SPI_MOSI_2  = P2^3;
sbit  SPI_MISO_2  = P2^2;
sbit  SPI_SCLK_2  = P2^1;

sbit  SPI_SS_3    = P5^4;
sbit  SPI_MOSI_3  = P4^0;
sbit  SPI_MISO_3  = P4^1;
sbit  SPI_SCLK_3  = P4^3;

/*  P2  */
sbit  P20 = P2^0;
sbit  P21 = P2^1;
sbit  P22 = P2^2;
sbit  P23 = P2^3;
sbit  P24 = P2^4;
sbit  P25 = P2^5;
sbit  P26 = P2^6;
sbit  P27 = P2^7;

/*  P3  */
sbit  P30 = P3^0;
sbit  P31 = P3^1;
sbit  P32 = P3^2;
sbit  P33 = P3^3;
sbit  P34 = P3^4;
sbit  P35 = P3^5;
sbit  P36 = P3^6;
sbit  P37 = P3^7;

sbit RXD  = P3^0;
sbit TXD  = P3^1;
sbit INT0 = P3^2;
sbit INT1 = P3^3;
sbit T0   = P3^4;
sbit T1   = P3^5;
sbit WR   = P3^6;
sbit RD   = P3^7;
sbit CCP2  = P3^7;

sbit CLKOUT0   = P3^5;
sbit CLKOUT1   = P3^4;

/*  P4  */
sbit  P40 = P4^0;
sbit  P41 = P4^1;
sbit  P42 = P4^2;
sbit  P43 = P4^3;
sbit  P44 = P4^4;
sbit  P45 = P4^5;
sbit  P46 = P4^6;
sbit  P47 = P4^7;

/*  P5  */
sbit  P50 = P5^0;
sbit  P51 = P5^1;
sbit  P52 = P5^2;
sbit  P53 = P5^3;
sbit  P54 = P5^4;
sbit  P55 = P5^5;
sbit  P56 = P5^6;
sbit  P57 = P5^7;

/*  P6  */
sbit  P60 = P6^0;
sbit  P61 = P6^1;
sbit  P62 = P6^2;
sbit  P63 = P6^3;
sbit  P64 = P6^4;
sbit  P65 = P6^5;
sbit  P66 = P6^6;
sbit  P67 = P6^7;

/*  P7  */
sbit  P70 = P7^0;
sbit  P71 = P7^1;
sbit  P72 = P7^2;
sbit  P73 = P7^3;
sbit  P74 = P7^4;
sbit  P75 = P7^5;
sbit  P76 = P7^6;
sbit  P77 = P7^7;


/*  SCON  */
sbit SM0  = SCON^7;	//SM0/FE		SM0 SM1 = 00 ~ 11: ��ʽ0~3
sbit SM1  = SCON^6;	//
sbit SM2  = SCON^5;	//���ͨѶ
sbit REN  = SCON^4;	//��������
sbit TB8  = SCON^3;	//�������ݵ�8λ
sbit RB8  = SCON^2;	//�������ݵ�8λ
sbit TI   = SCON^1;	//�����жϱ�־λ
sbit RI   = SCON^0;	//�����жϱ�־λ

/*  IE   */
sbit EA   = IE^7;	//�ж������ܿ���λ
sbit ELVD = IE^6;	//��ѹ����ж�����λ
sbit EADC = IE^5;	//ADC �ж� ����λ
sbit ES   = IE^4;	//�����ж� �������λ
sbit ET1  = IE^3;	//��ʱ�ж�1�������λ
sbit EX1  = IE^2;	//�ⲿ�ж�1�������λ
sbit ET0  = IE^1;	//��ʱ�ж�0�������λ
sbit EX0  = IE^0;	//�ⲿ�ж�0�������λ

sbit ACC0 = ACC^0;
sbit ACC1 = ACC^1;
sbit ACC2 = ACC^2;
sbit ACC3 = ACC^3;
sbit ACC4 = ACC^4;
sbit ACC5 = ACC^5;
sbit ACC6 = ACC^6;
sbit ACC7 = ACC^7;

sbit B0 = B^0;
sbit B1 = B^1;
sbit B2 = B^2;
sbit B3 = B^3;
sbit B4 = B^4;
sbit B5 = B^5;
sbit B6 = B^6;
sbit B7 = B^7;


//							7     6     5    4    3    2    1     0    Reset Value
//sfr IE2       = 0xAF;		-     -     -    -    -    -   ESPI  ES2   0000,0000B	//Auxiliary Interrupt   
#define		SPI_INT_ENABLE()		IE2 |=  2	/* ����SPI�ж�		*/
#define		SPI_INT_DISABLE()		IE2 &= ~2	/* ����SPI�ж�		*/
#define		UART2_INT_ENABLE()		IE2 |=  1	/* ������2�ж�	*/
#define		UART2_INT_DISABLE()		IE2 &= ~1	/* ������2�ж�	*/

//                                          7     6     5    4    3    2    1    0    Reset Value
//sfr IP      = 0xB8; //�ж����ȼ���λ      PPCA  PLVD  PADC  PS   PT1  PX1  PT0  PX0   0000,0000
//--------
sbit PPCA	= IP^7;	//PCA ģ���ж����ȼ�
sbit PLVD	= IP^6;	//��ѹ����ж����ȼ�
sbit PADC	= IP^5;	//ADC �ж����ȼ�
sbit PS   	= IP^4;	//�����ж�0���ȼ��趨λ
sbit PT1	= IP^3;	//��ʱ�ж�1���ȼ��趨λ
sbit PX1	= IP^2;	//�ⲿ�ж�1���ȼ��趨λ
sbit PT0	= IP^1;	//��ʱ�ж�0���ȼ��趨λ
sbit PX0	= IP^0;	//�ⲿ�ж�0���ȼ��趨λ

//                                           7      6      5     4     3     2    1     0        Reset Value
//sfr IPH   = 0xB7; //�ж����ȼ���λ       PPCAH  PLVDH  PADCH  PSH  PT1H  PX1H  PT0H  PX0H   0000,0000
//sfr IP2   = 0xB5; //                       -      -      -     -     -     -   PSPI   PS2   xxxx,xx00
//sfr IPH2  = 0xB6; //                       -      -      -     -     -     -   PSPIH  PS2H  xxxx,xx00
#define		PPCAH	0x80
#define		PLVDH	0x40
#define		PADCH	0x20
#define		PSH		0x10
#define		PT1H	0x08
#define		PX1H	0x04
#define		PT0H	0x02
#define		PX0H	0x01

#define		PCA_InterruptFirst()	PPCA = 1
#define		LVD_InterruptFirst()	PLVD = 1
#define		ADC_InterruptFirst()	PADC = 1
#define		UART1_InterruptFirst()	PS   = 1
#define		Timer1_InterruptFirst()	PT1  = 1
#define		INT1_InterruptFirst()	PX1  = 1
#define		Timer0_InterruptFirst()	PT0  = 1
#define		INT0_InterruptFirst()	PX0  = 1


/*************************************************************************************************/


//                       7      6     5    4    3    2     1      0        Reset Value
//sfr CMPCR1 = 0xE6;   CMPEN  CMPIF  PIE  NIE  PIS  NIS  CMPOE  CMPRES      00000000B
#define	CMPEN	0x80	//1: ����Ƚ���, 0: ��ֹ,�رձȽ�����Դ
#define	CMPIF	0x40	//�Ƚ����жϱ�־, ���������ػ��½����ж�, �����0
#define	PIE		0x20	//1: �ȽϽ����0��1, �����������ж�
#define	NIE		0x10	//1: �ȽϽ����1��0, �����½����ж�
#define	PIS		0x08	//����������ѡ��, 0: ѡ���ڲ�P5.5��������,           1: ��ADCIS[2:0]��ѡ���ADC�������������.
#define	NIS		0x04	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP5.4������.
#define	CMPOE	0x02	//1: ����ȽϽ�������P1.2, 0: ��ֹ.
#define	CMPRES	0x01	//�ȽϽ��, 1: CMP+��ƽ����CMP-,  0: CMP+��ƽ����CMP-,  ֻ��

//                       7        6       5  4  3  2  1  0    Reset Value
//sfr CMPCR2 = 0xE7;   INVCMPO  DISFLT       LCDTY[5:0]       00001001B
#define	INVCMPO	0x80	//1: �Ƚ������ȡ��,  0: ��ȡ��
#define	DISFLT	0x40	//1: �ر�0.1uF�˲�,   0: ����
#define	LCDTY	0x00	//0~63, �ȽϽ���仯��ʱ������


/*************************************************************************************************/
//                     7     6     5    4    3    2   1   0       Reset Value
//sfr SCON  = 0x98;   SM0   SM1   SM2  REN  TB8  RB8  TI  RI      00000000B		 //S1 Control

#define		S1_DoubleRate()		PCON  |=  0x80
#define		S1_SHIFT()			SCON  &=  0x3f

#define		S1_8bit()			SCON   =  (SCON & 0x3f) | 0x40
#define		S1_9bit()			SCON   =  (SCON & 0x3f) | 0xc0
#define		S1_RX_Enable()		SCON  |=  0x10
#define		S1_RX_Disable()		SCON  &= ~0x10
#define		TI1					TI					/* �ж�TI1�Ƿ������								 */
#define		RI1					RI					/* �ж�RI1�Ƿ�������								 */
#define		SET_TI1()			TI = 1				/* ����TI1(�����ж�)								 */
#define		CLR_TI1()			TI = 0				/* ���TI1											 */
#define		CLR_RI1()			RI = 0				/* ���RI1											 */
#define		S1TB8_SET()			TB8 = 1				/* ����TB8											 */
#define		S1TB8_CLR()			TB8 = 0				/* ���TB8											 */
#define		S1_Int_Enable()		ES     =  1			/* ����1�����ж�									 */
#define		S1_Int_Disable()	ES     =  0			/* ����1��ֹ�ж�									 */
#define 	S1_BRT_UseTimer1()	AUXR  &= ~1
#define 	S1_BRT_UseTimer2()	AUXR  |=  1
#define		S1_USE_P30P31()		P_SW1 &= ~0xc0						//UART1 ʹ��P30 P31��	Ĭ��
#define		S1_USE_P36P37()		P_SW1  =  (P_SW1 & ~0xc0) | 0x40	//UART1 ʹ��P36 P37��
#define		S1_USE_P16P17()		P_SW1  =  (P_SW1 & ~0xc0) | 0x80	//UART1 ʹ��P16 P17��
#define		S1_TXD_RXD_SHORT()	PCON2 |=  (1<<4)	//��TXD��RXD�����м����
#define		S1_TXD_RXD_OPEN()	PCON2 &= ~(1<<4)	//��TXD��RXD�����м̶Ͽ�	Ĭ��

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S2CON = 0x9A;		S2SM0    -    S2SM2  S2REN  S2TB8  S2RB8  S2TI  S2RI      00000000B		 //S2 Control

#define		S2_MODE0()			S2CON &= ~(1<<7)	/* ����2ģʽ0��8λUART�������� = ��ʱ��2������� / 4 */
#define		S2_MODE1()			S2CON |=  (1<<7)	/* ����2ģʽ1��9λUART�������� = ��ʱ��2������� / 4 */
#define		S2_8bit()			S2CON &= ~(1<<7)	/* ����2ģʽ0��8λUART�������� = ��ʱ��2������� / 4 */
#define		S2_9bit()			S2CON |=  (1<<7)	/* ����2ģʽ1��9λUART�������� = ��ʱ��2������� / 4 */
#define		S2_RX_Enable()		S2CON |=  (1<<4)	/* ����2����										 */
#define		S2_RX_Disable()		S2CON &= ~(1<<4)	/* ��ֹ��2����										 */
#define		TI2					(S2CON & 2) != 0	/* �ж�TI2�Ƿ������								 */
#define		RI2					(S2CON & 1) != 0	/* �ж�RI2�Ƿ�������								 */
#define		SET_TI2()			S2CON |=  (1<<1)	/* ����TI2(�����ж�)								 */
#define		CLR_TI2()			S2CON &= ~(1<<1)	/* ���TI2											 */
#define		CLR_RI2()			S2CON &= ~1			/* ���RI2											 */
#define		S2TB8_SET()			S2CON |=  (1<<3)	/* ����TB8											 */
#define		S2TB8_CLR()			S2CON &= ~(1<<3)	/* ���TB8											 */
#define		S2_Int_Enable()		IE2   |=  1			/* ����2�����ж�									 */
#define		S2_Int_Disable()	IE2   &= ~1			/* ����2��ֹ�ж�									 */
#define		S2_USE_P10P11()		P_SW2 &= ~1			/* UART2 ʹ��P1��	Ĭ��							 */
#define		S2_USE_P46P47()		P_SW2 |=  1			/* UART2 ʹ��P4��									 */

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S3CON = 0xAC;		S3SM0  S3ST3  S3SM2  S3REN  S3TB8  S3RB8  S3TI  S3RI      00000000B		 //S3 Control

#define		S3_MODE0()			S3CON &= ~(1<<7)	/* ����3ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S3_MODE1()			S3CON |=  (1<<7)	/* ����3ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S3_8bit()			S3CON &= ~(1<<7)	/* ����3ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S3_9bit()			S3CON |=  (1<<7)	/* ����3ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S3_RX_Enable()		S3CON |=  (1<<4)	/* ����3����									     */
#define		S3_RX_Disable()		S3CON &= ~(1<<4)	/* ��ֹ��3����									     */
#define		TI3					(S3CON & 2) != 0	/* �ж�TI3�Ƿ������								 */
#define		RI3					(S3CON & 1) != 0	/* �ж�RI3�Ƿ�������								 */
#define		SET_TI3()			S3CON |=  (1<<1)	/* ����TI3(�����ж�)								 */
#define		CLR_TI3()			S3CON &= ~(1<<1)	/* ���TI3											 */
#define		CLR_RI3()			S3CON &= ~1			/* ���RI3											 */
#define		S3TB8_SET()			S3CON |=  (1<<3)	/* ����TB8											 */
#define		S3TB8_CLR()			S3CON &= ~(1<<3)	/* ���TB8											 */
#define		S3_Int_Enable()		IE2   |=  (1<<3)	/* ����3�����ж�								     */
#define		S3_Int_Disable()	IE2   &= ~(1<<3)	/* ����3��ֹ�ж�								     */
#define 	S3_BRT_UseTimer3()	S3CON |=  (1<<6)	/* BRT select Timer3								 */
#define 	S3_BRT_UseTimer2()	S3CON &= ~(1<<6)	/* BRT select Timer2								 */
#define		S3_USE_P00P01()		P_SW2 &= ~2			/* UART3 ʹ��P0��	Ĭ��						     */
#define		S3_USE_P50P51()		P_SW2 |=  2			/* UART3 ʹ��P5��								     */

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S4CON = 0x84;		S4SM0  S4ST4  S4SM2  S4REN  S4TB8  S4RB8  S4TI  S4RI      00000000B		 //S4 Control

#define		S4_MODE0()			S4CON &= ~(1<<7)	/* ����4ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S4_MODE1()			S4CON |=  (1<<7)	/* ����4ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S4_8bit()			S4CON &= ~(1<<7)	/* ����4ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S4_9bit()			S4CON |=  (1<<7)	/* ����4ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S4_RX_Enable()		S4CON |=  (1<<4)	/* ����4����									     */
#define		S4_RX_Disable()		S4CON &= ~(1<<4)	/* ��ֹ��4����									     */
#define		TI4					(S4CON & 2) != 0	/* �ж�TI3�Ƿ������							     */
#define		RI4					(S4CON & 1) != 0	/* �ж�RI3�Ƿ�������							     */
#define		SET_TI4()			S4CON |=  2			/* ����TI3(�����ж�)							     */
#define		CLR_TI4()			S4CON &= ~2			/* ���TI3										     */
#define		CLR_RI4()			S4CON &= ~1			/* ���RI3										     */
#define		S4TB8_SET()			S4CON |=  8			/* ����TB8										     */
#define		S4TB8_CLR()			S4CON &= ~8			/* ���TB8										     */
#define		S4_Int_Enable()		IE2   |=  (1<<4)	/* ����4�����ж�								     */
#define		S4_Int_Disable()	IE2   &= ~(1<<4)	/* ����4��ֹ�ж�								     */
#define 	S4_BRT_UseTimer4()	S4CON |=  (1<<6)	/* BRT select Timer4								 */
#define 	S4_BRT_UseTimer2()	S4CON &= ~(1<<6)	/* BRT select Timer2								 */
#define		S4_USE_P02P03()		P_SW2 &= ~4			/* UART4 ʹ��P0��	Ĭ��						     */
#define		S4_USE_P52P53()		P_SW2 |=  4			/* UART4 ʹ��P5��								     */




/**********************************************************/
//						   7     6       5      4     3      2      1      0    Reset Value
//sfr AUXR  = 0x8E;		T0x12 T1x12 UART_M0x6  T2R  T2_C/T T2x12 EXTRAM  S1ST2  0000,0000	//Auxiliary Register 

#define 	ExternalRAM_enable()		AUXR |=  2		/* �����ⲿXRAM����ֹʹ���ڲ�1024RAM     */
#define 	InternalRAM_enable()		AUXR &= ~2		/* ��ֹ�ⲿXRAM������ʹ���ڲ�1024RAM     */
#define		S1_M0x6()					AUXR |=  (1<<5)	/* UART Mode0 Speed is 6x Standard       */
#define		S1_M0x1()					AUXR &= ~(1<<5)	/* default,	UART Mode0 Speed is Standard */

//====================================
#define		Timer0_16bitAutoReload()	TMOD &= ~0x03					/* 16λ�Զ���װ	*/
#define		Timer0_16bit()				TMOD  = (TMOD & ~0x03) | 0x01	/* 16λ         */
#define		Timer0_8bitAutoReload()		TMOD  = (TMOD & ~0x03) | 0x02	/* 8λ�Զ���װ	*/
#define		Timer0_16bitAutoRL_NoMask()	TMOD |=  0x03		/* 16λ�Զ���װ���������ж�	*/
#define 	Timer0_Run()	 			TR0 = 1				/* ����ʱ��0����			*/
#define 	Timer0_Stop()	 			TR0 = 0				/* ��ֹ��ʱ��0����			*/
#define		Timer0_Gate_INT0_P32()		TMOD |=  (1<<3)		/* ʱ��0���ⲿINT0�ߵ�ƽ����ʱ���� */
#define		Timer0_AsTimer()			TMOD &= ~(1<<2)		/* ʱ��0������ʱ��	*/
#define		Timer0_AsCounter()			TMOD |=  (1<<2)		/* ʱ��0����������	*/
#define		Timer0_AsCounterP34()		TMOD |=  (1<<2)		/* ʱ��0����������	*/
#define 	Timer0_1T()					AUXR |=  (1<<7)		/* Timer0 clodk = fo	*/
#define 	Timer0_12T()				AUXR &= ~(1<<7)		/* Timer0 clodk = fo/12	12��Ƶ,	default	*/
#define		Timer0_CLKO_Enable()		AUXR2 |=  1			/* ���� T0 ���������T0(P3.5)�������Fck0 = 1/2 T0 ����ʣ�T0����1T��12T��	*/
#define		Timer0_CLKO_Disable()		AUXR2 &= ~1
#define		Timer0_CLKO_Enable_P34()	AUXR2 |=  1			/* ���� T0 ���������T0(P3.5)�������Fck0 = 1/2 T0 ����ʣ�T0����1T��12T��	*/
#define		Timer0_CLKO_Disable_P34()	AUXR2 &= ~1
#define 	Timer0_InterruptEnable()	ET0 = 1				/* ����Timer1�ж�.*/
#define 	Timer0_InterruptDisable()	ET0 = 0				/* ��ֹTimer1�ж�.*/

#define		T0_Load(n)					TH0 = (n) / 256,	TL0 = (n) % 256
#define		T0_Load_us_1T(n)			Timer0_AsTimer(),Timer0_1T(), Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T0_Load_us_12T(n)			Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T0_Frequency_1T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_1T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/2)/(n))%256,AUXR2 |= bit0,TR0=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T0_Frequency_12T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/24)/(n))%256,AUXR2 |= bit0,TR0=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define		Timer1_16bitAutoReload()	TMOD &= ~0x30					/* 16λ�Զ���װ	*/
#define		Timer1_16bit()				TMOD  = (TMOD & ~0x30) | 0x10	/* 16λ			*/
#define		Timer1_8bitAutoReload()		TMOD  = (TMOD & ~0x30) | 0x20	/* 8λ�Զ���װ	*/
#define 	Timer1_Run()	 			TR1 = 1				/* ����ʱ��1����			*/
#define 	Timer1_Stop()	 			TR1 = 0				/* ��ֹ��ʱ��1����			*/
#define		Timer1_Gate_INT1_P33()		TMOD |=  (1<<7)		/* ʱ��1���ⲿINT1�ߵ�ƽ����ʱ����	*/
#define		Timer1_AsTimer()			TMOD &= ~(1<<6)		/* ʱ��1������ʱ��			*/
#define		Timer1_AsCounter()			TMOD |=  (1<<6)		/* ʱ��1����������			*/
#define		Timer1_AsCounterP35()		TMOD |=  (1<<6)		/* ʱ��1����������			*/
#define 	Timer1_1T()					AUXR |=  (1<<6)		/* Timer1 clodk = fo		*/
#define 	Timer1_12T()				AUXR &= ~(1<<6)		/* Timer1 clodk = fo/12	12��Ƶ,	default	*/
#define		Timer1_CLKO_Enable()		AUXR2 |=  2			/* ���� T1 ���������T1(P3.4)�������Fck1 = 1/2 T1 ����ʣ�T1����1T��12T��	*/
#define		Timer1_CLKO_Disable()		AUXR2 &= ~2
#define		Timer1_CLKO_Enable_P35()	AUXR2 |=  2			/* ���� T1 ���������T1(P3.4)�������Fck1 = 1/2 T1 ����ʣ�T1����1T��12T��	*/
#define		Timer1_CLKO_Disable_P35()	AUXR2 &= ~2
#define 	Timer1_InterruptEnable()	ET1 = 1				/* ����Timer1�ж�.	*/
#define 	Timer1_InterruptDisable()	ET1 = 0				/* ��ֹTimer1�ж�.	*/

#define		T1_Load(n)					TH1 = (n) / 256,	TL1 = (n) % 256
#define		T1_Load_us_1T(n)			Timer1_AsTimer(),Timer1_1T(), Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T1_Load_us_12T(n)			Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T1_Frequency_1T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_1T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/2)/(n))%256,AUXR2 |= bit1,TR1=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T1_Frequency_12T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/24)/(n))%256,AUXR2 |= bit1,TR1=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer2_Run()	 			AUXR |=  (1<<4)	/* ����ʱ��2����	*/
#define 	Timer2_Stop()	 			AUXR &= ~(1<<4)	/* ��ֹ��ʱ��2����	*/
#define		Timer2_AsTimer()			AUXR &= ~(1<<3)	/* ʱ��2������ʱ��	*/
#define		Timer2_AsCounter()			AUXR |=  (1<<3)	/* ʱ��2����������	*/
#define		Timer2_AsCounterP31()		AUXR |=  (1<<3)	/* ʱ��2����������	*/
#define 	Timer2_1T()					AUXR |=  (1<<2)	/* Timer0 clock = fo	*/
#define 	Timer2_12T()				AUXR &= ~(1<<2)	/* Timer0 clock = fo/12	12��Ƶ,	default	*/
#define		Timer2_CLKO_Enable()		AUXR2 |=  4		/* ���� T2 ���������T1(P3.0)�������Fck2 = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer2_CLKO_Disable()		AUXR2 &= ~4
#define		Timer2_CLKO_Enable_P30()	AUXR2 |=  4		/* ���� T2 ���������T1(P3.0)�������Fck2 = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer2_CLKO_Disable_P30()	AUXR2 &= ~4
#define 	Timer2_InterruptEnable()	IE2  |=  (1<<2)	/* ����Timer2�ж�.	*/
#define 	Timer2_InterruptDisable()	IE2  &= ~(1<<2)	/* ��ֹTimer2�ж�.	*/

#define		T2_Load(n)					TH2 = (n) / 256,	TL2 = (n) % 256
#define		T2_Load_us_1T(n)			Timer2_AsTimer(),Timer2_1T(), TH2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T2_Load_us_12T(n)			Timer2_AsTimer(),Timer2_12T(),TH2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T2_Frequency_1T_P30(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_1T(), TH2=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL2=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer2_CLKO_Enable_P30(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T2_Frequency_12T_P30(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_12T(),TH2=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL2=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer2_CLKO_Enable_P30(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer3_Run()	 			T4T3M |=  (1<<3)	/* ����ʱ��3����	*/
#define 	Timer3_Stop()	 			T4T3M &= ~(1<<3)	/* ��ֹ��ʱ��3����	*/
#define		Timer3_AsTimer()			T4T3M &= ~(1<<2)	/* ʱ��3������ʱ��	*/
#define		Timer3_AsCounter()			T4T3M |=  (1<<2)	/* ʱ��3����������, P0.5Ϊ�ⲿ����	*/
#define		Timer3_AsCounterP05()		T4T3M |=  (1<<2)	/* ʱ��3����������, P0.5Ϊ�ⲿ����	*/
#define 	Timer3_1T()					T4T3M |=  (1<<1)	/* 1Tģʽ	*/
#define 	Timer3_12T()				T4T3M &= ~(1<<1)	/* 12Tģʽ,	default	*/
#define		Timer3_CLKO_Enable()		T4T3M |=  1			/* ����T3���������T3(P0.4)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer3_CLKO_Disable()		T4T3M &= ~1			/* ��ֹT3���������T3(P0.4)�����	*/
#define		Timer3_CLKO_Enable_P04()	T4T3M |=  1			/* ����T3���������T3(P0.4)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer3_CLKO_Disable_P04()	T4T3M &= ~1			/* ��ֹT3���������T3(P0.4)�����	*/
#define 	Timer3_InterruptEnable()	IE2  |=  (1<<5)		/* ����Timer3�ж�.	*/
#define 	Timer3_InterruptDisable()	IE2  &= ~(1<<5)		/* ��ֹTimer3�ж�.	*/

#define		T3_Load(n)					TH3 = (n) / 256,	TL3 = (n) % 256
#define		T3_Load_us_1T(n)			Timer3_AsTimer(),Timer3_1T(), TH3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T3_Load_us_12T(n)			Timer3_AsTimer(),Timer3_12T(),TH3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T3_Frequency_1T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_1T(), TH3=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL3=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T3_Frequency_12T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_12T(),TH3=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL3=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer4_Run()	 			T4T3M |=  (1<<7)	/* ����ʱ��4����	*/
#define 	Timer4_Stop()	 			T4T3M &= ~(1<<7)	/* ��ֹ��ʱ��4����	*/
#define		Timer4_AsTimer()			T4T3M &= ~(1<<6)	/* ʱ��4������ʱ��  */
#define		Timer4_AsCounter()			T4T3M |=  (1<<6)	/* ʱ��4����������, P0.7Ϊ�ⲿ����	*/
#define		Timer4_AsCounterP07()		T4T3M |=  (1<<6)	/* ʱ��4����������, P0.7Ϊ�ⲿ����	*/
#define 	Timer4_1T()					T4T3M |=  (1<<5)	/* 1Tģʽ	*/
#define 	Timer4_12T()				T4T3M &= ~(1<<5)	/* 12Tģʽ,	default	*/
#define		Timer4_CLKO_Enable()		T4T3M |=  (1<<4)	/* ����T4���������T4(P0.6)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer4_CLKO_Disable()		T4T3M &= ~(1<<4)	/* ��ֹT4���������T4(P0.6)�����	*/
#define		Timer4_CLKO_Enable_P06()	T4T3M |=  (1<<4)	/* ����T4���������T4(P0.6)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer4_CLKO_Disable_P06()	T4T3M &= ~(1<<4)	/* ��ֹT4���������T4(P0.6)�����	*/
#define 	Timer4_InterruptEnable()	IE2  |=  (1<<6)		/* ����Timer4�ж�.	*/
#define 	Timer4_InterruptDisable()	IE2  &= ~(1<<6)		/* ��ֹTimer4�ж�.	*/

#define		T4_Load(n)					TH4 = (n) / 256,	TL4 = (n) % 256
#define		T4_Load_us_1T(n)			Timer4_AsTimer(),Timer4_1T(), TH4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T4_Load_us_12T(n)			Timer4_AsTimer(),Timer4_12T(),TH4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T4_Frequency_1T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_1T(), TH4=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL4=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T4_Frequency_12T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_12T(),TH4=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL4=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
//====================================================================================================================

//sfr WDT_CONTR = 0xC1; //Watch-Dog-Timer Control register
//                                      7     6     5      4       3      2   1   0     Reset Value
//                                  WDT_FLAG  -  EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0    xx00,0000
#define D_WDT_FLAG			(1<<7)
#define D_EN_WDT			(1<<5)
#define D_CLR_WDT			(1<<4)	/* auto clear	*/
#define D_IDLE_WDT			(1<<3)	/* WDT counter when Idle	*/
#define D_WDT_SCALE_2		0
#define D_WDT_SCALE_4		1
#define D_WDT_SCALE_8		2		/* T=393216*N/fo	*/
#define D_WDT_SCALE_16		3
#define D_WDT_SCALE_32		4
#define D_WDT_SCALE_64		5
#define D_WDT_SCALE_128		6
#define D_WDT_SCALE_256		7

#define	WDT_reset(n)	WDT_CONTR = D_EN_WDT + D_CLR_WDT + D_IDLE_WDT + (n)		/* ��ʼ��WDT��ι�� */


//						  7     6      5    4     3      2    1     0     Reset Value
//sfr PCON   = 0x87;	SMOD  SMOD0  LVDF  POF   GF1    GF0   PD   IDL    0001,0000	 //Power Control 
//SMOD		//����˫����
//SMOD0
#define		LVDF		(1<<5)	/* P4.6��ѹ����־ */
//POF
//GF1
//GF0
//#define 	D_PD		2		/* set 1, power down mode */
//#define 	D_IDLE		1		/* set 1, idle mode */
#define		MCU_IDLE()			PCON |= 1	/* MCU ���� IDLE ģʽ */
#define		MCU_POWER_DOWN()	PCON |= 2	/* MCU ���� ˯�� ģʽ */


//sfr ISP_CMD   = 0xC5;
#define		ISP_STANDBY()	ISP_CMD = 0		/* ISP���������ֹ��*/
#define		ISP_READ()		ISP_CMD = 1		/* ISP��������		*/
#define		ISP_WRITE()		ISP_CMD = 2		/* ISPд������		*/
#define		ISP_ERASE()		ISP_CMD = 3		/* ISP��������		*/

//sfr ISP_TRIG  = 0xC6;
#define 	ISP_TRIG()	ISP_TRIG = 0x5A,	ISP_TRIG = 0xA5		/* ISP�������� */

//							  7    6    5      4    3    2    1     0    Reset Value
//sfr IAP_CONTR = 0xC7;		IAPEN SWBS SWRST CFAIL  -   WT2  WT1   WT0   0000,x000	//IAP Control Register
#define ISP_EN			(1<<7)
#define ISP_SWBS		(1<<6)
#define ISP_SWRST		(1<<5)
#define ISP_CMD_FAIL	(1<<4)
#define ISP_WAIT_1MHZ	7
#define ISP_WAIT_2MHZ	6
#define ISP_WAIT_3MHZ	5
#define ISP_WAIT_6MHZ	4
#define ISP_WAIT_12MHZ	3
#define ISP_WAIT_20MHZ	2
#define ISP_WAIT_24MHZ	1
#define ISP_WAIT_30MHZ	0

#if (MAIN_Fosc >= 24000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_30MHZ
#elif (MAIN_Fosc >= 20000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_24MHZ
#elif (MAIN_Fosc >= 12000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_20MHZ
#elif (MAIN_Fosc >= 6000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_12MHZ
#elif (MAIN_Fosc >= 3000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_6MHZ
#elif (MAIN_Fosc >= 2000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_3MHZ
#elif (MAIN_Fosc >= 1000000L)
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_2MHZ
#else
	#define		ISP_WAIT_FREQUENCY	ISP_WAIT_1MHZ
#endif



/* ADC Register */
//								7       6      5       4         3      2    1    0   Reset Value
//sfr ADC_CONTR = 0xBC;		ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	/* AD ת�����ƼĴ��� */ 
//sfr ADC_RES  = 0xBD;		ADCV.9 ADCV.8 ADCV.7 ADCV.6 ADCV.5 ADCV.4 ADCV.3 ADCV.2	  0000,0000	/* A/D ת�������8λ */ 
//sfr ADC_RESL = 0xBE;												  ADCV.1 ADCV.0	  0000,0000	/* A/D ת�������2λ */
//sfr ADC_CONTR  = 0xBC;	//ֱ����MOV��������Ҫ�����


//sfr SPCTL  = 0xCE;	SPI���ƼĴ���
//   7       6       5       4       3       2       1       0    	Reset Value
//	SSIG	SPEN	DORD	MSTR	CPOL	CPHA	SPR1	SPR0		0x00

#define	SPI_SSIG_None()		SPCTL |=  (1<<7)		/* 1: ����SS��	*/
#define	SPI_SSIG_Enable()	SPCTL &= ~(1<<7)		/* 0: SS�����ھ������ӻ�	*/
#define	SPI_Enable()		SPCTL |=  (1<<6)		/* 1: ����SPI	*/
#define	SPI_Disable()		SPCTL &= ~(1<<6)		/* 0: ��ֹSPI	*/
#define	SPI_LSB_First()		SPCTL |=  (1<<5)		/* 1: LSB�ȷ�	*/
#define	SPI_MSB_First()		SPCTL &= ~(1<<5)		/* 0: MSB�ȷ�	*/
#define	SPI_Master()		SPCTL |=  (1<<4)		/* 1: ��Ϊ����	*/
#define	SPI_Slave()			SPCTL &= ~(1<<4)		/* 0: ��Ϊ�ӻ�	*/
#define	SPI_SCLK_NormalH()	SPCTL |=  (1<<3)		/* 1: ����ʱSCLKΪ�ߵ�ƽ	*/
#define	SPI_SCLK_NormalL()	SPCTL &= ~(1<<3)		/* 0: ����ʱSCLKΪ�͵�ƽ	*/
#define	SPI_PhaseH()		SPCTL |=  (1<<2)		/* 1: 	*/
#define	SPI_PhaseL()		SPCTL &= ~(1<<2)		/* 0: 	*/
#define	SPI_Speed(n)		SPCTL = (SPCTL & ~3) | (n)	/*�����ٶ�, 0 -- fosc/4, 1 -- fosc/16, 2 -- fosc/64, 3 -- fosc/128	*/

//sfr SPDAT  = 0xCF; //SPI Data Register                                                     0000,0000
//sfr SPSTAT  = 0xCD;	//SPI״̬�Ĵ���
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		/* SPI������ɱ�־��д��1��0��*/
#define	WCOL	0x40		/* SPIд��ͻ��־��д��1��0��  */

#define		SPI_USE_P12P13P14P15()	AUXR1 &= ~0x0c					/* ��SPI�л���P12(SS) P13(MOSI) P14(MISO) P15(SCLK)(�ϵ�Ĭ��)��*/
#define		SPI_USE_P24P23P22P21()	AUXR1 = (AUXR1 & ~0x0c) | 0x04	/* ��SPI�л���P24(SS) P23(MOSI) P22(MISO) P21(SCLK)��*/
#define		SPI_USE_P54P40P41P43()	AUXR1 = (AUXR1 & ~0x0c) | 0x08	/* ��SPI�л���P54(SS) P40(MOSI) P41(MISO) P43(SCLK)��*/


/*
;PCA_PWMn:    7       6     5   4   3   2     1       0
;			EBSn_1	EBSn_0	-	-	-	-	EPCnH	EPCnL
;B5-B2:		����
;B1(EPCnH):	��PWMģʽ�£���CCAPnH���9λ����
;B0(EPCnL):	��PWMģʽ�£���CCAPnL���9λ����
*/
#define		PWM0_NORMAL()	PCA_PWM0 &= ~2					/* PWM0�������(Ĭ��)	*/
#define		PWM0_OUT_0()	PCA_PWM0 |=  2, CCAP0H = 0xff	/* PWM0һֱ���0		*/
#define		PWM0_OUT_1()	PCA_PWM0 &= ~2, CCAP0H = 0		/* PWM0һֱ���1		*/

#define		PWM1_NORMAL()	PCA_PWM1 &= ~2					/* PWM1�������(Ĭ��)	*/
#define		PWM1_OUT_0()	PCA_PWM1 |=  2, CCAP1H = 0xff	/* PWM1һֱ���0		*/
#define		PWM1_OUT_1()	PCA_PWM1 &= ~2, CCAP1H = 0		/* PWM1һֱ���1		*/

#define		PWM2_NORMAL()	PCA_PWM2 &= ~2					/* PWM2�������(Ĭ��)	*/
#define		PWM2_OUT_0()	PCA_PWM2 |=  2, CCAP2H = 0xff	/* PWM2һֱ���0		*/
#define		PWM2_OUT_1()	PCA_PWM2 &= ~2, CCAP2H = 0		/* PWM2һֱ���1		*/


//						7     6     5     4     3     2     1     0     Reset Value
//sfr CCON   = 0xD8;	CF    CR    -     -     -    CCF2  CCF1  CCF0   00xx,xx00	//PCA ���ƼĴ�����
sbit CCF0  = CCON^0;	/* PCA ģ��0�жϱ�־����Ӳ����λ�������������0��	*/
sbit CCF1  = CCON^1;	/* PCA ģ��1�жϱ�־����Ӳ����λ�������������0��	*/
sbit CCF2  = CCON^2;	/* PCA ģ��2�жϱ�־����Ӳ����λ�������������0��	*/
sbit CR    = CCON^6;	/* 1: ����PCA�����������������������0��*/
sbit CF    = CCON^7;	/* PCA�����������CH��CL��FFFFH��Ϊ0000H����־��PCA�������������Ӳ����λ�������������0��*/

//					 7     6     5     4     3     2     1     0    Reset Value
//sfr CMOD  = 0xD9;	CIDL   -     -     -   CPS2   CPS1  CPS0  ECF   0xxx,0000	//PCA ����ģʽ�Ĵ�����
#define PCA_IDLE_OFF()		CMOD |=  (1<<7)				/* IDLE״̬PCAֹͣ������	*/
#define PCA_IDLE_ON()		CMOD &= ~(1<<7)				/* IDLE״̬PCA����������	*/
#define PCA_CLK_12T()		CMOD &= ~0x0E				/* PCA��������ѡ�� fosc/12	*/
#define PCA_CLK_2T()		CMOD = (CMOD & ~0x0E) + 2	/* PCA��������ѡ�� fosc/2	*/
#define PCA_CLK_T0()		CMOD = (CMOD & ~0x0E) + 4	/* PCA��������ѡ��Timer0�жϣ�Timer0��ͨ��AUXR�Ĵ������óɹ�����12T��1Tģʽ��	*/
#define PCA_CLK_ECI()		CMOD = (CMOD & ~0x0E) + 6	/* PCA��������ѡ���ECI/P3.4��������ⲿʱ�ӣ���� fosc/2��	*/
#define PCA_CLK_1T()		CMOD = (CMOD & ~0x0E) + 8	/* PCA��������ѡ�� Fosc	*/
#define PCA_CLK_4T()		CMOD = (CMOD & ~0x0E) + 10	/* PCA��������ѡ�� Fosc/4	*/
#define PCA_CLK_6T()		CMOD = (CMOD & ~0x0E) + 12	/* PCA��������ѡ�� Fosc/6	*/
#define PCA_CLK_8T()		CMOD = (CMOD & ~0x0E) + 14	/* PCA��������ѡ�� Fosc/8	*/
#define PCA_INT_ENABLE()	CMOD |=  1					/* PCA����������ж�����λ��1---����CF��CCON.7�������жϡ�	*/
#define PCA_INT_DISABLE()	CMOD &= ~1					/* PCA����������жϽ�ֹ��	*/

//					    7      6       5        4       3       2       1      0    Reset Value
//sfr AUXR1 = 0xA2;	  S1_S1  S1_S0  CCP_S1   CCP_S0  SPI_S1   SPI_S0    -     DPS   0100,0000	//Auxiliary Register 1

#define		PCA_USE_P12P11P10P37()	AUXR1 &= ~0x30					/* ��PCA/PWM�л���P12(ECI) P11(CCP0) P10(CCP1) P37(CCP2)(�ϵ�Ĭ��)��	*/
#define		PCA_USE_P34P35P36P37()	AUXR1 = (AUXR1 & ~0x30) | 0x10	/* ��PCA/PWM�л���P34(ECI) P35(CCP0) P36(CCP1) P37(CCP2)��	*/
#define		PCA_USE_P24P25P26P27()	AUXR1 = (AUXR1 & ~0x30) | 0x20	/* ��PCA/PWM�л���P24(ECI) P25(CCP0) P26(CCP1) P27(CCP2)��	*/

#define		DPS_SEL1()		AUXR1 |=  1		/* 1��ѡ��DPTR1��	*/
#define		DPS_SEL0()		AUXR1 &= ~1		/* 0��ѡ��DPTR0(�ϵ�Ĭ��)��	*/


/*									7     6      5      4     3     2     1     0     Reset Value
//sfr CCAPM0 = 0xDA;	PWM �Ĵ���  -   ECOM0  CAPP0  CAPN0  MAT0  TOG0  PWM0  ECCF0   x000,0000	//PCA ģ��0
//sfr CCAPM1 = 0xDB;	PWM �Ĵ���  -   ECOM1  CAPP1  CAPN1  MAT1  TOG1  PWM1  ECCF1   x000,0000	//PCA ģ��1
//sfr CCAPM2 = 0xDC;	PWM �Ĵ���  -   ECOM2  CAPP2  CAPN2  MAT2  TOG2  PWM2  ECCF2   x000,0000	//PCA ģ��2
;ECOMn = 1:	����ȽϹ��ܡ�
;CAPPn = 1:	���������ش�����׽���ܡ�
;CAPNn = 1:	�����½��ش�����׽���ܡ�
;MATn  = 1:	��ƥ���������ʱ������CCON�е�CCFn��λ��
;TOGn  = 1:	��ƥ���������ʱ��CEXn����ת��(CEX0/PCA0/PWM0/P3.7,CEX1/PCA1/PWM1/P3.5)
;PWMn  = 1:	��CEXn����ΪPWM�����
;ECCFn = 1:	����CCON�е�CCFn�����жϡ�
;ECOMn CAPPn CAPNn MATn TOGn PWMn ECCFn
;  0     0     0    0    0    0     0		00H	δ�����κι��ܡ�
;  x     1     0    0    0    0     x	 	20H	16λCEXn�����ش�����׽���ܡ�
;  x     0     1    0    0    0     x	 	10H	16λCEXn�½��ش�����׽���ܡ�
;  x     1     1    0    0    0     x	 	30H	16λCEXn/PCAn���أ��ϡ����أ�������׽���ܡ�
;  1     0     0    1    0    0     x	 	48H	16λ�����ʱ����
;  1     0     0    1    1    0     x	 	4CH	16λ�������������
;  1     0     0    0    0    1     0		42H	8λPWM�����ж�
;  1     1     0    0    0    1     1		63H	8λPWM���ͱ�߿ɲ����ж�
;  1     0     1    0    0    1     1		53H	8λPWM���߱�Ϳɲ����ж�
;  1     1     1    0    0    1     1		73H	8λPWM���ͱ�߻�߱�;��ɲ����ж�
;*******************************************************************
;*******************************************************************/
#define		PCA0_none()				CCAPM0 = 0
#define		PCA0_PWM(nbit)			CCAPM0 = 0x42,PCA_PWM0 = (PCA_PWM0 & 0x0c) | ((8-nbit)<<6)
#define		PCA0_PWM_rise_int(nbit) CCAPM0 = 0x63,PCA_PWM0 = (PCA_PWM0 & 0x0c) | ((8-nbit)<<6)
#define		PCA0_PWM_fall_int(nbit) CCAPM0 = 0x53,PCA_PWM0 = (PCA_PWM0 & 0x0c) | ((8-nbit)<<6)
#define		PCA0_PWM_edge_int(nbit) CCAPM0 = 0x73,PCA_PWM0 = (PCA_PWM0 & 0x0c) | ((8-nbit)<<6)
#define		PCA0_capture_rise()		CCAPM0 = (0x20 + 1)
#define		PCA0_capture_fall()		CCAPM0 = (0x10 + 1)
#define		PCA0_capture_edge()		CCAPM0 = (0x30 + 1)
#define		PCA0_16bit_Timer()		CCAPM0 = (0x48 + 1)
#define		PCA0_High_Pulse()		CCAPM0 = (0x4C + 1)

#define		PCA1_none()				CCAPM1 = 0
#define		PCA1_PWM(nbit)			CCAPM1 = 0x42,PCA_PWM1 = (PCA_PWM1 & 0x0c) | ((8-nbit)<<6)
#define		PCA1_PWM_rise_int(nbit) CCAPM1 = 0x63,PCA_PWM1 = (PCA_PWM1 & 0x0c) | ((8-nbit)<<6)
#define		PCA1_PWM_fall_int(nbit) CCAPM1 = 0x53,PCA_PWM1 = (PCA_PWM1 & 0x0c) | ((8-nbit)<<6)
#define		PCA1_PWM_edge_int(nbit) CCAPM1 = 0x73,PCA_PWM1 = (PCA_PWM1 & 0x0c) | ((8-nbit)<<6)
#define		PCA1_capture_rise()		CCAPM1 = (0x20 + 1)
#define		PCA1_capture_fall()		CCAPM1 = (0x10 + 1)
#define		PCA1_capture_edge()		CCAPM1 = (0x30 + 1)
#define		PCA1_16bit_Timer()		CCAPM1 = (0x48 + 1)
#define		PCA1_High_Pulse()		CCAPM1 = (0x4C + 1)

#define		PCA2_none()				CCAPM2 = 0
#define		PCA2_PWM(nbit)			CCAPM2 = 0x42,PCA_PWM2 = (PCA_PWM2 & 0x0c) | ((8-nbit)<<6)
#define		PCA2_PWM_rise_int(nbit) CCAPM2 = 0x63,PCA_PWM2 = (PCA_PWM2 & 0x0c) | ((8-nbit)<<6)
#define		PCA2_PWM_fall_int(nbit) CCAPM2 = 0x53,PCA_PWM2 = (PCA_PWM2 & 0x0c) | ((8-nbit)<<6)
#define		PCA2_PWM_edge_int(nbit) CCAPM2 = 0x73,PCA_PWM2 = (PCA_PWM2 & 0x0c) | ((8-nbit)<<6)
#define		PCA2_capture_rise()		CCAPM2 = (0x20 + 1)
#define		PCA2_capture_fall()		CCAPM2 = (0x10 + 1)
#define		PCA2_capture_edge()		CCAPM2 = (0x30 + 1)
#define		PCA2_16bit_Timer()		CCAPM2 = (0x48 + 1)
#define		PCA2_High_Pulse()		CCAPM2 = (0x4C + 1)

/* Above is STC additional SFR or change */




/**********************************************************/
typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

/**********************************************************/
#define NOP1()  _nop_()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N()


/**********************************************/
#define P0n_standard(bitn)			P0M1 &= ~(bitn),	P0M0 &= ~(bitn)	/* 00  */
#define P0n_push_pull(bitn)			P0M1 &= ~(bitn),	P0M0 |=  (bitn)	/* 01  */
#define P0n_pure_input(bitn)		P0M1 |=  (bitn),	P0M0 &= ~(bitn)	/* 10  */
#define P0n_open_drain(bitn)		P0M1 |=  (bitn),	P0M0 |=  (bitn)	/* 11  */

#define P1n_standard(bitn)			P1M1 &= ~(bitn),	P1M0 &= ~(bitn)
#define P1n_push_pull(bitn)			P1M1 &= ~(bitn),	P1M0 |=  (bitn)
#define P1n_pure_input(bitn)		P1M1 |=  (bitn),	P1M0 &= ~(bitn)
#define P1n_open_drain(bitn)		P1M1 |=  (bitn),	P1M0 |=  (bitn)

#define P2n_standard(bitn)			P2M1 &= ~(bitn),	P2M0 &= ~(bitn)
#define P2n_push_pull(bitn)			P2M1 &= ~(bitn),	P2M0 |=  (bitn)
#define P2n_pure_input(bitn)		P2M1 |=  (bitn),	P2M0 &= ~(bitn)
#define P2n_open_drain(bitn)		P2M1 |=  (bitn),	P2M0 |=  (bitn)

#define P3n_standard(bitn)			P3M1 &= ~(bitn),	P3M0 &= ~(bitn)
#define P3n_push_pull(bitn)			P3M1 &= ~(bitn),	P3M0 |=  (bitn)
#define P3n_pure_input(bitn)		P3M1 |=  (bitn),	P3M0 &= ~(bitn)
#define P3n_open_drain(bitn)		P3M1 |=  (bitn),	P3M0 |=  (bitn)

#define P4n_standard(bitn)			P4M1 &= ~(bitn),	P4M0 &= ~(bitn)
#define P4n_push_pull(bitn)			P4M1 &= ~(bitn),	P4M0 |=  (bitn)
#define P4n_pure_input(bitn)		P4M1 |=  (bitn),	P4M0 &= ~(bitn)
#define P4n_open_drain(bitn)		P4M1 |=  (bitn),	P4M0 |=  (bitn)

#define P5n_standard(bitn)			P5M1 &= ~(bitn),	P5M0 &= ~(bitn)
#define P5n_push_pull(bitn)			P5M1 &= ~(bitn),	P5M0 |=  (bitn)
#define P5n_pure_input(bitn)		P5M1 |=  (bitn),	P5M0 &= ~(bitn)
#define P5n_open_drain(bitn)		P5M1 |=  (bitn),	P5M0 |=  (bitn)

#define P6n_standard(bitn)			P6M1 &= ~(bitn),	P6M0 &= ~(bitn)
#define P6n_push_pull(bitn)			P6M1 &= ~(bitn),	P6M0 |=  (bitn)
#define P6n_pure_input(bitn)		P6M1 |=  (bitn),	P6M0 &= ~(bitn)
#define P6n_open_drain(bitn)		P6M1 |=  (bitn),	P6M0 |=  (bitn)

#define P7n_standard(bitn)			P7M1 &= ~(bitn),	P7M0 &= ~(bitn)
#define P7n_push_pull(bitn)			P7M1 &= ~(bitn),	P7M0 |=  (bitn)
#define P7n_pure_input(bitn)		P7M1 |=  (bitn),	P7M0 &= ~(bitn)
#define P7n_open_drain(bitn)		P7M1 |=  (bitn),	P7M0 |=  (bitn)


/****************************************************************/


//sfr INT_CLKO = 0x8F;	//���ӵ� SFR WAKE_CLKO (��ַ��0x8F)
/*
    7   6    5    4   3     2        1       0         Reset Value
    -  EX4  EX3  EX2  -   T2CLKO   T1CLKO  T0CLKO      0000,0000B
b6 -  EX4      : ���ж�INT4����
b5 -  EX3      : ���ж�INT3����
b4 -  EX2      : ���ж�INT2����
b2 - T1CLKO    : ���� T2 ���������P3.0�������Fck1 = 1/2 T1 �����
b1 - T1CLKO    : ���� T1 ���������P3.4�������Fck1 = 1/2 T1 �����
b0 - T0CLKO    : ���� T0 ���������P3.5�������Fck0 = 1/2 T0 �����
*/

#define		LVD_InterruptEnable()		ELVD = 1
#define		LVD_InterruptDisable()		ELVD = 0


//sfr WKTCL = 0xAA;	//STC11F\10��STC15ϵ�� ���Ѷ�ʱ�����ֽ�
//sfr WKTCH = 0xAB;	//STC11F\10��STC15ϵ�� ���Ѷ�ʱ�����ֽ�
//	B7		B6	B5	B4	B3	B2	B1	B0		B7	B6	B5	B4	B3	B2	B1	B0
//	WKTEN				S11	S10	S9	S8		S7	S6	S5	S4	S3	S2	S1	S0	n * 560us
#define		WakeTimerDisable()		WKTCH &= 0x7f	/* WKTEN = 0		��ֹ˯�߻��Ѷ�ʱ�� */
#define		WakeTimerSet(scale)		WKTCL = (scale) % 256,WKTCH = (scale) / 256 | 0x80	/* WKTEN = 1	����˯�߻��Ѷ�ʱ�� */


//sfr CLK_DIV = 0x97; //Clock Divder ϵͳʱ�ӷ�Ƶ  -     -      -       -     -  CLKS2 CLKS1 CLKS0 xxxx,x000
#define		SYSTEM_CLK_1T()		CLK_DIV &= ~0x07	//default
#define		SYSTEM_CLK_2T()		CLK_DIV = (CLK_DIV & ~0x07) | 1
#define		SYSTEM_CLK_4T()		CLK_DIV = (CLK_DIV & ~0x07) | 2
#define		SYSTEM_CLK_8T()		CLK_DIV = (CLK_DIV & ~0x07) | 3
#define		SYSTEM_CLK_16T()	CLK_DIV = (CLK_DIV & ~0x07) | 4
#define		SYSTEM_CLK_32T()	CLK_DIV = (CLK_DIV & ~0x07) | 5
#define		SYSTEM_CLK_64T()	CLK_DIV = (CLK_DIV & ~0x07) | 6
#define		SYSTEM_CLK_128T()	CLK_DIV =  CLK_DIV          | 7

#define		MCLKO_P54_None()	CLK_DIV &= ~0xc0					/* ��ʱ�Ӳ���� 	*/
#define		MCLKO_P54_DIV1()	CLK_DIV  = (CLK_DIV & ~0xc0) | 0x40	/* ��ʱ�Ӳ���Ƶ��� */
#define		MCLKO_P54_DIV2()	CLK_DIV  = (CLK_DIV & ~0xc0) | 0x80	/* ��ʱ��2��Ƶ���  */
#define		MCLKO_P54_DIV4()	CLK_DIV  =  CLK_DIV | 0xc0			/* ��ʱ��4��Ƶ���  */

#define		MCLKO_P34_None()	CLK_DIV &= ~0xc0					/* ��ʱ�Ӳ���� 	*/
#define		MCLKO_P34_DIV1()	CLK_DIV  = (CLK_DIV & ~0xc0) | 0x40	/* ��ʱ�Ӳ���Ƶ��� */
#define		MCLKO_P34_DIV2()	CLK_DIV  = (CLK_DIV & ~0xc0) | 0x80	/* ��ʱ��2��Ƶ���  */
#define		MCLKO_P34_DIV4()	CLK_DIV  =  CLK_DIV | 0xc0			/* ��ʱ��4��Ƶ���  */

//sfr BUS_SPEED = 0xA1; //Stretch register      -   -  -  -   -   -  EXRTS1  EXRTSS0 xxxx,xx10
#define		BUS_SPEED_1T()	BUS_SPEED = 0
#define		BUS_SPEED_2T()	BUS_SPEED = 1
#define		BUS_SPEED_4T()	BUS_SPEED = 2
#define		BUS_SPEED_8T()	BUS_SPEED = 3

/*   interrupt vector */
#define		INT0_VECTOR		0
#define		TIMER0_VECTOR	1
#define		INT1_VECTOR		2
#define		TIMER1_VECTOR	3
#define		UART1_VECTOR	4
#define		ADC_VECTOR		5
#define		LVD_VECTOR		6
#define		PCA_VECTOR		7
#define		UART2_VECTOR	8
#define		SPI_VECTOR		9
#define		INT2_VECTOR		10
#define		INT3_VECTOR		11
#define		TIMER2_VECTOR	12
#define		INT4_VECTOR		16
#define		UART3_VECTOR	17
#define		UART4_VECTOR	18
#define		TIMER3_VECTOR	19
#define		TIMER4_VECTOR	20
#define		CMP_VECTOR		21
#define		PWM_VECTOR		22
#define		PWMFD_VECTOR	23


#define	TRUE	1
#define	FALSE	0

//=============================================================

//========================================

#define	PolityLow			0	//�����ȼ��ж�
#define	PolityHigh			1	//�����ȼ��ж�

//========================================

#define		MCLKO_None	0
#define		MCLKO_DIV1	1
#define		MCLKO_DIV2	2
#define		MCLKO_DIV4	3

#define		ENABLE		1
#define		DISABLE		0

#define		STC15F_L2K08S2	8
#define		STC15F_L2K16S2	16
#define		STC15F_L2K24S2	24
#define		STC15F_L2K32S2	32
#define		STC15F_L2K40S2	40
#define		STC15F_L2K48S2	48
#define		STC15F_L2K56S2	56
#define		STC15F_L2K60S2	60
#define		IAP15F_L2K61S2	61

#endif

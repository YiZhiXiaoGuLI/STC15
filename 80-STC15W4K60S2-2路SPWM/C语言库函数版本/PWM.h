
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


#ifndef	__PWM_H
#define	__PWM_H

#include	"config.h"

#define		PWM_DeadZone	12	/* ����ʱ����, 6 ~ 24֮��  */

typedef struct
{ 
	u8	id;				//���ں�

	u8	TX_read;		//���Ͷ�ָ��
	u8	TX_write;		//����дָ��
	u8	B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
	u8	B_RX_OK;		//���տ����
} PWMx_Define; 

typedef struct
{
	u16	FirstEdge;				// ��һ����ת����, 1~32767
	u16	SecondEdge;				// �ڶ�����ת����, 1~32767
	u8	Start_IO_Level;			// ����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	u8	PWMx_IO_Select;			// PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	u8	PWMx_Interrupt;			// �ж�����,   ENABLE,DISABLE
	u8	FirstEdge_Interrupt;	// ��һ����ת�ж�����, ENABLE,DISABLE
	u8	SecondEdge_Interrupt;	// �ڶ�����ת�ж�����, ENABLE,DISABLE
} PWMx_InitDefine; 


void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty);
void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx);
void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge);


#endif

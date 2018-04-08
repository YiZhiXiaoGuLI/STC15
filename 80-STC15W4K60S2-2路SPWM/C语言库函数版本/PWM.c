
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


/*************	����˵��	**************

���ļ�ΪSTC15W4Kϵ�е�PWM����.

******************************************/

#include	"PWM.h"
#include	"T_SineTable.h"

u8	PWM_Index;	//SPWM�������

//========================================================================
// ����: void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
// ����: ����PWMʱ��Դ�����ں�����
// ����: PWM_SourceClk: PWMʱ��Դ, 0~15��Ӧ ��ʱ��/(PWM_SourceClk + 1), 16Ϊѡ��ʱ��2�������ʱ��.
//                      PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_Timer2.
//       init_duty: PWM���ڳ���, 1~32767.
// ����: none.
// �汾: VER1.0
// ����: 2014-8-15
// ��ע: 
//========================================================================
void	PWM_SourceClk_Duty(u8 PWM_SourceClk, u16 init_duty)
{
	u8	xdata	*px;

	EAXSFR();		// ����XFR
	px  = PWMCH;	// PWM�������ĸ��ֽ�
	*px = (u8)(init_duty >> 8);
	px++;
	*px = (u8)init_duty;	// PWM�������ĵ��ֽ�
	px++;			// PWMCKS, PWMʱ��ѡ��
	*px = PWM_SourceClk;
	EAXRAM();	//�ָ�����XRAM
}


//========================================================================
// ����: void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
// ����: PWM���ú�����
// ����: PWM_id: PWMͨ��, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
//       *PWMx:  ���ýṹָ��.
// ����: none.
// �汾: VER1.0
// ����: 2014-8-15
// ��ע: 
//========================================================================
void	PWMx_Configuration(u8 PWM_id, PWMx_InitDefine *PWMx)
{
	u8	xdata	*px;

	EAXSFR();		//����XFR
	px = PWM2T1H + (PWM_id << 4);
	*px = (u8)(PWMx->FirstEdge >> 8);	//��һ����ת�������ֽ�
	px++;
	*px = (u8)PWMx->FirstEdge;			//��һ����ת�������ֽ�
	px++;
	*px = (u8)(PWMx->SecondEdge >> 8);	//�ڶ�����ת�������ֽ�
	px++;
	*px = (u8)PWMx->SecondEdge;			//�ڶ�����ת�������ֽ�
	px++;
	*px = (PWMx->PWMx_IO_Select & 0x08)					// PWM���IOѡ��
	    | ((PWMx->PWMx_Interrupt << 2) & 0x04)			// �ж�����
		| ((PWMx->SecondEdge_Interrupt << 1) & 0x02)	// �ڶ�����ת�ж�����
		| (PWMx->FirstEdge_Interrupt & 0x01);			// ��һ����ת�ж�����
	PWMCR |= (1 << PWM_id);	// ��ӦPWMͨ���Ķ˿�ΪPWM����ڣ���PWM���η���������
	PWMCFG = (PWMCFG & ~(1 << PWM_id)) | ((PWMx->Start_IO_Level & 1) << PWM_id);	//����PWM����˿ڵĳ�ʼ��ƽ
	EAXRAM();		//�ָ�����XRAM
}

//========================================================================
// ����: void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge)
// ����: PWM���������Ⱥ�����
// ����: PWM_id: PWMͨ��, PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID.
//       FirstEdge:   ��һ����ת����.
//       SecondEdge:  ��һ����ת����.
// ����: none.
// �汾: VER1.0
// ����: 2014-8-15
// ��ע: 
//========================================================================
/*
void	PWMx_SetPwmWide(u8 PWM_id, u16 FirstEdge, u16 SecondEdge)
{
	u8	xdata	*px;

	EAXSFR();		//����XFR
	px = PWM2T1H + (PWM_id << 4);
	*px = (u8)(FirstEdge >> 8);	//��һ����ת�������ֽ�
	px++;
	*px = (u8)FirstEdge;			//��һ����ת�������ֽ�
	px++;
	*px = (u8)(SecondEdge >> 8);	//�ڶ�����ת�������ֽ�
	px++;
	*px = (u8)SecondEdge;			//�ڶ�����ת�������ֽ�
	EAXRAM();		//�ָ�����XRAM
}
*/

/********************* PWM�жϺ���************************/
void PWM_int (void) interrupt PWM_VECTOR
{
	u8	xdata	*px;
	u16	j;
	u8	SW2_tmp;


	if(PWMIF & CBIF)	//PWM�����������жϱ�־
	{
		PWMIF &= ~CBIF;	//����жϱ�־

		SW2_tmp = P_SW2;	//����SW2����
		EAXSFR();		//����XFR
		px = PWM3T2H;	// ָ��PWM3
		j = T_SinTable[PWM_Index];
		*px = (u8)(j >> 8);		//�ڶ�����ת�������ֽ�
		px++;
		*px = (u8)j;			//�ڶ�����ת�������ֽ�

		j += PWM_DeadZone;		//����
		px = PWM4T2H;			// ָ��PWM4
		*px = (u8)(j >> 8);		//�ڶ�����ת�������ֽ�
		px++;
		*px = (u8)j;			//�ڶ�����ת�������ֽ�
		P_SW2 = SW2_tmp;	//�ָ�SW2����

		if(++PWM_Index >= 200)	PWM_Index = 0;
		EAXRAM();		//�ָ�����XRAM

	}
/*
	if(PWMIF & C2IF)	//PWM2�жϱ�־
	{
		PWMIF &= ~C2IF;	//����жϱ�־
	}

	if(PWMIF & C3IF)	//PWM3�жϱ�־
	{
		PWMIF &= ~C3IF;	//����жϱ�־
	}

	if(PWMIF & C4IF)	//PWM4�жϱ�־
	{
		PWMIF &= ~C4IF;	//����жϱ�־
	}

	if(PWMIF & C5IF)	//PWM5�жϱ�־
	{
		PWMIF &= ~C5IF;	//����жϱ�־
	}

	if(PWMIF & C6IF)	//PWM6�жϱ�־
	{
		PWMIF &= ~C6IF;	//����жϱ�־
	}

	if(PWMIF & C7IF)	//PWM7�жϱ�־
	{
		PWMIF &= ~C7IF;	//����жϱ�־
	}
*/
}

/********************* PWMʧЧ�жϺ���************************/
void PWMFD_int (void) interrupt PWMFD_VECTOR
{
	if(PWMFDCR & FDIF) 		//PWM�쳣����жϱ�־λ
	{
		PWMFDCR &= ~FDIF;	//����жϱ�־
	}
}



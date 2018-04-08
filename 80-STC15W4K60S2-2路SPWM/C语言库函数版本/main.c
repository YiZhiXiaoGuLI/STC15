
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


#include	"config.h"
#include	"PWM.h"


/*************	����˵��	**************

��ʾʹ��2·PWM����������ͬ���SPWM.

��ʱ��ѡ��24MHZ, PWMʱ��ѡ��1T, PWM����2400, ����12��ʱ��(0.5us).���Ҳ�����200��. 

������Ҳ�Ƶ�� = 24000000 / 2400 / 200 = 50 HZ.

�����������һ��SPWM����ʾ����, �û�����ͨ������ļ��㷽���޸�PWM���ں����Ҳ��ĵ����ͷ���.

���������Ƶ�ʹ̶�, �����Ҫ��Ƶ, ���û��Լ���Ʊ�Ƶ����.

�������P2.1(PWM3)�����������, ��P2.2(PWM4)�����������(����).

�����ҪP2.2���ͬ���, ���ڳ�ʼ��������"Start_IO_Level"��ѡ��0(����PWM����˿ڵĳ�ʼ��ƽ, 0��1).


�����ļ�:
delay.c
pwm.c
main.c

******************************************/

/*************	���س�������	**************/


/*************	���ر�������	**************/


/*************	���غ�������	**************/



/*************  �ⲿ�����ͱ������� *****************/



//========================================================================
// ����: void	PWM_config(void)
// ����: PWM���ú�����
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2014-8-15
// ��ע: 
//========================================================================
void	PWM_config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;					//�ṹ����
	
	PWMx_InitStructure.PWMx_IO_Select       = PWM3_P21;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 0;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 65;			//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 1220;			//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM3_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P21 = 0;
	P2n_push_pull(1<<1);									//IO��ʼ��, �ϵ�ʱΪ����

	PWMx_InitStructure.PWMx_IO_Select       = PWM4_P22;		//PWM���IOѡ��. PWM2_P37,PWM2_P27,PWM3_P21,PWM3_P45,PWM4_P22,PWM4_P44,PWM5_P23,PWM5_P42,PWM6_P16,PWM6_P07,PWM7_P17,PWM7_P06
	PWMx_InitStructure.Start_IO_Level       = 1;			//����PWM����˿ڵĳ�ʼ��ƽ, 0��1
	PWMx_InitStructure.PWMx_Interrupt       = DISABLE;		//�ж�����,   			ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge_Interrupt  = DISABLE;		//��һ����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.SecondEdge_Interrupt = DISABLE;		//�ڶ�����ת�ж�����,   ENABLE��DISABLE
	PWMx_InitStructure.FirstEdge            = 65-PWM_DeadZone;	//��һ����ת����, 1~32767
	PWMx_InitStructure.SecondEdge           = 1220+PWM_DeadZone;//�ڶ�����ת����, 1~32767
	PWMx_Configuration(PWM4_ID, &PWMx_InitStructure);		//��ʼ��PWM, 	PWM2_ID,PWM3_ID,PWM4_ID,PWM5_ID,PWM6_ID,PWM7_ID
	P22 = 1;
	P2n_push_pull(1<<2);									//IO��ʼ��, �ϵ�ʱΪ����

	PWM_SourceClk_Duty(PwmClk_1T, 2400);	//ʱ��Դ: PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_Timer2,   PWM����: 1~32767
	
	PWMCR |= ENPWM;		// ʹ��PWM���η�������PWM��������ʼ����
//	PWMCR &= ~ECBI;		//��ֹPWM�����������ж�
	PWMCR |=  ECBI;		//����PWM�����������ж�

//	PWMFDCR = ENFD | FLTFLIO | FDIO;	//PWMʧЧ�жϿ���,  ENFD | FLTFLIO | EFDI | FDCMP | FDIO
}


/**********************************************/
void main(void)
{
	
	PWM_config();	//��ʼ��PWM

	EA = 1;			//����ȫ���ж�

	while (1)
	{
		
	}
}




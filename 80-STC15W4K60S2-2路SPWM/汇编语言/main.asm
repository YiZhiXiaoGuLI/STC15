
;*------------------------------------------------------------------*/
;* --- STC MCU International Limited -------------------------------*/
;* --- STC 1T Series MCU RC Demo -----------------------------------*/
;* --- Mobile: (86)13922805190 -------------------------------------*/
;* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
;* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
;* --- Web: www.GXWMCU.com -----------------------------------------*/
;* --- QQ:  800003751 ----------------------------------------------*/
;* If you want to use the program or the program referenced in the  */
;* article, please specify in which data and procedures from STC    */
;*------------------------------------------------------------------*/


PWM_DeadZone	EQU	12	; ����ʱ����, 6 ~ 24֮��


;*************	����˵��	**************

;��ʾʹ��2·PWM����������ͬ���SPWM.

;��ʱ��ѡ��24MHZ, PWMʱ��ѡ��1T, PWM����2400, ����12��ʱ��(0.5us).���Ҳ�����200��. 

;������Ҳ�Ƶ�� = 24000000 / 2400 / 200 = 50 HZ.

;�����������һ��SPWM����ʾ����, �û�����ͨ������ļ��㷽���޸�PWM���ں����Ҳ��ĵ����ͷ���.

;���������Ƶ�ʹ̶�, �����Ҫ��Ƶ, ���û��Լ���Ʊ�Ƶ����.

;�������P2.1(PWM3)�����������, ��P2.2(PWM4)�����������(����).

;�����ҪP2.2���ͬ���, ���ڳ�ʼ��������"PWMCFG"��ѡ������1(����PWM����˿ڵĳ�ʼ��ƽ, 0��1).

;******************************************/

P2M1     DATA 0x95;	//P2M1.n,P2M0.n 	=00--->Standard,	01--->push-pull
P2M0     DATA 0x96;	//					=10--->pure input,	11--->open drain
P_SW2    DATA 0xBA;
PWMCFG   DATA 0xF1;	//PWM���üĴ���
PWMCR    DATA 0xF5;	//PWM���ƼĴ���
PWMIF    DATA 0xF6;	//PWM�жϱ�־�Ĵ���
PWMFDCR  DATA 0xF7;	//PWM�ⲿ�쳣���ƼĴ���


PWMCH		EQU		0xFFF0	/* PWM���������ֽ�  */
PWMCL		EQU		0xFFF1	/* PWM���������ֽ�  */
PWMCKS		EQU		0xFFF2	/* PWMʱ��ѡ��      */
					
PWM2T1H		EQU		0xFF00	/* PWM2T1�������ֽ� */
PWM2T1L		EQU		0xFF01	/* PWM2T1�������ֽ� */
PWM2T2H		EQU		0xFF02	/* PWM2T2�������ֽ� */
PWM2T2L		EQU		0xFF03	/* PWM2T2�������ֽ� */
PWM2CR		EQU		0xFF04	/* PWM2����         */
					
PWM3T1H		EQU		0xFF10	/* PWM3T1�������ֽ� */
PWM3T1L		EQU		0xFF11	/* PWM3T1�������ֽ� */
PWM3T2H		EQU		0xFF12	/* PWM3T2�������ֽ� */
PWM3T2L		EQU		0xFF13	/* PWM3T2�������ֽ� */
PWM3CR		EQU		0xFF14	/* PWM3����         */

PWM4T1H		EQU		0xFF20	/* PWM4T1�������ֽ� */
PWM4T1L		EQU		0xFF21	/* PWM4T1�������ֽ� */
PWM4T2H		EQU		0xFF22	/* PWM4T2�������ֽ� */
PWM4T2L		EQU		0xFF23	/* PWM4T2�������ֽ� */
PWM4CR		EQU		0xFF24	/* PWM4����         */

PWM5T1H		EQU		0xFF30	/* PWM5T1�������ֽ� */
PWM5T1L		EQU		0xFF31	/* PWM5T1�������ֽ� */
PWM5T2H		EQU		0xFF32	/* PWM5T2�������ֽ� */
PWM5T2L		EQU		0xFF33	/* PWM5T2�������ֽ� */
PWM5CR		EQU		0xFF34	/* PWM5����         */

PWM6T1H		EQU		0xFF40	/* PWM6T1�������ֽ� */
PWM6T1L		EQU		0xFF41	/* PWM6T1�������ֽ� */
PWM6T2H		EQU		0xFF42	/* PWM6T2�������ֽ� */
PWM6T2L		EQU		0xFF43	/* PWM6T2�������ֽ� */
PWM6CR		EQU		0xFF44	/* PWM6����         */

PWM7T1H		EQU		0xFF50	/* PWM7T1�������ֽ� */
PWM7T1L		EQU		0xFF51	/* PWM7T1�������ֽ� */
PWM7T2H		EQU		0xFF52	/* PWM7T2�������ֽ� */
PWM7T2L		EQU		0xFF53	/* PWM7T2�������ֽ� */
PWM7CR		EQU		0xFF54	/* PWM7����         */

PwmClk_1T		EQU		0
PwmClk_2T		EQU		1
PwmClk_3T		EQU		2
PwmClk_4T		EQU		3
PwmClk_5T		EQU		4
PwmClk_6T		EQU		5
PwmClk_7T		EQU		6
PwmClk_8T		EQU		7
PwmClk_9T		EQU		8
PwmClk_10T		EQU		9
PwmClk_11T		EQU		10
PwmClk_12T		EQU		11
PwmClk_13T		EQU		12
PwmClk_14T		EQU		13
PwmClk_15T		EQU		14
PwmClk_16T		EQU		15
PwmClk_Timer2	EQU		16


;*******************************************************************
;*******************************************************************
PWM_Index		DATA	30H		; SPWM�������

STACK_POIRTER	EQU		0C0H	;��ջ��ʼ��ַ


;*******************************************************************
;*******************************************************************
		ORG		00H				;reset
		LJMP	F_Main

		ORG		00B3H			; PWM interrupt
		LJMP	F_PWM_Interrupt


;******************** ������ **************************/
F_Main:
	
	MOV		SP, #STACK_POIRTER
	MOV		PSW, #0
	USING	0		;ѡ���0��R0~R7

;================= �û���ʼ������ ====================================
	ORL		P_SW2, #0x80	; ����XFR

	MOV		DPTR, #PWM3T1H	; ָ��ָ��PWM3
	CLR		A
	MOVX	@DPTR, A		; ��һ����ת�������ֽ�
	INC		DPTR
	MOV		A, #65			; ��һ����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #HIGH 1220	; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #LOW 1220	; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A

	INC		DPTR
	CLR		A					; PWM3���ѡ��P2.1, ���ж�
	MOVX	@DPTR, A
	ORL		PWMCR, #0x02		; ��ӦPWMͨ���Ķ˿�ΪPWM����ڣ���PWM���η���������
	ANL		PWMCFG, #NOT 0x02	; ����PWM����˿ڵĳ�ʼ��ƽΪ0
;	ORL		PWMCFG, #0x02		; ����PWM����˿ڵĳ�ʼ��ƽΪ1
	CLR		P2.1				; P2.1����͵�ƽ
	ANL		P2M1, #NOT 0x02		; P2.1����Ϊ�������
	ORL		P2M0, #0x02

	MOV		DPTR, #PWM4T1H	; ָ��ָ��PWM4
	CLR		A
	MOVX	@DPTR, A		; ��һ����ת�������ֽ�
	INC		DPTR
	MOV		A, #(65-PWM_DeadZone)	; ��һ����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #HIGH (1220+PWM_DeadZone)	; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #LOW (1220+PWM_DeadZone)		; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A

	INC		DPTR
	CLR		A					; PWM4���ѡ��P2.2, ���ж�
	MOVX	@DPTR, A
	ORL		PWMCR, #0x04		; ��ӦPWMͨ���Ķ˿�ΪPWM����ڣ���PWM���η���������
	ANL		PWMCFG, #NOT 0x04	; ����PWM����˿ڵĳ�ʼ��ƽΪ0
;	ORL		PWMCFG, #0x04		; ����PWM����˿ڵĳ�ʼ��ƽΪ1
	SETB	P2.2				; P2.2����ߵ�ƽ
	ANL		P2M1, #NOT 0x04		; P2.2����Ϊ�������
	ORL		P2M0, #0x04

	MOV		DPTR, #PWMCH		; ָ��ָ��PWMCH
	MOV		A, #HIGH 2400		; PWM�������ĸ��ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #LOW 2400		; PWM�������ĵ��ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, #PwmClk_1T		; ʱ��Դ: PwmClk_1T,PwmClk_2T, ... PwmClk_16T, PwmClk_Timer2
	MOVX	@DPTR, A			; PWMCKS, PWMʱ��ѡ��

	ANL		P_SW2, #NOT 0x80	; �ָ�����XRAM
	
	ORL		PWMCR, #0xC0		; ����PWM�����������ж�, ʹ��PWM���η�������PWM��������ʼ����

;	MOV		PWMFDCR, # (ENFD + FLTFLIO + FDIO) ; PWMʧЧ�жϿ���,  ENFD | FLTFLIO | EFDI | FDCMP | FDIO

	SETB	EA		; ����ȫ���ж�
	

;=================== ��ѭ�� ==================================
L_MainLoop:

	LJMP	L_MainLoop
;===================================================================



;********************* PWM�жϺ���************************/

F_PWM_Interrupt:
	PUSH	PSW
	PUSH	ACC
	PUSH	DPH
	PUSH	DPL
	PUSH	AR2
	PUSH	AR3

	MOV		DPTR, #T_SinTable	; �����Ҳ���
	MOV		A, PWM_Index
	ADD		A, DPL
	MOV		DPL, A
	CLR		A
	ADDC	A, DPH
	MOV		DPH, A
	MOV		A, PWM_Index
	ADD		A, DPL
	MOV		DPL, A
	CLR		A
	ADDC	A, DPH
	MOV		DPH, A
	CLR		A
	MOVC	A, @A+DPTR
	MOV		R2, A
	MOV		A, #1
	MOVC	A, @A+DPTR
	MOV		R3, A
	
	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.6, L_Int_NotCBIF	; PWM�����������жϱ�־
	ANL		PWMIF, #NOT (1 SHL 6)	; ����жϱ�־
	PUSH	P_SW2			; ����SW2����
	ORL		P_SW2, #0x80	; ����XFR
	MOV		DPTR, #PWM3T2H	; ָ��ָ��PWM3
	MOV		A, R2			; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, R3			; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	
	MOV		A, R3
	ADD		A, #PWM_DeadZone	; ������
	MOV		R3, A
	CLR		A
	ADDC	A, R2
	MOV		R2, A

	MOV		DPTR, #PWM4T2H	; ָ��ָ��PWM4
	MOV		A, R2			; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	INC		DPTR
	MOV		A, R3			; �ڶ�����ת�������ֽ�
	MOVX	@DPTR, A
	POP		P_SW2	; �ָ�����P_SW2
	
	INC		PWM_Index
	MOV		A, PWM_Index
	CLR		C
	SUBB	A, #200
	JC		L_Int_NotCBIF
	MOV		PWM_Index, #0
L_Int_NotCBIF:

/*
	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.0, L_Int_NotC2IF	; PWM2�жϱ�־
	ANL		PWMIF, #NOT 1			; ����жϱ�־
L_Int_NotC2IF:

	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.1, L_Int_NotC3IF	; PWM3�жϱ�־
	ANL		PWMIF, #NOT (1 SHL 1)	; ����жϱ�־
L_Int_NotC3IF:

	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.2, L_Int_NotC4IF	; PWM4�жϱ�־
	ANL		PWMIF, #NOT (1 SHL 2)	; ����жϱ�־
L_Int_NotC4IF:

	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.3, L_Int_NotC5IF	; PWM5�жϱ�־
	ANL		PWMIF, #NOT (1 SHL 3)	; ����жϱ�־
L_Int_NotC5IF:

	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.4, L_Int_NotC6IF	; PWM6�жϱ�־
	ANL		PWMIF, #NOT (1 SHL 4)	; ����жϱ�־
L_Int_NotC6IF:

	MOV		A, PWMIF				; ���жϱ�־�Ĵ���
	JNB		ACC.5, L_Int_NotC7IF	; PWM7�жϱ�־
	ANL		PWMIF, #NOT (1 SHL 5)	; ����жϱ�־
L_Int_NotC7IF:
*/

	POP		AR3
	POP		AR2
	POP		DPL
	POP		DPH
	POP		ACC
	POP		PSW

	RETI


T_SinTable:
	DW	1220,1256,1292,1328,1364,1400,1435,1471,1506,1541,1575,1610,1643,1677,1710,1742,1774,1805,1836,1866
	DW	1896,1925,1953,1981,2007,2033,2058,2083,2106,2129,2150,2171,2191,2210,2228,2245,2261,2275,2289,2302
	DW	2314,2324,2334,2342,2350,2356,2361,2365,2368,2369,2370,2369,2368,2365,2361,2356,2350,2342,2334,2324
	DW	2314,2302,2289,2275,2261,2245,2228,2210,2191,2171,2150,2129,2106,2083,2058,2033,2007,1981,1953,1925
	DW	1896,1866,1836,1805,1774,1742,1710,1677,1643,1610,1575,1541,1506,1471,1435,1400,1364,1328,1292,1256
	DW	1220,1184,1148,1112,1076,1040,1005,969,934,899,865,830,797,763,730,698,666,635,604,574
	DW	544,515,487,459,433,407,382,357,334,311,290,269,249,230,212,195,179,165,151,138
	DW	126,116,106,98,90,84,79,75,72,71,70,71,72,75,79,84,90,98,106,116
	DW	126,138,151,165,179,195,212,230,249,269,290,311,334,357,382,407,433,459,487,515
	DW	544,574,604,635,666,698,730,763,797,830,865,899,934,969,1005,1040,1076,1112,1148,1184

	
	END
	




#include "STC_NEW_8051.H"
//#include <REG52.H>
#include <intrins.h>
#include <absacc.h>
#include "define.h"
#include "sd.h"
#include "fat.h"
#include "LCD.c"

void PORT_init()
{
	P0 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
}
void main(void)
{
	//uchar i;
	uchar item=0;
	T_CS = 1; //�رմ���IC ���ڹ�����SPI���ߣ� ����Ӱ��SD����ȡ���� ���ݳ�ͻ
 	PORT_init();
	LCD_Init();   //tft��ʼ��	
	Pant(RED>>8 , RED );
	Pant(GREEN>>8 ,GREEN);
	Pant(BLUE>>8 ,GREEN);
	Pant(WHITE>>8 ,GREEN);
	Pant(BLACK>>8 ,GREEN);
	Pant(YELLOW>>8 ,GREEN); 
	SD_Reset();
	SD_Init();	  //��SD������
  
  	pArg=&Init_Arg_SD; //pArg��znFAT�ġ���ʼ�����ṹָ�롱������ָ��Ľṹ���м�¼�˴洢�������ļ�ϵͳ����Ҫ������Ϣ
                       //���л��洢�豸ʱ������Ҫ�����豸�ţ���Ҫ��pArgָ����Ӧ�洢�豸�ġ���ʼ�����ṹ��
	Dev_No=SDCARD; 	   //�豸��ΪSDCARD��znFAT�н���궨��Ϊ 0
	FAT32_Init(); 	   //�ļ�ϵͳ��ʼ����ʹ��znFATǰ������г�ʼ������ʼ�������н���ʹ�õĴ洢�豸���ļ�ϵͳ��һЩ��Ҫ����
               		   //��¼����pArg��ָ��Ľṹ�У��Ա�����ʹ��
	while(1)
	{
		while(!FAT32_Open_File(&FileInfo,"\\*.bmp",item++)) //���β���SD����Ŀ¼�µ�����BMP�ļ�
		{
			display_pic();
			//while(touch_INT);
		    //while(touch_INT);
		} 
		item=0;
	}
}

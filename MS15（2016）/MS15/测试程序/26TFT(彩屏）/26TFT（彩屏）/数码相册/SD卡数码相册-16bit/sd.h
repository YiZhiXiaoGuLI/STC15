#ifndef __SD_H__
#define __SD_H__

#include "STC_NEW_8051.H"
//#include <REG52.H>

sbit SD_CS =P3^0;	//SD��Ƭѡ 	  ����
sbit SD_SI =P3^1;  //SD��ͬ������  ����
sbit SD_SCL=P3^2;  //SD��ͬ��ʱ��  ����
sbit SD_SO =P3^3;  //SD��ͬ������  ���

sbit T_CS =P3^6; //����IC��SD������SPIЭ��ͨ��  ����3������ͨ����   ͨ��ƬѡCS���л� ��ǰ�Ĺ����豸


#define DELAY_TIME 2000 //SD���ĸ�λ���ʼ��ʱSPI����ʱ����������ʵ�������޸���ֵ����������SD����λ���ʼ��ʧ��
#define TRY_TIME 200   //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��

//�����붨��
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0����
#define INIT_CMD1_ERROR     0x02 //CMD1����
#define WRITE_BLOCK_ERROR   0x03 //д�����
#define READ_BLOCK_ERROR    0x04 //�������
//-------------------------------------------------------------

unsigned char SD_Reset();
unsigned char SD_Init();
unsigned char SD_Write_Sector(unsigned long addr,uchar *Buffer);
unsigned char SD_Read_Sector(unsigned long addr,uchar *buffer);

#endif
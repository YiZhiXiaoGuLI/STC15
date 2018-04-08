/**********************
���ƣ�12864  4*8��ʾ����
���ߣ��β�٩
���ڣ�2013��8��25��
����ԭ��
	ֱ�Ӱ���ԭ��ͼ��ʾ
	
	���ߣ�
		sbit rs = P2^4;
		sbit rw = P2^5;
		sbit en = P2^6;
		sbit psb = P2^1;
		sbit rst = P2^3;
	���������У�
	��ʼ��12864��init12864();
	������clear()
	��ʾһ���ַ�: display_onchar(uint x,uint y,uchar dat)
	��ʾһ���ַ���: display_string(uint x,uint y,uchar *s)
***********************/

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int

sbit rs = P2^4;
sbit rw = P2^5;
sbit en = P2^6;
sbit psb = P2^1;
sbit rst = P2^3;
#define dataport P0




//12864���æλ
void check_busy()
{
	rs = 0;
	rw = 1;
	en = 1;
	dataport = 0xff;
	while((dataport&0x80) == 0x80);
	en = 0;

}
//16864дָ��
void write_cmd(uchar cmd)
{
	check_busy();
	rs = 0;
	rw = 0;
	en = 1;
	dataport = cmd;
	delay_us(5);
	en = 0;
	delay_us(5);
}
//12864д����
void write_dat(uchar dat)
{
	check_busy();
	rs = 1;
	rw = 0;
	en = 1;
	dataport = dat;
	delay_us(5);
	en = 0;
	delay_us(5);
}
//12864��ʼ������
void init12864()
{
	delay_ms(40);
	psb = 1;			//���ù�����ʽΪ8λ���ڹ���ģʽ
	delay_ms(1);
	rst = 0;			//��λ���͵�ƽ��Ч
	delay_ms(1);
	rst = 1;			//��λ���ø�
	delay_ms(10);
	write_cmd(0x30);
	delay_us(50);
	write_cmd(0x30);
	delay_us(20);
	write_cmd(0x0c);	//����ʾ���
	delay_us(50);
	write_cmd(0x06);	//����ƶ�Ϊ����һλ
	delay_us(50);	
	write_cmd(0x01);	//���������ó�ʼ��ַΪ00H
	delay_ms(15);
}
//��ʾ�����ַ�
void display_onchar(uint x,uint y,uchar dat)
{
	switch(y)
	{
		case 1:write_cmd(0x80+x);break;
		case 2:write_cmd(0x90+x);break;
		case 3:write_cmd(0x88+x);break;
		case 4:write_cmd(0x98+x);break;
		default: break;		
	}
	write_dat(dat);
}
//��ʾ�ַ���
void display_string(uint x,uint y,uchar *s)
{
	switch(y)
	{
		case 1:write_cmd(0x80+x);break;
		case 2:write_cmd(0x90+x);break;
		case 3:write_cmd(0x88+x);break;
		case 4:write_cmd(0x98+x);break;
		default: break;		
	}
	 while(*s>0)
   { 
      write_dat(*s);
      s++;
      delay_us(50);
   }
}
//��������
void clear()
{
	write_cmd(0x01);
	delay_ms(15);
}


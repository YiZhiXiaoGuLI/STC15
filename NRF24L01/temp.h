/**********************
���ƣ��¶ȴ�������ʾ����
���ߣ��β�٩
���ڣ�2013��8��25��
����ԭ��
	ֱ�Ӱ���ԭ��ͼ��ʾ
	
	���ߣ�
		sbit DQ = P1^3;
	���������У�
	change();
	�����¶ȷ�������S��
			s[0]=(temp/100)+0x30; 
	    s[1]=(temp/10)%10+0x30;
	    s[2]='.';
	    s[3]=temp%10+0x30;
	ʹ��ʱ��
		change();
		display_onchar(3,3,s[0]);
		display_onchar(4,3,s[1]);
		display_onchar(5,3,s[2]);
		display_onchar(6,3,s[3]);
		display_onchar(7,3,'C');
***********************/
#include "reg52.h"
#include "delay.h"
#define uint unsigned int 
#define uchar unsigned char

sbit DQ = P1^3;
uint temp=0;
float f_temp = 0;
uchar s[4] = {0,0,0,0}; 
/******************************************************************/
/*                    18B20��ʼ��                                 */
/******************************************************************/
void Init_DS18B20(void)
{
unsigned char x=0;
	DQ = 1;    //DQ��λ
	delay_us(8);  //������ʱ
	DQ = 0;    //��Ƭ����DQ����
	delay_us(80); //��ȷ��ʱ ���� 480us
	DQ = 1;    //��������
	delay_us(10);
	x=DQ;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	delay_us(5);
}

/******************************************************************/
/*                    ��һ���ֽ�                                  */
/******************************************************************/
unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
{
	DQ = 0; // �������ź�
	dat>>=1;
	DQ = 1; // �������ź�
	if(DQ)
	dat|=0x80;
	delay_us(5);
}
 return dat;
}

/******************************************************************/
/*                 дһ���ֽ�                                     */
/******************************************************************/
void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
{
	DQ = 0;
	DQ = dat&0x01;//����
	delay_us(5);
	DQ = 1;
	dat>>=1;
 }
	delay_us(5);
}

/******************************************************************/
/*                   ��ȡ�¶�                                     */
/******************************************************************/
unsigned int ReadTemperature(void)
{
	unsigned char a=0;
	unsigned int b=0;
	unsigned int t=0;
	
	Init_DS18B20();
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	delay_us(200);
	
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ��� 
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
	a=ReadOneChar();   //��λ
	b=ReadOneChar();   //��λ
	
	b<<=8;
	t=a+b;

	return(t);
}

/***************�¶�ת��**********/
void change()
{
	uchar i = 0;	
	temp=ReadTemperature();
	if(temp&0x8000)
	{
		temp=~temp;  // ȡ����1
		temp +=1;
	}
	f_temp=temp*0.0625;
 	temp=f_temp*10;
    s[0]=(temp/100)+0x30; 
    s[1]=(temp/10)%10+0x30;
    s[2]='.';
    s[3]=temp%10+0x30;

}



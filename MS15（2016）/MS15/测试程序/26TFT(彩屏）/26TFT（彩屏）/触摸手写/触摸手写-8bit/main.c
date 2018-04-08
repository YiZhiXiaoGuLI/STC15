
#include<reg52.h>
#include"LCD_driver.h"
#include <intrins.h>

struct pix_
{
	unsigned int x;
	unsigned int y;
};

struct pix_ Tp_pix;	 //��ǰ���������ȡ��ֵ  

sbit T_CS      =    P3^6;
sbit DIN       =    P3^1;
sbit DCLK	   =    P3^2;
sbit DOUT      =    P3^3;
sbit BUSY      =    P3^5;	 
sbit IRQ       =    P3^4;   //��ⴥ������Ӧ�ź�

unsigned int TP_X,TP_Y;

//******************************************************************************
//******************************************************************************
void spistar()                                     //SPI��ʼ
{
T_CS=1;
DCLK=1;
DIN=1;
DCLK=1;
}
//******************************************************************************
//******************************************************************************
void WriteCharTo7843(unsigned char num)//SPIд����
{
	unsigned char count=0;
	DCLK=0;
	for(count=0;count<8;count++)
	{
	num<<=1;
	DIN=CY;
	DCLK=0; _nop_();_nop_();_nop_(); //��������Ч
	DCLK=1; _nop_();_nop_();_nop_();
	}
}

//******************************************************************************
//******************************************************************************
unsigned int ReadFromCharFrom7843() //SPI ������
{
	unsigned char count=0;
	unsigned int Num=0;
	for(count=0;count<12;count++)
	{
	Num<<=1;
	DCLK=1; _nop_();_nop_();_nop_(); //�½�����Ч
	DCLK=0; _nop_();_nop_();_nop_();
	if(DOUT) Num++;
	}
	return(Num);
}

//******************************************************************************
//******************************************************************************
unsigned char Makpix(struct pix_ pix1,struct pix_ pix2)
{
  unsigned char l=0;
  int x=pix1.x>pix2.x?pix1.x-pix2.x:pix2.x-pix1.x;
  int y=pix1.y>pix2.y?pix1.y-pix2.y:pix2.y-pix1.y;
  if(x<3&&y<3)	 //����˲���2��ȡ����ֵ���̫�����Ϊ����
	{
	  l=1;
	  Tp_pix.x=pix1.x;
     Tp_pix.y=pix1.y;
	}
  return l;
}

//******************************************************************************
//******************************************************************************
struct pix_ AD7843()            
{
  struct pix_ pix;
  T_CS=0;
  WriteCharTo7843(0x90); //�Ϳ����� 10010000 ���ò�ַ�ʽ��X����
  DCLK=1; _nop_();_nop_();_nop_();_nop_();
  DCLK=0; _nop_();_nop_();_nop_();_nop_();
  pix.y=ReadFromCharFrom7843();
  WriteCharTo7843(0xD0); //�Ϳ����� 11010000 ���ò�ַ�ʽ��Y����
  DCLK=1; _nop_();_nop_();_nop_();_nop_();
  DCLK=0; _nop_();_nop_();_nop_();_nop_();
  pix.x=ReadFromCharFrom7843();
  T_CS=1; 
  return pix;
}

//******************************************************************************
//******************************************************************************
unsigned char Getpix() //ȡ����ֵ
{
	struct pix_ pix1;
	struct pix_ pix2; 
	pix1=AD7843();
	pix2=AD7843();
 	return	Makpix(pix1,pix2);	
}

//******************************************************************************
//******************************************************************************
void point()
{
	unsigned int lx,ly;	
	long i;
	i=0;
	while(i<200000)
	{
		if(IRQ==0)
		{
			i=0;
				if(Getpix()==1) //�õ���ǰTP��ȡ��ֵ���˴�ʹ������˲���2��ȡ����ֵ���̫�����Ϊ����
			 {
 		        lx=((Tp_pix.x)*10/142)-270-((Tp_pix.x)/170);
		   	    ly=335-((Tp_pix.y)/11)+((Tp_pix.y)/200);
				Address_set(lx,ly,lx+2,ly+2);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);
				LCD_Write_DATA(0,255);			
			 }		
		}
		else
		{
			i++;
		}
		
	} 
}

//******************************************************************************
//******************************************************************************
main()
{ 	 	
   unsigned int j;
   LCD_Init();  //TFT��ʼ��		
   spistar();  //ģ��spi��ʼ�� 	
   Pant(0xFF,0xFF); 			
   LCD_CS =0;  //��Ƭѡʹ��
   ChineseChar(14+46,10,colors[4],colors[7],1);
   ChineseChar(46+46,10,colors[4],colors[7],2);
   ChineseChar(78+46,10,colors[4],colors[7],3);
   ChineseChar(110+46,10,colors[4],colors[7],4);
   LCD_CS =1;  //�ر�Ƭѡʹ��
   while(1)
 		{
		  LCD_CS =0;  //��Ƭѡʹ��
		  for(j=0;j<6;j++)
			{	
				if (IRQ==0)
				{ 
			     point();	

				}
		 delayms(10);
 	
   	        } 
		}
}

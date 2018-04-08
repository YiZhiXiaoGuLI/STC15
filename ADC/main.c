#include <STC15.h>
#include <1602.h>
#include <intrins.h>
#include <12864.h>
#include <EEPROM.h>


u8  code uctech[] = {"南通国芯微电子  "};
u8	tmp[2]={10,11};
u8	tmp1[2]={0,0};

void Delay(uint n)
{
    uint x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

void InitADC()
{
    P1ASF = 0xff;                  
    ADC_RES = 0;                   
    ADC_CONTR =0xE0;  //最高速率  90T   122.88kHZ
    Delay(2);     
}

uint	Get_ADC10bitResult(uchar channel)	//channel = 0~7
{
	ADC_RES = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xe0) | 0x08 | channel; 	//start the ADC
	_nop_();_nop_();_nop_();_nop_();

	while((ADC_CONTR & 0x10) == 0)	;	//wait for ADC finish
	ADC_CONTR &= ~0x10;		//清除ADC结束标志
	return	(((uint)ADC_RES << 2) | (ADC_RESL & 3));
}

uint ReadAD(uchar channel)
{       
	      uchar i;
 	      uint j,Value,Bandgap;

	      P1ASF = 0;
				Get_ADC10bitResult(0);
				for(j=0, i=0; i<16; i++)
				{
					j += Get_ADC10bitResult(0);	
				}
				Bandgap = j >> 4;	
				
				P1ASF = 0xff;
				
				for(j=0, i=0; i<16; i++)
				{
					j += Get_ADC10bitResult(channel);	//读外部电压ADC
				}
				j = j >> 4;	//16次平均
				
				Value=(1.23*(float)j)/Bandgap*100;
				
				return Value;
}



void main()
{
	uchar i=0;
	uint VolValue;
	
	Initialize_LCD();
	
//  LCDInit(); //LCM初始化
//	LCDClear();
//	
//	InitADC();
	
	
	
	//EEPROM_SectorErase(EE_ADDRESS);
	//EEPROM_write_n(EE_ADDRESS,tmp,2);
	//EEPROM_read_n(EE_ADDRESS,tmp1,2);
	
	while(1)
	{
		
		
//    DisplayListNum(0,1,tmp1[0]/10);
//		DisplayListNum(1,1,tmp1[0]%10);
//		DisplayListNum(2,1,tmp1[1]/10);
//		DisplayListNum(3,1,tmp1[1]%10);
		
//		VolValue=ReadAD(3);
//		//VolValue=1024;
		PutString(0,0,"ADC:");
		PutString(1,0,"VOL");
//		WriteChar(1,5,VolValue / 1000 +'0');
//		WriteChar(1,6,VolValue % 1000/100 +'0');
//		WriteChar(1,7,VolValue % 100/10 +'0');
//		WriteChar(1,8,VolValue % 10 +'0');
	}
}
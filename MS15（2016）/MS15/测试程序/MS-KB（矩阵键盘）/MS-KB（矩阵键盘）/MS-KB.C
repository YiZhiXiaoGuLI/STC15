/**********************************************************************************************************/

/*******************************        矩阵键盘MS-KB例程      ********************************************/
/*******************************        hiold.taobao.com       ********************************************/

/**********************************************************************************************************/


#include <STC12C5A60S2.H>
#define KeyPort P0//键盘接口定义
#define LEDPortL P1//低位LED显示端口定义
#define LEDPortH P3 //高位LED显示端口定义
unsigned char Vx,Vy,Vv;//Vx代表行值，Vy代表列值,Vv代表键值
unsigned char code LED[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};//LED显示数组


/**********************************************************************************************************/
/***************************************  延时子程序  *****************************************************/
/**********************************************************************************************************/
void Delay20ms()
{
	unsigned char i, j, k;

	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


/**********************************************************************************************************/
/***************************************  扫描子程序  *****************************************************/
/**********************************************************************************************************/
void SCANS()
{
	KeyPort=0x0F;// 例为低，用于判断行值
	if(KeyPort!=0x0F)//如果有按键按下，端口的值就不会等于0x0F
		{
			switch(KeyPort)	//获取行值
				{
					case 0x0E:{Vx=1;}break;
					case 0x0D:{Vx=2;}break;
					case 0x0B:{Vx=3;}break;
					case 0x07:{Vx=4;}break;
					default:{Vx=0;}  break;
				}
			if(Vx!=0)//如果行值不为0，说明读到了正确的行值
				{
					Delay20ms();//延时消抖
					KeyPort=0xF0;//行为低，用于判断例值
					switch(KeyPort)//获取列值
						{
							case 0xE0:{Vy=1;}break;
							case 0xD0:{Vy=2;}break;
							case 0xB0:{Vy=3;}break;
							case 0x70:{Vy=4;}break;
							default:{Vx=0;}  break;
						}
				}
		}
}


/**********************************************************************************************************/
/***************************************  主程序  *********************************************************/
/**********************************************************************************************************/
void main()
{
	while(1)
		{
			SCANS();//扫描键值
			if(Vx!=0)//如果Vx不等于0，说明获取键值成功
				{
					Vv=Vx*4-Vy+1;//根据行列值，计算出键值
					if(Vv<9)//利用两组端口的LED显示键值
						{
							LEDPortL=LED[Vv-1];
						}
					else
						{
							LEDPortH=LED[Vv-9];
						}
				}
			else//没有按健按下时，关闭健值显示
			{
				LEDPortL=0XFF;
				LEDPortH=0XFF;
			}
		}
}
	




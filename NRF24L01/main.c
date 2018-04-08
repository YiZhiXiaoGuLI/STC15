#include "reg52.h"
#include "NRF.h"
#include "temp.h"
#include "12864.h"


#define uint unsigned int
#define uchar unsigned char


uchar rece[4];


void main()
{
	init12864();
	init_NRF24L01();
	while(1)
	{
		change();
		display_string(0,1,"本地温度");
		display_onchar(0,2,s[0]);
		display_onchar(1,2,s[1]);
		display_onchar(2,2,s[2]);
		display_onchar(3,2,s[3]);
		send(s);
		
		receive(rece);
		display_string(0,3,"外地温度");
		display_onchar(0,4,rece[0]);
		display_onchar(1,4,rece[1]);
		display_onchar(2,4,rece[2]);
		display_onchar(3,4,rece[3]);
	
	}

}
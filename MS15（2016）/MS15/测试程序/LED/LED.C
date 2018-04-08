
#include <reg52.h>
char LED,LED1;


/*******延时函数*************/
void delay(unsigned int i)
{
    unsigned char j;
    for(i; i > 0; i--)
        for(j = 255; j > 0; j--);

}


/*******主函数*************/
main()
{ 
  unsigned char i;
  
  while (1) 
  {	 LED  = 0xfe;
	 LED1 = 0x7f;
	 for (i = 0 ;i < 8 ; i++)
	  { 
	    P0 = LED;
		P1 = LED1;
		P2 = LED;
		P3 = LED;
	    delay(400);
	    LED = LED << 1;	           
		LED1= LED1>>1;              
	    LED = LED | 0x01;	           
		LED1= LED1 |0x80;
	   if (LED == 0x7f)	 break;	
	   }
	
	   for (i = 0 ;i < 8 ; i++)
	   {
		 
	   P0 = LED;
	   P1 = LED1;
	   P2 = LED;
	   P3 = LED;
	   delay(400);
	   LED = LED >> 1;	 
	   LED1 = LED1<<1;
	   LED = LED | 0x80;	 
	   LED1=LED1 | 0x01;
	   
	   }

   }
 
}




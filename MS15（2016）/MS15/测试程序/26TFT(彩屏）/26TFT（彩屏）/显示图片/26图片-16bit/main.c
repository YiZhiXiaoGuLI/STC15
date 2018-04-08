#include<reg52.h>
#include"LCD_driver.h"
#include"picture.h"


main()
{ 
	 int j;
  	 LCD_Init();      //TFT初始化
 	 Pant( colors[7]>>8 ,  colors[7]);
    LCD_CS =0;  //打开片选使能
	 Address_set(45,65,194,254); //设置坐标
	 for (j=0;j<57000/2;j++)	  
	   	{	   
        	LCD_Write_DATA(Image[j*2+1],Image[j*2]);
	      }				  
		   	LCD_CS =1; 
    while(1)
	     {   
		  }  

}

#include<reg52.h>
#include"LCD_driver.h"


main()
{ 
   LCD_Init();          //TFT初始化
   Pant(colors[2]>>8 , colors[2]); //蓝色 
   LCD_CS =0;  //打开片选使能
   LCD_color_H();   //8色彩条水平显示
   delayms(500);
   LCD_color_V();   //8色彩条垂直显示
   delayms(500);
   LCD_CS =1;  //关闭片选使能

}

















#include<reg52.h>
#include"LCD_driver.h"


main()
{ 
   LCD_Init();          //TFT��ʼ��
   Pant(colors[2]>>8 , colors[2]); //��ɫ 
   LCD_CS =0;  //��Ƭѡʹ��
   LCD_color_H();   //8ɫ����ˮƽ��ʾ
   delayms(500);
   LCD_color_V();   //8ɫ������ֱ��ʾ
   delayms(500);
   LCD_CS =1;  //�ر�Ƭѡʹ��

}


















//void LCD_Init(void);
//void delayms(int count) ;
//void LCD_Writ_Bus(char VH,char VL);
//void LCD_Writ_Bus(char VH,char VL);
//void LCD_Write_COM(char VH,char VL);
//void LCD_Write_DATA(char VH,char VL);
//void Pant(char VH,char VL);
//void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)


void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<100;j++);
}


void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
    LCD_DataPortH=VH;	  //高位P1口
	LCD_DataPortL=VL;	  //低位P0口	
	LCD_WR=0;
	LCD_WR=1; 
}


void LCD_Write_COM(char VH,char VL)	 //发送命令
{	
    LCD_RS=0;
	LCD_Writ_Bus(VH,VL);
}


void LCD_Write_DATA(char VH,char VL)	//发送数据
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}


void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
LCD_Write_COM(0x00,0x20);LCD_Write_DATA(x1>>8,x1);	  //设置X坐标位置
    LCD_Write_COM(0x00,0x21);LCD_Write_DATA(y1>>8,y1);   //设置Y坐标位置

								 

    LCD_Write_COM(0x00,0x50);LCD_Write_DATA(x1>>8,x1);   //开始X
	LCD_Write_COM(0x00,0x52);LCD_Write_DATA(y1>>8,y1);	  //开始Y
    LCD_Write_COM(0x00,0x51);LCD_Write_DATA(x2>>8,x2);   //结束X
	LCD_Write_COM(0x00,0x53);LCD_Write_DATA(y2>>8,y2);   //结束Y

	LCD_Write_COM(0x00,0x22);	//开启显示命令			 
}
void LCD_Init(void)
{

    LCD_REST=1;
    delayms(50);	
	LCD_REST=0;
	delayms(50);
	LCD_REST=1;
	delayms(50);

	LCD_CS =0;  //打开片选使能
		
	delayms(10);
    LCD_Write_COM(0x00,0x00); LCD_Write_DATA(0x00,0x01);//
	LCD_Write_COM(0x00,0x01); LCD_Write_DATA(0x01,0x00);//
	LCD_Write_COM(0x00,0x02); LCD_Write_DATA(0x02,0x00);//
	LCD_Write_COM(0x00,0x03); LCD_Write_DATA(0x10,0x30);//
	
	LCD_Write_COM(0x00,0x08); LCD_Write_DATA(0x08,0x08);//	
	LCD_Write_COM(0x00,0x09); LCD_Write_DATA(0x00,0x01);//	
	LCD_Write_COM(0x00,0x0A); LCD_Write_DATA(0x00,0x00);//
	LCD_Write_COM(0x00,0x0C); LCD_Write_DATA(0x00,0x00);//
	LCD_Write_COM(0x00,0x0D); LCD_Write_DATA(0x00,0x00);//
    LCD_Write_COM(0x00,0x0E); LCD_Write_DATA(0x00,0x30);//
	LCD_Write_COM(0x00,0x0F); LCD_Write_DATA(0x00,0x00);//

	//-------------Power On sequence -------------------//
	LCD_Write_COM(0x00,0x10); LCD_Write_DATA(0x04,0x10);// 
	LCD_Write_COM(0x00,0x11); LCD_Write_DATA(0x02,0x37);//
	delayms(50); 
	LCD_Write_COM(0x00,0x12); LCD_Write_DATA(0x01,0xb9);//
	delayms(50); 
	LCD_Write_COM(0x00,0x13); LCD_Write_DATA(0x11,0x00);//
	LCD_Write_COM(0x00,0x28); LCD_Write_DATA(0x00,0x00);// 
    LCD_Write_COM(0x00,0x29); LCD_Write_DATA(0x00,0x12);// 
    LCD_Write_COM(0x00,0x2A); LCD_Write_DATA(0x00,0x56);// 
	delayms(50); 
	LCD_Write_COM(0x00,0x20); LCD_Write_DATA(0x00,0x00);//
    LCD_Write_COM(0x00,0x21); LCD_Write_DATA(0x00,0x00);//

	// ----------- Adjust the Gamma Curve ----------//
	LCD_Write_COM(0x00,0x30); LCD_Write_DATA(0x0b,0x00);
	LCD_Write_COM(0x00,0x31); LCD_Write_DATA(0x7d,0x17);
	LCD_Write_COM(0x00,0x32); LCD_Write_DATA(0x0a,0x01);
    LCD_Write_COM(0x00,0x33); LCD_Write_DATA(0x0a,0x03);
    LCD_Write_COM(0x00,0x34); LCD_Write_DATA(0x00,0x00);
	LCD_Write_COM(0x00,0x35); LCD_Write_DATA(0x03,0x0a);
	LCD_Write_COM(0x00,0x36); LCD_Write_DATA(0x71,0x0a);
	LCD_Write_COM(0x00,0x37); LCD_Write_DATA(0x17,0x0d);
	LCD_Write_COM(0x00,0x38); LCD_Write_DATA(0x00,0x0b);
	LCD_Write_COM(0x00,0x39); LCD_Write_DATA(0x33,0x33);
	delayms(5);


		
	//------------------ Set GRAM area -----------------//
	LCD_Write_COM(0x00,0x50); LCD_Write_DATA(0x00,0x00);// 
	LCD_Write_COM(0x00,0x51); LCD_Write_DATA(0x00,0xEF);//
	LCD_Write_COM(0x00,0x52); LCD_Write_DATA(0x00,0x00);// 	
	LCD_Write_COM(0x00,0x53); LCD_Write_DATA(0x01,0x3F);//	
	LCD_Write_COM(0x00,0x60); LCD_Write_DATA(0x36,0x00);//
	LCD_Write_COM(0x00,0x61); LCD_Write_DATA(0x00,0x01);//	
	LCD_Write_COM(0x00,0x6A); LCD_Write_DATA(0x00,0x00);//
	
	//-------------- Partial Display Control -----------//
	LCD_Write_COM(0x00,0x80); LCD_Write_DATA(0x00,0x00);//	
	LCD_Write_COM(0x00,0x81); LCD_Write_DATA(0x00,0x00);//	
	LCD_Write_COM(0x00,0x82); LCD_Write_DATA(0x00,0x5f);//

	
	//-------------- Panel Control ---------------------//
	LCD_Write_COM(0x00,0x90); LCD_Write_DATA(0x00,0x15);//
    LCD_Write_COM(0x00,0x91); LCD_Write_DATA(0x00,0x00);//	
	LCD_Write_COM(0x00,0x92); LCD_Write_DATA(0x01,0x00);//
	LCD_Write_COM(0x00,0x93); LCD_Write_DATA(0x07,0x01);//
    LCD_Write_COM(0x00,0x94); LCD_Write_DATA(0x00,0x01);//
	LCD_Write_COM(0x00,0x95); LCD_Write_DATA(0x00,0x10);//
    LCD_Write_COM(0x00,0x96); LCD_Write_DATA(0x00,0x00);//
	LCD_Write_COM(0x00,0x97); LCD_Write_DATA(0x01,0x00);//	
	LCD_Write_COM(0x00,0x98); LCD_Write_DATA(0x00,0x01);//
    LCD_Write_COM(0x00,0x99); LCD_Write_DATA(0x00,0x01);//
    LCD_Write_COM(0x00,0x9C); LCD_Write_DATA(0x00,0x11);//
    LCD_Write_COM(0x00,0xA0); LCD_Write_DATA(0x00,0x00);//	
	LCD_Write_COM(0x00,0xA1); LCD_Write_DATA(0x00,0x00);//
    LCD_Write_COM(0x00,0xA3); LCD_Write_DATA(0x00,0x00);//
    LCD_Write_COM(0x00,0xA4); LCD_Write_DATA(0x00,0x00);//
	LCD_Write_COM(0x00,0x07); LCD_Write_DATA(0x01,0x00);// 
    delayms(300);
	
	LCD_CS =1;  //关闭片选使能

}  

void Pant(char VH,char VL)
{
	int i,j;
	LCD_CS =0;  //打开片选使能
	Address_set(0,0,239,319);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 LCD_Write_DATA(VH,VL);
	    }

	  }
     LCD_CS =1;  //关闭片选使能
}


/*void DispOneColor(uint color)
{
    uint i;
	uchar j;

	

	LCD_CS =0;  //打开片选使能

	Address_set(0,0,240-1,320-1);
	for(i=0;i<320;i++)
	{
		for (j=0;j<240;j++)
		{
			LCD_Write_DATA(color>>8,color);
		}
	}
	LCD_CS =1;  //关闭片选使能
} */

void display_pic()
{
	uint  i;
	uchar j;
	uint  color;
	LCD_CS =0;  //打开片选使能
	LCD_Write_COM(0x00,0x03); LCD_Write_DATA(0x10,0x10); // set GRAM write direction and BGR=1.
 	Address_set(0,0,240-1,320-1);
	 
	for(i=0;i<1920;i++) //读取76800个点的颜色数据	 1920
	{
		FAT32_Read_File(&FileInfo,(unsigned long)i*120+54,120,file_buf);
  		for(j=0;j<40;j++)		  //40
  		{	
   			color=COLOR(file_buf[2+3*j],file_buf[1+3*j],file_buf[0+3*j]);
  			LCD_Write_DATA(color>>8,color);
  		}
 	}
	// FAT32_File_Close(&FileInfo); 
	LCD_CS =1;  //关闭片选使能
}

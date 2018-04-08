
#define uchar unsigned char
#define uint unsigned int




#define  LCD_DataPortH P0     //高8位数据口,8位模式下只使用高8位 
#define  LCD_DataPortL P1     //低8位数据口	,8位模式下低8位可以不接线

sbit LCD_REST  = P2^3;    //RST 引脚定义
sbit LCD_RD   =  P2^7;	 //RD  引脚定义
sbit LCD_WR   =  P2^6;	 //WR  引脚定义
sbit LCD_RS   =  P2^5;	 //RS  引脚定义
sbit LCD_CS   =  P2^4;	 //CS  引脚定义 

extern  uint colors[];

void LCD_Init(void);
void delayms(int count) ;
void LCD_Writ_Bus(char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(unsigned char VH,unsigned char VL);
void Pant(char VH,char VL);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);




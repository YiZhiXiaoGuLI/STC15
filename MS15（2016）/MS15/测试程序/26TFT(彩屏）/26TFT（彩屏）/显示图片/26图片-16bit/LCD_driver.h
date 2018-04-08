
#define uchar unsigned char
#define uint unsigned int




#define  LCD_DataPortH P0     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P1     //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����

sbit LCD_REST  = P2^3;    //RST ���Ŷ���
sbit LCD_RD   =  P2^7;	 //RD  ���Ŷ���
sbit LCD_WR   =  P2^6;	 //WR  ���Ŷ���
sbit LCD_RS   =  P2^5;	 //RS  ���Ŷ���
sbit LCD_CS   =  P2^4;	 //CS  ���Ŷ��� 

extern  uint colors[];

void LCD_Init(void);
void delayms(int count) ;
void LCD_Writ_Bus(char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(unsigned char VH,unsigned char VL);
void Pant(char VH,char VL);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);




//======================================================

//==========================LCD DEFINE
#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW   0xFFE0

#define TRANSP  1           //������ʾ��ʱ�򲻴�������ɫ
#define NORMAL  0           //������ʾ��ʱ���б�����ɫ


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


#define  LCD_DataPortH P0     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P1     //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����



sbit LCD_REST  = P2^3;    //RST ���Ŷ���
sbit LCD_RD   =  P2^7;	 //RD  ���Ŷ���
sbit LCD_WR   =  P2^6;	 //WR  ���Ŷ���
sbit LCD_RS   =  P2^5;	 //RS  ���Ŷ���
sbit LCD_CS   =  P2^4;	 //CS  ���Ŷ��� 


struct FAT32_Init_Arg Init_Arg_SD;	   //��ʼ�������ṹ��ʵ��
struct FAT32_Init_Arg *pArg;
struct FileInfoStruct  FileInfo;        //�ļ���Ϣ�ṹ��ʵ��
uchar idata file_buf[150];	   //�ļ����ݻ���������ȡ�����ļ����ݷ�������

uchar Dev_No=0; //�豸�ţ�SDCARD��SD���豸�ŵĺ궨�壬�����豸�ţ�znFAT�Ὣ�ײ�洢�豸�������ӵ���Ӧ�Ĵ洢�豸����
                        //��̬���л��豸�ţ��Ϳ���ʵ���ڸ��ִ洢�豸֮������л�����Ҳ��znFATʵ�ֶ��豸����Ҫ�ֶΡ����磬��
						//���Խ�SD���ϵ��ļ�������CF����U���ϣ�����Ƕ��豸�������Ӧ��

#define COLOR(r,g,b) (((((((uint)r)>>3)<<6)|(((uint)g)>>2))<<5)|(((uint)b)>>3))	 //r��ɫ���� 0~31  g��ɫ���� 0~63  b��ɫ���� 0~31	






			
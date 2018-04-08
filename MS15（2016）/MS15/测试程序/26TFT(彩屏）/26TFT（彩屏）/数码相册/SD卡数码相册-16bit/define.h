//======================================================

//==========================LCD DEFINE
#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW   0xFFE0

#define TRANSP  1           //字体显示的时候不带背景颜色
#define NORMAL  0           //字体显示的时候有背景颜色


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


#define  LCD_DataPortH P0     //高8位数据口,8位模式下只使用高8位 
#define  LCD_DataPortL P1     //低8位数据口	,8位模式下低8位可以不接线



sbit LCD_REST  = P2^3;    //RST 引脚定义
sbit LCD_RD   =  P2^7;	 //RD  引脚定义
sbit LCD_WR   =  P2^6;	 //WR  引脚定义
sbit LCD_RS   =  P2^5;	 //RS  引脚定义
sbit LCD_CS   =  P2^4;	 //CS  引脚定义 


struct FAT32_Init_Arg Init_Arg_SD;	   //初始化参数结构体实体
struct FAT32_Init_Arg *pArg;
struct FileInfoStruct  FileInfo;        //文件信息结构体实体
uchar idata file_buf[150];	   //文件数据缓冲区，读取到的文件数据放在其中

uchar Dev_No=0; //设备号，SDCARD的SD卡设备号的宏定义，根据设备号，znFAT会将底层存储设备驱动连接到相应的存储设备驱动
                        //动态的切换设备号，就可以实现在各种存储设备之间进行切换，这也是znFAT实现多设备的重要手段。比如，我
						//可以将SD卡上的文件拷贝到CF卡或U盘上，这就是多设备的最典型应用

#define COLOR(r,g,b) (((((((uint)r)>>3)<<6)|(((uint)g)>>2))<<5)|(((uint)b)>>3))	 //r红色分量 0~31  g绿色分量 0~63  b蓝色分量 0~31	






			
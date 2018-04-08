#ifndef __FAT_H__
#define __FAT_H__

#include "mytype.h" //类型重定义

#define SOC(c) (((c-pArg->FirstDirClust)*(pArg->SectorsPerClust))+pArg->FirstDirSector) // 用于计算簇的开始扇区
#define DEVS 1 //这里表明存储设备的个数，这里只有1个存储设备，就是SD卡

//设备表
#define SDCARD 0 //SD卡
#define UDISK  1 //U盘
#define CFCARD 2 //CF卡
#define OTHER  3 //其它
				 //这里的存储设备表，可以灵活扩充，以实现对更多存储设备的支持
//-------------------------------------------

#define MAKE_FILE_TIME(h,m,s)	((((unsigned int)h)<<11)+(((unsigned int)m)<<5)+(((unsigned int)s)>>1))	/* 生成指定时分秒的文件时间数据 */
#define MAKE_FILE_DATE(y,m,d)	(((((unsigned int)y)+20)<<9)+(((unsigned int)m)<<5)+((unsigned int)d))	/* 生成指定年月日的文件日期数据 */

//DPT:分区记录结构如下
struct PartRecord
{
 UINT8 Active;         //0x80表示此分区有效
 UINT8 StartHead;      //分区的开始磁头
 UINT8 StartCylSect[2];//开始柱面与扇区
 UINT8 PartType;       //分区类型
 UINT8 EndHead;        //分区的结束头
 UINT8 EndCylSect[2];  //结束柱面与扇区
 UINT8 StartLBA[4];    //分区的第一个扇区
 UINT8 Size[4];        //分区的大小 
};

//MBR:分区扇区（绝对0扇区）定义如下
struct PartSector
{
 UINT8 PartCode[446]; //MBR的引导程序
 struct PartRecord Part[4];   //4个分区记录
 UINT8 BootSectSig0;  //55
 UINT8 BootSectSig1;  //AA
};


//FAT32中对BPB的定义如下  一共占用90个字节
struct FAT32_BPB
{
 UINT8 BS_jmpBoot[3];     //跳转指令            offset: 0
 UINT8 BS_OEMName[8];     //                    offset: 3
 UINT8 BPB_BytesPerSec[2];//每扇区字节数        offset:11
 UINT8 BPB_SecPerClus[1]; //每簇扇区数          offset:13
 UINT8 BPB_RsvdSecCnt[2]; //保留扇区数目        offset:14
 UINT8 BPB_NumFATs[1];    //此卷中FAT表数       offset:16
 UINT8 BPB_RootEntCnt[2]; //FAT32为0            offset:17
 UINT8 BPB_TotSec16[2];   //FAT32为0            offset:19
 UINT8 BPB_Media[1];      //存储介质            offset:21
 UINT8 BPB_FATSz16[2];    //FAT32为0            offset:22
 UINT8 BPB_SecPerTrk[2];  //磁道扇区数          offset:24
 UINT8 BPB_NumHeads[2];   //磁头数              offset:26
 UINT8 BPB_HiddSec[4];    //FAT区前隐扇区数     offset:28
 UINT8 BPB_TotSec32[4];   //该卷总扇区数        offset:32
 UINT8 BPB_FATSz32[4];    //一个FAT表扇区数     offset:36
 UINT8 BPB_ExtFlags[2];   //FAT32特有           offset:40
 UINT8 BPB_FSVer[2];      //FAT32特有           offset:42
 UINT8 BPB_RootClus[4];   //根目录簇号          offset:44
 UINT8 FSInfo[2];         //保留扇区FSINFO扇区数offset:48
 UINT8 BPB_BkBootSec[2];  //通常为6             offset:50
 UINT8 BPB_Reserved[12];  //扩展用              offset:52
 UINT8 BS_DrvNum[1];      //                    offset:64
 UINT8 BS_Reserved1[1];   //                    offset:65
 UINT8 BS_BootSig[1];     //                    offset:66
 UINT8 BS_VolID[4];       //                    offset:67
 UINT8 BS_FilSysType[11]; //	                offset:71
 UINT8 BS_FilSysType1[8]; //"FAT32    "         offset:82
};

struct FAT32_FAT_Item
{
 UINT8 Item[4];
};

struct FAT32_FAT
{
 struct FAT32_FAT_Item Items[128];
};

struct direntry 
{
 UINT8 deName[8];       // 文件名，不足部分以空格补充
 UINT8 deExtension[3]; 	// 扩展名，不足部分以空格补充
 UINT8 deAttributes;   	// 文件属性
 UINT8 deLowerCase;    	// 0
 UINT8 deCHundredth;   	// 世纪
 UINT8 deCTime[2];     	// 创建时间
 UINT8 deCDate[2];     	// 创建日期
 UINT8 deADate[2];     	// 访问日期
 UINT8 deHighClust[2];  // 开始簇的高字
 UINT8 deMTime[2];     	// 最近的修改时间
 UINT8 deMDate[2];     	// 最近的修改日期
 UINT8 deLowCluster[2]; 	// 开始簇的低字
 UINT8 deFileSize[4];      // 文件大小 
};

//FAT32初始化时初始参数装入如下结构体中
struct FAT32_Init_Arg
{
 UINT8 DEV_No;

 UINT8 BPB_Sector_No;   //BPB所在扇区号
 UINT32 Total_Size;      //磁盘的总容量

 UINT32 FirstDirClust;   //根目录的开始簇
 UINT32  BytesPerSector;	//每个扇区的字节数
 UINT32  FATsectors;      //FAT表所占扇区数
 UINT32  SectorsPerClust;	 //每簇的扇区数
 UINT32 FirstFATSector;	 //第一个FAT表所在扇区
 UINT32 FirstDirSector;	 //第一个目录所在扇区
};

struct Date
{
 UINT16 year;
 UINT8 month;
 UINT8 day;
};

struct Time
{
 UINT8 hour;
 UINT8 min;
 UINT8 sec;
};

// Stuctures
struct FileInfoStruct
{
 UINT8  FileName[12];       //文件名
 UINT32  FileStartCluster;   //文件的开始簇

 UINT32  FileCurCluster;
 UINT32  FileSize;	    //文件的当前簇
 UINT32  FileCurSector;	    //文件的当前扇区
 UINT16   FileCurPos;         //文件在当前扇区中的位置
 UINT32  FileCurOffset;	    //文件的当前偏移量
 UINT32  Rec_Sec;            //文件的文件/目录项所在的扇区
 UINT16   nRec;               //文件的文件/目录项所在扇区中的位置

 UINT8  FileAttr;	    //文件属性				
 struct Time    FileCreateTime;	    //文件的创建时间
 struct Date    FileCreateDate;	    //文件的创建日期
 struct Time    FileMTime;          //文件的修改时间
 struct Date    FileMDate;          //文件的修改日期
 struct Date	FileADate;          //文件的访问日期

};

struct FSInfo //FAT32的文件系统信息结构
{
 UINT8 Head[4];
 UINT8 Resv1[480];
 UINT8 Sign[4];
 UINT8 Free_Cluster[4];
 UINT8 Last_Cluster[4];
 UINT8 Resv2[14];
 UINT8 Tail[2];
};

UINT8 FAT32_ReadSector(UINT32 addr,UINT8 *buf); //znFAT的与底层存储设备的驱动接口，读取扇区
UINT8 FAT32_WriteSector(UINT32 addr,UINT8 *buf);//znFAT的与底层存储设备的驱动接口，写入扇区

UINT32 LE2BE(UINT8 *dat,UINT8 len); //小端转大端

UINT8 FAT32_is_MBR(); //是否存在MBR
void FAT32_Analysis_DPT(); //分析DPT结构
UINT16 FAT32_Find_DBR(); //定位DBR

UINT32 FAT32_Get_Total_Size(); //获取总容量
void FAT32_Init(); //文件系统初始化

UINT32 Search_Last_Usable_Cluster(); //从获取FSInfo中的下一个可用空闲簇
UINT32 FAT32_Get_Remain_Cap(); //获取剩余容量

void FAT32_Update_FSInfo_Free_Clu(UINT32 PlusOrMinus); //更新FSInfo的空闲簇的数量
void FAT32_Update_FSInfo_Last_Clu(UINT32 Last_Clu); //更新FSInfo的下一个可用空闲簇

UINT32 FAT32_GetNextCluster(UINT32 LastCluster); //获取下一个簇
UINT32 FAT32_Enter_Dir(INT8 *path); //进入目录
UINT8 FAT32_Open_File(struct FileInfoStruct *pfi,INT8 *filepath,UINT32 item); //打开文件，支持通配
UINT8 FAT32_Seek_File(struct FileInfoStruct *pfi,UINT32 offset); //文件定位 
UINT32 FAT32_Read_File(struct FileInfoStruct *pfi,UINT32 offset,UINT32 len,UINT8 *pbuf); //读取文件数据
UINT32 FAT32_Read_FileX(struct FileInfoStruct *pfi,UINT32 offset,UINT32 len,void (*pfun)(UINT8)); //读取文件数据并进行数据处理
UINT32 FAT32_Find_Free_Clust(unsigned char flag);	//寻找下一个可用的空闲簇
UINT8 FAT32_Create_Rec(struct FileInfoStruct *pfi,UINT32 cluster,INT8 *name,UINT8 is_dir,UINT8 *ptd); //构建文件/目录项
UINT32 FAT32_Add_Dat(struct FileInfoStruct *pfi,UINT32 len,UINT8 *pbuf); //向文件追加数据
UINT8 FAT32_Create_Dir(struct FileInfoStruct *pfi,INT8 *dirpath,UINT8 *ptd); //创建目录，支持创建时间
UINT8 FAT32_Create_File(struct FileInfoStruct *pfi,INT8 *filepath,UINT8 *ptd); //创建文件，支持创建时间
UINT8 FAT32_Del_File(INT8 *filepath); //删除文件
unsigned char FAT32_XCopy_File(struct FAT32_Init_Arg *pArg1,struct FAT32_Init_Arg *pArg2,INT8 *sfilename,INT8 *tfilename,UINT8 *file_buf,UINT32 buf_size,unsigned char *pt); //文件拷贝，支持多设备中文件互拷
UINT8 FAT32_File_Close(struct FileInfoStruct *pfi); //文件关闭
UINT8 FAT32_Rename_File(INT8 *filename,INT8 *newfilename); //文件重命名

#endif
#ifndef __FAT_H__
#define __FAT_H__

#include "mytype.h" //�����ض���

#define SOC(c) (((c-pArg->FirstDirClust)*(pArg->SectorsPerClust))+pArg->FirstDirSector) // ���ڼ���صĿ�ʼ����
#define DEVS 1 //��������洢�豸�ĸ���������ֻ��1���洢�豸������SD��

//�豸��
#define SDCARD 0 //SD��
#define UDISK  1 //U��
#define CFCARD 2 //CF��
#define OTHER  3 //����
				 //����Ĵ洢�豸������������䣬��ʵ�ֶԸ���洢�豸��֧��
//-------------------------------------------

#define MAKE_FILE_TIME(h,m,s)	((((unsigned int)h)<<11)+(((unsigned int)m)<<5)+(((unsigned int)s)>>1))	/* ����ָ��ʱ������ļ�ʱ������ */
#define MAKE_FILE_DATE(y,m,d)	(((((unsigned int)y)+20)<<9)+(((unsigned int)m)<<5)+((unsigned int)d))	/* ����ָ�������յ��ļ��������� */

//DPT:������¼�ṹ����
struct PartRecord
{
 UINT8 Active;         //0x80��ʾ�˷�����Ч
 UINT8 StartHead;      //�����Ŀ�ʼ��ͷ
 UINT8 StartCylSect[2];//��ʼ����������
 UINT8 PartType;       //��������
 UINT8 EndHead;        //�����Ľ���ͷ
 UINT8 EndCylSect[2];  //��������������
 UINT8 StartLBA[4];    //�����ĵ�һ������
 UINT8 Size[4];        //�����Ĵ�С 
};

//MBR:��������������0��������������
struct PartSector
{
 UINT8 PartCode[446]; //MBR����������
 struct PartRecord Part[4];   //4��������¼
 UINT8 BootSectSig0;  //55
 UINT8 BootSectSig1;  //AA
};


//FAT32�ж�BPB�Ķ�������  һ��ռ��90���ֽ�
struct FAT32_BPB
{
 UINT8 BS_jmpBoot[3];     //��תָ��            offset: 0
 UINT8 BS_OEMName[8];     //                    offset: 3
 UINT8 BPB_BytesPerSec[2];//ÿ�����ֽ���        offset:11
 UINT8 BPB_SecPerClus[1]; //ÿ��������          offset:13
 UINT8 BPB_RsvdSecCnt[2]; //����������Ŀ        offset:14
 UINT8 BPB_NumFATs[1];    //�˾���FAT����       offset:16
 UINT8 BPB_RootEntCnt[2]; //FAT32Ϊ0            offset:17
 UINT8 BPB_TotSec16[2];   //FAT32Ϊ0            offset:19
 UINT8 BPB_Media[1];      //�洢����            offset:21
 UINT8 BPB_FATSz16[2];    //FAT32Ϊ0            offset:22
 UINT8 BPB_SecPerTrk[2];  //�ŵ�������          offset:24
 UINT8 BPB_NumHeads[2];   //��ͷ��              offset:26
 UINT8 BPB_HiddSec[4];    //FAT��ǰ��������     offset:28
 UINT8 BPB_TotSec32[4];   //�þ���������        offset:32
 UINT8 BPB_FATSz32[4];    //һ��FAT��������     offset:36
 UINT8 BPB_ExtFlags[2];   //FAT32����           offset:40
 UINT8 BPB_FSVer[2];      //FAT32����           offset:42
 UINT8 BPB_RootClus[4];   //��Ŀ¼�غ�          offset:44
 UINT8 FSInfo[2];         //��������FSINFO������offset:48
 UINT8 BPB_BkBootSec[2];  //ͨ��Ϊ6             offset:50
 UINT8 BPB_Reserved[12];  //��չ��              offset:52
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
 UINT8 deName[8];       // �ļ��������㲿���Կո񲹳�
 UINT8 deExtension[3]; 	// ��չ�������㲿���Կո񲹳�
 UINT8 deAttributes;   	// �ļ�����
 UINT8 deLowerCase;    	// 0
 UINT8 deCHundredth;   	// ����
 UINT8 deCTime[2];     	// ����ʱ��
 UINT8 deCDate[2];     	// ��������
 UINT8 deADate[2];     	// ��������
 UINT8 deHighClust[2];  // ��ʼ�صĸ���
 UINT8 deMTime[2];     	// ������޸�ʱ��
 UINT8 deMDate[2];     	// ������޸�����
 UINT8 deLowCluster[2]; 	// ��ʼ�صĵ���
 UINT8 deFileSize[4];      // �ļ���С 
};

//FAT32��ʼ��ʱ��ʼ����װ�����½ṹ����
struct FAT32_Init_Arg
{
 UINT8 DEV_No;

 UINT8 BPB_Sector_No;   //BPB����������
 UINT32 Total_Size;      //���̵�������

 UINT32 FirstDirClust;   //��Ŀ¼�Ŀ�ʼ��
 UINT32  BytesPerSector;	//ÿ���������ֽ���
 UINT32  FATsectors;      //FAT����ռ������
 UINT32  SectorsPerClust;	 //ÿ�ص�������
 UINT32 FirstFATSector;	 //��һ��FAT����������
 UINT32 FirstDirSector;	 //��һ��Ŀ¼��������
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
 UINT8  FileName[12];       //�ļ���
 UINT32  FileStartCluster;   //�ļ��Ŀ�ʼ��

 UINT32  FileCurCluster;
 UINT32  FileSize;	    //�ļ��ĵ�ǰ��
 UINT32  FileCurSector;	    //�ļ��ĵ�ǰ����
 UINT16   FileCurPos;         //�ļ��ڵ�ǰ�����е�λ��
 UINT32  FileCurOffset;	    //�ļ��ĵ�ǰƫ����
 UINT32  Rec_Sec;            //�ļ����ļ�/Ŀ¼�����ڵ�����
 UINT16   nRec;               //�ļ����ļ�/Ŀ¼�����������е�λ��

 UINT8  FileAttr;	    //�ļ�����				
 struct Time    FileCreateTime;	    //�ļ��Ĵ���ʱ��
 struct Date    FileCreateDate;	    //�ļ��Ĵ�������
 struct Time    FileMTime;          //�ļ����޸�ʱ��
 struct Date    FileMDate;          //�ļ����޸�����
 struct Date	FileADate;          //�ļ��ķ�������

};

struct FSInfo //FAT32���ļ�ϵͳ��Ϣ�ṹ
{
 UINT8 Head[4];
 UINT8 Resv1[480];
 UINT8 Sign[4];
 UINT8 Free_Cluster[4];
 UINT8 Last_Cluster[4];
 UINT8 Resv2[14];
 UINT8 Tail[2];
};

UINT8 FAT32_ReadSector(UINT32 addr,UINT8 *buf); //znFAT����ײ�洢�豸�������ӿڣ���ȡ����
UINT8 FAT32_WriteSector(UINT32 addr,UINT8 *buf);//znFAT����ײ�洢�豸�������ӿڣ�д������

UINT32 LE2BE(UINT8 *dat,UINT8 len); //С��ת���

UINT8 FAT32_is_MBR(); //�Ƿ����MBR
void FAT32_Analysis_DPT(); //����DPT�ṹ
UINT16 FAT32_Find_DBR(); //��λDBR

UINT32 FAT32_Get_Total_Size(); //��ȡ������
void FAT32_Init(); //�ļ�ϵͳ��ʼ��

UINT32 Search_Last_Usable_Cluster(); //�ӻ�ȡFSInfo�е���һ�����ÿ��д�
UINT32 FAT32_Get_Remain_Cap(); //��ȡʣ������

void FAT32_Update_FSInfo_Free_Clu(UINT32 PlusOrMinus); //����FSInfo�Ŀ��дص�����
void FAT32_Update_FSInfo_Last_Clu(UINT32 Last_Clu); //����FSInfo����һ�����ÿ��д�

UINT32 FAT32_GetNextCluster(UINT32 LastCluster); //��ȡ��һ����
UINT32 FAT32_Enter_Dir(INT8 *path); //����Ŀ¼
UINT8 FAT32_Open_File(struct FileInfoStruct *pfi,INT8 *filepath,UINT32 item); //���ļ���֧��ͨ��
UINT8 FAT32_Seek_File(struct FileInfoStruct *pfi,UINT32 offset); //�ļ���λ 
UINT32 FAT32_Read_File(struct FileInfoStruct *pfi,UINT32 offset,UINT32 len,UINT8 *pbuf); //��ȡ�ļ�����
UINT32 FAT32_Read_FileX(struct FileInfoStruct *pfi,UINT32 offset,UINT32 len,void (*pfun)(UINT8)); //��ȡ�ļ����ݲ��������ݴ���
UINT32 FAT32_Find_Free_Clust(unsigned char flag);	//Ѱ����һ�����õĿ��д�
UINT8 FAT32_Create_Rec(struct FileInfoStruct *pfi,UINT32 cluster,INT8 *name,UINT8 is_dir,UINT8 *ptd); //�����ļ�/Ŀ¼��
UINT32 FAT32_Add_Dat(struct FileInfoStruct *pfi,UINT32 len,UINT8 *pbuf); //���ļ�׷������
UINT8 FAT32_Create_Dir(struct FileInfoStruct *pfi,INT8 *dirpath,UINT8 *ptd); //����Ŀ¼��֧�ִ���ʱ��
UINT8 FAT32_Create_File(struct FileInfoStruct *pfi,INT8 *filepath,UINT8 *ptd); //�����ļ���֧�ִ���ʱ��
UINT8 FAT32_Del_File(INT8 *filepath); //ɾ���ļ�
unsigned char FAT32_XCopy_File(struct FAT32_Init_Arg *pArg1,struct FAT32_Init_Arg *pArg2,INT8 *sfilename,INT8 *tfilename,UINT8 *file_buf,UINT32 buf_size,unsigned char *pt); //�ļ�������֧�ֶ��豸���ļ�����
UINT8 FAT32_File_Close(struct FileInfoStruct *pfi); //�ļ��ر�
UINT8 FAT32_Rename_File(INT8 *filename,INT8 *newfilename); //�ļ�������

#endif
#include "fat.h"
#include "sd.h"        //�洢�豸��������д������������SD��
#include "string.h"

//ȫ�ֱ�������
struct direntry idata temp_rec;
INT8 temp_dir_name[13]; 
UINT32 temp_dir_cluster;
UINT32 temp_last_cluster;

UINT8 FAT32_Buffer[512]; //�������ݶ�д������,���ⲿ�ṩ

extern struct FAT32_Init_Arg *pArg; //��ʼ�������ṹ��ָ�룬����ָ��ĳһ�洢�豸�ĳ�ʼ�������ṹ�壬���ⲿ�ṩ

uchar (*pRS)(ulong,uchar *); //ָ��ʵ�ʴ洢�豸�Ķ����������ĺ���ָ�룬����ʵ�ֶ��豸��֧��
uchar (*pWS)(ulong,uchar *); //ָ��ʵ�ʴ洢�豸��д���������ĺ���ָ�룬����ʵ�ֶ��豸��֧��

extern uchar Dev_No;

/******************************************************************
 - ����������FAT�Ĵ洢�豸�ײ������ӿڣ���ȡ�洢�豸��addr������
             512���ֽڵ����ݷ���buf���ݻ�������
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ���������洢�豸�ĵײ������Խӣ�
 - ����˵����addr:������ַ
             buf:ָ�����ݻ�����
 - ����˵����0��ʾ��ȡ�����ɹ�������ʧ��
 - ע����������������Ǿ������ϵ����ִ洢�豸����SD������Ч����U�̡�
       CF��ͨ���ڳ����ж�̬���л���ͬ���豸�������Ӷ�ʵ�ֶ��豸(��ͬ
	   ʱ�Զ��ִ洢�豸���в����������SD�������ļ���U�̵ȵ�)����ͬ
	   �������л���ֻ��Ҫ�ڳ����иı�Dev_No���ȫ�ֱ�����ֵ����
 ******************************************************************/

UINT8 FAT32_ReadSector(UINT32 addr,UINT8 *buf) 
{
	switch(Dev_No)
	{
		case SDCARD:
			pRS=SD_Read_Sector;
			break;
		case UDISK:
			//pRS=CH375_Read_Sector;
			break;
		case CFCARD:
			//pRS=CF_Read_Sector;
			//��
			break;
		case OTHER:
			//��
			break;
	}
	return (*pRS)(addr,buf);  //�滻��ʵ�ʴ洢����������������������SD������������
}

/******************************************************************
 - ����������FAT�Ĵ洢�豸�ײ������ӿڣ���buf���ݻ������е�512��
             �ֽڵ�����д�뵽�洢�豸��addr������
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ���������洢�豸�ĵײ������Խӣ�
 - ����˵����addr:������ַ
             buf:ָ�����ݻ�����
 - ����˵����0��ʾ��ȡ�����ɹ�������ʧ��
 - ע����
 ******************************************************************/

/*UINT8 FAT32_WriteSector(UINT32 addr,UINT8 *buf)
{
 switch(Dev_No)
 {
  case SDCARD:
         pWS=SD_Write_Sector;
         break;
  case UDISK:
         //pWS=CH375_Write_Sector;
         break;
  case CFCARD:
         //pWS=CF_Write_Sector;
         //��
         break;
  case OTHER:
         //��
         break;
 }
 return (*pWS)(addr,buf); //�滻��ʵ�ʴ洢��������д������������SD������д����
}
*/
/******************************************************************
 - ����������С��ת��ˣ���LittleEndian��BigEndian
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����dat:ָ��ҪתΪ��˵��ֽ�����
             len:ҪתΪ��˵��ֽ����г���
 - ����˵����תΪ���ģʽ���ֽ���������������
 - ע�����磺С��ģʽ��       0x33 0x22 0x11 0x00  (���ֽ���ǰ)
             תΪ���ģʽ��Ϊ 0x00 0x11 0x22 0x33  (���ֽ���ǰ)
             ��������ֵΪ   0x00112233
             (CISC��CPUͨ����С�˵ģ�����FAT32Ҳ���ΪС�ˣ�����Ƭ��
              ����RISC��CPU��ͨ����˵���Ǵ�˵ģ�������Ҫ�����������
              �ڵĴ�Ŵ�����е��������ܵõ���ȷ����ֵ)
 ******************************************************************/

UINT32 LE2BE(UINT8 *dat,UINT8 len) 
{
 UINT32 temp=0;
 UINT32 fact=1;
 UINT8  i=0;
 for(i=0;i<len;i++)
 {
  temp+=dat[i]*fact; //�����ֽڳ�����Ӧ��Ȩֵ���ۼ�
  fact*=256; //����Ȩֵ
 }
 return temp;
}

/******************************************************************
 - ������������С���ַ�תΪ��д
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����c:Ҫת��Ϊ��д���ַ�            
 - ����˵����Ҫת�����ֽڵ���Ӧ�Ĵ�д�ַ�
 - ע��ֻ��Сд�ַ���Ч���������a~z��Сд�ַ�����ֱ�ӷ���
 ******************************************************************/

INT8 L2U(INT8 c)
{
 if(c>='a' && c<='z') return c+'A'-'a';
 else return c;
}

/******************************************************************
 - ������������ȡ0�����������û��MBR(��������¼)
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵������     
 - ����˵����1��ʾ��⵽MBR��0��ʾû�м�⵽MBR
 - ע����Щ�洢�豸��ʽ��ΪFAT32�Ժ�û��MBR����0��������DBR
       �����MBR������Ҫ������н������Եõ�DBR������λ�ã�ͬʱMBR��
       ����������������������Ϣ
 ******************************************************************/

/*UINT8 FAT32_is_MBR()
{
	UINT8 result;
	FAT32_ReadSector(0,FAT32_Buffer);
	if(FAT32_Buffer[0]!=0xEB) 
	{
		result=1;
	}
	else 
	{
		result=0;
	}
	return result;
}*/

/***********************************************************************
 - �����������õ�DBR���ڵ�������(���û��MBR����DBR����0����)
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵������     
 - ����˵����DBR��������ַ
 - ע��DBR�а����˺ܶ����õĲ�����Ϣ�������ȷ��λDBR������λ�ã��Ǽ�Ϊ
       ��Ҫ�ģ����潫��ר�ŵĺ�����DBR���н�������ȷ����DBR��ʵ��FAT32��
       ����
 ***********************************************************************/

UINT16 FAT32_Find_DBR()
{
 UINT16 sec_dbr;
 FAT32_ReadSector(0,FAT32_Buffer);
 if(FAT32_Buffer[0]!=0xeb) 
 {
  sec_dbr=LE2BE(((((struct PartSector *)(FAT32_Buffer))->Part[0]).StartLBA),4);
 }
 else
 {
  sec_dbr=0;
 }
 return sec_dbr;
}

/***********************************************************************
 - ������������ȡ������������
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������     
 - ����˵������������ֵ����λΪ�ֽ�
 - ע������õ�����������FAT32������������һ��С��ʵ�ʵ���������
 ***********************************************************************/

UINT32 FAT32_Get_Total_Size() 
{
 UINT32 temp;
 FAT32_ReadSector(pArg->BPB_Sector_No,FAT32_Buffer);
 FAT32_ReadSector(pArg->BPB_Sector_No,FAT32_Buffer);
 temp=((LE2BE((((struct FAT32_BPB *)(FAT32_Buffer))->BPB_TotSec32),4)))*pArg->BytesPerSector;
 return temp;
}

/***********************************************************************
 - ������������ȡFSInfo��ȡ�����һ�����ÿ��д�
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵������     
 - ����˵���������һ�����ÿ��д�
 - ע��FAT32�е�FSInfo����(����1����)�м�¼�������һ�����ÿ��д�
 ***********************************************************************/

UINT32 Search_Last_Usable_Cluster()
{
	FAT32_ReadSector(1+pArg->BPB_Sector_No,FAT32_Buffer);
	return LE2BE(((struct FSInfo *)FAT32_Buffer)->Last_Cluster,4);
}

/***********************************************************************
 - ����������FAT32�ļ�ϵͳ��ʼ��
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����FAT32_Init_Arg���͵Ľṹ��ָ�룬����װ��һЩ��Ҫ�Ĳ�����Ϣ��
             �Ա�����ʹ��     
 - ����˵������
 - ע����ʹ��znFATǰ����������Ǳ����ȱ����õģ����ܶ������Ϣװ�뵽
       argָ��Ľṹ���У�����������С����Ŀ¼��λ�á�FAT���С�ȵȡ�
       ��Щ�������󲿷���������DBR��BPB�У���˴˺�����Ҫ������DBR�Ĳ�������
 ***********************************************************************/

void FAT32_Init()
{
 struct FAT32_BPB *bpb;

 bpb=(struct FAT32_BPB *)(FAT32_Buffer);               //�����ݻ�����ָ��תΪstruct FAT32_BPB ��ָ��

 pArg->DEV_No=Dev_No; //װ���豸��

 pArg->BPB_Sector_No   =FAT32_Find_DBR();               //FAT32_FindBPB()���Է���BPB���ڵ�������
 pArg->BPB_Sector_No   =FAT32_Find_DBR();               //FAT32_FindBPB()���Է���BPB���ڵ�������
 pArg->Total_Size      =FAT32_Get_Total_Size();         //FAT32_Get_Total_Size()���Է��ش��̵�����������λ���ֽ�
 pArg->Total_Size      =FAT32_Get_Total_Size();         //FAT32_Get_Total_Size()���Է��ش��̵�����������λ����

 pArg->FATsectors      =LE2BE((bpb->BPB_FATSz32)    ,4);//װ��FAT��ռ�õ���������FATsectors��
 pArg->FirstDirClust   =LE2BE((bpb->BPB_RootClus)   ,4);//װ���Ŀ¼�غŵ�FirstDirClust��
 pArg->BytesPerSector  =LE2BE((bpb->BPB_BytesPerSec),2);//װ��ÿ�����ֽ�����BytesPerSector��
 pArg->SectorsPerClust =LE2BE((bpb->BPB_SecPerClus) ,1);//װ��ÿ����������SectorsPerClust ��
 pArg->FirstFATSector  =LE2BE((bpb->BPB_RsvdSecCnt) ,2)+pArg->BPB_Sector_No;//װ���һ��FAT�������ŵ�FirstFATSector ��
 pArg->FirstDirSector  =(pArg->FirstFATSector)+(bpb->BPB_NumFATs[0])*(pArg->FATsectors); //װ���һ��Ŀ¼������FirstDirSector��

 temp_last_cluster=Search_Last_Usable_Cluster();
}

/***********************************************************************
 - ������������ȡʣ������
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������    
 - ����˵����ʣ����������λ�ֽ�
 - ע����FSInfo�ж�ȡ���д��������Ӽ���õ�ʣ�����������λ�ֽ�
 ***********************************************************************/

/*UINT32 FAT32_Get_Remain_Cap()
{
 FAT32_ReadSector(1+pArg->BPB_Sector_No,FAT32_Buffer);
 if(((struct FSInfo *)FAT32_Buffer)->Free_Cluster[0]==0xff 
 && ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[1]==0xff 
 && ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[2]==0xff 
 && ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[3]==0xff)
 return pArg->Total_Size;
 else
 return LE2BE(((struct FSInfo *)FAT32_Buffer)->Free_Cluster,4)*pArg->SectorsPerClust*pArg->BytesPerSector; 
}
*/
/***********************************************************************
 - ��������������FSInfo�еĿ��ÿ��дص�����
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����PlusOrMinus:���ÿ��д�����1���1    
 - ����˵������
 - ע�������ļ���׷�����ݡ�ɾ���ļ��Ȳ��������ܻ�ʹ���õĿ��д����仯
       Ҫ��ʱ����
 ***********************************************************************/

/*void FAT32_Update_FSInfo_Free_Clu(UINT32 PlusOrMinus)
{
 UINT32 Free_Clu=0;
 FAT32_ReadSector(1+pArg->BPB_Sector_No,FAT32_Buffer);

 Free_Clu=(FAT32_Get_Remain_Cap())/(pArg->SectorsPerClust*pArg->BytesPerSector);

 if(PlusOrMinus) Free_Clu++;
 else Free_Clu--;

 ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[0]=((uchar *)&Free_Clu)[3]; 
 ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[1]=((uchar *)&Free_Clu)[2];
 ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[2]=((uchar *)&Free_Clu)[1];
 ((struct FSInfo *)FAT32_Buffer)->Free_Cluster[3]=((uchar *)&Free_Clu)[0];
 FAT32_WriteSector(1+pArg->BPB_Sector_No,FAT32_Buffer);   
}*/

/***********************************************************************
 - ��������������FSInfo�е���һ�����ÿ��дصĴغ�
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����Last_Clu:��Ҫ���µ�FSInfo�е���һ�����ÿ��дصĴغ�    
 - ����˵������
 - ע��FSInfo�е���һ�����ÿ��дغſ��Ը��ļ�ϵͳһ���ο���ֱ�Ӹ����ļ�ϵͳ
       ��һ�����õĿ��д���ʲô�ط�
 ***********************************************************************/

/*void FAT32_Update_FSInfo_Last_Clu(UINT32 Last_Clu)
{
 FAT32_ReadSector(1+pArg->BPB_Sector_No,FAT32_Buffer);  
 ((struct FSInfo *)FAT32_Buffer)->Last_Cluster[0]=((uchar *)&Last_Clu)[3]; 
 ((struct FSInfo *)FAT32_Buffer)->Last_Cluster[1]=((uchar *)&Last_Clu)[2];
 ((struct FSInfo *)FAT32_Buffer)->Last_Cluster[2]=((uchar *)&Last_Clu)[1];
 ((struct FSInfo *)FAT32_Buffer)->Last_Cluster[3]=((uchar *)&Last_Clu)[0];
 FAT32_WriteSector(1+pArg->BPB_Sector_No,FAT32_Buffer);
}*/

/***********************************************************************
 - ���������������һ���صĴغ�
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����LastCluster:��׼�غ�  
 - ����˵����LastClutster����һ�صĴغ�
 - ע�������һ�صĴغţ�����ƾ��FAT��������¼�Ĵ�����ϵ��ʵ�ֵ�
 ***********************************************************************/

UINT32 FAT32_GetNextCluster(UINT32 LastCluster)
{
 UINT32 temp;
 struct FAT32_FAT *pFAT;
 struct FAT32_FAT_Item *pFAT_Item;
 temp=((LastCluster/128)+pArg->FirstFATSector);
 FAT32_ReadSector(temp,FAT32_Buffer);
 pFAT=(struct FAT32_FAT *)FAT32_Buffer;
 pFAT_Item=&((pFAT->Items)[LastCluster%128]);
 return LE2BE((UINT8 *)pFAT_Item,4);
}

/***********************************************************************
 - �����������Ƚ�Ŀ¼��
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����a:ָ��Ŀ¼��1��ָ��
             b:ָ��Ŀ¼��2��ָ��
 - ����˵�����������Ŀ¼����ͬ�ͷ���1������Ϊ0
 ***********************************************************************/

UINT8 Compare_Dir_Name(INT8 *a,INT8 *b)
{
 UINT8 i;
 for(i=0;i<8;i++)
 {
  if(a[i]!=b[i]) return 0;
 }
 return 1;
}

/***********************************************************************
 - �����������ļ���ƥ��(֧�ִ�*?ͨ������ļ�����ƥ��)
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����pat:Դ�ļ��������Ժ�*��?ͨ��� �� *.txt �� A?.mp3�ȵ�
             name:Ŀ���ļ���
 - ����˵������������ļ���ƥ��ͷ���1������Ϊ0
 - ע������ͨ���ļ���ƥ�䣬�����������ӣ����� A*.txt �� ABC.txt��ƥ���
   ͬʱ�� ABCDE.txtҲ��ƥ��ġ��˹������ļ�ö���н����õ�������ƥ��
   �ļ�������һ���������ļ�
 ***********************************************************************/

UINT8 FilenameMatch(INT8 *pat,INT8 *name)
{
 INT16 match,ndone;
 INT8 *cpp,*cpn;
 cpp=pat;
 cpn=name;
 match=1;
 ndone=1;
 while(ndone)
 {
  switch (*cpp)
  {
   case '*':
            cpp++;
            cpn=strchr(cpn,*cpp);
            if(cpn==NULL)
            {
             cpn=name;
             while(*cpn) cpn++;
            }
            break;
   case '?':
            cpp++;
            cpn++;
            break;
   case 0:
            if(*cpn!=0)
            match=0;
            ndone=0;
            break;
   default:
            if((*cpp)==(*cpn))
            {
             cpp++;
             cpn++;
            }
            else
            {
             match=0;
             ndone=0;
            }
            break;
  }
 }
 return(match);
}

/***********************************************************************
 - ����������FAT32���ļ�Ŀ¼����ļ����ֶ�(8���ֽ�)��תΪ��ͨ���ļ���
             �磺ABC     MP3 ��תΪ ABC.MP3
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����dName��ָ���ļ�Ŀ¼����ļ����ֶε�ָ��
             pName��ָ��ת����ɺ���ļ���
 - ����˵������
 - ע���˺�����������FilenameMatch�������Ϳ���ʵ�ֶ��ļ���ͨ��ƥ��
 ***********************************************************************/

void FAT32_toFileName(char *dName,char *pName)
{
 char i=7,j=0,k=0;
 while(dName[i--]==' ');
 for(j=0;j<i+2;j++) pName[j]=L2U(dName[j]);
 pName[j++]='.';
 i=10;
 while(dName[i--]==' ');
 k=j+i-6;
 i=0;
 for(;j<k;j++) pName[j]=dName[8+(i++)];
 pName[j]=0; 
}

/***********************************************************************
 - �������������ַ����е�Сд�ַ���תΪ��д�ַ�
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ڲ�
 - ����˵����str��ָ���ת�����ַ���
 - ����˵������
 - ע�����ļ���������£��ļ����е��ַ���ʵ���Ǵ�д�ַ���Ϊ�˷��㣬���ļ�
       ����תΪ��д
 ***********************************************************************/

void Str2Up(char *str)
{
 uchar len=strlen(str),i;
 for(i=0;i<len;i++)
 {
  str[i]=L2U(str[i]); 
 } 
}

/**************************************************************************
 - ��������������һ��Ŀ¼
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����path:Ŀ¼��·�� ���磺"\\dir1\\dir2\\" �����һ������\\���� 
 - ����˵��������Ŀ¼�Ŀ�ʼ�غţ��������Ŀ¼ʧ�ܣ�����Ŀ¼�����ڣ��򷵻�0
 - ע���˺����ɺ����FAT32_Open_File�Ⱥ������ã�����ʵ�ִ�����Ŀ¼�µ��ļ�
       �������û�����
 **************************************************************************/

UINT32 FAT32_Enter_Dir(INT8 *path)
{
 UINT32 Cur_Clust,sec_temp,iSec,iDir,Old_Clust;
 UINT8 i=1,counter=0,flag=0;
 struct direntry *pDir;
 INT8 name[20];

 Cur_Clust=pArg->FirstDirClust;
 if(path[1]==0 && path[0]=='\\') return Cur_Clust;
 else
 {
  while(path[i]!=0)
  {
   if(path[i]=='\\')
   {
    for(;counter<8;counter++)
	{
	 name[counter]=' ';
	}
	name[counter]=0;
	counter=0;
	
	do
	{
	 sec_temp=(SOC(Cur_Clust));
	 for(iSec=sec_temp;iSec<sec_temp+pArg->SectorsPerClust;iSec++)
	 {
	  FAT32_ReadSector(iSec,FAT32_Buffer);
	  for(iDir=0;iDir<pArg->BytesPerSector;iDir+=sizeof(struct direntry))
      {
       pDir=((struct direntry *)(FAT32_Buffer+iDir));
	   if(Compare_Dir_Name(pDir->deName,name))
	   {
	    flag=1;
		Cur_Clust=LE2BE(pDir->deLowCluster,2)+LE2BE(pDir->deHighClust,2)*65536;
		iDir=pArg->BytesPerSector;
		iSec=sec_temp+pArg->SectorsPerClust;
	   } 
	  }
	 }
	 Old_Clust=Cur_Clust;
	}while(!flag && (Cur_Clust=FAT32_GetNextCluster(Cur_Clust))!=0x0fffffff);
	if(!flag) 
	{
	 temp_dir_cluster=Old_Clust;
	 strcpy(temp_dir_name,name);
	 flag=0;
	 return 0;
	}
	flag=0; 
   }
   else
   {
    name[counter++]=(L2U(path[i]));
   }
   i++;
  }
 }
 name[counter]=0; 
 flag=1;
 temp_dir_cluster=Cur_Clust;
 strcpy(temp_dir_name,name);
 return Cur_Clust;
}

/**************************************************************************
 - ������������һ���ļ�(֧���ļ���ͨ�䣬�� A*.txt �� *.*)
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����pfi: FileInfoStruct���͵Ľṹ��ָ�룬����װ���ļ��Ĳ�����Ϣ
              �����ļ��Ĵ�С���ļ������ơ��ļ��Ŀ�ʼ�صȵȣ��Ա�����ʹ��
             filepath: �ļ���·����֧�������Ŀ¼ ����
              "\\dir1\\dir2\\dir3\\....\\test.txt"
			 item�����ļ�������ͨ���*��?������£�ʵ����֮ƥ����ļ�����
			 һ����item���Ǵ򿪵��ļ����������������ͨ���������ļ���6����
			 ���item=3����ô�˺����ͻ����6���ļ��а�˳���ź�Ϊ3���Ǹ�
			 �ļ�(item��Ŵ�0��ʼ)
 - ����˵����0���ɹ� 1���ļ������� 2��Ŀ¼������
 - ע�����ļ����ɹ��кܶ�ԭ�򣬱����ļ������ڡ��ļ���ĳһ��Ŀ¼������
       ͨ������������������ļ�����С��item��ֵ�ȵ�
	   ͨ������£��ļ�����û��ͨ�����item��ֵ����ȡ0�Ϳ�����
 **************************************************************************/

UINT8 FAT32_Open_File(struct FileInfoStruct *pfi,INT8 *filepath,unsigned long item)
{
 UINT32 Cur_Clust,sec_temp,iSec,iFile,iItem=0;
 UINT8 flag=0,index=0,i=0;
 struct direntry *pFile;
 INT8 temp_file_name[13];
 while(filepath[i]!=0)
 {
  if(filepath[i]=='\\') index=i;
  i++;
 }

 if(Cur_Clust=FAT32_Enter_Dir(filepath))
 {
  Str2Up(temp_dir_name);
 do
 { 
  sec_temp=SOC(Cur_Clust);
  for(iSec=sec_temp;iSec<sec_temp+pArg->SectorsPerClust;iSec++)
  {	
   FAT32_ReadSector(iSec,FAT32_Buffer);
   for(iFile=0;iFile<pArg->BytesPerSector;iFile+=sizeof(struct direntry))
   {
    pFile=((struct direntry *)(FAT32_Buffer+iFile));
	FAT32_toFileName(pFile->deName,temp_file_name);
	if(FilenameMatch(temp_dir_name,temp_file_name) && pFile->deName[0]!=0xe5 && pFile->deAttributes&0x20) //ƥ���ļ���
	{
	 if(item==iItem)
	 {	 
	 flag=1;
     Cur_Clust=LE2BE(pFile->deLowCluster,2)+LE2BE(pFile->deHighClust,2)*65536;

     pfi->FileSize=LE2BE(pFile->deFileSize,4);
	 strcpy(pfi->FileName,temp_file_name);
	 pfi->FileStartCluster=LE2BE(pFile->deLowCluster,2)+LE2BE(pFile->deHighClust,2)*65536;
	 pfi->FileCurCluster=pfi->FileStartCluster;
	 pfi->FileCurSector=SOC(pfi->FileStartCluster);
	 pfi->FileCurPos=0;
	 pfi->FileCurOffset=0;
	 pfi->Rec_Sec=iSec;
	 pfi->nRec=iFile;

	 pfi->FileAttr=pFile->deAttributes;
	 sec_temp=LE2BE(pFile->deCTime,2);
	 (pfi->FileCreateTime).sec=(sec_temp&0x001f)*2;
	 (pfi->FileCreateTime).min=((sec_temp>>5)&0x003f);
	 (pfi->FileCreateTime).hour=((sec_temp>>11)&0x001f);
	 sec_temp=LE2BE(pFile->deCDate,2);
	 (pfi->FileCreateDate).day=((sec_temp)&0x001f);
	 (pfi->FileCreateDate).month=((sec_temp>>5)&0x000f);
	 (pfi->FileCreateDate).year=((sec_temp>>9)&0x007f)+1980;

	 sec_temp=LE2BE(pFile->deMTime,2);
	 (pfi->FileMTime).sec=(sec_temp&0x001f)*2;
	 (pfi->FileMTime).min=((sec_temp>>5)&0x003f);
	 (pfi->FileMTime).hour=((sec_temp>>11)&0x001f);
	 sec_temp=LE2BE(pFile->deMDate,2);
	 (pfi->FileMDate).day=((sec_temp)&0x001f);
	 (pfi->FileMDate).month=((sec_temp>>5)&0x000f);
	 (pfi->FileMDate).year=((sec_temp>>9)&0x007f)+1980;

	 sec_temp=LE2BE(pFile->deADate,2);
	 (pfi->FileADate).day=((sec_temp)&0x001f);
	 (pfi->FileADate).month=((sec_temp>>5)&0x000f);
	 (pfi->FileADate).year=((sec_temp>>9)&0x007f)+1980;
	    
	 iFile=pArg->BytesPerSector;
	 iSec=sec_temp+pArg->SectorsPerClust;
	 }
	 else
	 {
	  iItem++;
	 }
	} 
   }
  }
 }while(!flag && (Cur_Clust=FAT32_GetNextCluster(Cur_Clust))!=0x0fffffff);
 if(!flag) 
 {
  return 1;
 }
 return 0;
 }
 else
 {
  return 2; 
 }
}

/**************************************************************************
 - �����������ļ���λ
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����pfi:FileInfoStruct���͵Ľṹ��ָ�룬����װ���ļ�������Ϣ���ļ�
             ��λ��pfi��ָ��Ľṹ���е���ز����ͱ������ˣ������ļ��ĵ�ǰ
             �������ļ���ǰ�����е�λ�ã��ļ��ĵ�ǰƫ�����ȵȣ��Ա�����ʹ��
             offset:Ҫ��λ��ƫ���������offset�����ļ��Ĵ�С����λ���ļ���
             ĩβ
 - ����˵�����ļ���λ�ɹ�����0������Ϊ1
 - ע���˺����������FAT32_Read_File���ã�����ʵ�ִ�ָ��λ�ö�ȡ���ݣ�������
       �û�ֱ�ӵ���Щ����
 **************************************************************************/

UINT8 FAT32_Seek_File(struct FileInfoStruct *pfi,UINT32 offset)
{
 UINT32 i,temp;

if(offset<=pfi->FileSize)
{ 
 if(offset==pfi->FileCurOffset)
 {
  pfi->FileCurPos%=pArg->BytesPerSector;
  return 1;  
 }
 if(offset<pfi->FileCurOffset) 
 {
  pfi->FileCurCluster=pfi->FileStartCluster;
  pfi->FileCurSector=SOC(pfi->FileCurCluster);
  pfi->FileCurPos=0;
  pfi->FileCurOffset=0;
 } 
 if((offset-pfi->FileCurOffset)>=(pArg->BytesPerSector-pfi->FileCurPos))	 //Ŀ��ƫ�������ļ���ǰƫ����������ֽ�����С���ļ��ڵ�ǰ�����е�λ�õ�����ĩβ���ֽ���
 {
  pfi->FileCurOffset+=(pArg->BytesPerSector-pfi->FileCurPos);
  pfi->FileCurPos=0;
  if(pfi->FileCurSector-SOC(pfi->FileCurCluster)==(pArg->SectorsPerClust-1))
  {
   pfi->FileCurCluster=FAT32_GetNextCluster(pfi->FileCurCluster);
   pfi->FileCurSector=SOC(pfi->FileCurCluster);
  }
  else
  {
   pfi->FileCurSector++; 
  }
 }
 else
 {
  pfi->FileCurPos=(pfi->FileCurPos+offset-pfi->FileCurOffset)%pArg->BytesPerSector;
  pfi->FileCurOffset=offset;
  return 1;
 }
 temp=SOC(pfi->FileCurCluster);
 if((offset-(pfi->FileCurOffset))/pArg->BytesPerSector+(pfi->FileCurSector-temp)>(pArg->SectorsPerClust-1))
 {
  pfi->FileCurOffset+=(((pArg->SectorsPerClust)-(pfi->FileCurSector-(SOC(pfi->FileCurCluster))))*pArg->BytesPerSector);
  pfi->FileCurCluster=FAT32_GetNextCluster(pfi->FileCurCluster);
  pfi->FileCurSector=SOC(pfi->FileCurCluster);
  pfi->FileCurPos=0;
 }
 else
 {
  pfi->FileCurSector+=(offset-pfi->FileCurOffset)/pArg->BytesPerSector;
  pfi->FileCurPos=(offset-pfi->FileCurOffset)%pArg->BytesPerSector;
  pfi->FileCurOffset=offset;
  return 1;
 }

 temp=(offset-pfi->FileCurOffset)/(pArg->BytesPerSector*pArg->SectorsPerClust);
 for(i=0;i<temp;i++)
 {
  pfi->FileCurCluster=FAT32_GetNextCluster(pfi->FileCurCluster);
 }
 pfi->FileCurOffset+=(temp*(pArg->BytesPerSector*pArg->SectorsPerClust));
 pfi->FileCurSector=(SOC(pfi->FileCurCluster))+(offset-pfi->FileCurOffset)/pArg->BytesPerSector;
 pfi->FileCurPos=((offset-pfi->FileCurOffset))%pArg->BytesPerSector;
 pfi->FileCurOffset=offset;
}
else
{
 return 1;
}
 return 0;
}

/**************************************************************************
 - �������������ļ���ĳһ��λ�ô�����ȡһ�����ȵ����ݣ��������ݻ�������
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����pfi:FileInfoStruct���͵Ľṹ��ָ�룬����װ���ļ�������Ϣ���ļ�
             ��ȡ�Ĺ����У��˽ṹ���е���ز�������£������ļ��ĵ�ǰƫ������
             �ļ��ĵ�ǰ�������ļ��ĵ�ǰ�صȵ�
             offset:Ҫ��λ��ƫ������ҪС���ļ��Ĵ�С 
             len:Ҫ��ȡ�����ݵĳ��ȣ����len+offset�����ļ��Ĵ�С����ʵ�ʶ�
             ȡ���������Ǵ�offset��ʼ���ļ�����
             pbuf:���ݻ�����
 - ����˵������ȡ����ʵ�ʵ����ݳ��ȣ������ȡʧ�ܣ�����ָ����ƫ�����������ļ�
             ��С���򷵻�0
 - ע���ڶ�ȡһ���ļ�������ǰ�������Ƚ����ļ���FAT32_Open_File��
 **************************************************************************/

UINT32 FAT32_Read_File(struct FileInfoStruct *pfi,UINT32 offset,UINT32 len,UINT8 *pbuf)
{
	UINT32 i,j,k,temp;
	UINT32 counter=0;
	if(offset<pfi->FileSize)
	{
		if(offset+len>pfi->FileSize) 
			len=pfi->FileSize-offset;
		FAT32_Seek_File(pfi,offset);  
		FAT32_ReadSector(pfi->FileCurSector,FAT32_Buffer);
		for(i=pfi->FileCurPos;i<pArg->BytesPerSector;i++)
		{
			if(counter>=len) 
			{
				return len;
			}
			pbuf[counter]=FAT32_Buffer[i];
			counter++;
			pfi->FileCurPos++;
			pfi->FileCurOffset++;
		}
		if(pfi->FileCurSector-(SOC(pfi->FileCurCluster))!=(pArg->SectorsPerClust-1))
		{
			for(j=pfi->FileCurSector+1;j<(SOC(pfi->FileCurCluster))+pArg->SectorsPerClust;j++)
			{
				FAT32_ReadSector(j,FAT32_Buffer);
				pfi->FileCurSector=j;
				for(i=0;i<pArg->BytesPerSector;i++)
				{
					if(counter>=len)
					{
						return len;
					}
					pbuf[counter]=FAT32_Buffer[i];
					counter++;
					pfi->FileCurPos++;
					pfi->FileCurOffset++;
				}
			}
		} 
  temp=(len-counter)/(pArg->BytesPerSector*pArg->SectorsPerClust);
  for(k=0;k<temp;k++)
  {
   pfi->FileCurCluster=FAT32_GetNextCluster(pfi->FileCurCluster);
   for(j=(SOC(pfi->FileCurCluster));j<(SOC(pfi->FileCurCluster))+pArg->SectorsPerClust;j++)
   {
    FAT32_ReadSector(j,FAT32_Buffer);
    pfi->FileCurSector=j;
    for(i=0;i<pArg->BytesPerSector;i++)
    {
     if(counter>=len)  
 	 {
       return len;
     }
     pbuf[counter]=FAT32_Buffer[i];
     counter++;
     pfi->FileCurOffset++;
	 pfi->FileCurPos++;
	 pfi->FileCurPos%=pArg->BytesPerSector;
    } 
   }    
  }
  pfi->FileCurCluster=FAT32_GetNextCluster(pfi->FileCurCluster);
  temp=(SOC(pfi->FileCurCluster))+((len-counter)/pArg->BytesPerSector);
  pfi->FileCurSector=(SOC(pfi->FileCurCluster));
  for(j=(SOC(pfi->FileCurCluster));j<temp;j++)
  {
   FAT32_ReadSector(j,FAT32_Buffer);
   pfi->FileCurSector=j;
   for(i=0;i<pArg->BytesPerSector;i++)
   {
    if(counter>=len) 
    {
      return len;
    }
    pbuf[counter]=FAT32_Buffer[i];
    counter++;
    pfi->FileCurPos++;
    pfi->FileCurPos%=pArg->BytesPerSector;
    pfi->FileCurOffset++;
   }   
  }
		pfi->FileCurSector=j;
		FAT32_ReadSector(pfi->FileCurSector,FAT32_Buffer);
		temp=len-counter;
		for(i=0;i<temp;i++)
		{
			if(counter>=len) 
			{
				return len;
			}
			pbuf[counter]=FAT32_Buffer[i];
			counter++;
			pfi->FileCurPos++;
			pfi->FileCurPos%=pArg->BytesPerSector;
			pfi->FileCurOffset++;  
		}
	}
	else
	{
		len=0;
	}
	return len;
}

/**************************************************************************
 - �����������ļ��ر�
 - ����ģ�飺FAT�ļ�ϵͳģ��
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����pfi:ָ��ǰ�򿪵��ļ����ļ���Ϣ�ṹ
 - ����˵����0:�ɹ�
 - ע����
 **************************************************************************/

/*UINT8 FAT32_File_Close(struct FileInfoStruct *pfi)
{
 UINT16 i=0;							
 for(i=0;i<sizeof(struct FileInfoStruct);i++)
 {
  ((UINT8 *)pfi)[i]=0;
 }
 return 0;
}*/

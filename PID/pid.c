//pid.c
/*PID = PID->UK_REAL + PID->KP*[E(k)-E(k-1)]+PID->KI*E(k)+PID->KD*[E(k)-2E(k-1)+E(k-2)];(������PID��ʽ)
�������: PID->RK(�趨ֵ),PID->CK(ʵ��ֵ),PID->KP,PID->KI,PID->KD
��������: U(K)*/
#include"defines.h"
#include"pid.h"
#define MAXOUT 0xff
//#define MAXGAP 100
 
void pid_exe(pid_str*PID)
{
    PID->EK[2]=PID->EK[1];
    PID->EK[1]=PID->EK[0];
    PID->EK[0]=PID->RK-PID->CK;
    PID->UK_REAL=PID->UK_REAL
        +PID->KP*(PID->EK[0]-PID->EK[1])//΢��һ�κ���ּ�ԭ��
        +(float)PID->KI*PID->EK[0]/PID->F//ֱ�ӻ���
        +(float)PID->KD*(PID->EK[0]-2*PID->EK[1]+PID->EK[2])*PID->F;//����΢�ֺ���ּ�һ��΢��
    if((PID->UK_REAL>>PID->BITMOV)>=MAXOUT)
    {
        PID->UK=MAXOUT;
    }else if(PID->UK_REAL>>PID->BITMOV<=-MAXOUT)
    {
        PID->UK=-MAXOUT;
    }else
    {
        PID->UK=PID->UK_REAL>>PID->BITMOV;
    }
         
}
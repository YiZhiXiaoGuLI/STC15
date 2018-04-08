//pid.h
#ifndef __PID__
#define __PID__
/*PID = Uk + KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)];(������PID��ʽ)
�������: RK(�趨ֵ),CK(ʵ��ֵ),KP,KI,KD
��������: U(K)*/
typedef struct PIDValue
{
    int8 KP;
    int8 KI;
    int8 KD;
    int8 F;
    int8 BITMOV;
    int EK[3];
     
    int UK;
    int RK;
    int CK;
    int UK_REAL;
 
}pid_str;
//PIDValueStr  PID;
void    pid_exe(pid_str *PID)  ;
#endif
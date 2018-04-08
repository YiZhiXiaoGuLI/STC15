//**************************************************************************************//
//******************MS15开发板LED（IO)测试程序******************************************//
//*******************本程序参考了STC官网例程********************************************//
//********************* hiold.taobao.com ***********************************************//
#include "reg51.h"

sfr P4 = 0xc0;
sfr P5 = 0xc8;

void delay()
{
    int i, j;

    for (i=0; i<800; i++)
    for (j=0; j<500; j++);
}


void main()
{

    P0 = 0xfe;
    delay();
    P0 = 0xfc;
    delay();
    P0 = 0xf8;
    delay();
    P0 = 0xf0;
    delay();
    P0 = 0xe0;
    delay();
    P0 = 0xc0;
    delay();
    P0 = 0x80;
    delay();
    P0 = 0x00;
    delay();
    P0 = 0xff;

    P1 = 0xfe;
    delay();
    P1 = 0xfc;
    delay();
    P1 = 0xf8;
    delay();
    P1 = 0xf0;
    delay();
    P1 = 0xe0;
    delay();
    P1 = 0xc0;
    delay();
    P1 = 0x80;
    delay();
    P1 = 0x00;
    delay();
    P1 = 0xff;

    P3 = 0xfe;
    delay();
    P3 = 0xfc;
    delay();
    P3 = 0xf8;
    delay();
    P3 = 0xf0;
    delay();
    P3 = 0xe0;
    delay();
    P3 = 0xc0;
    delay();
    P3 = 0x80;
    delay();
    P3 = 0x00;
    delay();
    P3 = 0xff;

    P2 = 0xfe;
    delay();
    P2 = 0xfc;
    delay();
    P2 = 0xf8;
    delay();
    P2 = 0xf0;
    delay();
    P2 = 0xe0;
    delay();
    P2 = 0xc0;
    delay();
    P2 = 0x80;
    delay();
    P2 = 0x00;
    delay();
    P2 = 0xff;

    P4 = 0xfe;
    delay();
    P4 = 0xfc;
    delay();
    P4 = 0xf8;
    delay();
    P4 = 0xf0;
    delay();
    P4 = 0xe0;
    delay();
    P4 = 0xc0;
    delay();
    P4 = 0x80;
    delay();
    P4 = 0x00;
    delay();
    P4 = 0xff;

    P5 = 0xfe;
    delay();
    P5 = 0xfc;
    delay();
    P5 = 0xf8;
    delay();
    P5 = 0xf0;
    delay();
    P5 = 0xe0;
    delay();
    P5 = 0xc0;
    delay();
    P5 = 0x80;
    delay();
    P5 = 0x00;
    delay();
    P5 = 0xff;

    while (1)
    {
        P0 = 0x00;
        delay();
        P0 = 0xff;

        P1 = 0x00;
        delay();
        P1 = 0xff;

        P3 = 0x00;
        delay();
        P3 = 0xff;

        P2 = 0x00;
        delay();
        P2 = 0xff;

        P4 = 0x00;
        delay();
        P4 = 0xff;

        P5 = 0x00;
        delay();
        P5 = 0xff;
    }
}

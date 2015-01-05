fir_pro
=======

#include<reg51.h>
#include<stdio.h>
#define OSC 11059200
#define BAUDRATE 9600
void main(void)
{
  unsigned char c;
  TMOD=0x20;
  SCON=0x50;
  PCON=0x80;
  TL1=256-(OSC/12/16/BAUDRATE);
  TH1=256-(OSC/12/16/BAUDRATE);
  TR1=1;
  RI=0;
  TI=0;
  while(1)
  {
  while(RI==0);
  RI=0;
  c=SBUF;
  switch(c)
  {
    case 0x0d:
	case 0x0a:SBUF=c;
	break;
	default:SBUF=++c;
	break;
  
  }
  while(!TI);
  TI=0;
  
  }
  
}

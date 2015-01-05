
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int


void Delay(uint del)
{
	uint i,j;
	for(i=0; i<del; i++)
	for(j=0; j<1827; j++)    
	;
}


void Main(void)
{
	while(1)
	{
		/*北面的三个LED亮*/
		P1 = 0xf8;
		P2 = 0xff;  
		Delay(30);
		/*东面的三个LED亮*/
		P1 = 0xc7;
		P2 = 0xff;  
		Delay(30);
		/*南面的三个LED亮*/
		P1 = 0x3f;
		P2 = 0xfe;
		Delay(30);
		/*西面的三个LED亮*/
		P1 = 0xff;
		P2 = 0xf1;
		Delay(30);

		/*北面的两个LED亮，中间一个不亮*/
		P1 = 0xfa;
		P2 = 0xff;
		Delay(30);
		/*东面的两个LED亮，中间一个不亮*/
		P1 = 0xd7;
		P2 = 0xff;
		Delay(30);
		/*南面的两个LED亮，中间一个不亮*/
		P1 = 0xbf;
		P2 = 0xfe;
		Delay(30);
		/*西面的两个LED亮，中间一个不亮*/
		P1 = 0xff;
		P2 = 0xf5;
		Delay(30);

		/*12个LED全亮*/
		P1 = 0x00;
		P2 = 0xf0;
		Delay(20);
		/*12个LED全灭*/
		P1 = 0xff;
		P2 = 0xff;
		Delay(20);
		/*12个LED全亮*/
		P1 = 0x00;
		P2 = 0xf0;
		Delay(20);
		/*12个LED全灭*/
		P1 = 0xff;
		P2 = 0xff;
		Delay(20);

		Delay(50);  //延时0.5秒
	}
}

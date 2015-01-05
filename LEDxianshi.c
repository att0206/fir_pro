
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
//数码管的段码编码
uchar table[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


void Delay(uint i)
{
	uint x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

void DisLED(uchar temp)
{
	P0 = 0;                          //消隐
	P2 = 0xfb;						 //第6位数码管显示
	P0 = table[(temp / 100)%10];	     //在这里取 i 的百位数
	Delay(2);			         	 //延时0.3秒后显示下一个数
	P0 = 0;	      					 //消隐
	P2 = 0xfd;						 //第7位数码管显示
	P0 = table[(temp / 10)%10];	     //在这里取 i 的十位数
	P0 = P0 | 0x80;
	Delay(2);			             //延时0.3秒后显示下一个数
	P0 = 0;	       	   				 //消隐
	P2 = 0xfe;						 //第8位数码管显示
	P0 = table[temp % 10];	       	     //在这里取 i 的个位数
	Delay(2);			             //延时0.3秒后显示下一个数		
}

void main()
{
	uchar i=150,j;
	while(1)
	{
		if(i != 0)					//i不等于0，那么 进行数码管的显示，10* 10=100毫秒
		{
			for(j=0;j<15;j++)
			{
				DisLED(i);		   	//调用数码管显示代码
			}
			i--;
		}
		else
		{
			for(j=0;j<10;j++)
			{
				DisLED(i);			 //数码管显示
			}
			P0 = 0x00;				 //数码管不显示
			Delay(300);	
		}             
	}
}

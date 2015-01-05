
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define jump_ROM 0xCC
#define start 0x44
#define read_EEROM 0xBE
            //DS18B
unsigned char TMPH,TMPL; 
uchar code tuxing[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x07,0x0F,0x1F,0x1F,
                     0x00,0x00,0x00,0x00,0x1C,0x1E,0x1F,0x1F,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                     0x1F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x00,
                     0x1F,0x1F,0x1E,0x1C,0x00,0x00,0x00,0x00,
                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uchar code yun[]={0x00,0x00,0x00,0x00,0x03,0x07,0x1F,0x1F,
                  0x00,0x00,0x00,0x0F,0x1F,0x1F,0x1F,0x1F,
                  0x00,0x00,0x00,0x00,0x18,0x1E,0x1F,0x1F,
                  0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1F,
                  0x1F,0x1F,0x07,0x00,0x00,0x00,0x00,0x00,
                  0x1F,0x1F,0x1E,0x0C,0x00,0x00,0x00,0x00,
                  0x1F,0x1F,0x1E,0x0C,0x00,0x00,0x00,0x00,
                  0x1E,0x1D,0x03,0x00,0x00,0x00,0x00,0x00};                                                           

unsigned char  table[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//这三个引脚参考资料
sbit E=P2^7;		//1602使能引脚
sbit RW=P2^6;		//1602读写引脚	
sbit RS=P2^5;		//1602数据/命令选择引脚
sbit sw1=P2^4;
sbit sw2=P2^3;
sbit led=P2^2;
sbit DQ = P2^1;
sbit sw3=P2^0;
/********************************************************************
延时
***********************************************************************/
void delay()
{
	_nop_();
	_nop_();
}
 void delay1(uint N)
{
	int i;
	for(i=0; i<N; i++)
	;
}
void Delay(uint del)
{
	uint i,j;
	for(i=0;i<del;i++)
	for(j=0;j<=148;j++)
	{
	}	
}
//DS1820温度读取
uchar Reset(void)
{
	uchar deceive_ready;
	DQ = 0;
	delay1(29);
	DQ = 1;
	delay1(3);
	deceive_ready = DQ;
	delay1(25);
	return(deceive_ready);
}


uchar read_bit(void)
{
	uchar i;
	DQ = 0;
	DQ = 1;
	for(i=0; i<3; i++);
	return(DQ);
}



void write_bit(uchar bitval)
{
DQ=0;if(bitval==1)
DQ=1;
delay1(5);
DQ=1;
}


uchar read_byte(void)
{
	uchar i,m,receive_data;
	m = 1;
	receive_data = 0;
	for(i=0; i<8; i++)
	{
		if(read_bit())
		{
			receive_data = receive_data + (m << i);
		}
		delay1(6);
	}
	return(receive_data);
}


void write_byte(uchar val)
{
	uchar i,temp;
	for(i=0; i<8; i++)
	{
		temp = val >> i;
		temp = temp & 0x01;
		write_bit(temp);
		delay1(5);
	}
}  //

/********************************************************************
检忙函数
***********************************************************************/
void Busy(void)
{
	bit busy_flag = 1;
	P0 = 0x80;
	RS = 0;
	delay();
	RW = 1;
	delay();
	E = 1;
	//Delay(1);
	while(1)
	{
		busy_flag = (bit)(P0 & 0x80);
		if(busy_flag == 0)
		{
			break;
		}
	}
	E = 0;
}
/********************************************************************
写入地址
***********************************************************************/
void wcmd(uchar del)
{
	RS = 0;
	delay();
	RW = 0;
	delay();
	E = 0;
	delay();
	P0 = del;
	delay();
	E = 1;
	delay();
	E = 0;
}

/********************************************************************
写入数据
***********************************************************************/

void wdata(uchar del)
{
	delay();
	RS = 1;
	delay();
	RW = 0;
	delay();
	E = 0;
	delay();
	P0 = del;
    delay();
	E = 1;
	delay();
	E = 0;
}

/********************************************************************
清屏函数
***********************************************************************/
void L1602_init(void)
{
	Delay(15);
	wcmd(0x38);
	Delay(5);
	wcmd(0x38);
	Delay(5);
	wcmd(0x38);
	wcmd(0x38);
	Busy();
	wcmd(0x08);
	Busy();	
	wcmd(0x01);
	Busy();
	wcmd(0x06);
	Busy();
	wcmd(0x0c);
}

/********************************************************************
输入字符
***********************************************************************/
void L1602_char(uchar hang,uchar lie,char sign)
{
	uchar a;
	if(hang == 1) 
	{
		a = 0x80;
	}
	if(hang == 2)
	{
		a = 0xc0;
	}
	a = a + lie - 1;
	Busy();
	wcmd(a);
	Busy();
	wdata(sign);
}

/******************************************************************** 
写入字符串
***********************************************************************/
void L1602_string(uchar hang,uchar lie,uchar *p)
{
	uchar a;
	if(hang == 1) 
	{
		a = 0x80;
	}
	if(hang == 2)
	{
		a = 0xc0;
	}
	a = a + lie - 1;
	while(1)
	{
		Busy();
		wcmd(a);
		Busy();
		wdata(*p);
		a++;
		p++;			
		if((*p == '\0')||(a==0x90)||(a==0xd0)) 
		{
			break;
		}
	}
}

void Main()		//主函数
{	
   
    uchar z,*p,i,j,tmp,k;
	uchar  table1[16]={" * 208121238! * "};
	L1602_init();
	for(k=0;k<3;k++)  //笑脸滚动
	{L1602_string(1,1,"   Welcoming   ");
     L1602_string(2,0," ^_^         ^_^");
	 if(sw1==0 || sw2==0 || sw3==0)	      //按键sw1,sw2,sw3任意一个按下则退出
	 {break;}
	 Delay(1000);
	 
	 L1602_init();
	 L1602_string(1,1,"   Welcoming   ");
    L1602_string(2,0,"   ^_^   ^_^   ");
	if(sw1==0 || sw2==0 || sw3==0)
	 {break;}
	Delay(1000);
	L1602_init();
	L1602_string(1,1,"   Welcoming   ");
    L1602_string(2,0,"       ^_^      ");
	if(sw1==0 || sw2==0 || sw3==0)
	 {break;}
	Delay(1000);
	L1602_init();
	}

	if(sw1==0)  //按键sw1按下
	{
	led=1;
	while(1)
	{	
	    L1602_init();
	    tmp=0x40;
	    k=0;
		
		p = table1;
		L1602_string(1,1,"Hello,Chao Long!");
		for(z=0;z<16;z++)
		{
			L1602_char(2,z+1,*p);
			p++;
			Delay(80);		
		}
		Delay(500);
		Busy();
		wcmd(0x01);
		if((sw2==0)||(sw3==0))
		{break;}

	}

	}
	if(sw2==0)	   //按键sw2按下
	{
	L1602_init();
	while(1)
	  {
	    uchar i;
	    led=0;
	    if((sw1==0)||(sw3==0))
	    {
	       break;
	    }
      }
	}	
    	
    if(sw3==0)		 //按键sw3按下
	{
	 uchar temp;
	 P3 = 0x00;
	 while(1)
	 {	L1602_init(); 
	    L1602_string(1,1,"W-State:");	//温度低于20度显示COOL；
		L1602_string(2,11,"Cool!");
	    Reset();
		write_byte(jump_ROM);
		write_byte(start);
		Reset();
		write_byte(jump_ROM);
		write_byte(read_EEROM);
		TMPL = read_byte();
		TMPH = read_byte();
		temp = TMPL / 16 + TMPH * 16;
		P1 = table[temp/10%10];
		P3 = 0xfd;
		Delay(1);
		P1 = table[temp%10];
		P3 = 0xfe;
		Delay(5);
		if(((temp/10%10)==2)&((temp%10)<9))	//当温度在20~29度之间时显示太阳
		{ 
		  L1602_init();
		  L1602_string(1,1,"W-State:"); 
		  while(1)						//显示太阳
	       {
	        tmp=0x40;
	        k=0;	
	        for(j=0;j<8;j++)
	         {
	          for(i=0;i<8;i++)
		       {
	             wcmd(tmp+i);
		         wdata(tuxing[k]);
		         k++;
	           }
		         tmp+=8;
	         }
		       for(i=0;i<4;i++)
		         {
		           L1602_char(1,12+i,i);

		         }
		   for(i=4;i<8;i++)
		    {
			  L1602_char(2,12+i-4,i);
			}
	  
	       
			  Delay(1000);
			 break;
	     	 }
	        }
		   if((sw1==0)||(sw2==0))
		   {
		     break;
		   
		   }
	  }
	}
}

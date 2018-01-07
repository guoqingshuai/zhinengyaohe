#include "stm32f10x.h"
#include "Hal_Step_otor.h"
#include "Hal_GUANGOU.h"
#include <delay.h>
#include "Hal_led/Hal_led.h"
//#define    MI_ERR    (-2)
extern int a;
extern int b;//提醒吃药
extern int h;//提醒吃药
extern int g;//提醒吃药
  
void yuandian(void);  //原点
void SXzhengzhuan(int);   //上下正传 
void SXfanzhuan(int);
//void Szhangzhuan();  //上正传
//void Sfanzhuan();    //上反转
void Xzhengzhuan(int);  //下正转
void Xfanzhuan(int);    //下反转
void zhendong(void);  //震动
void huiyuandian(void);   //下反转




void Delay1(__IO u32 nCount);


/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
void luoyao(uint8_t Tmp1,uint8_t Tmp2, uint8_t Tmp3,uint8_t Tmp4)
{
	printf("落药开始\n");
	int Ayao = Tmp1;
	int Byao = Tmp2;
	int Cyao = Tmp3;
	int Dyao = Tmp4;
	STEP_GPIO_Init();
//	/* LED 端口初始化 */
//	LED_GPIO_Config();

//开始写A药
//首先判断是不是在原点（不再原点）先回原点
//回原点之后  同时102 度
//然后下面再-30 读
//然后震动
//然后正传30度
//然后回原点
//判断时间和分钟书不是正确

	
//回原点完成

	

	huiyuandian(); 
 //回原点
	//A点 落药
		while(a <Ayao)
		{	   
			
			printf(" A药执行开始\n");
			SXzhengzhuan(190);  //上下正传
			for(g=0;g<3;g++)
		{
			Xfanzhuan(80);  //下反转30度  落药到中间
			zhendong();//震动
			Xzhengzhuan(80);  //下正传30度  归位
		}
			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
			{	
				SXfanzhuan(1);  //上下反转   回原点  落药
			}
			Delay1(39990000);
			printf("A=%d",a);
		}
		 huiyuandian();
     if(Byao!=0) {   //回原点
			Xfanzhuan(800);  //下反转30度  落药到中间
		 }
	      	a = 0;
		     while(a<Byao)
	   	{
			
			printf("B药执行开始\n");
			SXzhengzhuan(370);  //上下正传
			for(g=0;g<3;g++)
{				
			Xfanzhuan(70);  //下反转30度  落药到中间
			zhendong();  //震动
			Xzhengzhuan(70);  //下正传30度  归位
}
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//				SXfanzhuan(1);  //上下反转   回原点  落药
//			}
					SXfanzhuan(370);
			Delay1(39999999);
			printf("B=%d",a);
		}
	huiyuandian();   //回原点
		if(Cyao!=0){
	  Xfanzhuan(340);}
		a = 0;
		while(a<Cyao)
		{
	
			printf("C药执行开始\n");
			SXzhengzhuan(585);  //上下正传
			Xfanzhuan(70);  //下反转30度  落药到中间
			zhendong();  //震动
			Xzhengzhuan(70);  //下正传30度  归位
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//			SXfanzhuan(1);  //上下反转   回原点  落药
//			}
			SXfanzhuan(585);  //上下反转   回原点  落药
			Delay1(39999999);
			printf("C=%d",a);
		}
	
		huiyuandian();   //回原点
		if(Dyao!=0) {   //回原点
	   Xfanzhuan(500); }
				a = 0;
		while(a<Dyao)
		{

			printf("D药执行开始\n");
			SXzhengzhuan(790);  //上下正传
			Xfanzhuan(70);  //下反转30度  落药到中间
			zhendong();  //震动
			Xzhengzhuan(70);  //下正传30度  归位
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//			SXfanzhuan(1);  //上下反转   回原点  落药
//			}
			SXfanzhuan(790);  //上下反转   回原点  落药
			Delay1(39999999);
			printf("C=%d",a);
		}
//		a = 0;
//		while(a<Dyao)
//		{
//			printf("D药执行开始\n");
//			SXfanzhuan(200);  //上下正传
//			Xzhengzhuan(70);  //下正传30度  归位
//			zhendong();  //震动
//			Xfanzhuan(70);  //下反转30度  落药到中间
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			  {
//				SXzhengzhuan(1);  //上下反转   回原点  落药
//			  }
//			Delay1(39999999);
//      	printf("D=%d",a);			
//		  }
			b=1;
			h=1;
		printf("现在的数据是b=%d h=%d" ,b,h);

				
}


void yuandian()  //回原点
{
		Coil_A1 
		Delay1(30000);//上层正传
		Coil_AB1
		Delay1(30000);
		Coil_B1
		Delay1(30000);
		Coil_BC1
		Delay1(30000);
		Coil_C1
		Delay1(30000);
		Coil_CD1
		Delay1(30000);
		Coil_D1
		Delay1(30000);
		Coil_DA1
		Delay1(30000);
		Coil_OFF
		Delay1(30000);
}

void SXzhengzhuan(int t)  //上下正传
{
	printf("上下一起转");  
	int i;
	for(i=0;i<t;i++)
		{	
	    Coil_DA1   
		  Coil_A2 
			Delay1(30000);
			Coil_D1
		  Coil_AB2
			Delay1(30000);
			Coil_CD1
		  Coil_B2
			Delay1(30000);
			Coil_C1
		  Coil_BC2
			Delay1(30000);
			Coil_BC1
		  Coil_C2
			Delay1(30000);
			Coil_CD2
			Coil_B1
			Delay1(30000);
			Coil_AB1
		  Coil_D2
			Delay1(30000);
		  Coil_A1
			Coil_DA2
			Delay1(30000);
			Coil_OFF
			Coil_OFF2
			Delay1(30000);
	}
}

void SXfanzhuan(int t)   //上下反转
{
	printf("上下一起反转");
	int i;
	for(i=0;i<t;i++)
	{		
		  Coil_A1 
	    Coil_DA2 
			Delay1(30000);
	  	Coil_AB1
			Coil_D2
			Delay1(30000);
	  	Coil_B1
			Coil_CD2
			Delay1(30000); 
      Coil_BC1		
			Coil_C2
			Delay1(30000);
		  Coil_C1 
			Coil_BC2
			Delay1(30000);
		  Coil_CD1
		  Coil_B2
			Delay1(30000);
			Coil_D1
		  Coil_AB2
			Delay1(30000);
			Coil_DA1
			Coil_A2
			Delay1(30000);
			Coil_OFF
			Coil_OFF2
			Delay1(30000);
	}
}
 
void zhendong()    //震动
{
	printf("震动电机执行中");
	int i, x;
	for(i=0;i<1;i++)
	{
		    LED_ON(LED1); 
		for(i=0;i<50;i++)
		{
			for(x=0;x<5;x++)
			{Delay1(3000);}
		}
	   LED_OFF(LED1);
	}
}
//void Szhengzhuan()   //上正传
//{
//	
//}

//void Sfanzhuan()    //上反转
//{
//	
//}

void Xzhengzhuan(int t)  //下正传
{
	printf("下正传");
	int i;
	for(i=0;i<t;i++)//正传30 度   
	{
	    Coil_A2 
			Delay1(30000);//下层正传
			Coil_AB2
			Delay1(30000);
			Coil_B2
			Delay1(30000);
			Coil_BC2
			Delay1(30000);
			Coil_C2
			Delay1(30000);
			Coil_CD2
			Delay1(30000);
			Coil_D2
			Delay1(30000);
		  Coil_DA2
			Delay1(30000);
			Coil_OFF
			Delay1(30000);
	}
}
void Xfanzhuan(int t)    //下反转
{
	printf("下面反转\n");
	int i;
	for(i=0;i<t;i++)
	{
	    Coil_DA2 
			Delay1(30000);
			Coil_D2
			Delay1(30000);
			Coil_CD2
			Delay1(30000);
			Coil_C2
			Delay1(30000);
			Coil_BC2
			Delay1(30000);
			Coil_B2
			Delay1(30000);
			Coil_AB2
			Delay1(30000);
		  Coil_A2
			Delay1(30000);
			Coil_OFF2
			Delay1(30000);
	}
}
void huiyuandian()    //回原点
{
	printf("回原点中");
	
		while(1)
	{
		if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==0||GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==0)
		{
			SXfanzhuan(1); 
		}
		printf("上层回原点中");
		if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==1)  //判断是否为原点
		{
			Delay1(300000);//这个可以调整
			if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==1)
			{
					printf("上层回原点\n");
				  break;
			}
			else
			{
				yuandian();
			}
		}
		else
		{
			yuandian();
		}
	}
	
			while(1)
	{
		printf("下层回原点");
		if(GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==1)  //判断是否为原点
		{
			Delay1(30);//这个可以调整
			if(GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==1)
			{
					printf("下层回原点\n");
				break;
			}
			else
			{
				Xfanzhuan(1);
			}
		}
		else
		{
		Xfanzhuan(1);
		}
	}
	
	
	
}




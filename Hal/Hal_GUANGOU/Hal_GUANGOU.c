#include "Hal_GUANGOU.h"

#include "Hal_Step_otor.h"
#include "stdio.h"
#include "delay.h"
extern  int a ;

void Delay1(__IO u32 nCount)	 //简单的延时函数
{
	while(--nCount);
} 

void STEP_GPIO_GInit(void)//光耦
	{
      GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_APB2PeriphClockCmd( GPIO_G1_CLK | GPIO_G2_CLK, ENABLE);//??LED
    
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;//IPU					//???????????
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//?????
	
      GPIO_InitStructure.GPIO_Pin = GPIO_G1_PIN;	//光耦						//??LED1
      GPIO_Init(GPIO_G1_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_G2_PIN;	//光耦						//??LED2
      GPIO_Init(GPIO_G2_PORT, &GPIO_InitStructure);	
		
		    
		  
		
}
void STEP_GPIO_HUOER(void)//霍尔
	{
      GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_APB2PeriphClockCmd( GPIO_Y1_CLK | GPIO_Y2_CLK, ENABLE);//??LED
    
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;//IPU					//???????????
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//?????
	
	    GPIO_InitStructure.GPIO_Pin = GPIO_Y1_PIN;	//霍尔						//??LED1
      GPIO_Init(GPIO_Y1_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_Y2_PIN;		//霍尔					//??LED2
      GPIO_Init(GPIO_Y2_PORT, &GPIO_InitStructure);
	
		  GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG3_PIN;	//备用输入
      GPIO_Init(GPIO_BEIYONG3_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG4_PIN;		//备用输入
      GPIO_Init(GPIO_BEIYONG4_PORT, &GPIO_InitStructure);
}
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	  void STEP_GPIO_GInit();//光耦

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
//	
//    EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//下降沿
//	  EXTI_InitStructure.EXTI_LineCmd=ENABLE; 
//  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//    
//	
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键 所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0最高级
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 
 
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式 EXTI_Trigger_Rising  上升
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿
	  EXTI_InitStructure.EXTI_LineCmd=ENABLE; 
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键 所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0最高级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 	
	
	
}
void EXTI0_IRQHandler(void)  //0,1,2,3,4,9_5,15_10
{ 
	      printf("进入中断");
		     a=a+1;
        printf(" %d",a);
	      Delay1(300000);
        	
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE4上的中断标志位  
}

void EXTI1_IRQHandler(void)  //0,1,2,3,4,9_5,15_10
{	
 
	
	
	
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line12); //清除LINE0上的中断标志位  
}



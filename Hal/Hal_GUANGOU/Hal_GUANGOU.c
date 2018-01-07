#include "Hal_GUANGOU.h"

#include "Hal_Step_otor.h"
#include "stdio.h"
#include "delay.h"
extern  int a ;

void Delay1(__IO u32 nCount)	 //�򵥵���ʱ����
{
	while(--nCount);
} 

void STEP_GPIO_GInit(void)//����
	{
      GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_APB2PeriphClockCmd( GPIO_G1_CLK | GPIO_G2_CLK, ENABLE);//??LED
    
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;//IPU					//???????????
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//?????
	
      GPIO_InitStructure.GPIO_Pin = GPIO_G1_PIN;	//����						//??LED1
      GPIO_Init(GPIO_G1_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_G2_PIN;	//����						//??LED2
      GPIO_Init(GPIO_G2_PORT, &GPIO_InitStructure);	
		
		    
		  
		
}
void STEP_GPIO_HUOER(void)//����
	{
      GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_APB2PeriphClockCmd( GPIO_Y1_CLK | GPIO_Y2_CLK, ENABLE);//??LED
    
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;//IPU					//???????????
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//?????
	
	    GPIO_InitStructure.GPIO_Pin = GPIO_Y1_PIN;	//����						//??LED1
      GPIO_Init(GPIO_Y1_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_Y2_PIN;		//����					//??LED2
      GPIO_Init(GPIO_Y2_PORT, &GPIO_InitStructure);
	
		  GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG3_PIN;	//��������
      GPIO_Init(GPIO_BEIYONG3_PORT, &GPIO_InitStructure);						//???LED1

      GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG4_PIN;		//��������
      GPIO_Init(GPIO_BEIYONG4_PORT, &GPIO_InitStructure);
}
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	  void STEP_GPIO_GInit();//����

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
//	
//    EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж�ģʽ
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�½���
//	  EXTI_InitStructure.EXTI_LineCmd=ENABLE; 
//  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//	
//    
//	
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ��� ���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0��߼�
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure); 
 
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж�ģʽ EXTI_Trigger_Rising  ����
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//������
	  EXTI_InitStructure.EXTI_LineCmd=ENABLE; 
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ��� ���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0��߼�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 	
	
	
}
void EXTI0_IRQHandler(void)  //0,1,2,3,4,9_5,15_10
{ 
	      printf("�����ж�");
		     a=a+1;
        printf(" %d",a);
	      Delay1(300000);
        	
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE4�ϵ��жϱ�־λ  
}

void EXTI1_IRQHandler(void)  //0,1,2,3,4,9_5,15_10
{	
 
	
	
	
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line12); //���LINE0�ϵ��жϱ�־λ  
}



/**
********************************************************
*
* @file      Hal_led.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*
* @brief     ??? ????????
*            Gizwits Smart Cloud  for Smart Products
*            ??|??|??|??|??|??|??|??
*            www.gizwits.com
*
*********************************************************/







#include "Hal_Step_otor.h"
#include "stdio.h"
#include "delay.h"


#define WT588_1  GPIO_SetBits  (GPIO_WT588DA_PORT,GPIO_WT588DA_PIN);
#define WT588_0  GPIO_ResetBits(GPIO_WT588DA_PORT,GPIO_WT588DA_PIN);



/***********************************************
????:LED_GPIO_Init
?		?:???LED1,2,3,4?
?		?:?
? ? ?:?
***********************************************/
void STEP_GPIO_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(GPIO_A1_CLK | GPIO_B1_CLK | GPIO_C1_CLK | GPIO_D1_CLK|GPIO_A2_CLK | GPIO_B2_CLK | GPIO_C2_CLK | GPIO_D2_CLK, ENABLE);//??LED
    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					//??IO???
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					//???????????
	
    GPIO_InitStructure.GPIO_Pin = GPIO_A1_PIN;	//步进						//??LED1
    GPIO_Init(GPIO_A1_PORT, &GPIO_InitStructure);						//???LED1

    GPIO_InitStructure.GPIO_Pin = GPIO_B1_PIN;							//??LED2
    GPIO_Init(GPIO_B1_PORT, &GPIO_InitStructure);						//???LED2

    GPIO_InitStructure.GPIO_Pin = GPIO_C1_PIN;							//??LED3
    GPIO_Init(GPIO_C1_PORT, &GPIO_InitStructure);	//???LED3
		
    GPIO_InitStructure.GPIO_Pin = GPIO_D1_PIN;							//??LED4
    GPIO_Init(GPIO_D1_PORT, &GPIO_InitStructure);						//???LED4
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_A2_PIN;							//??LED1
    GPIO_Init(GPIO_A2_PORT, &GPIO_InitStructure);						//???LED1

    GPIO_InitStructure.GPIO_Pin = GPIO_B2_PIN;							//??LED2
    GPIO_Init(GPIO_B2_PORT, &GPIO_InitStructure);						//???LED2

    GPIO_InitStructure.GPIO_Pin = GPIO_C2_PIN;							//??LED3
    GPIO_Init(GPIO_C2_PORT, &GPIO_InitStructure);	//???LED3
		
    GPIO_InitStructure.GPIO_Pin = GPIO_D2_PIN;							//??LED4
    GPIO_Init(GPIO_D2_PORT, &GPIO_InitStructure);


		
//		GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG_PIN;//备用引脚配置成输出模式
//    GPIO_Init(GPIO_BEIYONG_PORT, &GPIO_InitStructure);//原理图二三
    
//    GPIO_InitStructure.GPIO_Pin = GPIO_BEIYONG1_PIN;
//    GPIO_Init(GPIO_BEIYONG1_PORT, &GPIO_InitStructure);	
		
		
		
		GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);//步进电机
		GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);
		GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);
		GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);
		
	  GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);//步进电机2
	  GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);
	  GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);
	  GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);
		
		

		

		
//		GPIO_ResetBits(GPIO_BEIYONG_PORT,GPIO_BEIYONG_PIN);//初始化备用引脚
//		GPIO_ResetBits(GPIO_BEIYONG1_PORT,GPIO_BEIYONG1_PIN);
		
		
		

}

void Send_oneline(unsigned char addr)
 {  u8 i;
	 
	WT588_0;
	Delay_ms(5);  
	for(i=0;i<8;i++)
	{  WT588_1;
	if(0x01&addr )
	{Delay_us(600);  
	WT588_0;
	Delay_us(200);} 
	else{
	Delay_us(200); 
	WT588_0;
	Delay_us(600); }
	addr>>=1; }
	WT588_1; 	
 }



uint8_t  Speed=10;
unsigned quan=512;//旋转一周时间

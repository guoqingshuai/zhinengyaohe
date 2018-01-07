/**
********************************************************
*
* @file      Hal_infrared.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*
* @brief     机智云 只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/

#include <stm32f10x.h>
#include "Hal_infrared/Hal_infrared.h"
#include "Hal_Step_otor.h"
extern int b;
extern int h;
extern int q;
void IR_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(Infrared_GPIO_CLK,ENABLE);//使能PORTA,PORTE时钟
    GPIO_InitStructure.GPIO_Pin  = Infrared_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(Infrared_GPIO_PORT, &GPIO_InitStructure);
}
bool IR_Handle(void)
{
	printf("进入霍尔检测");
    if(GPIO_ReadInputDataBit(Infrared_GPIO_PORT, Infrared_GPIO_PIN))
    {
			if(b%2==0)
				{
					if(q==1)
					{		
						if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
              {
								printf("语音提醒归位");
        Send_oneline(4);
								q=0;
                }
							}
						
					printf("药盒在原位置");
			   return 0;
				}
			else
			{
				
    printf("执行中药盒以拿出");				
		if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
       {
        Send_oneline(2);
       }
		    return 1;
			}

    }
    else
    {
			printf("yyyyyy%d",h);
			if(h ==1 )
			{
				printf("hahahhahahhh");
			
				if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
       {
        Send_oneline(3);
				 b=0;
				 	h=0;
				 q=1;
			 }
			 
		 }

        return 0;
		 }
			
    }

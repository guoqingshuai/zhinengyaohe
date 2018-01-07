/**
********************************************************
*
* @file      Hal_infrared.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*
* @brief     ������ ֻΪ����Ӳ������
*            Gizwits Smart Cloud  for Smart Products
*            ����|��ֵ|����|����|��ȫ|����|����|��̬
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

    RCC_APB2PeriphClockCmd(Infrared_GPIO_CLK,ENABLE);//ʹ��PORTA,PORTEʱ��
    GPIO_InitStructure.GPIO_Pin  = Infrared_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(Infrared_GPIO_PORT, &GPIO_InitStructure);
}
bool IR_Handle(void)
{
	printf("����������");
    if(GPIO_ReadInputDataBit(Infrared_GPIO_PORT, Infrared_GPIO_PIN))
    {
			if(b%2==0)
				{
					if(q==1)
					{		
						if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
              {
								printf("�������ѹ�λ");
        Send_oneline(4);
								q=0;
                }
							}
						
					printf("ҩ����ԭλ��");
			   return 0;
				}
			else
			{
				
    printf("ִ����ҩ�����ó�");				
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

/**
********************************************************
*
* @file      Hal_led.c
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
#include "Hal_led/Hal_led.h"
#include "Hal_Step_otor.h"


void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_LED1_CLK | GPIO_LED2_CLK | GPIO_LED3_CLK | GPIO_LED4_CLK|GPIO_WT588DA_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN;
    GPIO_Init(GPIO_LED1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_LED2_PIN;
    GPIO_Init(GPIO_LED2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_LED3_PIN;
    GPIO_Init(GPIO_LED3_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_LED4_PIN;
    GPIO_Init(GPIO_LED4_PORT, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_WT588DA_PIN;//����ģ��
    GPIO_Init(GPIO_WT588DA_PORT, &GPIO_InitStructure);	

    LED_OFF(LED1);
    LED_OFF(LED2);
    LED_OFF(LED3);
    LED_OFF(LED4);
}

void LED_ON(uint8_t LEDNUM)
{
    switch (LEDNUM)
    {
    case LED1:
        GPIO_SetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
        break;
    case LED2:
        GPIO_SetBits(GPIO_LED2_PORT,GPIO_LED2_PIN);
        break;
    case LED3:
        GPIO_SetBits(GPIO_LED3_PORT,GPIO_LED3_PIN);
        break;
    case LED4:
        GPIO_SetBits(GPIO_LED4_PORT,GPIO_LED4_PIN);
        break;
    default:
        break;
    }
}

void LED_OFF(uint8_t LEDNUM)
{
    switch (LEDNUM)
    {
    case LED1:
        GPIO_ResetBits(GPIO_LED1_PORT,GPIO_LED1_PIN);
        break;
    case LED2:
        GPIO_ResetBits(GPIO_LED2_PORT,GPIO_LED2_PIN);
        break;
    case LED3:
        GPIO_ResetBits(GPIO_LED3_PORT,GPIO_LED3_PIN);
        break;
    case LED4:
        GPIO_ResetBits(GPIO_LED4_PORT,GPIO_LED4_PIN);
        break;
    default:
        break;
    }
}

/**
********************************************************
*
* @file      hal_key.c
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
#include "Hal_key/hal_key.h"
#include "Hal_Step_otor.h"

extern uint8_t									     	 SN;
uint8_t 				KeyCountTime;


/*******************************************************************************
* Function Name  : KEY_GPIO_Init
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( GPIO_KEY2_CLK | GPIO_KEY3_CLK|GPIO_WT588BY_CLK, ENABLE);//GPIO_KEY1_CLK | 

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

//    GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
//    GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
    GPIO_Init(GPIO_KEY2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_KEY3_PIN;
    GPIO_Init(GPIO_KEY3_PORT, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = GPIO_WT588BY_PIN;//����ģ��
    GPIO_Init(GPIO_WT588BY_PORT, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : TIM3_Int_Init
* Description    : TIM3 initialization function
* Input          : arr ��װ��ֵ
									 psc Ԥ��Ƶ
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
}


/*******************************************************************************
* Function Name  : Get_Key
* Description    : Read the KEY state
* Input          : None
* Output         : None
* Return         : uint8_t KEY state
* Attention		 : None
*******************************************************************************/

uint8_t Get_Key(void)
{
    uint8_t ReadKey;

//    if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_PIN))
//    {
//        ReadKey |= PRESS_KEY1;
//    }
    if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT,GPIO_KEY2_PIN))
    {
        ReadKey |= PRESS_KEY2;
    }
    if(!GPIO_ReadInputDataBit(GPIO_KEY3_PORT,GPIO_KEY3_PIN))
    {
        ReadKey |= PRESS_KEY3;
    }

    return ReadKey;
}


/*******************************************************************************
* Function Name  : ReadKeyValue
* Description    : Read the KEY value
* Input          : None
* Output         : None
* Return         : uint8_t KEY value
* Attention		 : None
*******************************************************************************/
uint8_t ReadKeyValue(void)
{
    static uint8_t Key_Check;
    static uint8_t Key_State;
    static uint16_t Key_LongCheck;
    static uint8_t Key_Prev    = 0;        							//��һ�ΰ���

    uint8_t Key_press;
    uint8_t Key_return = 0;

    if(KeyCountTime >= 10)  //KeyCountTime 1MS+1  ��������10MS
    {
        KeyCountTime = 0;
        Key_Check = 1;
    }
    if(Key_Check == 1)
    {
        Key_Check = 0;
        Key_press = Get_Key();
        switch (Key_State)
        {
        case 0:
            if(Key_press != 0)
            {
                Key_Prev = Key_press;
                Key_State = 1;
            }

            break;
        case 1:
            if(Key_press == Key_Prev)
            {
                Key_State = 2;
                Key_return= Key_Prev | KEY_DOWN;
            }
            else 																					//����̧��,�Ƕ���,����Ӧ����
            {
                Key_State = 0;
            }
            break;
        case 2:

            if(Key_press != Key_Prev)
            {
                Key_State = 0;
                Key_LongCheck = 0;
                Key_return = Key_Prev | KEY_UP;
                return Key_return;
            }

            if(Key_press == Key_Prev)
            {
                Key_LongCheck++;
                if(Key_LongCheck >= 100)    //����2S
                {
                    Key_LongCheck = 0;
                    Key_State = 3;
                    Key_return= Key_press |  KEY_LONG;
                    return Key_return;
                }
            }
            break;

        case 3:
            if(Key_press != Key_Prev)
            {
                Key_State = 0;
            }
            break;
        }
    }

    return  NO_KEY;
}

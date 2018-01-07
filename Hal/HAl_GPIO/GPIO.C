#include "stm32f10x_gpio.h"
#include "GPIO.H"
/**************************************************************************************
* Copyright (C), 2012 D&K电子工作室  http://design-kernel.taobao.com/
* 文件名: GPIO.c
* 内容简述:	D&K电子工作室开发的GPIO中间件文件，使代码易读、易懂、易移植
* D&K库版本：      V1.0.5
*	MDK版本：        V4.53
* 官方外设库版本： V3.5
* 微博：  http://weibo.com/u/2613869605
* 淘宝店：http://design-kernel.taobao.com/
* 网站：  http://design-kernel.yahubb.com/
* QQ群：  253682599
* 备注：欢迎关注微博，了解最新动态及资源发布。
**************************************************************************************/
 #define RCC_APB2Periph_ALLGPIO             (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE )

/**************************************************************************************
* 名    称:    DK_GPIO_Init(u8 GPIOx,u16 GPIOx_x,u8 Type)  
* 功    能:    初始化GPIO端口
* 参    数:    GPIOx为PA,PB,PC,PD,PE,PF
* 返 回 值:    无
* 作    者：   D&K
**************************************************************************************/ 
void DK_GPIO_Init(unsigned char GPIOx,unsigned short GPIOx_x,unsigned char Type)  //参数类型参照 "GPIO.h"
{			  
	GPIO_InitTypeDef   GPIO_InitStructure;	  //数据结构
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置管脚速率，最高50M
  GPIO_InitStructure.GPIO_Pin = GPIOx_x;			//选择管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //复用管脚	
  switch(Type)
	{
	  case 1:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//管脚状态为模拟输入
		break;
		case 2:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//管脚状态为浮空输入
		break;
		case 3:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//管脚状态为下拉输入
		break;
		case 4:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//管脚状态为上拉输入
		break;
		case 5:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		//管脚状态为开漏输出
		break;
		case 6:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//管脚状态为推挽输出
		break;
		case 7:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;		//管脚状态为复用开漏输出
		break;
		case 8:
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//管脚状态为复用推挽输出
		break;
	}
	switch(GPIOx)
	{
		case 1:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOA时钟
		GPIO_Init(GPIOA, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 2:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能GPIOB时钟
		GPIO_Init(GPIOB, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 3:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOC时钟
		GPIO_Init(GPIOC, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 4:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能GPIOD时钟
		GPIO_Init(GPIOD, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 5:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能GPIOE时钟
		GPIO_Init(GPIOE, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 6:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能GPIOF时钟
		GPIO_Init(GPIOF, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
		case 7:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能GPIOG时钟
		GPIO_Init(GPIOG, &GPIO_InitStructure);				//调用函数初始化管脚
		break;
	}
}
 /**************************************************************************************
* 名    称:    DK_GPIO_Write_H()
* 功    能:    向指定GPIO口的高八位写入数据
* 参    数:    GPIOx指定端口，	PortVal要写入的数据
* 返 回 值:    无
* 作    者：   D&K
**************************************************************************************/ 
void DK_GPIO_Write_H(GPIO_TypeDef* GPIOx, unsigned char PortVal)
{
  unsigned short ReadValue;
	unsigned short WriteValue; 
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	ReadValue = GPIO_ReadOutputData(GPIOx);
	ReadValue = ReadValue&0x00ff;
	WriteValue=PortVal;
	WriteValue=WriteValue<<0x08;
	WriteValue=WriteValue|ReadValue;
	GPIOx->ODR = WriteValue;
}
/**************************************************************************************
* 名    称:    DK_GPIO_Write_L()
* 功    能:    向指定GPIO口的低八位写入数据
* 参    数:    GPIOx指定端口，	PortVal要写入的数据
* 返 回 值:    无
* 作    者：   D&K
**************************************************************************************/ 
void DK_GPIO_Write_L(GPIO_TypeDef* GPIOx, unsigned char PortVal)
{
  unsigned short ReadValue;
	unsigned short WriteValue; 
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	ReadValue = GPIO_ReadOutputData(GPIOx);
	ReadValue = ReadValue&0xFF00;
	WriteValue=PortVal;
	WriteValue=WriteValue|ReadValue;
	GPIOx->ODR = WriteValue;
}
/*******************************************************************************
* Function Name  : DK_GPIO_AINConfig
* Description    : Configures all IOs as AIN to reduce the power consumption.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DK_GPIO_AINConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable all GPIOs Clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, ENABLE);

  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);


#if defined (USE_STM3210E_EVAL) || defined (USE_STM3210C_EVAL)
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOG, &GPIO_InitStructure);
#endif /* USE_STM3210E_EVAL */

  /* Disable all GPIOs Clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, DISABLE);
}
/******************* (C) COPYRIGHT 2012 D&K电子工作室 *****END OF FILE****************/

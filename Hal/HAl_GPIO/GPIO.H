#ifndef __GPIO_H
#define __GPIO_H

#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7

#define AIN            	1
#define IN_FLOATING     2
#define IPD 			3
#define IPU 			4
#define Out_OD 			5
#define Out_PP 			6
#define AF_OD 			7
#define AF_PP 			8		


//IO口操作宏定义

 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
//示例：PAout(2)=1，PA2口输出1
//temp=PAin(3)，读入PA3口的电平


void DK_GPIO_Init(unsigned char GPIOx,unsigned short GPIOx_x,unsigned char Type);
//void DK_GPIO_Write_H(GPIO_TypeDef* GPIOx, unsigned char PortVal);
//void DK_GPIO_Write_L(GPIO_TypeDef* GPIOx, unsigned char PortVal);
void DK_GPIO_AINConfig(void);

#endif


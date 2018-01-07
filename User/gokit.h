#ifndef _GOKIT_H
#define _GOKIT_H

#include "stm32f10x.h"
#include "Hal_key/Hal_key.h"
#include "Hal_led/Hal_led.h"
//#include "Hal_motor/Hal_motor.h"
#include "Hal_rgb_led/Hal_rgb_led.h"
#include "Hal_temp_hum/Hal_temp_hum.h"
#include "Hal_infrared/Hal_infrared.h"
#include "Hal_Usart/hal_uart.h"
#include "ringbuffer.h"
#include "Protocol.h"
#include <string.h>
#include "GPIO.H"
#include "SW_PCF8563.H"

#include "Hal_Step_otor.h"  //落药头文件
#include "Hal_GUANGOU.h"


__packed	typedef struct	
{
	uint8_t			LED_Cmd;//孙 修改为 16位 becuse  meiju
	uint8_t							SetA_YAO;  
	uint8_t							SetB_YAO;
	uint8_t							SetC_YAO; 
  uint8_t							ZAO_SHI;
	uint8_t							ZAO_FEN;  
	uint8_t							SetZHONG_SHI ;
	uint8_t							SetZHONG_FEN;
	uint8_t							SetWAN_SHI;  
	uint8_t							SetWAN_FEN;  
	uint8_t							SetD_YAO;
	uint8_t       		Infrared;
	uint8_t       		Temperature;
	uint8_t       		Humidity;
	uint8_t				Alert;//这两个不知道要不要
	uint8_t				Fault;//这两个不知道要不要
}ReadTypeDef_t; 

__packed typedef struct	
{
	uint16_t  Attr_Flags;// 修改为 16位 标志位  临时测试  按大端字节排序
	uint8_t	   LED_Cmd;// 孙 修改为 16位 becuse  meiju   临时测试 
  uint8_t							SetA_YAO;  
	uint8_t							SetB_YAO;
	uint8_t							SetC_YAO;  
	uint8_t							ZAO_SHI;
	uint8_t							ZAO_FEN;  
	uint8_t							SetZHONG_SHI ;
	uint8_t							SetZHONG_FEN;
	uint8_t							SetWAN_SHI;  
	uint8_t							SetWAN_FEN;
	uint8_t							SetD_YAO;
	
}WirteTypeDef_t;

void HW_Init(void);
void Printf_SystemRccClocks(void);
void GizWits_GatherSensorData(void);
void GizWits_ControlDeviceHandle(void);
void SW_Init(void);
void KEY_Handle(void);
//void GizWits_WiFiStatueHandle(uint16_t wifiStatue);


void luoyao(uint8_t, uint8_t, uint8_t, uint8_t);

#endif

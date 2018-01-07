/**
********************************************************
*
* @file      main.c
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

/* Includes ------------------------------------------------------------------*/


#include "gokit.h"

int a=0;
int b=0;
u8 wtadd=0;
int h;
int q;
int g;

/*Global Variable*/
uint32_t ReportTimeCount = 0;
uint8_t gaterSensorFlag = 0;
uint8_t Set_LedStatus = 0;
uint8_t NetConfigureFlag = 0;
uint8_t curTem = 0, curHum = 0;
uint8_t lastTem = 0,lastHum = 0;

extern RingBuffer u_ring_buff;
uint8_t p0Flag = 0;

WirteTypeDef_t	WirteTypeDef;
ReadTypeDef_t	ReadTypeDef;

extern uint8_t benday;  //???
extern uint8_t benDhour;//?
extern uint8_t benminute;//?
extern uint8_t bensecond;//?

extern uint8_t getTime[9];
extern uint8_t XIEDate;
extern uint8_t XIEHour;
extern uint8_t XIEMin;
extern uint8_t XIEsecond;
extern unsigned char time[7],Tmp[20],temp,Flag8563_2402;


extern uint8_t Month;   
extern uint8_t Date;
extern uint8_t Hour;
extern uint8_t Min;
extern uint8_t second;


uint8_t  CENCHU_A;
uint8_t  CENCHU_B;
uint8_t  CENCHU_C;
uint8_t  CENCHU_D;


uint8_t  ZAOSHI;
uint8_t  ZAOFEN;
uint8_t  ZHONGSHI;
uint8_t  ZHONGFEN;
uint8_t  WANSHI;
uint8_t  WANFEN;

uint16_t cx=0, cxx=0,cxxx=0;


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t p0_control_buf[MAX_P0_LEN],frist;
	uint16_t cxx=0,cxxx=0;
 // uint8_t frist[2] ;
	SystemInit();	
	HW_Init();
	Printf_SystemRccClocks();
	SW_Init();
	
//	 Time_Disposal ();
//PCF8563_set(0x10,0x07,XIEDate,XIEHour,XIEMin,XIEsecond,0x05);//，年、月、日、时、分、秒、星期。BCD码表示
  Flag8563_2402=0;


	
	IIC_ReadBuf(0,Tmp,16);
		
	 Flag8563_2402=111;
	IIC_ReadBuf(2,&frist,1);// 判断是否第一次启动8563
	if((frist&0x20)!=0)
     {
		 PCF8563_set(0x16,0x07,0x14,XIEHour,XIEMin,XIEsecond,0x05);
		 }
	
	while(1)
	{
		if(++cxxx==60000)
			{
				if(++cx>>3)
				{
				Pro_UART_SendBuf(getTime,9,1);
        Flag8563_2402=WR8563;				
				PCF8563_read(time);
			  Ben_AckHandle();
				printf("\r\nEEPROM: %d %d %d %d %d %d %d %d %d %d %d %d %d   \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);		
				printf("\r\nTime: %s %d  %d :%d:%d\r\n","下位机--时间",benday,benDhour,benminute,bensecond);			
				printf("\r\nTime: %s %d-%d %d:%d:%d \r\n","云端----时间",Month,Date,Hour,Min,second);

			}
				
    if(wtadd==0)
		{
	 if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
       {
        Send_oneline( 0 ); 
				 ++wtadd;
          }
	   }			 


			
			
			
			

			
		if((Tmp[5] == benDhour && Tmp[6] == benminute&&(bensecond<5))  || (Tmp[7] == benDhour && Tmp[8] == benminute&&(bensecond<5)) || (Tmp[9] == benDhour && Tmp[10] == benminute&&(bensecond<5)))
	    {
				if(benDhour==0)////bug	
				{
					if(benminute==0)
					{}
						else
			luoyao(Tmp[1],Tmp[2],Tmp[3],Tmp[4]);
	    }
				
				if(benDhour!=0)
				{	
						if(benminute!=0)
					luoyao(Tmp[1],Tmp[2],Tmp[3],Tmp[4]);
					
		}
	}
}
		
		
		if(cxx==1)
		{ 
			cxx=0;
			printf("开始写入数据");
			Flag8563_2402=WR2402;
			Tmp[1]= CENCHU_A;Tmp[2]=CENCHU_B;Tmp[3]=CENCHU_C;Tmp[4]=CENCHU_D;
		  Tmp[5]= ZAOSHI;Tmp[6]=ZAOFEN;Tmp[7]=ZHONGSHI;Tmp[8]=ZHONGFEN;
		  Tmp[9]= WANSHI;Tmp[10]=WANFEN;Tmp[11]=CENCHU_C;Tmp[12]=CENCHU_D;
		  IIC_WriteBuf(0,Tmp,16);
		  IIC_ReadBuf(0,Tmp,16);
	printf("\r\nEEPROM: %d %d %d %d %d %d %d %d %d %d %d %d %d \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);		
		Flag8563_2402=WR8563;
		}
		
		KEY_Handle();		
		GizWits_MessageHandle(p0_control_buf, sizeof(WirteTypeDef_t));
		if(p0Flag == 1)
		{
			memcpy((uint8_t *)&WirteTypeDef, p0_control_buf, sizeof(WirteTypeDef_t));
			GizWits_ControlDeviceHandle();
			GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 1);
			p0Flag =0;
		}
        if(gaterSensorFlag != 0)
        {
            GizWits_GatherSensorData(); 
            gaterSensorFlag = 0;
        }
        GizWits_DevStatusUpgrade((uint8_t *)&ReadTypeDef, 10*60*1000, 0);
	}
}
/** @addtogroup GizWits_HW_Init
  * @{
  */
void HW_Init(void)
{
	Delay_Init(72);	
	UARTx_Init();
 //   RGB_KEY_GPIO_Init();
	RGB_LED_Init();	
	LED_GPIO_Init();	
	KEY_GPIO_Init();
	TIM3_Int_Init(7199,9);   //ms interrupt	
//	Motor_Init();	
	DHT11_Init();	
	IR_Init();
	EXTIX_Init();
}
/** @addtogroup GizWits_SW_Init
  * @{
  */
void SW_Init()
{
	ReadTypeDef.Alert = 0;
	ReadTypeDef.LED_Cmd = 0;
	ReadTypeDef.Infrared = 0;
	
	ReadTypeDef.SetA_YAO=0;
  ReadTypeDef.SetB_YAO=0;  
  ReadTypeDef.SetC_YAO=0 ;
  ReadTypeDef.SetD_YAO=0;
	
	ReadTypeDef.ZAO_SHI=0;
  ReadTypeDef.ZAO_FEN=0;  
  ReadTypeDef.SetZHONG_SHI=0 ;
  ReadTypeDef.SetZHONG_FEN=0;
  ReadTypeDef.SetWAN_SHI=0;  
  ReadTypeDef.SetWAN_FEN=0;
	
	ReadTypeDef.Temperature = 0;
	ReadTypeDef.Humidity = 0;
	ReadTypeDef.Alert = 0;
	ReadTypeDef.Fault = 0;
	GizWits_init(sizeof(ReadTypeDef_t));
	printf("Gokit Init Ok ...\r\n");
}
/** @addtogroup Printf_SystemRccClocks
  * @{
  */
void Printf_SystemRccClocks(void)
{
	uint8_t SYSCLKSource;

	RCC_ClocksTypeDef  SystemRCC_Clocks;
	printf("System start...\r\n");
	SYSCLKSource = RCC_GetSYSCLKSource();
	if(SYSCLKSource==0x04)
		printf("SYSCLKSource is HSE\r\n");
	else if(SYSCLKSource==0x00)
		printf("SYSCLKSource is HSI\r\n");
	else if(SYSCLKSource==0x08)
		printf("SYSCLKSource is PL!\r\n");
	
	RCC_GetClocksFreq(&SystemRCC_Clocks);
	printf("SYS clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.SYSCLK_Frequency/1000000);
	printf("HCLK clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.HCLK_Frequency/1000000);
	printf("PCLK1 clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK1_Frequency/1000000);
	printf("PCLK2_clock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.PCLK2_Frequency/1000000);	
	printf("SADCCLK_Frequencyclock =%dMHz \r\n",(uint32_t)SystemRCC_Clocks.ADCCLK_Frequency/1000000);

}

/*******************************************************************************
* Function Name  : GizWits_ControlDeviceHandle
* Description    : Analy P0 Package
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention		 : 
*******************************************************************************/
void GizWits_ControlDeviceHandle()
{
	if( ((WirteTypeDef.Attr_Flags>>8) & 1) == 1)
	 {
		if(Set_LedStatus != 1)
		{
			if(WirteTypeDef.LED_Cmd == LED_OnOff)
			{
				printf("\r\nEEPROM: %d %d %d %d %d %d %d %d %d %d %d %d %d \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);		
				printf("\r\nTime: %s %d  %d :%d:%d\r\n","下位机--时间",benday,benDhour,benminute,bensecond);			
				printf("\r\nTime: %s %d-%d %d:%d:%d \r\n","云端----时间",Month,Date,Hour,Min,second);
				
				LED_RGB_Control(0,0,0);
				ReadTypeDef.LED_Cmd = LED_OnOff;
				printf("SetLED_Off \r\n");
			}
			if(WirteTypeDef.LED_Cmd == LED_OnOn)
			{
				ReadTypeDef.LED_Cmd = LED_OnOn;
				
				Flag8563_2402=WR8563;
				 cxx=1;
				Time_Disposal();
			  PCF8563_set(0x10,0x07,XIEDate,XIEHour,XIEMin,XIEsecond,0x05);//设置时间，年、月、日、时、分、秒、星期。BCD码表示
				PCF8563_read(time);
				Ben_AckHandle();
					if(cxx==1)
		          { 
		         	  cxx=0;
			          printf("开始写入数据");
			          Flag8563_2402=0;
			         Tmp[1]= CENCHU_A;Tmp[2]=CENCHU_B;Tmp[3]=CENCHU_C;Tmp[4]=CENCHU_D;
		            Tmp[5]= ZAOSHI;Tmp[6]=ZAOFEN;Tmp[7]=ZHONGSHI;Tmp[8]=ZHONGFEN;
		             Tmp[9]= WANSHI;Tmp[10]=WANFEN;Tmp[11]=CENCHU_C;Tmp[12]=CENCHU_D;
		               IIC_WriteBuf(0,Tmp,16);
		                IIC_ReadBuf(0,Tmp,16);
	      printf("\r\nEEPROM: %d %d %d %d %d %d %d %d %d %d %d %d %d  \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);		
		}
		
				printf("\r\nTime: %s %d  %d :%d:%d\r\n","下位机--时间",benday,benDhour,benminute,bensecond);			
				printf("\r\nTime: %s %d-%d %d:%d:%d \r\n","云端----时间",Month,Date,Hour,Min,second); 		    			
				
				ReadTypeDef.LED_Cmd = LED_OnOn;
				LED_RGB_Control(254,0,0);
				printf("SetLED_On \r\n");
		 if((GPIO_ReadInputDataBit(GPIO_WT588BY_PORT,GPIO_Pin_1)))
       {
        Send_oneline(1);
          }
			}
		}	
	}
	if( ((WirteTypeDef.Attr_Flags>>9) & 1) == 1)
		{     printf("开始输入A药数据");
						ReadTypeDef.SetA_YAO= WirteTypeDef.SetA_YAO;
		            CENCHU_A= WirteTypeDef.SetA_YAO;	
			printf("输入的a药数据为%d  不要忘记写入哦",CENCHU_A);
//			printf("\r\上次数据EEPROM: %s %d %d %d %d %d %d %d %d %d %d %d %d %d  \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);
//      	printf("开始写入A药数据");
//			IIC_ReadBuf(0,Tmp,16);
//			printf("\r\nEEPROM: %s %d %d %d %d %d %d %d %d %d %d %d %d %d  \r\n",Tmp[0],Tmp[1],Tmp[2],Tmp[3],Tmp[4],Tmp[5],Tmp[6],Tmp[7],Tmp[8],Tmp[9],Tmp[10],Tmp[11],Tmp[12]);
//			if(WirteTypeDef.LED_Cmd ==LED_A_LING )
//				{
//					ReadTypeDef.LED_Cmd = LED_A_LING;
//					CENCHU_A=LED_A_LING;
//					printf("检测数据是否写入成功0=%d\n",CENCHU_A);
//			 }
//			if(WirteTypeDef.LED_Cmd ==LED_A_YI )
//			   { 
//				   ReadTypeDef.LED_Cmd = LED_A_YI<<8;
//				   CENCHU_A= 1;
//				   printf("检测数据是否写入成功1=%d",CENCHU_A);
//					 
//			   }
//			if(WirteTypeDef.LED_Cmd ==LED_A_ER )
//			   {
//					ReadTypeDef.LED_Cmd = LED_A_ER<<8;
//					CENCHU_A=2;
//					printf("检测数据是否写入成功2=%d",CENCHU_A);
//				}
//     if(WirteTypeDef.LED_Cmd ==LED_A_SAN )
//				{
//				ReadTypeDef.LED_Cmd = LED_A_SAN<<8;
//				CENCHU_A=3;
//			printf("检测数据是否写入成功3=%d",CENCHU_A);
//				}
	}
		
	
	
	
	if( ((WirteTypeDef.Attr_Flags>>10) & 1) == 1)
		{    printf("开始输入B药数据");
						ReadTypeDef.SetB_YAO= WirteTypeDef.SetB_YAO;
		             CENCHU_B= WirteTypeDef.SetB_YAO;
		
			printf("输入的B要数据%d  不要忘记写入哦",CENCHU_B);
		
//			if(WirteTypeDef.LED_Cmd ==LED_B_LING )
//					{
//					ReadTypeDef.LED_Cmd = LED_B_LING;
//					CENCHU_B=LED_B_LING;
//					printf("检测数据是否写入成功0=%d",CENCHU_B);
//					}
//			if(WirteTypeDef.LED_Cmd ==LED_B_YI )
//				  {
//					ReadTypeDef.LED_Cmd = LED_B_YI<<8;
//					CENCHU_B= LED_B_YI>>3;
//					printf("检测数据是否写入成功1=%d",CENCHU_B);
//				  }
//				if(WirteTypeDef.LED_Cmd ==LED_B_ER )
//					{					
//					ReadTypeDef.LED_Cmd = LED_B_ER<<8;
//					CENCHU_B=LED_B_ER>>3;
//					printf("检测数据是否写入成功2=%d",CENCHU_B);
//					}
//			  if(WirteTypeDef.LED_Cmd ==LED_B_SAN )
//				  {
//           ReadTypeDef.LED_Cmd = LED_B_SAN<<8;
//           CENCHU_B=LED_B_SAN>>3;
//						printf("检测数据是否写入成功3=%d",CENCHU_B);
//           }
//         }
//  if( ((WirteTypeDef.Attr_Flags>>11) & 1) == 1)
//     {printf("开始输入C药数据");
//      if(WirteTypeDef.LED_Cmd ==LED_C_LING )
//        {
//         ReadTypeDef.LED_Cmd = LED_C_LING;
//	       CENCHU_C=LED_C_LING;
//          printf("检测数据是否写入成功0=%d",CENCHU_C);
//          }
//			if(WirteTypeDef.LED_Cmd ==LED_C_YI )
//				{
//				ReadTypeDef.LED_Cmd = LED_C_YI<<8;
//				CENCHU_C= LED_C_YI>>5;
//				printf("检测数据是否写入成功1=%d",CENCHU_C);
//				}
//			if(WirteTypeDef.LED_Cmd ==LED_C_ER )
//				{
//					ReadTypeDef.LED_Cmd = LED_C_ER<<8;
//					CENCHU_C=LED_C_ER>>5;
//					printf("检测数据是否写入成功2=%d",CENCHU_C);
//					}
//		if(WirteTypeDef.LED_Cmd ==LED_C_SAN )
//			{
//			ReadTypeDef.LED_Cmd = LED_C_SAN<<8;
//			CENCHU_C=LED_C_SAN>>5;
//			printf("检测数据是否写入成功3=%d",CENCHU_C);
//			}
	}
		if( ((WirteTypeDef.Attr_Flags>>11) & 1) == 1)
			{   printf("开始输入C药数据");
							ReadTypeDef.SetC_YAO= WirteTypeDef.SetC_YAO;
		            CENCHU_C = WirteTypeDef.SetC_YAO;
		
			printf("输入的C要数据%d  不要忘记写入哦",CENCHU_C);
		
//				if(WirteTypeDef.LED_Cmd ==LED_D_LING )
//					{
//					ReadTypeDef.LED_Cmd = LED_D_LING;
//					CENCHU_D=LED_D_LING;
//					printf("检测数据是否写入成功0=%d",CENCHU_D);
//					}
//				if(WirteTypeDef.LED_Cmd ==LED_D_YI )
//					{
//					ReadTypeDef.LED_Cmd = LED_D_YI;
//					CENCHU_D= LED_D_YI>>15;
//					printf("检测数据是否写入成功1=%d",CENCHU_D);
//					}
//		if(WirteTypeDef.LED_Cmd ==LED_D_ER )
//				{
//					ReadTypeDef.LED_Cmd = LED_D_ER;
//					CENCHU_D=LED_D_ER<<1;
//					printf("检测数据是否写入成功2=%d",CENCHU_D);
//				}
//			if(WirteTypeDef.LED_Cmd ==LED_D_SAN )
//				{
//					ReadTypeDef.LED_Cmd = LED_D_SAN;
//					CENCHU_D=3;
//					printf("检测数据是否写入成功3=%d",CENCHU_D);
//				}
	}
	if( ((WirteTypeDef.Attr_Flags>>12) & 1) == 1)
	{
		
		
			ReadTypeDef.ZAO_SHI= WirteTypeDef.ZAO_SHI;
		             ZAOSHI= WirteTypeDef.ZAO_SHI;
		
			printf("输入早晨小时为%d  不要忘记写入哦",ZAOSHI);
		
		
	}
		if( ((WirteTypeDef.Attr_Flags>>13) & 1) == 1)
	{
		
		
			ReadTypeDef.ZAO_FEN= WirteTypeDef.ZAO_FEN;
		             ZAOFEN= WirteTypeDef.ZAO_FEN;
		
			printf("输入早晨分钟%d  不要忘记写入哦",ZAOFEN);
		
		
	}
	if( ((WirteTypeDef.Attr_Flags>>14) & 1) == 1)
	{
		
		
			ReadTypeDef.SetZHONG_SHI= WirteTypeDef.SetZHONG_SHI;
									ZHONGSHI= WirteTypeDef.SetZHONG_SHI;
		
			printf("输入SHANGWU时为%d  不要忘记写入哦",ZHONGSHI);
		
		
	}
		if( ((WirteTypeDef.Attr_Flags>>15) & 1) == 1)
	{
		
		
			ReadTypeDef.SetZHONG_FEN= WirteTypeDef.SetZHONG_FEN;
		             ZHONGFEN= WirteTypeDef.SetZHONG_FEN;
		
			printf("输入SHANGWU分钟%d  不要忘记写入哦",ZHONGFEN);	
	}
			if( ((WirteTypeDef.Attr_Flags>>0) & 1) == 1)
	{
		
		
			ReadTypeDef.SetWAN_SHI= WirteTypeDef.SetWAN_SHI;
		             WANSHI= WirteTypeDef.SetWAN_SHI;
		
			printf("晚上的小时%d  不要忘记写入哦",WANSHI);
		
		
	}
	if( ((WirteTypeDef.Attr_Flags>>1) & 1) == 1)
	{
		
		
			ReadTypeDef.SetWAN_FEN= WirteTypeDef.SetWAN_FEN;
								WANFEN= WirteTypeDef.SetWAN_FEN;
		
			printf("晚上的分钟%d  不要忘记写入哦",WANFEN);
		
		
	}
		if( ((WirteTypeDef.Attr_Flags>>2) & 1) == 1)
	{
		
		
			ReadTypeDef.SetD_YAO= WirteTypeDef.SetD_YAO;
								CENCHU_D= WirteTypeDef.SetD_YAO;
		
			printf("输入D药数据时为%d  不要忘记写入哦",CENCHU_D);
		
		
	}
}
/*******************************************************************************
* Function Name  : GizWits_GatherSensorData();
* Description    : Gather Sensor Data
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GizWits_GatherSensorData(void)
{
	ReadTypeDef.Infrared = IR_Handle();
	DHT11_Read_Data(&curTem, &curHum);
	ReadTypeDef.Temperature = (curTem + lastTem) /2;
	ReadTypeDef.Humidity = (curHum + lastHum)/2;

	ReadTypeDef.Temperature = ReadTypeDef.Temperature + 13;//Temperature Data Correction
	lastTem = curTem;
	lastHum = curHum;
}
/*******************************************************************************
* Function Name  : KEY_Handle
* Description    : Key processing function
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void KEY_Handle(void)
{
	uint8_t Key_return =0;	
	Key_return = ReadKeyValue();	
	if(Key_return & KEY_UP)
	{
		if(Key_return & PRESS_KEY1)
		{
#ifdef PROTOCOL_DEBUG
  				printf("KEY1 PRESS\r\n");
#endif		
		}
		if(Key_return & PRESS_KEY2)
		{
#ifdef PROTOCOL_DEBUG
			printf("KEY2 PRESS ,Soft AP mode\r\n");
#endif	
			//Soft AP mode, RGB red
			LED_RGB_Control(255, 0, 0);
			GizWits_D2WConfigCmd(SoftAp_Mode);
			NetConfigureFlag = 1;
		}				
	}

	if(Key_return & KEY_LONG)
	{
		if(Key_return & PRESS_KEY1)
		{
#ifdef PROTOCOL_DEBUG
				printf("KEY1 PRESS LONG ,Wifi Reset\r\n");
#endif			
			GizWits_D2WResetCmd();
		}
		if(Key_return & PRESS_KEY2)
		{
			//AirLink mode, RGB Green
#ifdef PROTOCOL_DEBUG
				printf("KEY2 PRESS LONG ,AirLink mode\r\n");
#endif	
			LED_RGB_Control(0, 128, 0);
			GizWits_D2WConfigCmd(AirLink_Mode);
			NetConfigureFlag = 1;
		}
	}
}
/*******************************************************************************
* Function Name  : GizWits_WiFiStatueHandle
* Description    : Callback function , Judge Wifi statue
* Input          : None
* Output         : None
* Return         : Bit , Attr_Flags
* Attention		 : 
*******************************************************************************/
void GizWits_WiFiStatueHandle(uint16_t wifiStatue) 
{	
	if(((wifiStatue & Wifi_ConnClouds) == Wifi_ConnClouds) && (NetConfigureFlag == 1))
	{
		printf("W2M->Wifi_ConnClouds\r\n");
		NetConfigureFlag = 0;
		LED_RGB_Control(0,0,0);
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

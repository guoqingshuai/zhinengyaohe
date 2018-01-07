#include <string.h>
#include "stm32f10x.h"
#include "GPIO.H"
#include "stm32f10x_gpio.h"
#include "Hal_rgb_led/Hal_rgb_led.h"
#include "Hal_temp_hum/sys.h" 

#define PCF8563_Read_Add	0xA3
#define PCF8563_Write_Add	0xA2
#define PCF2402_Read_Add	0xA1
#define PCF2402_Write_Add	0xA0



//ģ��IIC�ܽ�����
#define 	SWIIC_SDA_GPIO     		PB
#define 	SWIIC_SDA_BIT      		GPIO_Pin_9
#define 	SWIIC_SDA_Type_Out     	Out_PP
#define 	SWIIC_SDA_Type_In     	IPU
#define 	SWIIC_SDA          		PEout(9) 

#define 	SWIIC_CLK_GPIO     		PB
#define 	SWIIC_CLK_BIT      		GPIO_Pin_8
#define 	SWIIC_CLK_Type	     	Out_PP
#define 	SWIIC_CLK          		PEout(8) 
extern  unsigned char time[7],Tmp[10],temp,Flag8563_2402;

void Delay(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=0;j<1000;j++);
}
//IO��������
#define CLK_OUT() DK_GPIO_Init(SWIIC_CLK_GPIO,SWIIC_CLK_BIT,SWIIC_CLK_Type);
#define SDA_IN()  DK_GPIO_Init(SWIIC_SDA_GPIO,SWIIC_SDA_BIT,SWIIC_SDA_Type_In);
#define SDA_OUT() DK_GPIO_Init(SWIIC_SDA_GPIO,SWIIC_SDA_BIT,SWIIC_SDA_Type_Out);

//IO��������	 
//#define IIC_SCL    GPIO_SetBits(GPIOB,GPIO_Pin_8)
//#define READ_SCL    GPIO_ResetBits(GPIOB,GPIO_Pin_8)
//#define IIC_SDA   	GPIO_SetBits(GPIOB,GPIO_Pin_9) 
//#define READ_SDA   GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 
unsigned char PCF8563_start(void);
static void Init_SWIIC(void);// ��ʼ��ģ���
static void IIC_Start(void);				//����IIC��ʼ�ź�
static void IIC_Stop(void);	  			//����IICֹͣ�ź�
static void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
static unsigned char IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
static unsigned char IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
static void IIC_Ack(void);					//IIC����ACK�ź�
static void IIC_NAck(void);				//IIC������ACK�ź�
unsigned char IIC_WriteBuf(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite);
unsigned char IIC_ReadBuf(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead);
static void IIC_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite);
static unsigned char IIC_ReadOneByte(unsigned short ReadAddr);

//�����е���ʱ��������ڲ���Ϊ0��65535
static void SW_EEPROM_Delay_nus(unsigned short nus)
{
	for(;nus>0;nus--)
	{   __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
      __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();	
      //__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();	
	   // __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();	

  }
}


//����IIC��ʼ�ź�
static void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	SW_EEPROM_Delay_nus(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	SW_EEPROM_Delay_nus(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
static void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	SW_EEPROM_Delay_nus(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	SW_EEPROM_Delay_nus(4);							   	
}

static void Init_SWIIC(void)//���Բ�Ҫ����ģ��
{
	CLK_OUT();
	SDA_OUT();	
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
static void IIC_Send_Byte(unsigned char txd)
{                        
    unsigned char t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		SW_EEPROM_Delay_nus(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		SW_EEPROM_Delay_nus(2); 
		IIC_SCL=0;	
		SW_EEPROM_Delay_nus(2);
    }	 
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
static unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        SW_EEPROM_Delay_nus(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		SW_EEPROM_Delay_nus(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
static unsigned char IIC_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;SW_EEPROM_Delay_nus(1);	   
	IIC_SCL=1;SW_EEPROM_Delay_nus(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
}
//����ACKӦ��
static void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	SW_EEPROM_Delay_nus(2);
	IIC_SCL=1;
	SW_EEPROM_Delay_nus(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	SW_EEPROM_Delay_nus(2);
	IIC_SCL=1;
	SW_EEPROM_Delay_nus(2);
	IIC_SCL=0;
}
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
unsigned char IIC_WriteBuf(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite)
{
	while(NumToWrite--)
	{
		IIC_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}		
	return 0;
}
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
unsigned char IIC_ReadBuf(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=IIC_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
	return 0;
} 
//��ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
static void IIC_WriteOneByte(unsigned short WriteAddr,unsigned char DataToWrite)
{				   	  	    																 
    IIC_Start();  
	
	if(Flag8563_2402==111)	
	IIC_Send_Byte(PCF8563_Write_Add);   //����������ַPCF8563_Write_Add,д���� 
	else
	IIC_Send_Byte(PCF2402_Write_Add);   //����������ַPCF8563_Write_Add,д���� 	
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	//printf("����˧��˧������ִ�в��� ������������");//�������ɴ󲻿�С	������С��6000
	SW_EEPROM_Delay_nus(8000);
}
//��ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
static unsigned char IIC_ReadOneByte(unsigned short ReadAddr)
{				  
	unsigned char temp=0;		  	    																 
    IIC_Start();  
	if(Flag8563_2402==111)	
	IIC_Send_Byte(PCF8563_Write_Add);   //����������ַPCF8563_Read_Add,д���� 	 
  else
	IIC_Send_Byte(PCF2402_Write_Add);   //����������ַPCF8563_Read_Add,д���� 	
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();
  if(Flag8563_2402==111)	
	IIC_Send_Byte(PCF8563_Read_Add);	//�������ģʽ
  else
  IIC_Send_Byte(PCF2402_Read_Add);		
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//����Ӳ����ʼ��
void PCF8563_Init(void)
{
	 Init_SWIIC();
}
/*****************************************************************/
/*
********************************************************************/ 
//PCF8563ʱ��ָֹͣ��   i2c_write_n_bytes(unsigned char SLA_W, uint16 ADDR,uint16 N, unsigned char *DAT)
static unsigned char PCF8563_stop(void)
{
 	unsigned char stopcode=0x20;
 	if(0==IIC_WriteBuf(0,&stopcode,1))
		return 0;
 	else return 1;
}
//PCF8563ʱ������ָ��
unsigned char PCF8563_start(void)
{
	//unsigned char startcode=0x00;
 	unsigned char qwqw=0x83,startcode=0x00;
	if(0==IIC_WriteBuf(0,&startcode,1))
	IIC_Stop();
	if(0==IIC_WriteBuf(0x0d,&qwqw,1))
//		return 0;
	return 0;
 	else return 1;	
//	IIC_Stop();
//	if(0==IIC_WriteBuf(0x0d,&qwqw,1))
//		return 0;
// 	else return 1;	
//	
}


/************************************************************************
PCF8563ʱ������
����˵������BCD�룩
yy:  �꣨0x00��0x99��
mm:	 �£�0x01��0x12��
dd:	 �գ�0x01��0x31��
hh:	 ʱ��0x00��0x23��
mi:	 �֣�0x00��0x59��
ss:	 �루0x00��0x59��
da:	 ���ڣ�0x01��0x07��
************************************************************************/
unsigned char PCF8563_set(unsigned char year,unsigned char month, unsigned char day,unsigned char hour,unsigned char minute,unsigned char second,unsigned char date)
{
	 unsigned char time[7]; 
	 time[6]=year;//��
	 time[5]=month;//��
	 time[4]=date;//����
	 time[3]=day;//��
	 time[2]=hour;//ʱ
	 time[1]=minute;//��
	 time[0]=second;//��
	 PCF8563_stop();
	 if(0==IIC_WriteBuf(2,time,7))
	 {
	 	PCF8563_start();	
		 
		return 0;
	 }
 	 else return 1;
}


/************************************************************************
PCF8563ʱ�Ӷ�ȡ
����˵������BCD�룩
time:	  ��Ŷ���ʱ���������
time[6]:  �꣨0x00��0x99��
time[5]:  �£�0x01��0x12��
time[3]:  �գ�0x01��0x31��
time[2]:  ʱ��0x00��0x23��
time[1]:  �֣�0x00��0x59��
time[0]:  �루0x00��0x59��
time[4]:  ���ڣ�0x01��0x07��
************************************************************************/
unsigned char PCF8563_read(unsigned char *time)
{
	 unsigned char temp[7];
	 if(0==IIC_ReadBuf(2,temp,7))
	 {
		 temp[6] = temp[6];       //��
		 temp[5] &= 0x1F;//��
		 temp[4] &= 0x07;//����
		 temp[3] &= 0x3F;//��
		 temp[2] &= 0x3F;//ʱ
		 temp[1] &= 0x7F;//��
		 temp[0] &= 0x7F;//�� 
		 
		 
		 time[6]=temp[6]; 
		 time[5]=temp[5]; 
		 time[4]=temp[3]; 
		 time[3]=temp[2]; 
		 time[2]=temp[1]; 
		 time[1]=temp[0]; 
		 time[0]=temp[4];
	
	 	return 0;
	 }	  
	else return 1;
}
/************************************************************************
���� ����  �½����ⲿ�ж�
comΪ1�����ӣ�Ϊ0������
timeѡ������Դ��1Ϊ�֣�2Ϊʱ��3Ϊ�գ�4Ϊ����
setΪBCD����ʱ��
************************************************************************/
static unsigned char Set_Alarm(unsigned char com,unsigned char time,unsigned char set)
{
	unsigned char temp;
	if(com)  
	{  temp=0x12;   if(0!=IIC_WriteBuf(0x01,&temp,1))  goto EndOfFunc; }
	else   set=0x80;
	
//	if(0!=IIC_ReadBuf(0x01,&i,1))  goto EndOfFunc;
	if(time==1)//��
	{
	    if(0!=IIC_WriteBuf(0x09,&set,1))  goto EndOfFunc;
	}
	else if(time==2)//ʱ
	{
	    if(0!=IIC_WriteBuf(0x0a,&set,1))  goto EndOfFunc;
	}
	else if(time==3)//��
	{
	    if(0!=IIC_WriteBuf(0x0b,&set,1))  goto EndOfFunc;
	}
	else if(time==4) //����
	{
	    if(0!=IIC_WriteBuf(0x0c,&set,1))  goto EndOfFunc;
	}
	return 0;
	EndOfFunc:
	return 1;
}
//�ر�����
unsigned char PCF8563_CloseAlarm(void)
{
	return (Set_Alarm(0,0,0));
}
//��������
//timeѡ������Դ��1Ϊ�֣�2Ϊʱ��3Ϊ�գ�4Ϊ����
//setΪBCD����ʱ��
//unsigned char PCF8563_SetAlarm(unsigned char time,unsigned char set)
//{
//	PCF8563_ClearINT();
//	return (Set_Alarm(1,time,set));
//}
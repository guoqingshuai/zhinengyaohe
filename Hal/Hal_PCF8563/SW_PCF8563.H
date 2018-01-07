#ifndef _SW_PCF8563_H_
#define _SW_PCF8563_H_	

unsigned char PCF8563_set(unsigned char year,unsigned char month,unsigned char day,unsigned char hour,unsigned char minute,unsigned char second,unsigned char date);
unsigned char PCF8563_read(unsigned char *time);
unsigned char IIC_WriteBuf(unsigned short WriteAddr,unsigned char *pBuffer,unsigned short NumToWrite);
unsigned char IIC_ReadBuf(unsigned short ReadAddr,unsigned char *pBuffer,unsigned short NumToRead);
unsigned char PCF8563_CloseAlarm(void);
unsigned char PCF8563_SetAlarm(unsigned char time,unsigned char set);
void PCF8563_Init(void);
void PCF8563_INT_SERVER_FUN(void);
unsigned char PCF8563_ClearINT(void);
 unsigned char PCF8563_start(void);
 
#define WR8563 111
#define WR2402 0

#define PCF8563_Read_Add	0xA3
#define PCF8563_Write_Add	0xA2
#define PCF2402_Read_Add	0xA1
#define PCF2402_Write_Add	0xA0



#endif


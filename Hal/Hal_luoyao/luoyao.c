#include "stm32f10x.h"
#include "Hal_Step_otor.h"
#include "Hal_GUANGOU.h"
#include <delay.h>
#include "Hal_led/Hal_led.h"
//#define    MI_ERR    (-2)
extern int a;
extern int b;//���ѳ�ҩ
extern int h;//���ѳ�ҩ
extern int g;//���ѳ�ҩ
  
void yuandian(void);  //ԭ��
void SXzhengzhuan(int);   //�������� 
void SXfanzhuan(int);
//void Szhangzhuan();  //������
//void Sfanzhuan();    //�Ϸ�ת
void Xzhengzhuan(int);  //����ת
void Xfanzhuan(int);    //�·�ת
void zhendong(void);  //��
void huiyuandian(void);   //�·�ת




void Delay1(__IO u32 nCount);


/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
void luoyao(uint8_t Tmp1,uint8_t Tmp2, uint8_t Tmp3,uint8_t Tmp4)
{
	printf("��ҩ��ʼ\n");
	int Ayao = Tmp1;
	int Byao = Tmp2;
	int Cyao = Tmp3;
	int Dyao = Tmp4;
	STEP_GPIO_Init();
//	/* LED �˿ڳ�ʼ�� */
//	LED_GPIO_Config();

//��ʼдAҩ
//�����ж��ǲ�����ԭ�㣨����ԭ�㣩�Ȼ�ԭ��
//��ԭ��֮��  ͬʱ102 ��
//Ȼ��������-30 ��
//Ȼ����
//Ȼ������30��
//Ȼ���ԭ��
//�ж�ʱ��ͷ����鲻����ȷ

	
//��ԭ�����

	

	huiyuandian(); 
 //��ԭ��
	//A�� ��ҩ
		while(a <Ayao)
		{	   
			
			printf(" Aҩִ�п�ʼ\n");
			SXzhengzhuan(190);  //��������
			for(g=0;g<3;g++)
		{
			Xfanzhuan(80);  //�·�ת30��  ��ҩ���м�
			zhendong();//��
			Xzhengzhuan(80);  //������30��  ��λ
		}
			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
			{	
				SXfanzhuan(1);  //���·�ת   ��ԭ��  ��ҩ
			}
			Delay1(39990000);
			printf("A=%d",a);
		}
		 huiyuandian();
     if(Byao!=0) {   //��ԭ��
			Xfanzhuan(800);  //�·�ת30��  ��ҩ���м�
		 }
	      	a = 0;
		     while(a<Byao)
	   	{
			
			printf("Bҩִ�п�ʼ\n");
			SXzhengzhuan(370);  //��������
			for(g=0;g<3;g++)
{				
			Xfanzhuan(70);  //�·�ת30��  ��ҩ���м�
			zhendong();  //��
			Xzhengzhuan(70);  //������30��  ��λ
}
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//				SXfanzhuan(1);  //���·�ת   ��ԭ��  ��ҩ
//			}
					SXfanzhuan(370);
			Delay1(39999999);
			printf("B=%d",a);
		}
	huiyuandian();   //��ԭ��
		if(Cyao!=0){
	  Xfanzhuan(340);}
		a = 0;
		while(a<Cyao)
		{
	
			printf("Cҩִ�п�ʼ\n");
			SXzhengzhuan(585);  //��������
			Xfanzhuan(70);  //�·�ת30��  ��ҩ���м�
			zhendong();  //��
			Xzhengzhuan(70);  //������30��  ��λ
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//			SXfanzhuan(1);  //���·�ת   ��ԭ��  ��ҩ
//			}
			SXfanzhuan(585);  //���·�ת   ��ԭ��  ��ҩ
			Delay1(39999999);
			printf("C=%d",a);
		}
	
		huiyuandian();   //��ԭ��
		if(Dyao!=0) {   //��ԭ��
	   Xfanzhuan(500); }
				a = 0;
		while(a<Dyao)
		{

			printf("Dҩִ�п�ʼ\n");
			SXzhengzhuan(790);  //��������
			Xfanzhuan(70);  //�·�ת30��  ��ҩ���м�
			zhendong();  //��
			Xzhengzhuan(70);  //������30��  ��λ
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			{
//			SXfanzhuan(1);  //���·�ת   ��ԭ��  ��ҩ
//			}
			SXfanzhuan(790);  //���·�ת   ��ԭ��  ��ҩ
			Delay1(39999999);
			printf("C=%d",a);
		}
//		a = 0;
//		while(a<Dyao)
//		{
//			printf("Dҩִ�п�ʼ\n");
//			SXfanzhuan(200);  //��������
//			Xzhengzhuan(70);  //������30��  ��λ
//			zhendong();  //��
//			Xfanzhuan(70);  //�·�ת30��  ��ҩ���м�
//			while(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN) == 0)
//			  {
//				SXzhengzhuan(1);  //���·�ת   ��ԭ��  ��ҩ
//			  }
//			Delay1(39999999);
//      	printf("D=%d",a);			
//		  }
			b=1;
			h=1;
		printf("���ڵ�������b=%d h=%d" ,b,h);

				
}


void yuandian()  //��ԭ��
{
		Coil_A1 
		Delay1(30000);//�ϲ�����
		Coil_AB1
		Delay1(30000);
		Coil_B1
		Delay1(30000);
		Coil_BC1
		Delay1(30000);
		Coil_C1
		Delay1(30000);
		Coil_CD1
		Delay1(30000);
		Coil_D1
		Delay1(30000);
		Coil_DA1
		Delay1(30000);
		Coil_OFF
		Delay1(30000);
}

void SXzhengzhuan(int t)  //��������
{
	printf("����һ��ת");  
	int i;
	for(i=0;i<t;i++)
		{	
	    Coil_DA1   
		  Coil_A2 
			Delay1(30000);
			Coil_D1
		  Coil_AB2
			Delay1(30000);
			Coil_CD1
		  Coil_B2
			Delay1(30000);
			Coil_C1
		  Coil_BC2
			Delay1(30000);
			Coil_BC1
		  Coil_C2
			Delay1(30000);
			Coil_CD2
			Coil_B1
			Delay1(30000);
			Coil_AB1
		  Coil_D2
			Delay1(30000);
		  Coil_A1
			Coil_DA2
			Delay1(30000);
			Coil_OFF
			Coil_OFF2
			Delay1(30000);
	}
}

void SXfanzhuan(int t)   //���·�ת
{
	printf("����һ��ת");
	int i;
	for(i=0;i<t;i++)
	{		
		  Coil_A1 
	    Coil_DA2 
			Delay1(30000);
	  	Coil_AB1
			Coil_D2
			Delay1(30000);
	  	Coil_B1
			Coil_CD2
			Delay1(30000); 
      Coil_BC1		
			Coil_C2
			Delay1(30000);
		  Coil_C1 
			Coil_BC2
			Delay1(30000);
		  Coil_CD1
		  Coil_B2
			Delay1(30000);
			Coil_D1
		  Coil_AB2
			Delay1(30000);
			Coil_DA1
			Coil_A2
			Delay1(30000);
			Coil_OFF
			Coil_OFF2
			Delay1(30000);
	}
}
 
void zhendong()    //��
{
	printf("�𶯵��ִ����");
	int i, x;
	for(i=0;i<1;i++)
	{
		    LED_ON(LED1); 
		for(i=0;i<50;i++)
		{
			for(x=0;x<5;x++)
			{Delay1(3000);}
		}
	   LED_OFF(LED1);
	}
}
//void Szhengzhuan()   //������
//{
//	
//}

//void Sfanzhuan()    //�Ϸ�ת
//{
//	
//}

void Xzhengzhuan(int t)  //������
{
	printf("������");
	int i;
	for(i=0;i<t;i++)//����30 ��   
	{
	    Coil_A2 
			Delay1(30000);//�²�����
			Coil_AB2
			Delay1(30000);
			Coil_B2
			Delay1(30000);
			Coil_BC2
			Delay1(30000);
			Coil_C2
			Delay1(30000);
			Coil_CD2
			Delay1(30000);
			Coil_D2
			Delay1(30000);
		  Coil_DA2
			Delay1(30000);
			Coil_OFF
			Delay1(30000);
	}
}
void Xfanzhuan(int t)    //�·�ת
{
	printf("���淴ת\n");
	int i;
	for(i=0;i<t;i++)
	{
	    Coil_DA2 
			Delay1(30000);
			Coil_D2
			Delay1(30000);
			Coil_CD2
			Delay1(30000);
			Coil_C2
			Delay1(30000);
			Coil_BC2
			Delay1(30000);
			Coil_B2
			Delay1(30000);
			Coil_AB2
			Delay1(30000);
		  Coil_A2
			Delay1(30000);
			Coil_OFF2
			Delay1(30000);
	}
}
void huiyuandian()    //��ԭ��
{
	printf("��ԭ����");
	
		while(1)
	{
		if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==0||GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==0)
		{
			SXfanzhuan(1); 
		}
		printf("�ϲ��ԭ����");
		if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==1)  //�ж��Ƿ�Ϊԭ��
		{
			Delay1(300000);//������Ե���
			if(GPIO_ReadInputDataBit(GPIO_Y1_PORT,GPIO_Y1_PIN)==1)
			{
					printf("�ϲ��ԭ��\n");
				  break;
			}
			else
			{
				yuandian();
			}
		}
		else
		{
			yuandian();
		}
	}
	
			while(1)
	{
		printf("�²��ԭ��");
		if(GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==1)  //�ж��Ƿ�Ϊԭ��
		{
			Delay1(30);//������Ե���
			if(GPIO_ReadInputDataBit(GPIO_Y2_PORT,GPIO_Y2_PIN)==1)
			{
					printf("�²��ԭ��\n");
				break;
			}
			else
			{
				Xfanzhuan(1);
			}
		}
		else
		{
		Xfanzhuan(1);
		}
	}
	
	
	
}




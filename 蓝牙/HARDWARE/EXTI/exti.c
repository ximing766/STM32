#include "exti.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "audio.h"

int temp=2;

//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
 
 	  

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	  KEY_Init();//��ʼ��������Ӧioģʽ
	


    //GPIOC.5 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);              //KEY0

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.15	  �ж����Լ��жϳ�ʼ������      KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);        //KEY1

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	

    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);   //KEY_UP

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}


// void EXTI9_5_IRQHandler(void)
//{

//	int b;
//	int a=0;

//	int longkey=0;
//	delay_ms(10);   //����	
//	if(KEY0==0)
//	{
//		while(KEY0==0 && longkey<200)  //�����ж� 1s ��ʱ20��50ms
//		{
//			delay_ms(14);    //���10ms
//			longkey++;
//		}	
//		if(longkey>=180)
//		{
//		    MusicStop();
//		}
//		else
//		{
//			for(b = 0;b<20;b++)   //�ڶ��ε���жϣ�����ʱ��Ҫ��������ε���жϣ���Ȼ�����ε����ʱ������жϻ�û�г�ȥ����ֻ�ܼ�⵽���ε��
//			{
//				delay_ms(14);  
//				if(KEY0==0)    //��������ٴΰ���a+1
//				{ 
//					a=1;    //��������ж�
//				} 
//			}
//			for(b = 0;b<40;b++)   //�����ε���жϣ�
//			{
//				delay_ms(14);  
//				if(KEY0==0)    //��������ٴΰ���a+1
//				{ 
//					a=2;    //�������
//					PreMusic();
//				} 
//			}
//			if(a==1)
//			{
//				NextMusic();
//				delay_ms(500);
//				if(temp==2)
//				{
//		
//					temp = temp+1;
//				}else if(temp==3)
//				{
//		
//					temp=temp+1;
//				}else if(temp==4)
//				{

//					temp = temp+1;
//				}else if(temp==5)
//				{
//			temp=temp+1;
//				}else if(temp==6)
//				{
//	
//					temp=2;
//				}
//				
//			}
//			if(a==0)  //a=0 ��������
//			{
//				//	Vol_sub();
//				//Audio7();                 //07���Ե�
//				delay_ms(500);
//				temp=2;

//				delay_ms(500);

//			}
//		}
//	}
// 	 EXTI_ClearITPendingBit(EXTI_Line5);    //���LINE5�ϵ��жϱ�־λ

//}


 void EXTI0_IRQHandler(void)
{
	int b;
	int a=0;
	int longkey=0;
	delay_ms(10);   //����	
	if(WK_UP==1)
	{
		while(WK_UP==1 && longkey<200)  //�����ж� 1s ��ʱ20��50ms
		{
			delay_ms(14);    //���10ms
			longkey++;
		}	
		if(longkey>=180)
		{	
			//��������
		}
		else
		{
			for(b = 0;b<20;b++)   //�ڶ��ε���жϣ�����ʱ��Ҫ��������ε���жϣ���Ȼ�����ε����ʱ������жϻ�û�г�ȥ����ֻ�ܼ�⵽���ε��
			{
				delay_ms(14);  
				if(WK_UP==1)    //��������ٴΰ���a+1
				{ 
					a=1;    //��������ж�
				} 
			}
			for(b = 0;b<40;b++)   //�����ε���жϣ�
			{
				delay_ms(14);  
				if(WK_UP==1)    //��������ٴΰ���a=2
				{ 
					a=2;    //��������	
				} 
			}
			if(a==1)  //˫�� = 
			{
				delay_ms(300);
			}
			if(a==0)  //a=0 ��������
			{
				EQSET();
			}
		}
	}
 	 EXTI_ClearITPendingBit(EXTI_Line0);    //���LINE5�ϵ��жϱ�־λ  
}


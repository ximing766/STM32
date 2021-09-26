#include "exti.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "audio.h"

int temp=2;

//外部中断初始化函数
void EXTIX_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
 
 	  

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
	  KEY_Init();//初始化按键对应io模式
	


    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);              //KEY0

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.15	  中断线以及中断初始化配置      KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);        //KEY1

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	

    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);   //KEY_UP

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}


// void EXTI9_5_IRQHandler(void)
//{

//	int b;
//	int a=0;

//	int longkey=0;
//	delay_ms(10);   //消抖	
//	if(KEY0==0)
//	{
//		while(KEY0==0 && longkey<200)  //长按判断 1s 延时20次50ms
//		{
//			delay_ms(14);    //大概10ms
//			longkey++;
//		}	
//		if(longkey>=180)
//		{
//		    MusicStop();
//		}
//		else
//		{
//			for(b = 0;b<20;b++)   //第二次点击判断，这里时间要少与第三次点击判断，不然第三次点击的时候这个判断还没有出去，就只能检测到两次点击
//			{
//				delay_ms(14);  
//				if(KEY0==0)    //如果按键再次按下a+1
//				{ 
//					a=1;    //多击处理判断
//				} 
//			}
//			for(b = 0;b<40;b++)   //第三次点击判断，
//			{
//				delay_ms(14);  
//				if(KEY0==0)    //如果按键再次按下a+1
//				{ 
//					a=2;    //多击处理
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
//			if(a==0)  //a=0 单击处理
//			{
//				//	Vol_sub();
//				//Audio7();                 //07请稍等
//				delay_ms(500);
//				temp=2;

//				delay_ms(500);

//			}
//		}
//	}
// 	 EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位

//}


 void EXTI0_IRQHandler(void)
{
	int b;
	int a=0;
	int longkey=0;
	delay_ms(10);   //消抖	
	if(WK_UP==1)
	{
		while(WK_UP==1 && longkey<200)  //长按判断 1s 延时20次50ms
		{
			delay_ms(14);    //大概10ms
			longkey++;
		}	
		if(longkey>=180)
		{	
			//长按处理
		}
		else
		{
			for(b = 0;b<20;b++)   //第二次点击判断，这里时间要少与第三次点击判断，不然第三次点击的时候这个判断还没有出去，就只能检测到两次点击
			{
				delay_ms(14);  
				if(WK_UP==1)    //如果按键再次按下a+1
				{ 
					a=1;    //多击处理判断
				} 
			}
			for(b = 0;b<40;b++)   //第三次点击判断，
			{
				delay_ms(14);  
				if(WK_UP==1)    //如果按键再次按下a=2
				{ 
					a=2;    //三击处理	
				} 
			}
			if(a==1)  //双击 = 
			{
				delay_ms(300);
			}
			if(a==0)  //a=0 单击处理
			{
				EQSET();
			}
		}
	}
 	 EXTI_ClearITPendingBit(EXTI_Line0);    //清除LINE5上的中断标志位  
}


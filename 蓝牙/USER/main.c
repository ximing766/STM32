#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "audio.h"
#include "exti.h" 
#include "key.h"
extern u8 res;

//串口二接蓝牙，串口一接语音模块

 int main(void)
 {	

 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化为9600
	My_USART2_Init();
	KEY_Init();
	EXTIX_Init();
	 
	LED_Init();		  	 //初始化与LED连接的硬件接口 
  LED0=1;
	LED1=1;
	GoSD();
	AUDIO_VOL();
	//Vol_sub();

	while(1)
	{
		if(res=='1')
		{
			Audio1();
			delay_ms(50);
			res=0;
		}
		if(res=='2')
		{
			NextMusic();
			delay_ms(50);
			res=0;
		}
		if(res=='3')
		{
			PreMusic();
			delay_ms(50);
			res=0;
		}
		if(res=='4')
		{
			MusicSuspend();
			delay_ms(50);
			res=0;
		}
		if(res=='5')
		{
			Vol_add();
			delay_ms(50);
			
			res=0;
		}
		if(res=='6')
		{
			Vol_sub();
			delay_ms(50);
			res=0;
		}
		if(res=='7')
		{
			EQSET();
			delay_ms(50);
			res=0;
		}
		
//		 switch(res)
//		 {
//			 case 1: Audio1();break;
//			 case 2: NextMusic(); break;
//			 case 3: PreMusic(); break;
//			 case 4: MusicSuspend(); break;
//			 case 5: LED0=0;
//			 case 6: LED0=1;
//			 //case 5: Vol_add(); break;
//			 //case 6: Vol_sub(); break;
//			 case 7: EQSET(); break;
//			 default : LED1=0;
//		 }

		
	}	 
	return 0;
}



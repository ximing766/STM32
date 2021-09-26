#include "audio.h"

int EQValue=0;
int ModeValue=0;

u16 EQ[5][5] = {
	{0xAA, 0x1A, 0x01 ,0x00 ,0xC5},    //normal
	{0xAA, 0x1A, 0x01 ,0x01 ,0xC6},	  //POP
	{0xAA, 0x1A, 0x01 ,0x02 ,0xC7},    //ROCK
	{0xAA, 0x1A, 0x01 ,0x03 ,0xC8},	  //JAZZ
	{0xAA, 0x1A, 0x01 ,0x04 ,0xC9}	  //CLASSIC

};

u16 Mode[4][5] = {
	{0xAA, 0x18, 0x01 ,0x00 ,0xC4},    /*ȫ��ѭ�� ��˳�򲥷�ȫ����Ŀ,�������ѭ������*/
	{0xAA, 0x18, 0x01 ,0x01 ,0xC5},	   /*����ѭ�� һֱѭ�����ŵ�ǰ��Ŀ*/
	{0xAA, 0x18, 0x01 ,0x02 ,0xC6},    /*����ֹͣ �����굱ǰ��Ŀһ��ֹͣ*/
	{0xAA, 0x18, 0x01 ,0x03 ,0xC7},	   /*ȫ����� ��������̷�����Ŀ*/


};
//ָ���̷�·�� AA 08 ���� �̷� ·�� SM   ����=1+·������
//�л��̷�  AA 0B 01 �̷� SM   �̷���00U�� 01TF�� 02 FLASH�����л���ֹͣ
void GoSD(void)
{
	u16 t;
	u8 volAdd[5] = {0xAA, 0x0B, 0x01, 0x01, 0xB7};
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, volAdd[t]);//�򴮿�1��������
		delay_ms(100);
	}
}

void MusicMode(void)
{
	u16 t;
	
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, Mode[ModeValue][t]);//�򴮿�1��������
		delay_ms(100);
	}
	if(ModeValue!=3)
	{
		ModeValue++;
	}
	else
	{
		ModeValue=0;
	}
}


void AUDIO_PLAY(u8 AUDIO_BUF[20])
{
	u16 t; 
	for(t=0;t<20;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ��� TC�������RXNE�����ݼĴ����ǿ�
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�1��������  ���͵�USART_DR�����ͽ��ն�ͨ������Ĵ���
		delay_ms(100);
			
	}	
	
	//delay_ms(20000);
}


void AUDIO_VOL(void)
{
	u16 t;
	u8 AUDIO_VOL[5] = {0xAA, 0x13, 0x01, 0x20, 0xDE};  //0xAA 0x13 0x01�ǹ̶���ʽ�������������������30����0x1E 0xDC�Ǻ�У��ǰ�������
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_VOL[t]);//�򴮿�1��������
		delay_ms(100);
			
	}	
	//delay_ms(20000);
	
}


void Vol_add(void)
{
	u16 t;
	u8 volAdd[5] = {0xAA, 0x13, 0x01, 0x30, 0xEE};
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, volAdd[t]);//�򴮿�1��������
		delay_ms(100);
	}
}


void Vol_sub(void)
{
	u16 t;
	u8 volSub[5] = {0xAA, 0x13, 0x01, 0x10, 0xCE};
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, volSub[t]);//�򴮿�1��������
		delay_ms(100);
	}
}


void EQSET(void)
{
	u16 t;
	
	for(t=0;t<5;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, EQ[EQValue][t]);//�򴮿�1��������
		delay_ms(100);
	}
	if(EQValue!=4)
	{
		EQValue++;
	}
	else
	{
		EQValue=0;
	}
}


void PreMusic(void)    //��һ��
{
	uint8_t t;
	uint8_t AUDIO_BUF[4] = {0xAA, 0x05, 0x00, 0xAF};	  //ָ����Ŀ���ţ�ǰ�����̶���00��ǰ�̷���06�������
	for(t=0;t<4;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void PleaseW(void)    //
{
	uint8_t t;
	u8 PleaseW[22] = {0xAA, 0x08, 0x12, 0x01, 0x2F, 0xCE, 0xD2, 0xB5, 0xC4, 0x2A, 0x2F, 0xC7, 0xEB, 0xC9, 0xD4, 0xB5, 0xC8, 0x2A, 0x3F, 0x3F, 0x3F, 0x19};

	for(t=0;t<22;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, PleaseW[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void NextMusic(void)   //��һ��
{
	uint8_t t;
	uint8_t AUDIO_BUF[4] = {0xAA, 0x06, 0x00, 0xB0};	  //ָ����Ŀ���ţ�ǰ�����̶���00��ǰ�̷���06�������
	for(t=0;t<4;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void MusicSuspend(void)  //��ͣ
{
	uint8_t t;
	uint8_t AUDIO_BUF[4] = {0xAA, 0x03, 0x00, 0xAD};	  //ָ����Ŀ���ţ�ǰ�����̶���00��ǰ�̷���06�������
	for(t=0;t<4;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void MusicStop(void)  //ֹͣ����
{
	uint8_t t;
	uint8_t AUDIO_BUF[4] = {0xAA, 0x04, 0x00, 0xAE};	  //ָ����Ŀ���ţ�ǰ�����̶���02��Flash 00��ǰ�̷���06�������
	for(t=0;t<4;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio6(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x06, 0xB9};	  //ָ����Ŀ���ţ�ǰ�����̶���00��ǰ�̷���06�������
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio1(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio2(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio3(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x03, 0xB6};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio4(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x04, 0xB7};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}



void Audio5(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x05, 0xB8};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


void Audio7(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x07, 0xBA};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}

void Audio8(void)
{
	uint8_t t;
	uint8_t AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x08, 0xBB};	
	for(t=0;t<6;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		USART_SendData(USART1, AUDIO_BUF[t]);//�򴮿�2��������
		delay_ms(100);	
	}	
}


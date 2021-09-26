#ifndef __AUDIO_H
#define __AUDIO_H	 

//ͷ�ļ�
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

//�궨��
typedef enum {
    JQ8X00_USB                      = 0X00,                 /*UPANND*/
    JQ8X00_SD                       = 0x01,                 /*SD*/
    JQ8X00_FLASH                    = 0x02,                 /*FLASH*/
}JQ8X00_Symbol;       //ϵͳ�̷�
//ѭ��ģʽѡ���ڰ����������ָ������
//    SetLoopMode                     = 0x18,                 /*����ѭ��ģʽ*/
typedef enum {
    OverallCycle                = 0X00,         /*ȫ��ѭ�� ��˳�򲥷�ȫ����Ŀ,�������ѭ������*/
    SingleCycle                 = 0x01,         /*����ѭ�� һֱѭ�����ŵ�ǰ��Ŀ*/
    SingleStop                  = 0x02,         /*����ֹͣ �����굱ǰ��Ŀһ��ֹͣ*/
    OverallRandom               = 0X03,         /*ȫ����� ��������̷�����Ŀ*/
    CatalogCycle                = 0X04,          /*Ŀ¼ѭ�� ��˳�򲥷ŵ�ǰ�ļ�������Ŀ,�������ѭ�����ţ�Ŀ¼��������Ŀ¼*/
    CatalogRandom               = 0x05,          /*Ŀ¼��� �ڵ�ǰĿ¼��������ţ�Ŀ¼��������Ŀ¼*/
    CatalogTurnPlay             = 0x06,         /*Ŀ¼˳�򲥷� ��˳�򲥷ŵ�ǰ�ļ�������Ŀ,�������ֹͣ��Ŀ¼��������Ŀ¼*/
    OverallTurnPlay             = 0x07,         /*ȫ��˳�򲥷� ��˳�򲥷�ȫ����Ŀ,�������ֹͣ*/ 
}LoopModeSelect;      //ѭ��ģʽѡ��
//��������
void AUDIO_PLAY(u8 AUDIO_BUF[20]);
void AUDIO_VOL(void);
void PreMusic(void);
void NextMusic(void);
void MusicSuspend(void);
void MusicStop(void);
void Audio6(void);
void Audio5(void);
void Audio4(void);
void Audio3(void);
void Audio2(void);
void Audio1(void);
void PleaseW(void);
void Audio7(void);
void Vol_add(void);
void Vol_sub(void);
void EQSET(void);
void Audio8(void);
void GoSD(void);
void MusicMode(void);
		

#endif


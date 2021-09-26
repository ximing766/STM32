#ifndef __AUDIO_H
#define __AUDIO_H	 

//头文件
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

//宏定义
typedef enum {
    JQ8X00_USB                      = 0X00,                 /*UPANND*/
    JQ8X00_SD                       = 0x01,                 /*SD*/
    JQ8X00_FLASH                    = 0x02,                 /*FLASH*/
}JQ8X00_Symbol;       //系统盘符
//循环模式选择在包含多个数据指令里面
//    SetLoopMode                     = 0x18,                 /*设置循环模式*/
typedef enum {
    OverallCycle                = 0X00,         /*全盘循环 按顺序播放全盘曲目,播放完后循环播放*/
    SingleCycle                 = 0x01,         /*单曲循环 一直循环播放当前曲目*/
    SingleStop                  = 0x02,         /*单曲停止 播放完当前曲目一次停止*/
    OverallRandom               = 0X03,         /*全盘随机 随机播放盘符内曲目*/
    CatalogCycle                = 0X04,          /*目录循环 按顺序播放当前文件夹内曲目,播放完后循环播放，目录不包含子目录*/
    CatalogRandom               = 0x05,          /*目录随机 在当前目录内随机播放，目录不包含子目录*/
    CatalogTurnPlay             = 0x06,         /*目录顺序播放 按顺序播放当前文件夹内曲目,播放完后停止，目录不包含子目录*/
    OverallTurnPlay             = 0x07,         /*全盘顺序播放 按顺序播放全盘曲目,播放完后停止*/ 
}LoopModeSelect;      //循环模式选择
//函数声明
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


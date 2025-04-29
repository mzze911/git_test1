#ifndef __FUNC_ALONE_KEY_H__
#define __FUNC_ALONE_KEY_H__

#include "bsp_stm32f1_mzze.h"

/****************条件编译参数*****************/
#define FUNC_ALONE_KEY_BEEP_EN    1         //是否需要蜂鸣宏定义，若定义则增加蜂鸣相关函数
//#define FUNC_ALONE_KEY_SCAN_IN_MAIN   1     //按键扫描函数,MAIN函数中调用

//--枚举类型----
typedef enum 
{
    ALONE_KEY_IDLE=0,
    ALONE_KEY_ON,
    ALONE_KEY_ON_1S,
    ALONE_KEY_ON_2S,
    ALONE_KEY_ON_4S,
    ALONE_KEY_ON_5S,
    ALONE_KEY_ON_6S,
    ALONE_KEY_ON_7S,
    ALONE_KEY_ON_8S,
    ALONE_KEY_ON_12S,	
}FUNC_ALONE_KEY_STATE_ENUM;


/**********按键名宏定义*********/
#define KEY_1         FUNC_ALONE_KEY_STATE[0]
#define KEY_2         FUNC_ALONE_KEY_STATE[1]
#define KEY_3         FUNC_ALONE_KEY_STATE[2]
#define KEY_4         FUNC_ALONE_KEY_STATE[3]
#define KEY_5         FUNC_ALONE_KEY_STATE[4]
#define KEY_6         FUNC_ALONE_KEY_STATE[5]

#define KEY_SELECT_WORKOUT FUNC_ALONE_KEY_STATE[0]
#define KEY_START_ENTER    FUNC_ALONE_KEY_STATE[1]
#define KEY_UP             FUNC_ALONE_KEY_STATE[2]
#define KEY_DOWN           FUNC_ALONE_KEY_STATE[3]
#define KEY_STOP           FUNC_ALONE_KEY_STATE[4]
#define KEY_BLUETOOTH      FUNC_ALONE_KEY_STATE[5]

#define KEY_BLUETOOTH_1      FUNC_ALONE_KEY_STATE_1[5]    

/*------------------------------单个按键状态标志位----------------------------------*/
extern FUNC_ALONE_KEY_STATE_ENUM FUNC_ALONE_KEY_STATE[];		 //第key_num个按键状态 ｛无按键=0;单击=1;双击=2;长按2S=3;长按5S=4;}
extern FUNC_ALONE_KEY_STATE_ENUM FUNC_ALONE_KEY_STATE_1[];	

extern unsigned char FUNC_ALONE_KEY_PD_NUM;             //当前被按下的按键数量
/**********tim0中断中需要调用的程序***************/
#ifdef FUNC_ALONE_KEY_SCAN_IN_MAIN
void FUNC_ALONE_KEY_TIMER(void);    
#endif



void FUNC_ALONE_KEY_SCAN(void);

void FUNC_ALONE_KEY_INIT(void);



#endif

























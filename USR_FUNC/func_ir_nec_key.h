#ifndef __FUNC_IR_NEC_KEY_H__
#define __FUNC_IR_NEC_KEY_H__

#include "bsp_stm32f1_mzze.h"
#include "func_ir_decode.h"


/****************条件编译参数*****************/
#define FUNC_IR_NEC_KEY_BEEP_ON  1           //是否需要蜂鸣宏定义，若定义则增加蜂鸣相关函数

//--枚举类型----
typedef enum 
{
    IR_NEC_KEY_IDLE=0,
    IR_NEC_KEY_ON,
    IR_NEC_KEY_ON_1S,
    IR_NEC_KEY_ON_2S,
    IR_NEC_KEY_ON_4S,
    IR_NEC_KEY_ON_5S,
    IR_NEC_KEY_ON_6S,
    IR_NEC_KEY_ON_7S,
    IR_NEC_KEY_ON_8S,
    IR_NEC_KEY_ON_12S,	
}FUNC_IR_NEC_KEY_STATE_ENUM;


/**********按键名宏定义*********/
#define IR_NEC_KEY_1         FUNC_IR_NEC_KEY_STATE[0]
#define IR_NEC_KEY_2         FUNC_IR_NEC_KEY_STATE[1]
#define IR_NEC_KEY_3         FUNC_IR_NEC_KEY_STATE[2]
#define IR_NEC_KEY_4         FUNC_IR_NEC_KEY_STATE[3]
#define IR_NEC_KEY_5         FUNC_IR_NEC_KEY_STATE[4]
#define IR_NEC_KEY_6         FUNC_IR_NEC_KEY_STATE[5]

#define IR_KEY_SELECT_WORKOUT IR_NEC_KEY_1
#define IR_KEY_START_ENTER    IR_NEC_KEY_2
#define IR_KEY_UP             IR_NEC_KEY_3
#define IR_KEY_DOWN           IR_NEC_KEY_4
#define IR_KEY_STOP           IR_NEC_KEY_5
#define IR_KEY_BLUETOOTH      IR_NEC_KEY_6

#define IR_KEY_BLUETOOTH_1      FUNC_IR_NEC_KEY_STATE_1[5]    

/*--------------对外接口变量------------------*/
extern FUNC_IR_NEC_KEY_STATE_ENUM FUNC_IR_NEC_KEY_STATE[];		 //第key_num个按键状态
extern FUNC_IR_NEC_KEY_STATE_ENUM FUNC_IR_NEC_KEY_STATE_1[];	


/*--------------对外接口函数------------------*/
extern void FUNC_IR_NEC_KEY_GET(unsigned char bus_idle,STRUCT_FUNC_IR_NEC_CMD* cmd);

extern void FUNC_IR_NEC_KEY_INIT(void);

#endif

























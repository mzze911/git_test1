#ifndef __MAIN_H__
#define __MAIN_H__

#include "bsp_stm32f1_mzze.h"
#include "func_s_state_machine.h"



/**********主状态机相关定义*********/
//----状态定义-----
#define MCS_ID_0     0         //设备上电状态
#define MCS_ID_1     1         //状态1
#define MCS_ID_2     2         //状态2
#define MCS_ID_3     3         //状态3
#define MCS_ID_4     4         //状态4
#define MCS_ID_5     5         //状态5


#define MCS_ID_POWER_UP     MCS_ID_0
//#define MCS_ID_POWER_DW     MCS_ID_0
//#define MCS_ID_POWER_SLEEP  MCS_ID_0



/************对外接口*************/
//---主状态机-----
extern STRUCT_FUNC_STATE_MACHINE1 MAIN_CON_SM;




#endif




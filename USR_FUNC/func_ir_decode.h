#ifndef __FUNC_IR_DECODE_H__
#define __FUNC_IR_DECODE_H__

#include "bsp_stm32f1_mzze.h"

/**************红外协议类型宏定义**************/
#define FUNC_IR_DECODE_TYPE   0    //0->NEC

	
//----结构体定义----------
#if(FUNC_IR_DECODE_TYPE==0)	
typedef struct{
    
	//--参数---	
	unsigned char add;             //地址
	unsigned char cmd;             //命令
	unsigned char get_mark;        //第一次获取标志 0->代表没获取到 1->代表获取到	
	unsigned short int repeat;          //重复获取次数
}STRUCT_FUNC_IR_NEC_CMD;
#endif



//----------对外接口变量------------
#if(FUNC_IR_DECODE_TYPE==0)	
extern STRUCT_FUNC_IR_NEC_CMD FUNC_IR_DECODE_NEC_CCMD;     //最近一次获取到的命令
#endif



//----------对外接口函数------------

extern void FUNC_IR_DECODE_INIT(void);

extern void FUNC_IR_DECODE_WORK_TIMER(void);

extern void FUNC_IR_DECODE_WORK_EXTI(void);
	



#endif


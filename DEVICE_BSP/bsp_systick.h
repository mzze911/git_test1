#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_
#include "bsp_stm32f1_mzze.h"


extern volatile unsigned long int bsp_systick_count;   //µÎ´ð¼ÆÊý

extern void BSP_SYSTICK_INIT(void);
extern void BSP_SYSTICK_DEINIT(void);

extern void BSP_SYSTICK_DELAY_US(u32 nus);
extern void BSP_SYSTICK_DELAY_MS(u16 nms);    


#endif


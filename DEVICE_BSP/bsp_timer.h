#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#include "bsp_stm32f1_mzze.h"

/************宏定义*****************/
#define BSP_TIM2_EXT_TICK_EN   1     //是否使能额外计数，对于开了中断的有效
#define BSP_TIM3_EXT_TICK_EN   1  
#define BSP_TIM4_EXT_TICK_EN   0  







//--------------对外接口函数---------------------

extern void BSP_TIM2_INIT(u32 arr,u16 psc);
extern void BSP_TIM2_SET_COUNT(unsigned long int t);
extern unsigned long int BSP_TIM2_GET_COUNT(void);
#if(BSP_TIM2_EXT_TICK_EN==1)
extern void BSP_TIM2_SET_EXT_TICK(unsigned long int t);
extern unsigned long int BSP_TIM2_GET_EXT_TICK(void);
#endif


extern void BSP_TIM3_INIT(u32 arr,u16 psc);
extern void BSP_TIM3_SET_COUNT(unsigned long int t);
extern unsigned long int BSP_TIM3_GET_COUNT(void);
#if(BSP_TIM3_EXT_TICK_EN==1)
extern void BSP_TIM3_SET_EXT_TICK(unsigned long int t);
extern unsigned long int BSP_TIM3_GET_EXT_TICK(void);
#endif


extern void BSP_TIM4_INIT(u32 arr,u16 psc);
extern void BSP_TIM4_SET_COUNT(unsigned long int t);
extern unsigned long int BSP_TIM4_GET_COUNT(void);
#if(BSP_TIM4_EXT_TICK_EN==1)
extern void BSP_TIM4_SET_EXT_TICK(unsigned long int t);
extern unsigned long int BSP_TIM4_GET_EXT_TICK(void);
#endif



#endif



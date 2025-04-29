#ifndef _BSP_IWDG_H_
#define _BSP_IWDG_H_

#include "bsp_stm32f1_mzze.h"


extern void BSP_IWDG_INIT(u8 prer,u16 rlr);    //初始化IWDG，并使能IWDG
extern void BSP_IWDG_FEED(void);               //喂狗



#endif


















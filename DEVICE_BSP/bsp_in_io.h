#ifndef _BSP_IN_IO_H_
#define _BSP_IN_IO_H_

#include "bsp_stm32f1_mzze.h"

//-------开关端口--------
#define BSP_IN_IO_S1 PEin(0)        //开关1
#define BSP_IN_IO_S2 PEin(1)        //开关2 

#define BSP_IN_IO_S1_ON   0   //闭合
#define BSP_IN_IO_S1_OFF  1   //断开

#define BSP_IN_IO_S2_ON   0   //闭合
#define BSP_IN_IO_S2_OFF  1   //断开




extern void BSP_IN_IO_INIT(void);















#endif



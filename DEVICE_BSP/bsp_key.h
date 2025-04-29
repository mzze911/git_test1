#ifndef __MSP_KEY_H__
#define __MSP_KEY_H__

#include "bsp_stm32f1_mzze.h"

//#define BSP_IO_KEY0   PEin(0)
//#define BSP_IO_KEY1   PAin(0)
//#define BSP_IO_KEY2   PAin(8)
//#define BSP_IO_KEY3   PBin(10)
//#define BSP_IO_KEY4   PEin(4)

#define BSP_IO_KEY1   PEin(4)
#define BSP_IO_KEY2   PEin(3)
#define BSP_IO_KEY3   PEin(2)


extern void BSP_KEY_INIT(void);


#endif


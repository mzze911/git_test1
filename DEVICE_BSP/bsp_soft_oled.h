#ifndef __BSP_SOFT_OLED_H__
#define __BSP_SOFT_OLED_H__

#include "bsp_stm32f1_mzze.h"


/**************oled接口类型宏定义*********************/
#define BSP_SOFT_OLED_TYPE  2     //1->iic   2->spi







extern void BSP_SOFT_OLED_REFRESH_GRAM(void);

extern void BSP_SOFT_OLED_INIT(void);



#endif

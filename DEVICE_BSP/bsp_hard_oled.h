#ifndef __BSP_HARD_OLED_H__
#define __BSP_HARD_OLED_H__

#include "bsp_stm32f1_mzze.h"


/**************oled接口类型宏定义*********************/
#define BSP_HARD_OLED_TYPE  2     //1->iic   2->spi
#define BSP_HARD_SPI_DMA_EN 1     //0->不使用 1->使用






extern unsigned char BSP_HARD_OLED_REFRESH_GRAM(void);

extern void BSP_HARD_OLED_INIT(void);



#endif

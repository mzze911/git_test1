#ifndef __APP_OLED_DISPLAY_H__
#define __APP_OLED_DISPLAY_H__


#include "bsp_stm32f1_mzze.h"



extern unsigned char APP_OLED_REFRESH_OLED_RAM_MARK;    //更新OLED_RAM标志位  0-->代表更新完成 1-->代表正在更新


extern unsigned char APP_OLED_DISPLAY_PICTURE(unsigned char arg_picture_id,unsigned char arg_mod_step);






















#endif

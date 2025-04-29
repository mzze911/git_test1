#ifndef __FUNC_OLED_H__
#define __FUNC_OLED_H__

#include "bsp_stm32f1_mzze.h"


/**************ASCII字符大小宏定义*********************/
#define OLED_ASCII_12X12             12      //ASCII编码6X12点阵
#define OLED_ASCII_16X16             16      //ASCII编码8X16点阵
#define OLED_ASCII_24X24             24    //ASCII编码12x24点阵
/***************GB2312字符大小宏定义*******************/
#define OLED_GB2312_12X12           12
#define OLED_GB2312_16X16           16

/***************字符串显示字体大小定义******************/
#define OLED_STRING_12         12
#define OLED_STRING_16         16
#define OLED_STRING_24         24


extern unsigned char FUNC_OLED_GRAM[8][128];






extern void FUNC_OLED_INIT(void);
extern unsigned char FUNC_OLED_GRAM_REFRESH(void);




extern void FUNC_OLED_GRAM_ALL_CLEAR(void);
	

extern void FUNC_OLED_GRAM_ALL_SET(void);



extern void FUNC_OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
 

extern void FUNC_OLED_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);


extern void FUNC_OLED_clearRectangle(u16 x1, u16 y1, u16 x_wide, u16 y_wide);
  

extern void FUNC_OLED_fillRectangle(u16 x1, u16 y1, u16 x_wide, u16 y_wide);


extern void FUNC_OLED_Draw_Circle(u16 x0,u16 y0,u8 r);

 
 
extern void FUNC_OLED_Show_ASCII_Mat(u16 x,u16 y,u8 *ascii,u8 size,u8 mode);

extern void FUNC_OLED_Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode,u8 ascii_ypy);
 
extern unsigned short int FUNC_OLED_Show_Str_gundon(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode,u16 str_hang_py,u8 ascii_ypy);
  
extern void FUNC_OLED_Show_time(u16 x, u16 y,unsigned char h,unsigned char m,unsigned char s,u8 size);



#endif
























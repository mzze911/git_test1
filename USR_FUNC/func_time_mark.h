#ifndef __FUNC_TIME_MARK_H__
#define	__FUNC_TIME_MARK_H__

#include "bsp_stm32f1_mzze.h"


//---------------------时间标志宏定义-----------------------
/******50ms标志的8个标志位********/     //若使用了某一位则取消注释，同一位不可用于多处任务
#define R_time_mark_50ms_mark1_b1   GET_8BIT(time_mark_50ms_mark1,0)           //主函数中调用
#define CLR_time_mark_50ms_mark1_b1   CLR_8BIT(time_mark_50ms_mark1,0)

#define R_time_mark_50ms_mark1_b2   GET_8BIT(time_mark_50ms_mark1,1)        //gui_app1.c中使用
#define CLR_time_mark_50ms_mark1_b2   CLR_8BIT(time_mark_50ms_mark1,1)

//#define R_time_mark_50ms_mark1_b3   GET_8BIT(time_mark_50ms_mark1,2)
//#define CLR_time_mark_50ms_mark1_b3   CLR_8BIT(time_mark_50ms_mark1,2)

//#define R_time_mark_50ms_mark1_b4   GET_8BIT(time_mark_50ms_mark1,3)
//#define CLR_time_mark_50ms_mark1_b4   CLR_8BIT(time_mark_50ms_mark1,3)

//#define R_time_mark_50ms_mark1_b5   GET_8BIT(time_mark_50ms_mark1,4)
//#define CLR_time_mark_50ms_mark1_b5   CLR_8BIT(time_mark_50ms_mark1,4)

//#define R_time_mark_50ms_mark1_b6   GET_8BIT(time_mark_50ms_mark1,5)
//#define CLR_time_mark_50ms_mark1_b6   CLR_8BIT(time_mark_50ms_mark1,5)

//#define R_time_mark_50ms_mark1_b7   GET_8BIT(time_mark_50ms_mark1,6)
//#define CLR_time_mark_50ms_mark1_b7   CLR_8BIT(time_mark_50ms_mark1,6)

//#define R_time_mark_50ms_mark1_b8   GET_8BIT(time_mark_50ms_mark1,7)
//#define CLR_time_mark_50ms_mark1_b8   CLR_8BIT(time_mark_50ms_mark1,7)

//#define R_time_mark_50ms_mark2_b1   GET_8BIT(time_mark_50ms_mark2,0)
//#define CLR_time_mark_50ms_mark2_b1   CLR_8BIT(time_mark_50ms_mark2,0)

//#define R_time_mark_50ms_mark2_b2   GET_8BIT(time_mark_50ms_mark2,1)
//#define CLR_time_mark_50ms_mark2_b2   CLR_8BIT(time_mark_50ms_mark2,1)

//#define R_time_mark_50ms_mark2_b3   GET_8BIT(time_mark_50ms_mark2,2)
//#define CLR_time_mark_50ms_mark2_b3   CLR_8BIT(time_mark_50ms_mark2,2)

//#define R_time_mark_50ms_mark2_b4   GET_8BIT(time_mark_50ms_mark2,3)
//#define CLR_time_mark_50ms_mark2_b4   CLR_8BIT(time_mark_50ms_mark2,3)

//#define R_time_mark_50ms_mark2_b5   GET_8BIT(time_mark_50ms_mark2,4)
//#define CLR_time_mark_50ms_mark2_b5   CLR_8BIT(time_mark_50ms_mark2,4)

//#define R_time_mark_50ms_mark2_b6   GET_8BIT(time_mark_50ms_mark2,5)
//#define CLR_time_mark_50ms_mark2_b6   CLR_8BIT(time_mark_50ms_mark2,5)

//#define R_time_mark_50ms_mark2_b7   GET_8BIT(time_mark_50ms_mark2,6)
//#define CLR_time_mark_50ms_mark2_b7   CLR_8BIT(time_mark_50ms_mark2,6)

//#define R_time_mark_50ms_mark2_b8   GET_8BIT(time_mark_50ms_mark2,7)
//#define CLR_time_mark_50ms_mark2_b8   CLR_8BIT(time_mark_50ms_mark2,7)



/******100ms标志的8个标志位********/     //若使用了某一位则取消注释，同一位不可用于多处任务
#define R_time_mark_100ms_mark1_b1   GET_8BIT(time_mark_100ms_mark1,0)           //gui_app1.c中使用
#define CLR_time_mark_100ms_mark1_b1   CLR_8BIT(time_mark_100ms_mark1,0)

#define R_time_mark_100ms_mark1_b2   GET_8BIT(time_mark_100ms_mark1,1)           //mian.c中使用
#define CLR_time_mark_100ms_mark1_b2   CLR_8BIT(time_mark_100ms_mark1,1)

#define R_time_mark_100ms_mark1_b3   GET_8BIT(time_mark_100ms_mark1,2)         //func_bat_con.c中使用
#define CLR_time_mark_100ms_mark1_b3   CLR_8BIT(time_mark_100ms_mark1,2)

#define R_time_mark_100ms_mark1_b4   GET_8BIT(time_mark_100ms_mark1,3)         //ntc_temp_detct.c中使用
#define CLR_time_mark_100ms_mark1_b4   CLR_8BIT(time_mark_100ms_mark1,3)

#define R_time_mark_100ms_mark1_b5   GET_8BIT(time_mark_100ms_mark1,4)         //func_bat_con.c中使用
#define CLR_time_mark_100ms_mark1_b5   CLR_8BIT(time_mark_100ms_mark1,4)

//#define R_time_mark_100ms_mark1_b6   GET_8BIT(time_mark_100ms_mark1,5)
//#define CLR_time_mark_100ms_mark1_b6   CLR_8BIT(time_mark_100ms_mark1,5)

//#define R_time_mark_100ms_mark1_b7   GET_8BIT(time_mark_100ms_mark1,6)
//#define CLR_time_mark_100ms_mark1_b7   CLR_8BIT(time_mark_100ms_mark1,6)

//#define R_time_mark_100ms_mark1_b8   GET_8BIT(time_mark_100ms_mark1,7)
//#define CLR_time_mark_100ms_mark1_b8   CLR_8BIT(time_mark_100ms_mark1,7)

//#define R_time_mark_100ms_mark2_b1   GET_8BIT(time_mark_100ms_mark2,0)
//#define CLR_time_mark_100ms_mark2_b1   CLR_8BIT(time_mark_100ms_mark2,0)

//#define R_time_mark_100ms_mark2_b2   GET_8BIT(time_mark_100ms_mark2,1)
//#define CLR_time_mark_100ms_mark2_b2   CLR_8BIT(time_mark_100ms_mark2,1)

//#define R_time_mark_100ms_mark2_b3   GET_8BIT(time_mark_100ms_mark2,2)
//#define CLR_time_mark_100ms_mark2_b3   CLR_8BIT(time_mark_100ms_mark2,2)

//#define R_time_mark_100ms_mark2_b4   GET_8BIT(time_mark_100ms_mark2,3)
//#define CLR_time_mark_100ms_mark2_b4   CLR_8BIT(time_mark_100ms_mark2,3)

//#define R_time_mark_100ms_mark2_b5   GET_8BIT(time_mark_100ms_mark2,4)
//#define CLR_time_mark_100ms_mark2_b5   CLR_8BIT(time_mark_100ms_mark2,4)

//#define R_time_mark_100ms_mark2_b6   GET_8BIT(time_mark_100ms_mark2,5)
//#define CLR_time_mark_100ms_mark2_b6   CLR_8BIT(time_mark_100ms_mark2,5)

//#define R_time_mark_100ms_mark2_b7   GET_8BIT(time_mark_100ms_mark2,6)
//#define CLR_time_mark_100ms_mark2_b7   CLR_8BIT(time_mark_100ms_mark2,6)

//#define R_time_mark_100ms_mark2_b8   GET_8BIT(time_mark_100ms_mark2,7)
//#define CLR_time_mark_100ms_mark2_b8   CLR_8BIT(time_mark_100ms_mark2,7)

/******500ms标志的8个标志位********/     //若使用了某一位则取消注释，同一位不可用于多处任务
#define R_time_mark_500ms_mark1_b1   GET_8BIT(time_mark_500ms_mark1,0)            //主函数中调用
#define CLR_time_mark_500ms_mark1_b1   CLR_8BIT(time_mark_500ms_mark1,0)

#define R_time_mark_500ms_mark1_b2   GET_8BIT(time_mark_500ms_mark1,1)            //mian.c中使用
#define CLR_time_mark_500ms_mark1_b2   CLR_8BIT(time_mark_500ms_mark1,1)

#define R_time_mark_500ms_mark1_b3   GET_8BIT(time_mark_500ms_mark1,2)            //app_local_con.c中使用
#define CLR_time_mark_500ms_mark1_b3   CLR_8BIT(time_mark_500ms_mark1,2)

#define R_time_mark_500ms_mark1_b4   GET_8BIT(time_mark_500ms_mark1,3)            //func_co2_sensor.c中使用
#define CLR_time_mark_500ms_mark1_b4   CLR_8BIT(time_mark_500ms_mark1,3)

#define R_time_mark_500ms_mark1_b5   GET_8BIT(time_mark_500ms_mark1,4)            //func_pc_interface_com.c中使用
#define CLR_time_mark_500ms_mark1_b5   CLR_8BIT(time_mark_500ms_mark1,4)
 
#define R_time_mark_500ms_mark1_b6   GET_8BIT(time_mark_500ms_mark1,5)            //app_oled_display.c中使用
#define CLR_time_mark_500ms_mark1_b6   CLR_8BIT(time_mark_500ms_mark1,5)
//
//#define R_time_mark_500ms_mark1_b7   GET_8BIT(time_mark_500ms_mark1,6)
//#define CLR_time_mark_500ms_mark1_b7   CLR_8BIT(time_mark_500ms_mark1,6)
//
//#define R_time_mark_500ms_mark1_b8   GET_8BIT(time_mark_500ms_mark1,7)
//#define CLR_time_mark_500ms_mark1_b8   CLR_8BIT(time_mark_500ms_mark1,7)

//#define R_time_mark_500ms_mark2_b1   GET_8BIT(time_mark_500ms_mark2,0)
//#define CLR_time_mark_500ms_mark2_b1   CLR_8BIT(time_mark_500ms_mark2,0)

//#define R_time_mark_500ms_mark2_b2   GET_8BIT(time_mark_500ms_mark2,1)
//#define CLR_time_mark_500ms_mark2_b2   CLR_8BIT(time_mark_500ms_mark2,1)

//#define R_time_mark_500ms_mark2_b3   GET_8BIT(time_mark_500ms_mark2,2)
//#define CLR_time_mark_500ms_mark2_b3   CLR_8BIT(time_mark_500ms_mark2,2)

//#define R_time_mark_500ms_mark2_b4   GET_8BIT(time_mark_500ms_mark2,3)
//#define CLR_time_mark_500ms_mark2_b4   CLR_8BIT(time_mark_500ms_mark2,3)

//#define R_time_mark_500ms_mark2_b5   GET_8BIT(time_mark_500ms_mark2,4)
//#define CLR_time_mark_500ms_mark2_b5   CLR_8BIT(time_mark_500ms_mark2,4)

//#define R_time_mark_500ms_mark2_b6   GET_8BIT(time_mark_500ms_mark2,5)
//#define CLR_time_mark_500ms_mark2_b6   CLR_8BIT(time_mark_500ms_mark2,5)

//#define R_time_mark_500ms_mark2_b7   GET_8BIT(time_mark_500ms_mark2,6)
//#define CLR_time_mark_500ms_mark2_b7   CLR_8BIT(time_mark_500ms_mark2,6)

//#define R_time_mark_500ms_mark2_b8   GET_8BIT(time_mark_500ms_mark2,7)
//#define CLR_time_mark_500ms_mark2_b8   CLR_8BIT(time_mark_500ms_mark2,7)

/*****1000ms标志的8个标志位*********/    //若使用了某一位则取消注释，同一位不可用于多处任务
#define R_time_mark_1000ms_mark_b1   GET_8BIT(time_mark_1000ms_mark,0)              //用于主函数
#define CLR_time_mark_1000ms_mark_b1   CLR_8BIT(time_mark_1000ms_mark,0)

#define R_time_mark_1000ms_mark_b2   GET_8BIT(time_mark_1000ms_mark,1)              //用于BLUE_CLient函数
#define CLR_time_mark_1000ms_mark_b2   CLR_8BIT(time_mark_1000ms_mark,1)

#define R_time_mark_1000ms_mark_b3   GET_8BIT(time_mark_1000ms_mark,2)              //用于BSP_SIM_EEPROM函数
#define CLR_time_mark_1000ms_mark_b3   CLR_8BIT(time_mark_1000ms_mark,2)

#define R_time_mark_1000ms_mark_b4   GET_8BIT(time_mark_1000ms_mark,3)              //app_oled_display.c中使用
#define CLR_time_mark_1000ms_mark_b4   CLR_8BIT(time_mark_1000ms_mark,3)

//#define R_time_mark_1000ms_mark_b5   GET_8BIT(time_mark_1000ms_mark,4)
//#define CLR_time_mark_1000ms_mark_b5   CLR_8BIT(time_mark_1000ms_mark,4)

//#define R_time_mark_1000ms_mark_b6   GET_8BIT(time_mark_1000ms_mark,5)
//#define CLR_time_mark_1000ms_mark_b6   CLR_8BIT(time_mark_1000ms_mark,5)

//#define R_time_mark_1000ms_mark_b7   GET_8BIT(time_mark_1000ms_mark,6)
//#define CLR_time_mark_1000ms_mark_b7   CLR_8BIT(time_mark_1000ms_mark,6)

//#define R_time_mark_1000ms_mark_b8   GET_8BIT(time_mark_1000ms_mark,7)
//#define CLR_time_mark_1000ms_mark_b8   CLR_8BIT(time_mark_1000ms_mark,7)

/*****5000ms标志的8个标志位*********/    //若使用了某一位则取消注释，同一位不可用于多处任务
#define R_time_mark_5000ms_mark_b1   GET_8BIT(time_mark_5000ms_mark,0)                        //用于主函数
#define CLR_time_mark_5000ms_mark_b1   CLR_8BIT(time_mark_5000ms_mark,0)

#define R_time_mark_5000ms_mark_b2   GET_8BIT(time_mark_5000ms_mark,1)                       //用于主函数测试模式
#define CLR_time_mark_5000ms_mark_b2   CLR_8BIT(time_mark_5000ms_mark,1)

//#define R_time_mark_5000ms_mark_b3   GET_8BIT(time_mark_5000ms_mark,2)
//#define CLR_time_mark_5000ms_mark_b3   CLR_8BIT(time_mark_5000ms_mark,2)

//#define R_time_mark_5000ms_mark_b4   GET_8BIT(time_mark_5000ms_mark,3)
//#define CLR_time_mark_5000ms_mark_b4   CLR_8BIT(time_mark_5000ms_mark,3)

//#define R_time_mark_5000ms_mark_b5   GET_8BIT(time_mark_5000ms_mark,4)
//#define CLR_time_mark_5000ms_mark_b5   CLR_8BIT(time_mark_5000ms_mark,4)

//#define R_time_mark_5000ms_mark_b6   GET_8BIT(time_mark_5000ms_mark,5)
//#define CLR_time_mark_5000ms_mark_b6   CLR_8BIT(time_mark_5000ms_mark,5)

//#define R_time_mark_5000ms_mark_b7   GET_8BIT(time_mark_5000ms_mark,6)
//#define CLR_time_mark_5000ms_mark_b7   CLR_8BIT(time_mark_5000ms_mark,6)

//#define R_time_mark_5000ms_mark_b8   GET_8BIT(time_mark_5000ms_mark,7)
//#define CLR_time_mark_5000ms_mark_b8   CLR_8BIT(time_mark_5000ms_mark,7)    
    
    
    
    
    
/*****主循环需要的相关时间变量********/
extern unsigned char time_mark_50ms_mark1;     //50MS标志位

extern unsigned char time_mark_100ms_mark1;     //100MS标志位
extern unsigned char time_mark_500ms_mark1;     //500MS标志位
extern unsigned char time_mark_500ms_mark2;     //500MS标志位

extern unsigned char time_mark_1000ms_mark;    //1000MS标志位
extern unsigned char time_mark_5000ms_mark;    //5000MS标志位

extern unsigned char time_mark_500ms_fb_mark;     //500MS方波标志位
extern unsigned char time_mark_1000ms_fb_mark;    //1000MS方波标志位



extern void FUNC_TIME_MARK_TIMER(void);


#endif	

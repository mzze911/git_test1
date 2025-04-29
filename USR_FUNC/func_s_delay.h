#ifndef __FUNC_S_DELAY_H__
#define __FUNC_S_DELAY_H__




/********结构体定义********/
typedef struct 
{
	unsigned char delay_over;        //延时完成标志
	unsigned char delay_mode;        //延时模式  1->单次延时  2->循环延时
	unsigned long int tick_mark;     //开始延时的节拍数
	unsigned long int delay_tick;    //需要延时的节拍数
}STRUCT_FUNC_S_NB_DELAY;






/**************接口函数*******************/
extern void FUNC_S_DELAY_MS_TICK_INC(void);
extern void FUNC_S_DELAY_MS(unsigned long int ms);     //阻塞延时
extern unsigned char FUNC_S_NB_DELAY_MS_START(STRUCT_FUNC_S_NB_DELAY*d,unsigned char mode,unsigned long int ms);     //非阻塞延时
extern unsigned char FUNC_S_NB_DELAY_MS_STATE(STRUCT_FUNC_S_NB_DELAY*d);









#endif 


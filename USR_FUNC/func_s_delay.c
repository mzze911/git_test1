#include "func_s_delay.h"



//--------变量定义----------
volatile unsigned long int func_s_delay_time_tick=0;






void FUNC_S_DELAY_MS_TICK_INC()
{	
	func_s_delay_time_tick++;	
}


void FUNC_S_DELAY_MS(unsigned long int ms)
{
	unsigned long int tick_mark=0;
	unsigned long int tick_delay=ms;
	tick_mark=func_s_delay_time_tick;
	while(1)
	{
		if((func_s_delay_time_tick-tick_mark)>=tick_delay)
		{
			break;
		}
	}
}


unsigned char FUNC_S_NB_DELAY_MS_START(STRUCT_FUNC_S_NB_DELAY*d,unsigned char mode,unsigned long int ms)
{
	unsigned char res=0;
	if((mode==1)||(mode==2))
	{
		d->delay_over=0;                         //延时完成标志
		d->delay_mode=mode;                      //延时模式  1->单次延时  2->循环延时
		d->tick_mark=func_s_delay_time_tick;     //开始延时的节拍数
		d->delay_tick=ms;                        //需要延时的节拍数		
	}
	else
	{
		res=1;
	}
	return res;
}


unsigned char FUNC_S_NB_DELAY_MS_STATE(STRUCT_FUNC_S_NB_DELAY*d)
{
	if((func_s_delay_time_tick-(d->tick_mark))>=d->delay_tick)
	{
		d->delay_over=1;
		if((d->delay_mode)==2)
		{
			d->tick_mark=func_s_delay_time_tick;
		}
	}	
	else
	{
		d->delay_over=0;		
	}
	return d->delay_over;
}


























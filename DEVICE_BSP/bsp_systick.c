#include "bsp_systick.h"
#include "func_s_delay.h"


volatile unsigned long int bsp_systick_count=0;   //滴答计数


void BSP_SYSTICK_INIT(void)
{
/*
 *函数名：BSP_SYSTICK_INIT
 *描述  ：滴答时钟初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/     

    SysTick->LOAD  = (uint32_t)(72000 - 1UL);                 //设置SYSTICK的重装寄存器，1ms定时
    SysTick->VAL   = (uint32_t)(72000 - 1UL);                 //加载当前计数值
    
    HAL_NVIC_SetPriority(SysTick_IRQn,1,3);                 //设置中断优先级，抢占优先级1，子优先级2  

    
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;            //选择SysTick时钟为FCLK
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;              //使能SysTick异常请求
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;               //开始SysTick

    
    
}								    

void BSP_SYSTICK_DEINIT(void)
{
/*
 *函数名：BSP_SYSTICK_DEINIT
 *描述  ：滴答时钟初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/     

    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;              //关闭SysTick异常请求
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;               //关闭SysTick

}	

//--中断服务函数----
void SysTick_Handler(void)
{
    HAL_IncTick();
    FUNC_S_DELAY_MS_TICK_INC();
    bsp_systick_count++;
    
}






void BSP_SYSTICK_DELAY_US(u32 nus)
{
/*
 *函数名：BSP_DELAY_US
 *描述  ：US级硬延时功能函数
 *输入  ：要延时的us数.0~190887435(最大值即2^32/fac_us@fac_us=22.5)	
 *输出  ：无
 *调用  ：外部调用
*/     
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD的值	    	 
	ticks=nus*72; 						    //需要的节拍数      //这里的72代表经过1us时间SYSTICK计数器需要计数的量，和systick计数时钟有关
	told=SysTick->VAL;        				//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}


void BSP_SYSTICK_DELAY_MS(u16 nms)
{
/*
 *函数名：BSP_DELAY_MS
 *描述  ：MS级硬延时功能函数
 *输入  ：nms:要延时的ms数
 *输出  ：无
 *调用  ：外部调用
*/ 
	u32 i;
	for(i=0;i<nms;i++) BSP_SYSTICK_DELAY_US(1000);
}
	 





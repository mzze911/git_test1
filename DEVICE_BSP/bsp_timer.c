#include "bsp_timer.h"
#include "bsp_led.h"
#include "func_time_mark.h"
#include "func_alone_key.h"
#include "func_ir_decode.h"
#include "func_beep.h"

/**************变量定义**************/

//-----定时器2------
TIM_HandleTypeDef TIM2_Handler;      //定时器句柄 
#if(BSP_TIM2_EXT_TICK_EN==1)
unsigned long int bsp_tim2_ext_tick=0;
unsigned long int bsp_tim2_ext_tick_set_mark=0;
unsigned long int BSP_TIM2_EXT_TICK_UP_CNT=0;
#endif

//-----定时器3------
TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
#if(BSP_TIM3_EXT_TICK_EN==1)
unsigned long int bsp_tim3_ext_tick=0;
unsigned long int bsp_tim3_ext_tick_set_mark=0;
unsigned long int BSP_TIM3_EXT_TICK_UP_CNT=0;
#endif

//-----定时器4------
TIM_HandleTypeDef TIM4_Handler;      //定时器句柄 
#if(BSP_TIM4_EXT_TICK_EN==1)
unsigned long int bsp_tim4_ext_tick=0;
unsigned long int bsp_tim4_ext_tick_set_mark=0;
unsigned long int BSP_TIM4_EXT_TICK_UP_CNT=0;
#endif




//基本定时器2中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器2!(定时器2挂在APB1上，时钟为72M)
void BSP_TIM2_INIT(u32 arr,u16 psc)
{  
	TIM_MasterConfigTypeDef  TIM_MasterConfig;
	
	__HAL_RCC_TIM2_CLK_ENABLE();            //使能TIM2时钟  
    
    TIM2_Handler.Instance=TIM2;                          //基本定时器2
    TIM2_Handler.Init.Prescaler=psc;                     //分频系数
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM2_Handler.Init.Period=arr;                        //自动装载值
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM2_Handler);

//	TIM_MasterConfig.MasterSlaveMode=TIM_SLAVEMODE_DISABLE;
//	TIM_MasterConfig.MasterOutputTrigger=TIM_TRGO_UPDATE;
//	HAL_TIMEx_MasterConfigSynchronization(&TIM2_Handler,&TIM_MasterConfig);
//	
	
	HAL_NVIC_SetPriority(TIM2_IRQn,3,2);    //设置中断优先级，抢占优先级3，子优先级2
	HAL_NVIC_EnableIRQ(TIM2_IRQn);          //开启TIM2中断  
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //使能定时器2和定时器2更新中断：TIM_IT_UPDATE   
//	HAL_TIM_Base_Start(&TIM2_Handler); //使能定时器2 
}


//基本定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为72M)
void BSP_TIM3_INIT(u32 arr,u16 psc)
{  
  
	__HAL_RCC_TIM3_CLK_ENABLE();        //使能TIM3时钟
	
    TIM3_Handler.Instance=TIM3;                          //基本定时器3
    TIM3_Handler.Init.Prescaler=psc;                     //分频系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=arr;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);

	HAL_NVIC_SetPriority(TIM3_IRQn,2,3);    //设置中断优先级，抢占优先级1，子优先级3
	HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启TIM3中断   
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}


//基本定时器4中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器4!(定时器3挂在APB1上，时钟为72M)
void BSP_TIM4_INIT(u32 arr,u16 psc)
{  
  
	__HAL_RCC_TIM4_CLK_ENABLE();        //使能TIM4时钟
	
    TIM4_Handler.Instance=TIM4;                          //基本定时器4
    TIM4_Handler.Init.Prescaler=psc;                     //分频系数
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM4_Handler.Init.Period=arr;                        //自动装载值
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM4_Handler);

//	HAL_NVIC_SetPriority(TIM4_IRQn,2,3);    //设置中断优先级，抢占优先级1，子优先级3
//	HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启TIM4中断   
    
//  HAL_TIM_Base_Start_IT(&TIM4_Handler); //使能定时器4和定时器4更新中断：TIM_IT_UPDATE  
	
	HAL_TIM_Base_Start(&TIM4_Handler); //使能定时器4 	
}




void BSP_TIM2_SET_TICK(unsigned long int t)
{
	
    __HAL_TIM_SET_COUNTER(&TIM2_Handler,t);  	
}

unsigned long int BSP_TIM2_GET_TICK()
{
    return __HAL_TIM_GET_COUNTER(&TIM2_Handler);	
}


#if(BSP_TIM2_EXT_TICK_EN==1)
void BSP_TIM2_SET_EXT_TICK(unsigned long int t)
{
	bsp_tim2_ext_tick=t;
	__HAL_TIM_DISABLE(&TIM2_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();
	bsp_tim2_ext_tick_set_mark=__HAL_TIM_GET_COUNTER(&TIM2_Handler);	
	BSP_TIM2_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM2_Handler);    //允许计数	
}

unsigned long int BSP_TIM2_GET_EXT_TICK()
{
	unsigned short int cnt=0;
	__HAL_TIM_DISABLE(&TIM2_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();	
	cnt=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
	if(BSP_TIM2_EXT_TICK_UP_CNT==0)
	{
		bsp_tim2_ext_tick+=cnt-bsp_tim2_ext_tick_set_mark;
	}
	else if(BSP_TIM2_EXT_TICK_UP_CNT==1)
	{
		bsp_tim2_ext_tick+=cnt+(TIM2_Handler.Init.Period-bsp_tim2_ext_tick_set_mark+1);
	}
	else
	{
		bsp_tim2_ext_tick+=cnt+(TIM2_Handler.Init.Period-bsp_tim2_ext_tick_set_mark+1)+(BSP_TIM2_EXT_TICK_UP_CNT-1)*(TIM2_Handler.Init.Period+1);		
	}
	bsp_tim2_ext_tick_set_mark=cnt;	
	BSP_TIM2_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM2_Handler);    //允许计数		
    return bsp_tim2_ext_tick;		
}
#endif




void BSP_TIM3_SET_TICK(unsigned long int t)
{
    __HAL_TIM_SET_COUNTER(&TIM3_Handler,t);  	
}


unsigned long int BSP_TIM3_GET_TICK()
{
    return __HAL_TIM_GET_COUNTER(&TIM3_Handler);	
}


#if(BSP_TIM3_EXT_TICK_EN==1)
void BSP_TIM3_SET_EXT_TICK(unsigned long int t)
{
	bsp_tim3_ext_tick=t;
	__HAL_TIM_DISABLE(&TIM3_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();
	bsp_tim3_ext_tick_set_mark=__HAL_TIM_GET_COUNTER(&TIM3_Handler);	
	BSP_TIM3_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM3_Handler);    //允许计数	
}

unsigned long int BSP_TIM3_GET_EXT_TICK()
{
	unsigned short int cnt=0;
	__HAL_TIM_DISABLE(&TIM3_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();	
	cnt=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
	if(BSP_TIM3_EXT_TICK_UP_CNT==0)
	{
		bsp_tim3_ext_tick+=cnt-bsp_tim3_ext_tick_set_mark;
	}
	else if(BSP_TIM3_EXT_TICK_UP_CNT==1)
	{
		bsp_tim3_ext_tick+=cnt+(TIM3_Handler.Init.Period-bsp_tim3_ext_tick_set_mark+1);
	}
	else
	{
		bsp_tim3_ext_tick+=cnt+(TIM3_Handler.Init.Period-bsp_tim3_ext_tick_set_mark+1)+(BSP_TIM3_EXT_TICK_UP_CNT-1)*(TIM3_Handler.Init.Period+1);		
	}
	bsp_tim3_ext_tick_set_mark=cnt;	
	BSP_TIM3_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM3_Handler);    //允许计数		
    return bsp_tim3_ext_tick;		
}
#endif



void BSP_TIM4_SET_TICK(unsigned long int t)
{
    __HAL_TIM_SET_COUNTER(&TIM4_Handler,t);  	
}


unsigned long int BSP_TIM4_GET_TICK()
{
    return __HAL_TIM_GET_COUNTER(&TIM4_Handler);	
}



#if(BSP_TIM4_EXT_TICK_EN==1)
void BSP_TIM4_SET_EXT_TICK(unsigned long int t)
{
	bsp_tim4_ext_tick=t;
	__HAL_TIM_DISABLE(&TIM4_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();
	bsp_tim4_ext_tick_set_mark=__HAL_TIM_GET_COUNTER(&TIM4_Handler);	
	BSP_TIM4_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM4_Handler);    //允许计数	
}

unsigned long int BSP_TIM4_GET_EXT_TICK()
{
	unsigned short int cnt=0;
	__HAL_TIM_DISABLE(&TIM4_Handler);    //禁止计数
	__NOP();__NOP();__NOP();__NOP();	
	cnt=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
	if(BSP_TIM4_EXT_TICK_UP_CNT==0)
	{
		bsp_tim4_ext_tick+=cnt-bsp_tim4_ext_tick_set_mark;
	}
	else if(BSP_TIM4_EXT_TICK_UP_CNT==1)
	{
		bsp_tim4_ext_tick+=cnt+(TIM4_Handler.Init.Period-bsp_tim4_ext_tick_set_mark+1);
	}
	else
	{
		bsp_tim4_ext_tick+=cnt+(TIM4_Handler.Init.Period-bsp_tim4_ext_tick_set_mark+1)+(BSP_TIM4_EXT_TICK_UP_CNT-1)*(TIM4_Handler.Init.Period+1);		
	}
	bsp_tim4_ext_tick_set_mark=cnt;	
	BSP_TIM4_EXT_TICK_UP_CNT=0;		
	__HAL_TIM_ENABLE(&TIM4_Handler);    //允许计数		
    return bsp_tim4_ext_tick;		
}
#endif





//定时器2中断服务函数
void TIM2_IRQHandler(void)   //10ms
{    
    static unsigned short int j=0;
	if(__HAL_TIM_GET_FLAG(&TIM2_Handler, TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&TIM2_Handler, TIM_IT_UPDATE) !=RESET)
		{
			__HAL_TIM_CLEAR_IT(&TIM2_Handler, TIM_IT_UPDATE);
			#if(BSP_TIM2_EXT_TICK_EN==1)
			BSP_TIM2_EXT_TICK_UP_CNT++;
			#endif			
			//用户中断函数	
			FUNC_TIME_MARK_TIMER();
			FUNC_ALONE_KEY_SCAN();
			FUNC_IR_DECODE_WORK_TIMER();
			FUNC_BEEP_CONTROL_TIMER();			
			if(j<10)
			{
				j++;

			}
			else
			{
				j=0;
//				BSP_IO_LED2=!BSP_IO_LED2;
			}
		}
	}	
    
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)   //1ms
{   
    static unsigned short int j=0;	

	if(__HAL_TIM_GET_FLAG(&TIM3_Handler, TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&TIM3_Handler, TIM_IT_UPDATE) !=RESET)
		{
			__HAL_TIM_CLEAR_IT(&TIM3_Handler, TIM_IT_UPDATE);
			#if(BSP_TIM3_EXT_TICK_EN==1)
			BSP_TIM3_EXT_TICK_UP_CNT++;
			#endif				
			//用户中断函数

			if(j<100)
			{
				j++;

			}
			else
			{
				j=0;
//				BSP_IO_LED1=!BSP_IO_LED1;
			}
		}
	}    
}







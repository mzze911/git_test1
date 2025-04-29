/****************************************************
*模块说明：红外解码模块
*作者：mzze
*版本：v1.0  
*日期：2024.5.23    初版
*上一版本：
*版本变更说明： 无  
*
*
*****************************************************/
#include "func_ir_decode.h"
#include "bsp_timer.h"
#include "func_ir_nec_key.h"



/**************宏定义**********/


/*************变量定义*********/ 
static unsigned char bus_idle_mark=1;     //总线空闲标志 0-不空闲 1-空闲
static unsigned char bus_idle_count=0;    //总线空闲判断计数

#if(FUNC_IR_DECODE_TYPE==0)
//-----NEC协议解码相关变量------
static unsigned char nec_data_end_mark=0;      //数据结束标志
static unsigned char nec_data_end_count=0;     //数据结束判断计数
static unsigned char nec_ecode_state=0;            //解码状态机状态 0->空闲  1->接收引导帧 2->接收地址 3->接收数据 4->接收重复
static unsigned char nec_ecode_get_cmd_mark=0;     //获取到命令标志 0->未获取到 1->获取到 2->重复获取到

static unsigned char nec_add_bit_count=0;           //地址位计数
static unsigned char nec_add=0;                     //地址数据
static unsigned char nec_add_f=0;                   //地址数据

static unsigned char nec_cmd_bit_count=0;           //命令位计数
static unsigned char nec_cmd=0;                     //命令数据
static unsigned char nec_cmd_f=0;                   //命令数据


//----接收的NEC命令------
STRUCT_FUNC_IR_NEC_CMD FUNC_IR_DECODE_NEC_CCMD;     //最近一次获取到的命令


#endif

/*******************************/



static unsigned long int get_time_tick()
{
/*
 *函数名：get_time_tick
 *描述  ：获取时间节拍
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用,要求节拍单位为10us
*/       
	return BSP_TIM2_GET_EXT_TICK();
}

static void set_time_tick(unsigned short int t)
{
/*
 *函数名：set_time_tick
 *描述  ：设置时间节拍
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用,要求节拍单位为10us
*/      
	BSP_TIM2_SET_EXT_TICK(t);
}




void FUNC_IR_DECODE_WORK_EXTI()
{
/*
 *函数名：FUNC_IR_DECODE_WORK_EXTI
 *描述  ：红外解码下降沿中断工作函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部中断服务函数中调用，下降沿中断
*/ 
#if(FUNC_IR_DECODE_TYPE==0)	
	#define T_DUTY 300    
	unsigned short int tick_diff=0;    //节拍差值
	unsigned short int low_time=0;     //低电平时间
	unsigned char bus_signal=0xff;        //总线信号
	
	//----总线活动状态清0----
	bus_idle_count=0;
	nec_data_end_count=0;
	//----获取下降沿时间差----
	if((bus_idle_mark==1)||(nec_data_end_mark==1))   //从总线空闲或者数据结束中恢复
	{
		set_time_tick(0);    //节拍清0
		if(bus_idle_mark==1)
		{
			nec_ecode_state=0;   //重置状态机
		}
		bus_idle_mark=0;
		nec_data_end_mark=0;		
	}
	else
	{
		tick_diff=get_time_tick();
		low_time=tick_diff*10;       //单位US
		//----判断信号种类--------
		if((low_time>=(13500-T_DUTY))&&(low_time<=(13500+T_DUTY)))        //引导码
		{
			bus_signal=100;
			
		}
		else if((low_time>=(11250-T_DUTY))&&(low_time<=(11250+T_DUTY)))   //重复码
		{
			bus_signal=200;		
			
		}	
		else if((low_time>=(2250-T_DUTY))&&(low_time<=(2250+T_DUTY)))   //逻辑1
		{
			bus_signal=1;		
			
		}	
		else if((low_time>=(1120-T_DUTY))&&(low_time<=(1120+T_DUTY)))  //逻辑0
		{
			bus_signal=0;		
			
		}
		//-----节拍清0----------------
		if(bus_signal!=0xff)
		{
			set_time_tick(0); 
		}		
	}
	//-----红外解析状态机---------
	switch(nec_ecode_state)
	{
		case 0:      //空闲
		{
			//-------做一些重置工作-----
//			FUNC_IR_DECODE_NEC_CCMD.add=0;
//			FUNC_IR_DECODE_NEC_CCMD.cmd=0;
//			FUNC_IR_DECODE_NEC_CCMD.get_mark=0;
//			FUNC_IR_DECODE_NEC_CCMD.repeat=0;				
			nec_ecode_state=1;
		}break;
		case 1:     //接收引导帧
		{
			if(bus_signal==100)    //接收到引导帧
			{
				nec_add_bit_count=0;           //地址位计数清0
				nec_add=0;                     //地址数据清0
				nec_add_f=0;                   //地址数据清0
														
				nec_cmd_bit_count=0;           //命令位计数清0
				nec_cmd=0;                     //命令数据清0
				nec_cmd_f=0;                   //命令数据清0
				
				nec_ecode_state=2;
			
			}			
		}break;
		case 2:     //接收地址
		{
			if((bus_signal==1)||(bus_signal==0))
			{
				if(nec_add_bit_count<8)        //接收地址数据
				{
					nec_add|=bus_signal<<nec_add_bit_count;
				}
				else if(nec_add_bit_count<16)  //接收地址数据反码
				{
					nec_add_f|=bus_signal<<(nec_add_bit_count-8);					
				}
				nec_add_bit_count++;
				if(nec_add_bit_count==16)
				{
					nec_ecode_state=3;				
				}
			}
			
			
		}break;
		case 3:     //接收命令    
		{
			if((bus_signal==1)||(bus_signal==0))
			{
				if(nec_cmd_bit_count<8)        //接收命令数据
				{
					nec_cmd|=bus_signal<<nec_cmd_bit_count;
				}
				else if(nec_cmd_bit_count<16)  //接收命令数据反码
				{
					nec_cmd_f|=bus_signal<<(nec_cmd_bit_count-8);					
				}
				nec_cmd_bit_count++;
				if(nec_cmd_bit_count==16)
				{
					//----对数据进行校验----
					if(
						((nec_add+nec_add_f)==0xff)
						&&((nec_cmd+nec_cmd_f)==0xff)
					)
					{
						//---赋值数据标志-----
						nec_ecode_get_cmd_mark=1;
						
						nec_ecode_state=4;							
					}					
		            else
					{
						nec_ecode_state=1;
					}
				}
			}			
			
		}break;
		case 4:     //接收引导帧/重复帧
		{
			if(bus_signal==100)    //接收到引导帧
			{
				nec_add_bit_count=0;           //地址位计数清0
				nec_add=0;                     //地址数据清0
				nec_add_f=0;                   //地址数据清0
														
				nec_cmd_bit_count=0;           //命令位计数清0
				nec_cmd=0;                     //命令数据清0
				nec_cmd_f=0;                   //命令数据清0	
				
				nec_ecode_state=2;
			
			}
			else if(bus_signal==200)
			{
				//---赋值数据标志-----			
				nec_ecode_get_cmd_mark=2;				
				
			}
		}break;				
		default:break;		
	}
#endif	
}




void FUNC_IR_DECODE_WORK_TIMER()
{
/*
 *函数名：FUNC_IR_DECODE_WORK_TIMER
 *描述  ：红外解码工作函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部中断服务函数中调用，10ms定时中断
*/    
	unsigned char i=0;
	#if(FUNC_IR_DECODE_TYPE==0)	
	//--总线空闲判断--
	if(bus_idle_count<50)
	{
		bus_idle_count++;
	}
	else
	{					
		bus_idle_mark=1;		
	}
	//--数据结束判断--
	if(nec_data_end_count<2)
	{
		nec_data_end_count++;
	}
	else
	{
		nec_data_end_mark=1;
	}	
	//---提取数据-----
	if((nec_ecode_get_cmd_mark==1)||(nec_ecode_get_cmd_mark==2))
	{
		//----更新当前命令---
		if(nec_ecode_get_cmd_mark==1)
		{
			FUNC_IR_DECODE_NEC_CCMD.add=nec_add;
			FUNC_IR_DECODE_NEC_CCMD.cmd=nec_cmd;
			FUNC_IR_DECODE_NEC_CCMD.get_mark=1;
			FUNC_IR_DECODE_NEC_CCMD.repeat=0;	
		}	
		else
		{	
			if(FUNC_IR_DECODE_NEC_CCMD.repeat<0xffff)
			{
				FUNC_IR_DECODE_NEC_CCMD.repeat++;
			}				
		}
		nec_ecode_get_cmd_mark=0;
		//----针对不同命令进行处理----
		
		
		//----红外按键处理-----
		FUNC_IR_NEC_KEY_GET(bus_idle_mark,&FUNC_IR_DECODE_NEC_CCMD);        
	}
	if(bus_idle_mark==1)  //总线空闲
	{
		//----红外按键处理-----
		FUNC_IR_NEC_KEY_GET(bus_idle_mark,&FUNC_IR_DECODE_NEC_CCMD);	
	}
	#endif
	
	
}


void FUNC_IR_DECODE_INIT()
{
/*
 *函数名：FUNC_IR_DECODE_INIT
 *描述  ：红外解码初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：主函数调用
*/   
	unsigned char i=0;
	//-----初始化控制变量----
	bus_idle_mark=1;     //总线空闲标志 0-不空闲 1-空闲
	bus_idle_count=0;    //总线空闲判断计数
	#if(FUNC_IR_DECODE_TYPE==0)
	//-----NEC协议解码相关变量------
	nec_data_end_mark=1;      //数据结束标志
	nec_data_end_count=0;     //数据结束判断计数	
	nec_ecode_state=0;            //解码状态机状态 0->空闲  1->接收引导帧 2->接收地址 3->接收数据 4->接收重复
	nec_ecode_get_cmd_mark=0;     //获取到命令标志 0->未获取到 1->获取到

	nec_add_bit_count=0;           //地址位计数
	nec_add=0;                     //地址数据
	nec_add_f=0;                   //地址数据

	nec_cmd_bit_count=0;           //命令位计数
	nec_cmd=0;                     //命令数据
	nec_cmd_f=0;                   //命令数据
	//------收到当前的命令----
	FUNC_IR_DECODE_NEC_CCMD.add=0;
	FUNC_IR_DECODE_NEC_CCMD.cmd=0;
	FUNC_IR_DECODE_NEC_CCMD.get_mark=0;
	FUNC_IR_DECODE_NEC_CCMD.repeat=0;	
	#endif    
}

















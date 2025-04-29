/****************************************************
*模块说明：用于STM32F系列单片机的蜂鸣器控制模块函数
          控制蜂鸣器鸣响时间和次数，和是否允许鸣响
					蜂鸣器控制方式为IO控制
*作者：mzze
*版本：v1.1  
*日期：2024.6.13    初版
*上一版本：v1.0
*版本变更说明： 修改对外接口函数名称 
*
*
*****************************************************/
#include "func_beep.h"
#include "BSP_beep.h"

/**************宏定义**********/
#define BEEP_ON  1	 //蜂鸣器响
#define BEEP_OFF 0	 //蜂鸣器不响
#define TIMER_BEEP 10   //单位毫秒  //与定时器中断时间一致
/*************蜂鸣器控制IO口定义**********/
#define BEEP_IO   BSP_IO_BEEP
/*************变量定义*********/ 
unsigned char BEEP_ON_ALLOW=0;    //蜂鸣器控制允许位  0-->不允许进行蜂鸣器控制  1-->允许进行蜂鸣器控制
static unsigned short int beep_t=0;	 //响的时间
static unsigned char beep_n=0;   	 //响的次数

static unsigned short int beep_timer_t=0;

/*******************************/

static void beep_on()
{
/*
 *函数名：beep_on
 *描述  ：蜂鸣器响函数
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/       
    BEEP_IO=BEEP_ON;
}

static void beep_off()
{
/*
 *函数名：beep_off
 *描述  ：蜂鸣器关函数
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/      
    BEEP_IO=BEEP_OFF;    
}


extern void FUNC_BEEP_CONTROL_TIMER()
{
/*
 *函数名：FUNC_BEEP_CONTROL_TIMER
 *描述  ：定时器中断中调用的蜂鸣器控制函数
 *输入  ：无
 *输出  ：无
 *调用  ：定时器中断服务函数中调用，定时间隔为10ms
*/     
	if(BEEP_ON_ALLOW==1)   //若允许进行蜂鸣器控制
	{
		if(beep_n>0)
		{
			if(beep_timer_t>0)
			{
				beep_timer_t--;
				if(beep_timer_t>(beep_t/2))
				{
					beep_on();  //蜂鸣器响
				}
				else
				{
					beep_off();  //蜂鸣器不响
				}
			}
			else
			{
				beep_n--;		//鸣响次数减一
				if(beep_n>0)    //若鸣响次数仍大于0
				{
					beep_timer_t=beep_t; //重新赋值
				}
			}
		}
	}
	else
	{
		beep_off();  //蜂鸣器不响  		
	}
}

/*********蜂鸣器初始化子函数***********/
extern void FUNC_BEEP_INIT()
{
/*
 *函数名：FUNC_BEEP_INIT
 *描述  ：蜂鸣器初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：主函数调用
*/        
//--------初始状态下蜂鸣器不响------
    beep_off();         //蜂鸣器不响  
    BEEP_ON_ALLOW=1;    //允许蜂鸣器
//    if(CANSHU_CUN[U8_USER_CANSHU_VOLUME]==0)
//    {
//        BEEP_ON_ALLOW=0;        
//    }
//    else
//    {
//        BEEP_ON_ALLOW=1;        
//    }
      
    
}

extern void FUNC_BEEP_CONTROL(unsigned short int i,unsigned char n) 	
{
/*
 *函数名：BEEP_CONTROL
 *描述  ：蜂鸣器控制函数
 *输入  ：i:蜂鸣器响i个毫秒  n:蜂鸣器响n次 
 *输出  ：无
 *调用  ：主函数调用
*/    
	if(BEEP_ON_ALLOW==1)   //若允许进行蜂鸣器控制
	{
		beep_t=beep_timer_t=2*(i/TIMER_BEEP);  
		beep_n=n;
	}
}


















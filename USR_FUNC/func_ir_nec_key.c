/*******************************************
*模块说明：红外按键模块
*作者：mzze
*版本：v1.0
*日期：2024.5.24
*上一版本：初版
*版本变更说明：
********************************************/

#include "func_ir_nec_key.h"


#ifdef FUNC_IR_NEC_KEY_BEEP_ON
#include "func_beep.h"
#endif


/*****************按键参数常量宏定义*****************************/
#define IR_NEC_KEY_NUM     10			 //按键数
#define IR_NEC_KEY_REPEAT_TIME 110       //按键重复时间单位ms



#define T_DANJI    (100/IR_NEC_KEY_REPEAT_TIME)			 //单击时间常量 即按下按键后多久按键被认为是单击
#define T_2S       (2000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是2s长按 
#define T_4S       (4000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是4s长按 
#define T_5S       (5000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是5s长按
#define T_6S       (6000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是6s长按 
#define T_7S       (7000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是7s长按 
#define T_8S       (8000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是8s长按 
#define T_12S      (12000/IR_NEC_KEY_REPEAT_TIME)		 //长按时间常量 即按下按键后多久按键被认为是12s长按 



/*********I/O口宏定义***********/
//----需要接收的按键的命令定义------
unsigned char const ir_nec_key_nec_cmd[IR_NEC_KEY_NUM][2]=
{
	{0x08,0xD9},	 //0
	{0x08,0x95},     //1
	{0x08,0x99},     //2
	{0x08,0x9D},     //3
	{0x08,0xD6},     //4
	{0x08,0xDA},     //5
	{0x08,0xDE},     //6
	{0x08,0x96},     //7
	{0x08,0x9A},     //8
	{0x08,0x9E},     //9

};
/*------------------------------单个按键状态标志位----------------------------------*/
FUNC_IR_NEC_KEY_STATE_ENUM FUNC_IR_NEC_KEY_STATE[IR_NEC_KEY_NUM];	  //第ir_nec_key_num个按键状态
FUNC_IR_NEC_KEY_STATE_ENUM FUNC_IR_NEC_KEY_STATE_1[IR_NEC_KEY_NUM];   //第二组按键状态，用于某些特殊场合，一般不用,用于某一按键有区别于其他按键的状态

#ifdef FUNC_IR_NEC_KEY_BEEP_ON
static unsigned char beep_mark=0;    //蜂鸣鸣响标记位
#endif




void FUNC_IR_NEC_KEY_GET(unsigned char bus_idle,STRUCT_FUNC_IR_NEC_CMD* cmd)
{
/**************
*函数名：FUNC_IR_NEC_KEY_GET
*函数说明：红外按键获取程序
*输入：无
*输出：无
*调用：外部调用
****************/	
	static unsigned char get_key_en=0;    //允许获取按键
    unsigned char i=0;
	if(bus_idle==0)
	{
		
		//判断当前命令是否有效
		for(i=0;i<IR_NEC_KEY_NUM;i++)
		{
			if(
				(cmd->add==ir_nec_key_nec_cmd[i][0])
				&&(cmd->cmd==ir_nec_key_nec_cmd[i][1])		
			)
			{
				if(cmd->repeat==0)
				{
					get_key_en=1;
				}
				break;
			}
		}
		//进行按键状态赋值
		if((i<IR_NEC_KEY_NUM)&&(get_key_en==1))
		{
			switch(cmd->repeat)
			{
				case T_DANJI:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON;	
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;
				case T_2S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_2S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_2S;	
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;			
				case T_4S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_4S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_4S;	
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;
				case T_5S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_5S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_5S;	
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;
				case T_6S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_6S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_6S;
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;	
				case T_7S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_7S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_7S;
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;				
				case T_8S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_8S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_8S;
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;
				case T_12S:
				{
					FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_ON_12S;
					FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_ON_12S;
					#ifdef FUNC_IR_NEC_KEY_BEEP_ON
					beep_mark=1;
					#endif						
				}break;	
				default:break;
			}
		}
	}
	else
	{
		get_key_en=0;    //不允许获取按键
		for(i=0;i<IR_NEC_KEY_NUM;i++)
		{
			FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_IDLE;
			FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_IDLE;			
		}		
	}
	/************************是否需要蜂鸣******************************/
	#ifdef FUNC_IR_NEC_KEY_BEEP_ON
	if(beep_mark)
	{
		for(i=0;i<IR_NEC_KEY_NUM;i++)
		{
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON)
			{
				beep_mark=0;
				FUNC_BEEP_CONTROL(100,1); 
			}
//			if(FUNC_IR_NEC_KEY_STATE[i]>ON)
//			{
//				beep_mark=0;
//				FUNC_BEEP_CONTROL(300,1); 
//			}		
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON_2S)
			{
				beep_mark=0;
//				FUNC_BEEP_CONTROL(100,1); 
			}
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON_4S)
			{
				beep_mark=0;
//				FUNC_BEEP_CONTROL(100,1); 
			} 
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON_6S)
			{
				beep_mark=0;
//				FUNC_BEEP_CONTROL(100,1); 
			}  
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON_7S)
			{
				beep_mark=0;
//				FUNC_BEEP_CONTROL(100,1); 
			} 
			if(FUNC_IR_NEC_KEY_STATE[i]==IR_NEC_KEY_ON_8S)
			{
				beep_mark=0;
//				FUNC_BEEP_CONTROL(100,1); 
			}                           
		}
	}	
	#endif  	  		
}

void FUNC_IR_NEC_KEY_INIT()
{
/*
 *函数名：FUNC_IR_NEC_KEY_INIT
 *描述  ：红外按键判断初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：main函数中调用
*/    
    
    unsigned char i=0;
    //按键状态清0
	for(i=0;i<IR_NEC_KEY_NUM;i++)
	{
		FUNC_IR_NEC_KEY_STATE[i]=IR_NEC_KEY_IDLE;
		FUNC_IR_NEC_KEY_STATE_1[i]=IR_NEC_KEY_IDLE;			
	}	
}
































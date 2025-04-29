/*******************************************
*模块说明：单片机的按键独立方式
*作者：mzze
*版本：v1.0
*日期：2024.5.27
*上一版本：初版
*版本变更说明：

********************************************/
#include "func_alone_key.h"
#include "bsp_key.h"

#ifdef FUNC_ALONE_KEY_BEEP_EN
#include "func_beep.h"
#endif


/*********I/O口宏定义***********/
#define KEY1_IO  (BSP_IO_KEY1)
#define KEY2_IO  (BSP_IO_KEY2)
#define KEY3_IO  (BSP_IO_KEY3)
//#define KEY4_IO  (BSP_IO_KEY4)
//#define KEY5_IO  (BSP_IO_KEY5)
//#define KEY6_IO KEY6_PORT


/*****************按键参数常量宏定义*****************************/
#define key_num     3			 //按键数
#define t_changan_max_num  8000			 //按键最大有效计数值
#define t_danji    2				 //单击时间常量 即按下按键后多久按键被认为是单击（即消抖功能）
#define t_changan_2s  200			 //长按时间常量 即按下按键后多久按键被认为是2s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_4s  400			 //长按时间常量 即按下按键后多久按键被认为是4s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_5s  500			 //长按时间常量 即按下按键后多久按键被认为是5s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_6s  600			 //长按时间常量 即按下按键后多久按键被认为是6s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_7s  700			 //长按时间常量 即按下按键后多久按键被认为是7s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_8s  800			 //长按时间常量 即按下按键后多久按键被认为是8s长按  //需要根据扫描间隔时间做适当的调整
#define t_changan_12s  1200			 //长按时间常量 即按下按键后多久按键被认为是12s长按  //需要根据扫描间隔时间做适当的调整


/*------------------------------单个按键状态标志位----------------------------------*/
unsigned char const FUNC_ALONE_KEY_ON[key_num]={0,0,0};              //按键被按下时的状态，当修改了按键数时需要调整 
FUNC_ALONE_KEY_STATE_ENUM FUNC_ALONE_KEY_STATE[key_num];		     //第key_num个按键状态 ｛无按键=0;单击=1;双击=2;长按2S=3;长按7S=4;长按12S=5;}
FUNC_ALONE_KEY_STATE_ENUM FUNC_ALONE_KEY_STATE_1[key_num];           //第二组按键状态，用于某些特殊场合，一般不用,用于某一按键有区别于其他按键的状态
unsigned char FUNC_ALONE_KEY_PD_NUM=0;                               //当前被按下的按键数量

/*------------------按键有效次数记录变量--------------------------------------------*/
static unsigned short int key_ynum[key_num]={0};

#ifdef FUNC_ALONE_KEY_SCAN_IN_MAIN
static unsigned char key_scan_time_mark=0;   //按键扫描周期标志位
#endif

#ifdef FUNC_ALONE_KEY_BEEP_EN
static unsigned char beep_mark=0;    //蜂鸣鸣响标记位
#endif





void FUNC_ALONE_KEY_SCAN()
{
/**************
*函数名：FUNC_ALONE_KEY_SCAN
*函数说明：单个按键判断扫描程序
*输入：无
*输出：无
*调用：主函数，主循环中调用  / 定时器中断函数中调用定时中断为10ms
****************/	
    unsigned char i=0;
    unsigned char j=0;
    unsigned char i_key_num=0;   //标记当前需要扫描的按键
	unsigned char key_value=0;	 //当前扫描的按键的状态
#ifdef KEY_SCAN_IN_MAIN 	
		if(key_scan_time_mark==1)        //若到达按键判断时间进行按键判断
		{
			key_scan_time_mark=0;
#endif
			//-----完成所有按键的判断-----------
			while(i_key_num<key_num)
			{
	/**************************读取所有按键状态**********************/
				switch(i_key_num)
				{
					case 0:key_value=KEY1_IO;break;                    
					case 1:key_value=KEY2_IO;break;
					case 2:key_value=KEY3_IO;break;
//					case 3:key_value=KEY4_IO;break;
//					case 4:key_value=KEY5_IO;break;
//					case 5:key_value=KEY6_IO;break;
//					case 6:key_value=KEY7_IO;break;
//					case 7:key_value=KEY8_IO;break;
//					case 8:key_value=KEY9_IO;break;					
				}
	/*-----------------------------------单个按键判断-------------------------------------*/
				if(key_value==FUNC_ALONE_KEY_ON[i_key_num])
				{		
	//-------------------------------按键有效次数计数---------------------------------------
						key_ynum[i_key_num]++;         //按键有效次数判断（全局变量）
						if(key_ynum[i_key_num]>=t_changan_max_num)  
						key_ynum[i_key_num]=t_changan_max_num;
	//-------------------------------按键单击判断(判断是否有效)------------------------------
						if(key_ynum[i_key_num]==t_danji)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON;         //按键1单击有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}
	//-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_2s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_2S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}   
    //-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_4s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_4S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}  
	//-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_5s)
						{
							//FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_5S;		 //长按有效
                            FUNC_ALONE_KEY_STATE_1[i_key_num]=ALONE_KEY_ON_5S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}    						
    //-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_6s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_6S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}                      
	//-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_7s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_7S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}
    //-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_8s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_8S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}                      
	//-------------------------------按键长按判断(判断是否无效)-----------------------------
						if(key_ynum[i_key_num]==t_changan_12s)
						{
							FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_ON_12S;		 //长按有效
							#ifdef FUNC_ALONE_KEY_BEEP_EN
							beep_mark=1;
							#endif
						}  
                     
				}
				else
				{
						FUNC_ALONE_KEY_STATE[i_key_num]=ALONE_KEY_IDLE;		     //按键无效
                        FUNC_ALONE_KEY_STATE_1[i_key_num]=ALONE_KEY_IDLE;		 //按键无效
						key_ynum[i_key_num]=0;
				}	
/*-------------------------------------------------------------------------*/
				i_key_num++;    //判断下一个按键
			}	
		/*------------------------------------------------------------------------------------*/
		/************************是否需要蜂鸣******************************/
		#ifdef FUNC_ALONE_KEY_BEEP_EN
			if(beep_mark)
			{
				for(i=0;i<key_num;i++)
				{
						if(FUNC_ALONE_KEY_STATE[i]==ALONE_KEY_ON)
						{
							beep_mark=0;
							FUNC_BEEP_CONTROL(100,1); 
						}
//						if(FUNC_ALONE_KEY_STATE[i]>ON)
//						{
//							beep_mark=0;
//							FUNC_BEEP_CONTROL(300,1); 
//						}		
						if(FUNC_ALONE_KEY_STATE[i]==ALONE_KEY_ON_2S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						}
						if(FUNC_ALONE_KEY_STATE[i]==ALONE_KEY_ON_4S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						} 
						if(FUNC_ALONE_KEY_STATE[i]==ALONE_KEY_ON_5S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						}  
						if(FUNC_ALONE_KEY_STATE[i]==ALONE_KEY_ON_6S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						} 
						if(FUNC_ALONE_KEY_STATE_1[i]==ALONE_KEY_ON_7S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						}      
						if(FUNC_ALONE_KEY_STATE_1[i]==ALONE_KEY_ON_8S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						}    
						if(FUNC_ALONE_KEY_STATE_1[i]==ALONE_KEY_ON_12S)
						{
							beep_mark=0;
//							FUNC_BEEP_CONTROL(100,1); 
						}    						
				}
			}	
		#endif
        /********检测当前被按按键数量**********/
        for(i=0;i<key_num;i++)
        {            
            if((FUNC_ALONE_KEY_STATE[i]>ALONE_KEY_IDLE)||(FUNC_ALONE_KEY_STATE_1[i]>ALONE_KEY_IDLE))
            {
                j++;
            }  
            FUNC_ALONE_KEY_PD_NUM=j;
        }            
#ifdef KEY_SCAN_IN_MAIN			
		}
#endif			
}


#ifdef FUNC_ALONE_KEY_SCAN_IN_MAIN
void FUNC_ALONE_KEY_TIMER(void)      
{
/*
 *函数名：FUNC_ALONE_KEY_TIMER
 *描述  ：tim0中断中需要调用的程序
 *输入  ：无
 *输出  ：无
 *调用  ：tim中断服务程序中调用,定时周期1ms
*/
#define ALONE_KEY_SCAN_TIME_MS  2    //按键扫描周期ALONE_KEY_PD_TIME_MS毫秒 
	static unsigned short int ms_count=0;
	if(ms_count<ALONE_KEY_SCAN_TIME_MS)
	{
		ms_count++;
	}
	else
	{
		ms_count=0;
		key_scan_time_mark=1;
	}

}

#endif

void FUNC_ALONE_KEY_INIT()
{
/*
 *函数名：FUNC_ALONE_KEY_INIT
 *描述  ：按键单个判断初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：main函数中调用
*/    
    
    unsigned char i=0;
    //按键状态清0
    for(i=0;i<key_num;i++)
    {
        FUNC_ALONE_KEY_STATE[i]=ALONE_KEY_IDLE;    //清相应按键状态
		FUNC_ALONE_KEY_STATE_1[i]=ALONE_KEY_IDLE; 
        key_ynum[i]=0;     //清相应按键按键次数
    }
    FUNC_ALONE_KEY_PD_NUM=0;
}



























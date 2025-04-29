/*******************************************
*模块说明：时间标志函数
*作者：mzze
*版本：v1.0
*日期：2020.5.29
*上一版本：
*版本变更说明：初版
***********************************************/
#include "func_time_mark.h"



/*****主循环需要的相关时间变量********/


unsigned char time_mark_50ms_mark1=0;     //50MS标志位
unsigned char time_mark_100ms_mark1=0;     //100MS标志位
unsigned char time_mark_500ms_mark1=0;     //500MS标志位
unsigned char time_mark_500ms_mark2=0;     //500MS标志位

unsigned char time_mark_1000ms_mark=0;    //1000MS标志位
unsigned char time_mark_5000ms_mark=0;    //5000MS标志位

unsigned char time_mark_500ms_fb_mark=0;     //500MS方波标志位
unsigned char time_mark_1000ms_fb_mark=0;    //1000MS方波标志位





void FUNC_TIME_MARK_TIMER()
{
/*
 *函数名：FUNC_TIME_MARK_TIMER
 *描述  ：时间基准
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/ 
    static unsigned short int _50_ms_count=0;     
    static unsigned short int _100_ms_count=0;    
    static unsigned short int _500_ms_count=0;
    static unsigned short int _1000_ms_count=0;   
    static unsigned short int _5000_ms_count=0;    
    static unsigned short int _500_ms_fb_count=0;
    static unsigned short int _1000_ms_fb_count=0;  

    if(_50_ms_count<5)
    {
        _50_ms_count++;        
    }
    else
    {
        _50_ms_count=0;
        time_mark_50ms_mark1=0xff;
        
    }    
    
    if(_100_ms_count<10)
    {
        _100_ms_count++;        
    }
    else
    {
        _100_ms_count=0;
        time_mark_100ms_mark1=0xff;
        //time_mark_100ms_mark2=0xff;        
    }
    
    if(_500_ms_count<50)
    {
        _500_ms_count++;        
    }
    else
    {
        _500_ms_count=0;
        time_mark_500ms_mark1=0xff;
        time_mark_500ms_mark2=0xff;        
    }
    if(_1000_ms_count<100)
    {
        _1000_ms_count++;
    }
    else
    {
        _1000_ms_count=0;     
        time_mark_1000ms_mark=0xff;     
    } 
    
    if(_5000_ms_count<500)
    {
        _5000_ms_count++;
    }
    else
    {
        _5000_ms_count=0;     
        time_mark_5000ms_mark=0xff;     
    }     
    /*********方波基准生成***************/
    if(_500_ms_fb_count<100)            //500ms方波基准
    {
        _500_ms_fb_count++;
        if(_500_ms_fb_count<50)
        {
            time_mark_500ms_fb_mark=1;            
        }
        else
        {
            time_mark_500ms_fb_mark=0;
        }        
    }
    else
    {
        _500_ms_fb_count=0;           
    }        
    if(_1000_ms_fb_count<200)            //1000ms方波基准
    {
        _1000_ms_fb_count++;
        if(_1000_ms_fb_count<100)
        {
            time_mark_1000ms_fb_mark=1;            
        }
        else
        {
            time_mark_1000ms_fb_mark=0;
        } 
      
    }
    else
    {
        _1000_ms_fb_count=0;           
    }       
}


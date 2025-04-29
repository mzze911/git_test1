/*********************************************************
函数模块说明： 用于异或校验的函数模块,用于stm32

当前版本号 ： func_s_xorc8.c v2.0
上一版本号 ： yihuo_jy_8.c v1func_s_xorc8.0

修改人：  mzze

修改内容：改变函数名称

日期   ： 2022.8.15
**********************************************************/
#include "func_s_xorc8.h"

#ifdef miyao_enable              //是否允许使用异或密钥
    #define miyao_1 0xE1 
    #define miyao_2 0xE2
#endif


/**************对一组数据外加两个字节的密钥进行异或运算***********/
//返回的数据为生成的异或校验值
unsigned char FUNC_S_XORC8_CAL(unsigned char *start_add, unsigned short int length)
{
    unsigned char yihuo_count=0;  //用于计数异或次数
    unsigned char yihuo_zhi=0;
    for(;yihuo_count<length;yihuo_count++)   //循环执行异或处理
    {
        yihuo_zhi=yihuo_zhi^(*(start_add++));
    }
#ifdef miyao_enable     
    //-----与另外两个密钥进行异或------
    yihuo_zhi=yihuo_zhi^miyao_1;   
    yihuo_zhi=yihuo_zhi^miyao_2; 
#endif    
    return yihuo_zhi;
}
/*************对一组数据(length参数包括一位校验值)进行校验************/
unsigned char FUNC_S_XORC8_CHECK(unsigned char *start_add, unsigned short int length)
{
    unsigned char yihuo_count=0;  //用于计数异或次数
    unsigned char yihuo_zhi=0;
    //unsigned char *start_add_s=start_add;
    for(;yihuo_count<(length-1);yihuo_count++)   //循环执行异或处理
    {
        yihuo_zhi=yihuo_zhi^(*(start_add++));
    }
#ifdef miyao_enable    
    //-----与另外两个密钥进行异或------
    yihuo_zhi=yihuo_zhi^miyao_1;   
    yihuo_zhi=yihuo_zhi^miyao_2;  
#endif    
    //-----比对接收到的异或值和生成的异或值是否一样---
    if(yihuo_zhi==(*(start_add)))
    {
       return 1;     //校验成功
    }
    else
    {
       return 0;     //校验失败
    }
}    


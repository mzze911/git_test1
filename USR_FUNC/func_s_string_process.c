#include "func_s_string_process.h"





unsigned char FUNC_S_SP_GET_MATCH_POS(unsigned char*str1,unsigned char mask,unsigned char str1_size)
{
/*
 *函数名：FUNC_S_SP_GET_MATCH_POS
 *描述  ：在str1中找到第一个匹配mask的位置
 *输入  ：str1:源字符串
		  mask:需要匹配的字符
		  str1_size:小于255
 *输出  ：无
 *调用  ：内部调用
*/     
    unsigned char i=0;            
    for(i=0;i<str1_size;i++)                    
    {
        if((*(str1+i))==mask)  //匹配
        {
            return i;    //返回该匹配位置   
        }        
    }
    if(i==str1_size)
    {
        return str1_size+1;    //未找到匹配字符串
    }
}


unsigned char FUNC_S_SP_COMPAR_STR1_STR2(char*str1,char*str2,unsigned char bidui_mode)
{
/*
 *函数名：FUNC_S_SP_COMPAR_STR1_STR2
 *描述  ：按规定方式比对两个字符串，并输出比较结果
 *输入  ：str1：字符串1指针
          str2: 字符串2指针
          bidui_mode:比对方式，这里的比对意指str2是否以某种方式与str1发生关系
 *输出  ：0：比对成功 1：比对不成功
 *调用  ：外部调用
*/       
    unsigned char r=0;
    switch(bidui_mode)
    {
        case 0:         //不进行比对
        {
            r=0;
            
        }break;
        case 1:         //完全比对
        {
            while((*str1)!='\0')    //当字符串结束
            {
                if((*str1)!=(*str2))
                {
                    r=1;
                    break;
                }
                str1++;
                str2++;
            }
            if((*str1)!=(*str2))//判断最后一个字节是否相同
            {
                r=1;   
            }
            
        }break;
        case 2:         //不完全比对，判断STR1是否包含STR2
        {
            while((*str1)!='\0')
            {
                r=1;
                if((*str1)==(*str2))  //当发现一个字符相等时
                {
                    char*str1_f=str1;
                    char*str2_f=str2;
                    while((*str2_f)!='\0')   //当字符串2未结束时
                    {
                        if((*str1_f)!=(*str2_f))  //若有两个字符不相等
                        {
                            r=1; 
                            break; //跳出此循环
                        }
                        str1_f++;
                        str2_f++;
                    }
                    if((*str2_f)=='\0')   //若成功比对到
                    {
                        r=0;
                        break;  //跳出循环
                    }
                }
                str1++;                               
            }
            
        }break;
        default:
        {
            r=1;
            
        }break;
    }
    return r;
}


unsigned char FUNC_S_SP_CUT_OUT_STR(unsigned char*n_str,unsigned char n_str_size,unsigned char*str,unsigned char cut_mask)
{
/*
 *函数名：FUNC_S_SP_CUT_OUT_STR
 *描述  ：截取字符串形成新的字符串
 *输入  ：n_str：新的字符串 n_str_size：新的字符串最大大小
		  str: 需要被截取的字符串  cut_mask:截取停止标志
 *输出  ：0：截取成功 1：新字符串大小溢出  2:未找到截取停止标志
 *调用  ：外部调用
*/   
	unsigned char r=0;
    unsigned char i=0;
    while(i<n_str_size)
    {
		if((*(str+i))!='\0')
		{
			if(*(str+i)==cut_mask)
			{
				
				break;
			}
			else
			{				
				*(n_str+i)=*(str+i);
				i++;
			}
		}
		else
		{
			r=2;
            break;			
		}
    }
	if(i==n_str_size)
	{
		r=1;
		*(n_str+i-1)=0; //字符串结尾	
	}
	else
	{
		*(n_str+i)=0; //字符串结尾			
	}
	return r;
	
}



unsigned char FUNC_S_SP_COPY_STR(unsigned char*n_str,unsigned char n_str_size,unsigned char*str)
{
/*
 *函数名：FUNC_S_SP_COPY_STR
 *描述  ：复制字符串形成新的字符串
 *输入  ：n_str：新的字符串 n_str_size：新的字符串最大大小
		  str: 需要被复制的字符串 
 *输出  ：0：复制成功 1：新字符串大小溢出
 *调用  ：外部调用
*/   
	unsigned char r=0;
    unsigned char i=0;
    while(i<n_str_size)
    {
		*(n_str+i)=*(str+i);		
		if((*(str+i))=='\0')
		{
			break;
		}
		else
		{
			i++;		
		}
    }
	if(i==n_str_size)
	{
		r=1;
		*(n_str+i-1)=0; //字符串结尾	
	}
	return r;	
}




















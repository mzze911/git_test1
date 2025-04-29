#include "func_s_ring_queue.h"









/***************8位环形队列操作基本函数*******/
void FUNC_S_RING_QUEUE8_INIT(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char*b,unsigned short int que_size)
{	
	unsigned short int i=0;
	que->over_mark=0;
	que->head=0;
	que->tail=0;	
	que->length=0;
	que->que_size=que_size;
	que->que=b;
	for(i=0;i<que_size;i++)
	{
		que->que[i]=0;
	}

}

void FUNC_S_RING_QUEUE8_RESET(FUNC_S_STRUCT_RING_QUEUE8*que)
{	
	unsigned short int i=0;
	que->over_mark=0;
	que->head=0;
	que->tail=0;	
	que->length=0;
	for(i=0;i<(que->que_size);i++)
	{
		que->que[i]=0;
	}

}


unsigned short int FUNC_S_RING_QUEUE8_GET_LEN(FUNC_S_STRUCT_RING_QUEUE8*que)	
{
/*
 *函数名：ringque_get_len
 *描述  ：环形缓冲区获取当前数据长度
 *输入  ：
 *输出  ：当前缓冲区内数据长度 
 *调用  ：外部调用
*/ 	
	return que->length;
}



unsigned char FUNC_S_RING_QUEUE8_WRITE(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char *d,unsigned short int l)
{
/*
 *函数名：ringque_write
 *描述  ：环形缓冲区写数据
 *输入  ：
 *输出  ：写入是否成功 0成功 1失败 
 *调用  ：外部调用
*/ 	
	unsigned short int i=0;
	while(l)
	{
		//-----判断缓冲区是否满----
		if((que->length)>=(que->que_size))
		{
			que->over_mark=1;  //赋值溢出标志
			return 1;		
		}		
		que->que[que->tail]=d[i];
		que->tail=(que->tail+1)%(que->que_size);
		que->length++;		
		i++;
		l--;		
	}
	return 0;
	
}



unsigned char FUNC_S_RING_QUEUE8_READ(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char *d)
{
/*
 *函数名：ringque_read
 *描述  ：环形缓冲区读数据
 *输入  ：
 *输出  ：读取是否成功 0成功 1失败 
 *调用  ：外部调用
*/ 	
	//-----判断缓冲区是否空----
	if((que->length)==0)
	{
		return 1;		
	}		
	*d=que->que[que->head];
	que->head=(que->head+1)%(que->que_size);
	que->length--;	      //读写存在打断的情况下，需要开启和关闭中断，防止长度计算不准确，丢数据
	return 0;
}


unsigned char FUNC_S_RING_QUEUE8_GET_DATA(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char pos,short int pos_off,     //缓冲区，读取数据位置，读取数据位置偏移
	                             unsigned char*td,unsigned char td_size,                                             //目标放置位置，目标放置位置大小
	                             unsigned char len,unsigned char cut_musk)                                          //读取长度，读取停止字符，两种读取方式二选一
{
/*
 *函数名：FUNC_S_RING_QUEUE8_GET_DATA
 *描述  ：环形缓冲区读取数据
 *输入  ：
 *输出  ：读取的数据量
 *调用  ：外部调用
*/ 		
	unsigned char i=0;
	unsigned char s_pos=0;
	//-----计算新的位置------
	while(pos_off<0)
	{
		pos_off+=que->que_size;
	}
	s_pos=(pos+pos_off)%(que->que_size);
	
	//-----读取数据-----------
	if(
		(len!=0)
		&&(len<(que->que_size))
	)
	{
		while(len)
		{
			if(i<td_size)
			{
				*(td+i)=que->que[s_pos];
				i++;
				s_pos=(s_pos+1)%(que->que_size);
				len--;
			}
			else
			{
				break;
			}			
		}
	}
	else
	{
		if(cut_musk!=0)
		{
			while(que->que[s_pos]!=cut_musk)
			{
				if(
					(i<td_size)
					&&(i<(que->que_size))
				)
				{
					*(td+i)=que->que[s_pos];
					i++;
					s_pos=(s_pos+1)%(que->que_size);
					len--;
				}
				else
				{
					break;
				}				
			}
		}	
	}
	return i;	
}























#ifndef _FUNC_S_RING_QUEUE_H_
#define _FUNC_S_RING_QUEUE_H_

#include "bsp_stm32f1_mzze.h"





//-------环形队列结构体定义----
typedef struct{
    unsigned char over_mark;             //溢出状态
    unsigned short int head;             //头
    unsigned short int tail;             //尾
    unsigned short int length;           //数据长度 
	unsigned short int que_size;         //队列大小
    unsigned char *que;                  //队列区	
}FUNC_S_STRUCT_RING_QUEUE8;     //8位环形队列




/***************8位环形队列操作基本函数*******/
extern void FUNC_S_RING_QUEUE8_INIT(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char*b,unsigned short int que_size);
extern void FUNC_S_RING_QUEUE8_RESET(FUNC_S_STRUCT_RING_QUEUE8*que);
extern unsigned short int FUNC_S_RING_QUEUE8_GET_LEN(FUNC_S_STRUCT_RING_QUEUE8*que);	
extern unsigned char FUNC_S_RING_QUEUE8_WRITE(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char *d,unsigned short int l);
extern unsigned char FUNC_S_RING_QUEUE8_READ(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char *d);

extern unsigned char FUNC_S_RING_QUEUE8_GET_DATA(FUNC_S_STRUCT_RING_QUEUE8*que,unsigned char pos,short int pos_off,     //缓冲区，读取数据位置，读取数据位置偏移
	                             unsigned char*td,unsigned char td_size,                                             //目标放置位置，目标放置位置大小
	                             unsigned char len,unsigned char cut_musk);                                          //读取长度，读取停止字符，两种读取方式二选一








#endif



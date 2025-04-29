#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "bsp_stm32f1_mzze.h"

//-----串口使用宏定义----
#define BSP_UART1_EN  1      //使用串口1，注释掉不使用
#define BSP_UART2_EN  1
//#define BSP_UART3_EN  1
//#define BSP_UART4_EN  1
//#define BSP_UART5_EN  1

//-----串口DMA使用宏定义----
#ifdef BSP_UART1_EN
	#define BSP_UART1_TX_DISABLE_EN     0     //---0->禁止发送禁止    1->允许发送禁止
	#define BSP_UART1_TX_DMA_EN         0     //---0->不使用DMA方式发送  1->DMA方式发送（不开DMA传输中断）  2->DMA方式发送（开DMA传输中断）  
	#define BSP_UART1_RX_DMA_EN         0     //---0->不使用DMA方式接收  1->DMA方式接收（不开串口空闲中断） 2->DMA方式接收（开串口空闲中断）
	#define BSP_UART1_DMA_RX_BUF_SIZE  50     //接收缓冲区大小
	#define BSP_UART1_RX_BUF_MODE       1     //串口接收缓冲方式配置  0->不使用缓冲，中断中处理  1->使用环形缓冲区
	#define BSP_UART1_RX_BUF_SIZE     200     //接收缓冲区大小
#endif

#ifdef BSP_UART2_EN
	#define BSP_UART2_TX_DISABLE_EN     1     //---0->禁止发送禁止    1->允许发送禁止
	#define BSP_UART2_TX_DMA_EN         0
	#define BSP_UART2_RX_DMA_EN         2
	#define BSP_UART2_DMA_RX_BUF_SIZE  50     //接收缓冲区大小
	#define BSP_UART2_RX_BUF_MODE       1     //串口接收缓冲方式配置  0->不使用缓冲，中断中处理  1->使用环形缓冲区
	#define BSP_UART2_RX_BUF_SIZE     200     //接收缓冲区大小
#endif

#ifdef BSP_UART3_EN
	#define BSP_UART3_TX_DISABLE_EN     0     //---0->禁止发送禁止    1->允许发送禁止
	#define BSP_UART3_TX_DMA_EN         0
	#define BSP_UART3_RX_DMA_EN         2
	#define BSP_UART3_DMA_RX_BUF_SIZE  50     //接收缓冲区大小
	#define BSP_UART3_RX_BUF_MODE       1     //串口接收缓冲方式配置  0->不使用缓冲，中断中处理  1->使用环形缓冲区
	#define BSP_UART3_RX_BUF_SIZE     200     //接收缓冲区大小
#endif

#ifdef BSP_UART4_EN
	#define BSP_UART4_TX_DISABLE_EN     0     //---0->禁止发送禁止    1->允许发送禁止
	#define BSP_UART4_TX_DMA_EN         0
	#define BSP_UART4_RX_DMA_EN         2
	#define BSP_UART4_DMA_RX_BUF_SIZE  50     //接收缓冲区大小
	#define BSP_UART4_RX_BUF_MODE       1     //串口接收缓冲方式配置  0->不使用缓冲，中断中处理  1->使用环形缓冲区
	#define BSP_UART4_RX_BUF_SIZE     200     //接收缓冲区大小
#endif

#ifdef BSP_UART5_EN
	//串口5无法使用DMA
	#define BSP_UART5_TX_DISABLE_EN     1     //---0->禁止发送禁止    1->允许发送禁止
	#define BSP_UART5_RX_BUF_MODE       1     //串口接收缓冲方式配置  0->不使用缓冲，中断中处理  1->使用环形缓冲区
	#define BSP_UART5_RX_BUF_SIZE     200     //接收缓冲区大小
#endif



//-----接收缓冲区结构体定义--------
typedef struct{
    unsigned char over_mark;             //溢出状态
    unsigned short int head;             //头
    unsigned short int tail;             //尾
    unsigned short int length;           //数据长度 
	unsigned short int buf_size;         //缓冲区大小
    unsigned char *buf;                  //缓冲区	
}STRUCT_UART_RX_BUF;


typedef struct{
    unsigned short int read_pos;         //读取的位置 
	unsigned short int read_len;         //需要读的数据长度
	unsigned short int buf_half_size;         //缓冲区大小	
	unsigned short int buf_size;         //缓冲区大小
    unsigned char *buf;                  //缓冲区	
}STRUCT_UART_DMA_RX_BUF;




//---------------对外接口变量--------------
#if(BSP_UART1_TX_DMA_EN==2)
extern unsigned char BSP_UART1_TX_MARK;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if(BSP_UART2_TX_DMA_EN==2)
extern unsigned char BSP_UART2_TX_MARK;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if(BSP_UART3_TX_DMA_EN==2)
extern unsigned char BSP_UART3_TX_MARK;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if(BSP_UART4_TX_DMA_EN==2)
extern unsigned char BSP_UART4_TX_MARK;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif

//---------------对外接口函数---------------
#ifdef BSP_UART1_EN
extern void BSP_UART1_INIT(void);

extern void BSP_USART1_RX_RINGBUF_PROCESS_TASK(unsigned char pl);                	

extern void BSP_USART1_RX_USR_CALL(unsigned char res);

extern void BSP_USART1_SEND_BUF(unsigned char *b,unsigned short int b_l);

extern void BSP_USART1_FA_STRING(unsigned char*str);
#endif


#ifdef BSP_UART2_EN
extern void BSP_UART2_INIT(void);

extern void BSP_USART2_RX_RINGBUF_PROCESS_TASK(unsigned char pl);                	

extern void BSP_USART2_RX_USR_CALL(unsigned char res);

extern void BSP_USART2_SEND_BUF(unsigned char *b,unsigned short int b_l);

extern void BSP_USART2_FA_STRING(unsigned char*str);
#endif


#ifdef BSP_UART3_EN
extern void BSP_UART3_INIT(void);

extern void BSP_USART3_RX_RINGBUF_PROCESS_TASK(unsigned char pl);                	

extern void BSP_USART3_RX_USR_CALL(unsigned char res);

extern void BSP_USART3_SEND_BUF(unsigned char *b,unsigned short int b_l);

extern void BSP_USART3_FA_STRING(unsigned char*str);
#endif



#ifdef BSP_UART4_EN
extern void BSP_UART4_INIT(void);

extern void BSP_USART4_RX_RINGBUF_PROCESS_TASK(unsigned char pl);                	

extern void BSP_USART4_RX_USR_CALL(unsigned char res);

extern void BSP_USART4_SEND_BUF(unsigned char *b,unsigned short int b_l);

extern void BSP_USART4_FA_STRING(unsigned char*str);
#endif


#ifdef BSP_UART5_EN
extern void BSP_UART5_INIT(void);

extern void BSP_USART5_RX_RINGBUF_PROCESS_TASK(unsigned char pl);                	

extern void BSP_USART5_RX_USR_CALL(unsigned char res);

extern void BSP_USART5_SEND_BUF(unsigned char *b,unsigned short int b_l);

extern void BSP_USART5_FA_STRING(unsigned char*str);
#endif






#endif
























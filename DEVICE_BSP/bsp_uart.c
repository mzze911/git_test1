#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_systick.h"
#include "func_pc_interface_com.h"


/******************变量定义***********************/
#ifdef BSP_UART1_EN
//----串口1相关变量定义---
UART_HandleTypeDef UART1_Handler; //UART句柄

#if(BSP_UART1_TX_DMA_EN==2)
unsigned char BSP_UART1_TX_MARK=0;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if((BSP_UART1_RX_DMA_EN==1)||(BSP_UART1_RX_DMA_EN==2))  //使用DMA
	unsigned char BSP_UART1_DMA_RX_BUF[BSP_UART1_DMA_RX_BUF_SIZE];
	STRUCT_UART_DMA_RX_BUF BSP_UART1_DMA_RX;	
	
#endif
	
#if(BSP_UART1_RX_BUF_MODE==1)  //使用缓冲区
	unsigned char BSP_UART1_RX_BUF[BSP_UART1_RX_BUF_SIZE];
	STRUCT_UART_RX_BUF BSP_UART1_RX;	
	
#endif
#endif
#ifdef BSP_UART2_EN	
//----串口2相关变量定义---
UART_HandleTypeDef UART2_Handler; //UART句柄
#if(BSP_UART2_TX_DMA_EN==2)
unsigned char BSP_UART2_TX_MARK=0;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif	
#if((BSP_UART2_RX_DMA_EN==1)||(BSP_UART2_RX_DMA_EN==2))  //使用DMA
	unsigned char BSP_UART2_DMA_RX_BUF[BSP_UART2_DMA_RX_BUF_SIZE];
	STRUCT_UART_DMA_RX_BUF BSP_UART2_DMA_RX;	
	
#endif
	
#if(BSP_UART2_RX_BUF_MODE==1)  //使用缓冲区
	unsigned char BSP_UART2_RX_BUF[BSP_UART2_RX_BUF_SIZE];
	STRUCT_UART_RX_BUF BSP_UART2_RX;	
	
#endif
#endif
#ifdef BSP_UART3_EN
//----串口3相关变量定义---
UART_HandleTypeDef UART3_Handler; //UART句柄
#if(BSP_UART3_TX_DMA_EN==2)
unsigned char BSP_UART3_TX_MARK=0;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if((BSP_UART3_RX_DMA_EN==1)||(BSP_UART3_RX_DMA_EN==2))  //使用DMA
	unsigned char BSP_UART3_DMA_RX_BUF[BSP_UART3_DMA_RX_BUF_SIZE];
	STRUCT_UART_DMA_RX_BUF BSP_UART3_DMA_RX;	
	
#endif
	
#if(BSP_UART3_RX_BUF_MODE==1)  //使用缓冲区
	unsigned char BSP_UART3_RX_BUF[BSP_UART3_RX_BUF_SIZE];
	STRUCT_UART_RX_BUF BSP_UART3_RX;	
	
#endif
#endif
#ifdef BSP_UART4_EN
//----串口4相关变量定义---
UART_HandleTypeDef UART4_Handler; //UART句柄
#if(BSP_UART4_TX_DMA_EN==2)
unsigned char BSP_UART4_TX_MARK=0;   //0->无意义   1->正在发送   2->发送完成一半  3->发送完成

#endif
#if((BSP_UART4_RX_DMA_EN==1)||(BSP_UART4_RX_DMA_EN==2))  //使用DMA
	unsigned char BSP_UART4_DMA_RX_BUF[BSP_UART4_DMA_RX_BUF_SIZE];
	STRUCT_UART_DMA_RX_BUF BSP_UART4_DMA_RX;	
	
#endif
	
#if(BSP_UART4_RX_BUF_MODE==1)  //使用缓冲区
	unsigned char BSP_UART4_RX_BUF[BSP_UART4_RX_BUF_SIZE];
	STRUCT_UART_RX_BUF BSP_UART4_RX;	
	
#endif
#endif
#ifdef BSP_UART5_EN
//----串口5相关变量定义---
UART_HandleTypeDef UART5_Handler; //UART句柄

#if(BSP_UART5_RX_BUF_MODE==1)  //使用缓冲区
	unsigned char BSP_UART5_RX_BUF[BSP_UART5_RX_BUF_SIZE];
	STRUCT_UART_RX_BUF BSP_UART5_RX;	
	
#endif
#endif

/***************DMA接收缓冲区操作基本函数*******/
static void dma_rx_buf_init(STRUCT_UART_DMA_RX_BUF*buf,unsigned char*b,unsigned short int buf_size)
{	
	unsigned short int i=0;
	buf->read_pos=0;	
	buf->read_len=0;
	buf->buf_size=buf_size;
	if((buf->buf_size%2)==0)
	{
		buf->buf_half_size=buf->buf_size/2;
	}
	else
	{
		buf->buf_half_size=(buf->buf_size+1)/2;		
	}
	buf->buf=b;
	for(i=0;i<buf_size;i++)
	{
		b[i]=0;
	}

}

static void dma_rx_buf_reset(STRUCT_UART_DMA_RX_BUF*buf)
{	
	unsigned short int i=0;
	buf->read_pos=0;	
	buf->read_len=0;;
	for(i=0;i<(buf->buf_size);i++)
	{
		buf->buf[i]=0;
	}

}



/***************环形缓冲区操作基本函数*******/
static void ringbuf_init(STRUCT_UART_RX_BUF*buf,unsigned char*b,unsigned short int buf_size)
{	
	unsigned short int i=0;
	buf->over_mark=0;
	buf->head=0;
	buf->tail=0;	
	buf->length=0;
	buf->buf_size=buf_size;
	buf->buf=b;
	for(i=0;i<buf_size;i++)
	{
		b[i]=0;
	}

}

static void ringbuf_reset(STRUCT_UART_RX_BUF*buf)
{	
	unsigned short int i=0;
	buf->over_mark=0;
	buf->head=0;
	buf->tail=0;	
	buf->length=0;
	for(i=0;i<(buf->buf_size);i++)
	{
		buf->buf[i]=0;
	}

}


static unsigned short int ringbuf_get_len(STRUCT_UART_RX_BUF*buf)
{
/*
 *函数名：ringbuf_get_len
 *描述  ：环形缓冲区获取当前数据长度
 *输入  ：
 *输出  ：当前缓冲区内数据长度 
 *调用  ：外部调用
*/ 	

	return buf->length;
}



static unsigned char ringbuf_write(STRUCT_UART_RX_BUF*buf,unsigned char *d,unsigned short int l)
{
/*
 *函数名：ringbuf_write
 *描述  ：环形缓冲区写数据
 *输入  ：
 *输出  ：写入是否成功 0成功 1失败 
 *调用  ：外部调用
*/ 	
	unsigned short int i=0;
	while(l)
	{
		//-----判断缓冲区是否满----
		if((buf->length)>=(buf->buf_size))
		{
			buf->over_mark=1;  //赋值溢出标志
			return 1;		
		}		
		buf->buf[buf->tail]=d[i];
		buf->tail=(buf->tail+1)%(buf->buf_size);
		buf->length++;		
		i++;
		l--;		
	}
	return 0;
	
}



static unsigned char ringbuf_read(STRUCT_UART_RX_BUF*buf,unsigned char *d)
{
/*
 *函数名：ringbuf_read
 *描述  ：环形缓冲区读数据
 *输入  ：
 *输出  ：读取是否成功 0成功 1失败 
 *调用  ：外部调用
*/ 	
	//-----判断缓冲区是否空----
	if((buf->length)==0)
	{
		return 1;		
	}		
	*d=buf->buf[buf->head];
	buf->head=(buf->head+1)%(buf->buf_size);
	__disable_irq();
	buf->length--;	
	__enable_irq();
	return 0;
}



/****************串口初始化*******************/
#ifdef BSP_UART1_EN
void BSP_UART1_INIT(void)
{	
#if((BSP_UART1_RX_DMA_EN==1)||(BSP_UART1_RX_DMA_EN==2)) 
	dma_rx_buf_init(&BSP_UART1_DMA_RX,BSP_UART1_DMA_RX_BUF,BSP_UART1_DMA_RX_BUF_SIZE);
#endif
	
#if(BSP_UART1_RX_BUF_MODE==1) 
	ringbuf_init(&BSP_UART1_RX,BSP_UART1_RX_BUF,BSP_UART1_RX_BUF_SIZE);
#endif

	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=115200;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //发送接收模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1


	
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_PE);    
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_ERR); 

#if(BSP_UART1_RX_DMA_EN==0)   //不使用DMA方式接收数据
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_RXNE);
#endif	


#if(BSP_UART1_RX_DMA_EN==1)  //DMA方式接收（不开串口空闲中断）
	HAL_UART_Receive_DMA(&UART1_Handler,BSP_UART1_DMA_RX.buf,BSP_UART1_DMA_RX.buf_size);
#endif

#if(BSP_UART1_RX_DMA_EN==2)  //DMA方式接收（开串口空闲中断）
    __HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_IDLE); 
	HAL_UART_Receive_DMA(&UART1_Handler,BSP_UART1_DMA_RX.buf,BSP_UART1_DMA_RX.buf_size);
#endif

   //--避免使能后进入发送中断--
//    __HAL_UART_CLEAR_FLAG(&UART1_Handler,USART_FLAG_RXNE); 
    __HAL_UART_CLEAR_FLAG(&UART1_Handler,USART_FLAG_TC); 

    while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TC)==RESET)
    {}   //等待空闲帧发送完成后 再清零发送标志
    __HAL_UART_CLEAR_FLAG(&UART1_Handler,USART_FLAG_TC);   

}
#endif
#ifdef BSP_UART2_EN
void BSP_UART2_INIT(void)
{
#if((BSP_UART2_RX_DMA_EN==1)||(BSP_UART2_RX_DMA_EN==2)) 
	dma_rx_buf_init(&BSP_UART2_DMA_RX,BSP_UART2_DMA_RX_BUF,BSP_UART2_DMA_RX_BUF_SIZE);
#endif
	
#if(BSP_UART2_RX_BUF_MODE==1) 
	ringbuf_init(&BSP_UART2_RX,BSP_UART2_RX_BUF,BSP_UART2_RX_BUF_SIZE);
#endif
	
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    //USART2
	UART2_Handler.Init.BaudRate=57600;				    //波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //发送接收模式
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()会使能UART2
	
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_PE);    
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_ERR);  
	
#if(BSP_UART2_RX_DMA_EN==0)   //不使用DMA方式接收数据
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_RXNE);
#endif	


#if(BSP_UART2_RX_DMA_EN==1)  //DMA方式接收（不开串口空闲中断）
	HAL_UART_Receive_DMA(&UART2_Handler,BSP_UART2_DMA_RX.buf,BSP_UART2_DMA_RX.buf_size);
#endif

#if(BSP_UART2_RX_DMA_EN==2)  //DMA方式接收（开串口空闲中断）
    __HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_IDLE); 
	HAL_UART_Receive_DMA(&UART2_Handler,BSP_UART2_DMA_RX.buf,BSP_UART2_DMA_RX.buf_size);
#endif

   //--避免使能后进入发送中断--
//    __HAL_UART_CLEAR_FLAG(&UART2_Handler,USART_FLAG_RXNE); 
    __HAL_UART_CLEAR_FLAG(&UART2_Handler,USART_FLAG_TC); 

    while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TC)==RESET)
    {}   //等待空闲帧发送完成后 再清零发送标志
    __HAL_UART_CLEAR_FLAG(&UART2_Handler,USART_FLAG_TC);    
}
#endif
#ifdef BSP_UART3_EN
void BSP_UART3_INIT(void)
{
#if((BSP_UART3_RX_DMA_EN==1)||(BSP_UART3_RX_DMA_EN==2)) 
	dma_rx_buf_init(&BSP_UART3_DMA_RX,BSP_UART3_DMA_RX_BUF,BSP_UART3_DMA_RX_BUF_SIZE);
#endif
	
#if(BSP_UART3_RX_BUF_MODE==1) 
	ringbuf_init(&BSP_UART3_RX,BSP_UART3_RX_BUF,BSP_UART3_RX_BUF_SIZE);
#endif
	
	//UART 初始化设置
	UART3_Handler.Instance=USART3;					    //USART2
	UART3_Handler.Init.BaudRate=115200;				    //波特率
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART3_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		    //发送接收模式
	HAL_UART_Init(&UART3_Handler);					    //HAL_UART_Init()会使能UART3
	
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&UART3_Handler, UART_IT_PE);    
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&UART3_Handler, UART_IT_ERR); 
	
#if(BSP_UART3_RX_DMA_EN==0)   //不使用DMA方式接收数据
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UART3_Handler, UART_IT_RXNE);
#endif	


#if(BSP_UART3_RX_DMA_EN==1)  //DMA方式接收（不开串口空闲中断）
	HAL_UART_Receive_DMA(&UART3_Handler,BSP_UART3_DMA_RX.buf,BSP_UART3_DMA_RX.buf_size);
#endif

#if(BSP_UART3_RX_DMA_EN==2)  //DMA方式接收（开串口空闲中断）
    __HAL_UART_ENABLE_IT(&UART3_Handler, UART_IT_IDLE); 
	HAL_UART_Receive_DMA(&UART3_Handler,BSP_UART3_DMA_RX.buf,BSP_UART3_DMA_RX.buf_size);
#endif

   //--避免使能后进入发送中断--
//    __HAL_UART_CLEAR_FLAG(&UART3_Handler,USART_FLAG_RXNE); 
    __HAL_UART_CLEAR_FLAG(&UART3_Handler,USART_FLAG_TC); 

    while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TC)==RESET)
    {}   //等待空闲帧发送完成后 再清零发送标志
    __HAL_UART_CLEAR_FLAG(&UART3_Handler,USART_FLAG_TC);    
}

#endif
#ifdef BSP_UART4_EN
void BSP_UART4_INIT(void)
{
#if((BSP_UART4_RX_DMA_EN==1)||(BSP_UART4_RX_DMA_EN==2)) 
	dma_rx_buf_init(&BSP_UART4_DMA_RX,BSP_UART4_DMA_RX_BUF,BSP_UART4_DMA_RX_BUF_SIZE);
#endif
	
#if(BSP_UART4_RX_BUF_MODE==1) 
	ringbuf_init(&BSP_UART4_RX,BSP_UART4_RX_BUF,BSP_UART4_RX_BUF_SIZE);
#endif
	
	//UART 初始化设置
	UART4_Handler.Instance=UART4;					    //UART4
	UART4_Handler.Init.BaudRate=115200;				    //波特率
	UART4_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART4_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART4_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART4_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART4_Handler.Init.Mode=UART_MODE_TX_RX;		    //发送接收模式
	HAL_UART_Init(&UART4_Handler);					    //HAL_UART_Init()会使能UART4
	
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&UART4_Handler, UART_IT_PE);    
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&UART4_Handler, UART_IT_ERR);    
	
#if(BSP_UART4_RX_DMA_EN==0)   //不使用DMA方式接收数据
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UART4_Handler, UART_IT_RXNE);
#endif	


#if(BSP_UART4_RX_DMA_EN==1)  //DMA方式接收（不开串口空闲中断）
	HAL_UART_Receive_DMA(&UART4_Handler,BSP_UART4_DMA_RX.buf,BSP_UART4_DMA_RX.buf_size);
#endif

#if(BSP_UART4_RX_DMA_EN==2)  //DMA方式接收（开串口空闲中断）
    __HAL_UART_ENABLE_IT(&UART4_Handler, UART_IT_IDLE); 
	HAL_UART_Receive_DMA(&UART4_Handler,BSP_UART4_DMA_RX.buf,BSP_UART4_DMA_RX.buf_size);
#endif

   //--避免使能后进入发送中断--
//    __HAL_UART_CLEAR_FLAG(&UART4_Handler,USART_FLAG_RXNE); 
    __HAL_UART_CLEAR_FLAG(&UART4_Handler,USART_FLAG_TC); 

    while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TC)==RESET)
    {}   //等待空闲帧发送完成后 再清零发送标志
    __HAL_UART_CLEAR_FLAG(&UART4_Handler,USART_FLAG_TC);    
}

#endif
#ifdef BSP_UART5_EN
void BSP_UART5_INIT(void)
{
#if(BSP_UART5_RX_BUF_MODE==1) 
	ringbuf_init(&BSP_UART5_RX,BSP_UART5_RX_BUF,BSP_UART5_RX_BUF_SIZE);
#endif	
	//UART 初始化设置
	UART5_Handler.Instance=UART5;					    //USART5
	UART5_Handler.Init.BaudRate=115200;				    //波特率
	UART5_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART5_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART5_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART5_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART5_Handler.Init.Mode=UART_MODE_TX_RX;		    //发送接收模式
	HAL_UART_Init(&UART5_Handler);					    //HAL_UART_Init()会使能UART5
	
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&UART5_Handler, UART_IT_PE);    
    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&UART5_Handler, UART_IT_ERR);    
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&UART5_Handler, UART_IT_RXNE);

   //--避免使能后进入发送中断--
//    __HAL_UART_CLEAR_FLAG(&UART5_Handler,USART_FLAG_RXNE); 
    __HAL_UART_CLEAR_FLAG(&UART5_Handler,USART_FLAG_TC); 

    while(__HAL_UART_GET_FLAG(&UART5_Handler,USART_FLAG_TC)==RESET)
    {}   //等待空闲帧发送完成后 再清零发送标志
    __HAL_UART_CLEAR_FLAG(&UART5_Handler,USART_FLAG_TC);    
}
#endif



//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;

	#ifdef BSP_UART1_EN    
    /***************进行串口1相关的设置*********************/
//	if(huart->Instance==USART1)//如果是串口1，进行串口1 BSP初始化
//	{
//		__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOB时钟
//		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
//	
//		GPIO_Initure.Pin=GPIO_PIN_6;			//PB6
//		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
//		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
//		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
//		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
//		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB6

//		GPIO_Initure.Pin=GPIO_PIN_7;			//PB7
//		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB7
//		
//		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
//		HAL_NVIC_SetPriority(USART1_IRQn,1,3);	//抢占优先级3，子优先级3
//	}
	if(huart->Instance==USART1)//如果是串口1，进行串口1 BSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟


		
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//复用输入		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,0,2);	//抢占优先级3，子优先级3
		
		//-----配置DMA-----------		
#if((BSP_UART1_TX_DMA_EN==1)||(BSP_UART1_TX_DMA_EN==2))
		BSP_DMA_UART1_TX_INIT(&UART1_Handler);
#endif	
		
#if((BSP_UART1_RX_DMA_EN==1)||(BSP_UART1_RX_DMA_EN==2))
		BSP_DMA_UART1_RX_INIT(&UART1_Handler);
#endif	

	}	
	#endif
	#ifdef BSP_UART2_EN	
    /********************************************************/
    /***************进行串口2相关的设置*********************/
//	if(huart->Instance==USART2)//如果是串口2，进行串口2 BSP初始化
//	{
//		__HAL_RCC_GPIOD_CLK_ENABLE();			//使能GPIOD时钟
//		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
//	
//		GPIO_Initure.Pin=GPIO_PIN_5;			//PD5
//		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
//		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
//		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
//		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//初始化PD5

//		GPIO_Initure.Pin=GPIO_PIN_6;			//PD6
//		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//复用输入				
//		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//初始化PD6
//		
//		HAL_NVIC_EnableIRQ(USART2_IRQn);		//使能USART2中断通道
//		HAL_NVIC_SetPriority(USART2_IRQn,1,2);	//抢占优先级0，子优先级3
//	}
	
	if(huart->Instance==USART2)//如果是串口2，进行串口2 BSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//复用输入		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA3
		
		HAL_NVIC_EnableIRQ(USART2_IRQn);		//使能USART2中断通道
		HAL_NVIC_SetPriority(USART2_IRQn,0,2);	//抢占优先级0，子优先级3
		
		//-----配置DMA-----------		
#if((BSP_UART2_TX_DMA_EN==1)||(BSP_UART2_TX_DMA_EN==2))
		BSP_DMA_UART2_TX_INIT(&UART2_Handler);
#endif	

#if((BSP_UART2_RX_DMA_EN==1)||(BSP_UART2_RX_DMA_EN==2))
		BSP_DMA_UART2_RX_INIT(&UART2_Handler);
#endif	
	}	
	#endif
	#ifdef BSP_UART3_EN	
    /********************************************************/    
    /***************进行串口3相关的设置*********************/
	if(huart->Instance==USART3)//如果是串口3，进行串口3 BSP初始化
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOB时钟
		__HAL_RCC_USART3_CLK_ENABLE();			//使能USART3时钟
	
		GPIO_Initure.Pin=GPIO_PIN_10;			//PB10
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB10

		GPIO_Initure.Pin=GPIO_PIN_11;			//PB11
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//复用输入			
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB11
		
		HAL_NVIC_EnableIRQ(USART3_IRQn);		//使能USART3中断通道
		HAL_NVIC_SetPriority(USART3_IRQn,1,2);	//抢占优先级0，子优先级3
		
		//-----配置DMA-----------		
#if((BSP_UART3_TX_DMA_EN==1)||(BSP_UART3_TX_DMA_EN==2))
		BSP_DMA_UART3_TX_INIT(&UART3_Handler);
#endif			

#if((BSP_UART3_RX_DMA_EN==1)||(BSP_UART3_RX_DMA_EN==2))
		BSP_DMA_UART3_RX_INIT(&UART3_Handler);
#endif	

	}
//	if(huart->Instance==USART3)//如果是串口3，进行串口3 BSP初始化
//	{
//		__HAL_RCC_GPIOD_CLK_ENABLE();			//使能GPIOD时钟
//		__HAL_RCC_USART3_CLK_ENABLE();			//使能USART3时钟
//	
//		GPIO_Initure.Pin=GPIO_PIN_8;			//PD8
//		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
//		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
//		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
//		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//初始化PB10

//		GPIO_Initure.Pin=GPIO_PIN_9;			//PD9
//		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//初始化PB11
//		
//		HAL_NVIC_EnableIRQ(USART3_IRQn);		//使能USART3中断通道
//		HAL_NVIC_SetPriority(USART3_IRQn,1,2);	//抢占优先级0，子优先级3
//	}	
	#endif
	#ifdef BSP_UART4_EN	
    /********************************************************/     
    /***************进行串口4相关的设置*********************/
	if(huart->Instance==UART4)//如果是串口4，进行串口4 BSP初始化
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();			//使能GPIOC时钟
		__HAL_RCC_UART4_CLK_ENABLE();			//使能USART4时钟
	
		GPIO_Initure.Pin=GPIO_PIN_10;			//PC10
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   	//初始化

		GPIO_Initure.Pin=GPIO_PIN_11;			//PC11
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//复用输入			
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   	//初始化
		
		HAL_NVIC_EnableIRQ(UART4_IRQn);		//使能UART4中断通道
		HAL_NVIC_SetPriority(UART4_IRQn,1,2);	//抢占优先级0，子优先级3
		//-----配置DMA-----------		
#if((BSP_UART4_TX_DMA_EN==1)||(BSP_UART4_TX_DMA_EN==2))
		BSP_DMA_UART4_TX_INIT(&UART4_Handler);
#endif

#if((BSP_UART4_RX_DMA_EN==1)||(BSP_UART4_RX_DMA_EN==2))
		BSP_DMA_UART4_RX_INIT(&UART4_Handler);
#endif	

	}	
	#endif
	#ifdef BSP_UART5_EN
    /********************************************************/     
    /***************进行串口5相关的设置*********************/
	if(huart->Instance==UART5)//如果是串口5，进行串口5 BSP初始化
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();			//使能GPIOC时钟
		__HAL_RCC_GPIOD_CLK_ENABLE();			//使能GPIOD时钟		
		__HAL_RCC_UART5_CLK_ENABLE();			//使能UART5时钟
	
		GPIO_Initure.Pin=GPIO_PIN_12;			//PC12
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);	   	//初始化

		GPIO_Initure.Pin=GPIO_PIN_2;			//PD2
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//复用输入			
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	//初始化
		
		HAL_NVIC_EnableIRQ(UART5_IRQn);		//使能UART5中断通道
		HAL_NVIC_SetPriority(UART5_IRQn,1,2);	//抢占优先级0，子优先级3
	}	
	#endif
	
}

#ifdef BSP_UART1_EN
//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 
    /* UART parity error interrupt occurred ------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_PE) != RESET)  //奇偶校验错误中断
    { 
        __HAL_UART_CLEAR_PEFLAG(&UART1_Handler);
    }
    /* UART frame error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_FE)!= RESET)  //帧错误中断
    { 
        __HAL_UART_CLEAR_FEFLAG(&UART1_Handler);
    }
    /* UART noise error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_NE)!= RESET)  //噪音错误中断
    { 
        __HAL_UART_CLEAR_NEFLAG(&UART1_Handler);
    }
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_ORE)!= RESET)  //上溢错误中断
    { 
        __HAL_UART_CLEAR_OREFLAG(&UART1_Handler);
    }
    //-------接收空闲中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_IDLE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART1_Handler, UART_IT_IDLE)!=RESET)     //是否使能
	)  
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		__HAL_UART_CLEAR_IDLEFLAG(&UART1_Handler); 	  //清空闲标志	
		#if(BSP_UART1_RX_DMA_EN==2)   //使用DMA方式加空闲中断方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART1_DMA_RX.buf_size-__HAL_DMA_GET_COUNTER(UART1_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART1_DMA_RX.read_pos)
			{
				BSP_UART1_DMA_RX.read_len=dma_rx_dl-BSP_UART1_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART1_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART1_DMA_RX.read_len>0)
			{
				while(BSP_UART1_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART1_DMA_RX.buf[BSP_UART1_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART1_DMA_RX.read_pos=(BSP_UART1_DMA_RX.read_pos+1)%(BSP_UART1_DMA_RX.buf_size);						
					BSP_UART1_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART1_RX_BUF_MODE==0)
					    BSP_USART1_RX_USR_CALL(res);
					#endif
					#if(BSP_UART1_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART1_RX,&res,1);
					#endif
				}			
			}		
		#endif	
		
	}

    
    //-------接收中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART1_Handler, UART_IT_RXNE)!=RESET)     //是否使能
	)  
	{
		unsigned char res=0;        
		res=USART1->DR;   //读取数据
		#if(BSP_UART1_RX_DMA_EN==0)   //不使用DMA方式接收数据
			#if(BSP_UART1_RX_BUF_MODE==0)   //不使用环形缓冲区
				//----在此处添加用户处理函数---
				BSP_USART1_RX_USR_CALL(res);

			#endif
			#if(BSP_UART1_RX_BUF_MODE==1)   //使用环形缓冲区
				//----在此处添加环形缓冲区操作函数---				
				ringbuf_write(&BSP_UART1_RX,&res,1);
			#endif		
		#endif
		
	}
	//----发送完成中断-----
#if(BSP_UART1_TX_DMA_EN==2)
	
	/* UART in mode Transmitter end --------------------------------------------*/
	if (
		(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART1_Handler, UART_IT_TC)!=RESET)     //是否使能		
	)
	{
		/* Disable the UART Transmit Complete Interrupt */
		__HAL_UART_DISABLE_IT(&UART1_Handler, UART_IT_TC);


		#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
			/*Call registered Tx complete callback*/
			huart->TxCpltCallback(huart);
		#else
			/*Call legacy weak Tx complete callback*/
			HAL_UART_TxCpltCallback(&UART1_Handler);
		#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
		
		/* Tx process is ended, restore huart->gState to Ready */
		UART1_Handler.gState = HAL_UART_STATE_READY;		
		
	}	
	
#endif	
			

} 

#endif
#ifdef BSP_UART2_EN
//串口2中断服务程序
void USART2_IRQHandler(void)                	
{ 
    /* UART parity error interrupt occurred ------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_PE) != RESET)  //奇偶校验错误中断
    { 
        __HAL_UART_CLEAR_PEFLAG(&UART2_Handler);
    }
    /* UART frame error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_FE)!= RESET)  //帧错误中断
    { 
        __HAL_UART_CLEAR_FEFLAG(&UART2_Handler);
    }
    /* UART noise error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_NE)!= RESET)  //噪音错误中断
    { 
        __HAL_UART_CLEAR_NEFLAG(&UART2_Handler);
    }
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_ORE)!= RESET)  //上溢错误中断
    { 
        __HAL_UART_CLEAR_OREFLAG(&UART2_Handler);
    } 
	
    //-------接收空闲中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_IDLE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART2_Handler, UART_IT_IDLE)!=RESET)     //是否使能
	)  
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		__HAL_UART_CLEAR_IDLEFLAG(&UART2_Handler); 	  //清空闲标志	
		#if(BSP_UART2_RX_DMA_EN==2)   //使用DMA方式加空闲中断方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART2_DMA_RX.buf_size-__HAL_DMA_GET_COUNTER(UART2_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART2_DMA_RX.read_pos)
			{
				BSP_UART2_DMA_RX.read_len=dma_rx_dl-BSP_UART2_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART2_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART2_DMA_RX.read_len>0)
			{
				while(BSP_UART2_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART2_DMA_RX.buf[BSP_UART2_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART2_DMA_RX.read_pos=(BSP_UART2_DMA_RX.read_pos+1)%(BSP_UART2_DMA_RX.buf_size);						
					BSP_UART2_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART2_RX_BUF_MODE==0)
					    BSP_USART2_RX_USR_CALL(res);
					#endif
					#if(BSP_UART2_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART2_RX,&res,1);
					#endif
				}			
			}		
		#endif	
		
	}

    //-------接收中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART2_Handler, UART_IT_RXNE)!=RESET)     //是否使能
	)  
	{
		unsigned char res=0;        
		res=USART2->DR;   //读取数据
		#if(BSP_UART2_RX_DMA_EN==0)   //不使用DMA方式接收数据
			#if(BSP_UART2_RX_BUF_MODE==0)   //不使用环形缓冲区
				//----在此处添加用户处理函数---
				BSP_USART2_RX_USR_CALL(res);

			#endif
			#if(BSP_UART2_RX_BUF_MODE==1)   //使用环形缓冲区
				//----在此处添加环形缓冲区操作函数---				
				ringbuf_write(&BSP_UART2_RX,&res,1);
			#endif		
		#endif	
	}
	//----发送完成中断-----
#if(BSP_UART2_TX_DMA_EN==2)
	
	/* UART in mode Transmitter end --------------------------------------------*/
	if (
		(__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_TC)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART2_Handler, UART_IT_TC)!=RESET)     //是否使能		
	)
	{
		/* Disable the UART Transmit Complete Interrupt */
		__HAL_UART_DISABLE_IT(&UART2_Handler, UART_IT_TC);


		#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
			/*Call registered Tx complete callback*/
			huart->TxCpltCallback(huart);
		#else
			/*Call legacy weak Tx complete callback*/
			HAL_UART_TxCpltCallback(&UART2_Handler);
		#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
		
		/* Tx process is ended, restore huart->gState to Ready */
		UART2_Handler.gState = HAL_UART_STATE_READY;		
		
	}	
	
#endif	
} 
#endif
#ifdef BSP_UART3_EN
//串口3中断服务程序
void USART3_IRQHandler(void)                	
{ 
    /* UART parity error interrupt occurred ------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART3_Handler, UART_FLAG_PE) != RESET)  //奇偶校验错误中断
    { 
        __HAL_UART_CLEAR_PEFLAG(&UART3_Handler);
    }
    /* UART frame error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART3_Handler, UART_FLAG_FE)!= RESET)  //帧错误中断
    { 
        __HAL_UART_CLEAR_FEFLAG(&UART3_Handler);
    }
    /* UART noise error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART3_Handler, UART_FLAG_NE)!= RESET)  //噪音错误中断
    { 
        __HAL_UART_CLEAR_NEFLAG(&UART3_Handler);
    }
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART3_Handler, UART_FLAG_ORE)!= RESET)  //上溢错误中断
    { 
        __HAL_UART_CLEAR_OREFLAG(&UART3_Handler);
    }  
    //-------接收空闲中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_IDLE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART3_Handler, UART_IT_IDLE)!=RESET)     //是否使能
	)  
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		__HAL_UART_CLEAR_IDLEFLAG(&UART3_Handler); 	  //清空闲标志	
		#if(BSP_UART3_RX_DMA_EN==2)   //使用DMA方式加空闲中断方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART3_DMA_RX.buf_size-__HAL_DMA_GET_COUNTER(UART3_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART3_DMA_RX.read_pos)
			{
				BSP_UART3_DMA_RX.read_len=dma_rx_dl-BSP_UART3_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART3_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART3_DMA_RX.read_len>0)
			{
				while(BSP_UART3_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART3_DMA_RX.buf[BSP_UART3_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART3_DMA_RX.read_pos=(BSP_UART3_DMA_RX.read_pos+1)%(BSP_UART3_DMA_RX.buf_size);						
					BSP_UART3_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART3_RX_BUF_MODE==0)
					    BSP_USART3_RX_USR_CALL(res);
					#endif
					#if(BSP_UART3_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART3_RX,&res,1);
					#endif
				}			
			}		
		#endif	
		
	}
	
    //-------接收中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_RXNE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART3_Handler, UART_IT_RXNE)!=RESET)     //是否使能
		)  
	{
		unsigned char res=0;        
		res=USART3->DR;   //读取数据
		#if(BSP_UART3_RX_DMA_EN==0)   //不使用DMA方式接收数据
			#if(BSP_UART3_RX_BUF_MODE==0)   //不使用环形缓冲区
				//----在此处添加用户处理函数---
				BSP_USART3_RX_USR_CALL(res);

			#endif
			#if(BSP_UART3_RX_BUF_MODE==1)   //使用环形缓冲区
				//----在此处添加环形缓冲区操作函数---				
				ringbuf_write(&BSP_UART3_RX,&res,1);
			#endif		
		#endif
	}
	
	//----发送完成中断-----
#if(BSP_UART3_TX_DMA_EN==2)
	
	/* UART in mode Transmitter end --------------------------------------------*/
	if (
		(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_TC)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART3_Handler, UART_IT_TC)!=RESET)     //是否使能		
	)
	{
		/* Disable the UART Transmit Complete Interrupt */
		__HAL_UART_DISABLE_IT(&UART3_Handler, UART_IT_TC);


		#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
			/*Call registered Tx complete callback*/
			huart->TxCpltCallback(huart);
		#else
			/*Call legacy weak Tx complete callback*/
			HAL_UART_TxCpltCallback(&UART3_Handler);
		#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
		
		/* Tx process is ended, restore huart->gState to Ready */
		UART3_Handler.gState = HAL_UART_STATE_READY;		
		
	}	
	
#endif
} 
 
#endif
#ifdef BSP_UART4_EN
//串口4中断服务程序
void UART4_IRQHandler(void)                	
{ 
    /* UART parity error interrupt occurred ------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART4_Handler, UART_FLAG_PE) != RESET)  //奇偶校验错误中断
    { 
        __HAL_UART_CLEAR_PEFLAG(&UART4_Handler);
    }
    /* UART frame error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART4_Handler, UART_FLAG_FE)!= RESET)  //帧错误中断
    { 
        __HAL_UART_CLEAR_FEFLAG(&UART4_Handler);
    }
    /* UART noise error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART4_Handler, UART_FLAG_NE)!= RESET)  //噪音错误中断
    { 
        __HAL_UART_CLEAR_NEFLAG(&UART4_Handler);
    }
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART4_Handler, UART_FLAG_ORE)!= RESET)  //上溢错误中断
    { 
        __HAL_UART_CLEAR_OREFLAG(&UART4_Handler);
    }   
    //-------接收空闲中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART4_Handler,UART_FLAG_IDLE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART4_Handler, UART_IT_IDLE)!=RESET)     //是否使能
	)  
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		__HAL_UART_CLEAR_IDLEFLAG(&UART4_Handler); 	  //清空闲标志	
		#if(BSP_UART4_RX_DMA_EN==2)   //使用DMA方式加空闲中断方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART4_DMA_RX.buf_size-__HAL_DMA_GET_COUNTER(UART4_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART4_DMA_RX.read_pos)
			{
				BSP_UART4_DMA_RX.read_len=dma_rx_dl-BSP_UART4_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART4_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART4_DMA_RX.read_len>0)
			{
				while(BSP_UART4_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART4_DMA_RX.buf[BSP_UART4_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART4_DMA_RX.read_pos=(BSP_UART4_DMA_RX.read_pos+1)%(BSP_UART4_DMA_RX.buf_size);						
					BSP_UART4_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART4_RX_BUF_MODE==0)
					    BSP_USART4_RX_USR_CALL(res);
					#endif
					#if(BSP_UART4_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART4_RX,&res,1);
					#endif
				}			
			}		
		#endif	
		
	}	
    //-------接收中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART4_Handler,UART_FLAG_RXNE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART4_Handler, UART_IT_RXNE)!=RESET)     //是否使能
	)  
	{
		unsigned char res=0;        
		res=UART4->DR;   //读取数据
		#if(BSP_UART4_RX_DMA_EN==0)   //不使用DMA方式接收数据
			#if(BSP_UART4_RX_BUF_MODE==0)   //不使用环形缓冲区
				//----在此处添加用户处理函数---
				BSP_USART4_RX_USR_CALL(res);

			#endif
			#if(BSP_UART4_RX_BUF_MODE==1)   //使用环形缓冲区
				//----在此处添加环形缓冲区操作函数---				
				ringbuf_write(&BSP_UART4_RX,&res,1);
			#endif		
		#endif
	}
	//----发送完成中断-----
#if(BSP_UART4_TX_DMA_EN==2)
	
	/* UART in mode Transmitter end --------------------------------------------*/
	if (
		(__HAL_UART_GET_FLAG(&UART4_Handler,UART_FLAG_TC)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART4_Handler, UART_IT_TC)!=RESET)     //是否使能		
	)
	{
		/* Disable the UART Transmit Complete Interrupt */
		__HAL_UART_DISABLE_IT(&UART4_Handler, UART_IT_TC);


		#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
			/*Call registered Tx complete callback*/
			huart->TxCpltCallback(huart);
		#else
			/*Call legacy weak Tx complete callback*/
			HAL_UART_TxCpltCallback(&UART4_Handler);
		#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
		
		/* Tx process is ended, restore huart->gState to Ready */
		UART4_Handler.gState = HAL_UART_STATE_READY;		
		
	}	
	
#endif
} 
 
#endif
#ifdef BSP_UART5_EN
//串口5中断服务程序
void UART5_IRQHandler(void)                	
{ 
    /* UART parity error interrupt occurred ------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART5_Handler, UART_FLAG_PE) != RESET)  //奇偶校验错误中断
    { 
        __HAL_UART_CLEAR_PEFLAG(&UART5_Handler);
    }
    /* UART frame error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART5_Handler, UART_FLAG_FE)!= RESET)  //帧错误中断
    { 
        __HAL_UART_CLEAR_FEFLAG(&UART5_Handler);
    }
    /* UART noise error interrupt occurred -------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART5_Handler, UART_FLAG_NE)!= RESET)  //噪音错误中断
    { 
        __HAL_UART_CLEAR_NEFLAG(&UART5_Handler);
    }
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if(__HAL_UART_GET_FLAG(&UART5_Handler, UART_FLAG_ORE)!= RESET)  //上溢错误中断
    { 
        __HAL_UART_CLEAR_OREFLAG(&UART5_Handler);
    }   
    //-------接收空闲中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART5_Handler,UART_FLAG_IDLE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART5_Handler, UART_IT_IDLE)!=RESET)     //是否使能
	)  
	{
		__HAL_UART_CLEAR_IDLEFLAG(&UART5_Handler); 	  //清空闲标志		
	}
   	
    //-------接收中断-------
	if(
		(__HAL_UART_GET_FLAG(&UART5_Handler,UART_FLAG_RXNE)!=RESET)           //标志判断
		&&(__HAL_UART_GET_IT_SOURCE(&UART5_Handler, UART_IT_RXNE)!=RESET)     //是否使能
	)  
	{
		unsigned char res=0;        
		res=UART5->DR;   //读取数据

		#if(BSP_UART5_RX_BUF_MODE==0)   //不使用环形缓冲区
			//----在此处添加用户处理函数---
			BSP_USART5_RX_USR_CALL(res);

		#endif
		#if(BSP_UART5_RX_BUF_MODE==1)   //使用环形缓冲区
			//----在此处添加环形缓冲区操作函数---				
			ringbuf_write(&BSP_UART5_RX,&res,1);
		#endif		

	}

} 
#endif

/*****************串口接收回调函数*********************/
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
/*
 *函数名：HAL_UART_RxHalfCpltCallback
 *描述  ：串口接收一半回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_UART1_EN	
	//-----串口1接收一半回调函数----
	if(huart->Instance==USART1)//如果是串口1
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART1_RX_DMA_EN==1)||(BSP_UART1_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART1_DMA_RX.buf_half_size;//-__HAL_DMA_GET_COUNTER(UART1_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART1_DMA_RX.read_pos)
			{
				BSP_UART1_DMA_RX.read_len=dma_rx_dl-BSP_UART1_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART1_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART1_DMA_RX.read_len>0)
			{
				while(BSP_UART1_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART1_DMA_RX.buf[BSP_UART1_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART1_DMA_RX.read_pos=(BSP_UART1_DMA_RX.read_pos+1)%(BSP_UART1_DMA_RX.buf_size);						
					BSP_UART1_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART1_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
					    BSP_USART1_RX_USR_CALL(res);
					#endif
					#if(BSP_UART1_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART1_RX,&res,1);
					#endif
					
				}			
			}		
		#endif		
	}
	#endif
	#ifdef BSP_UART2_EN	
	//-----串口2接收一半回调函数----
	if(huart->Instance==USART2)//如果是串口2
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART2_RX_DMA_EN==1)||(BSP_UART2_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART2_DMA_RX.buf_half_size;//-__HAL_DMA_GET_COUNTER(UART2_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART2_DMA_RX.read_pos)
			{
				BSP_UART2_DMA_RX.read_len=dma_rx_dl-BSP_UART2_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART2_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART2_DMA_RX.read_len>0)
			{
				while(BSP_UART2_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART2_DMA_RX.buf[BSP_UART2_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART2_DMA_RX.read_pos=(BSP_UART2_DMA_RX.read_pos+1)%(BSP_UART2_DMA_RX.buf_size);						
					BSP_UART2_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART2_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
					    BSP_USART2_RX_USR_CALL(res);
					#endif
					#if(BSP_UART2_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART2_RX,&res,1);
					#endif
					
				}			
			}		
		#endif			
	}
	#endif
	#ifdef BSP_UART3_EN	
	//-----串口3接收一半回调函数----
	if(huart->Instance==USART3)//如果是串口3
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART3_RX_DMA_EN==1)||(BSP_UART3_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART3_DMA_RX.buf_half_size;//-__HAL_DMA_GET_COUNTER(UART3_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART3_DMA_RX.read_pos)
			{
				BSP_UART3_DMA_RX.read_len=dma_rx_dl-BSP_UART3_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART3_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART3_DMA_RX.read_len>0)
			{
				while(BSP_UART3_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART3_DMA_RX.buf[BSP_UART3_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART3_DMA_RX.read_pos=(BSP_UART3_DMA_RX.read_pos+1)%(BSP_UART3_DMA_RX.buf_size);						
					BSP_UART3_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART3_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
					    BSP_USART3_RX_USR_CALL(res);
					#endif
					#if(BSP_UART3_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART3_RX,&res,1);
					#endif
					
				}			
			}		
		#endif			
	}
	#endif
	#ifdef BSP_UART4_EN	
	//-----串口4接收一半回调函数----
	if(huart->Instance==UART4)//如果是串口4
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART4_RX_DMA_EN==1)||(BSP_UART4_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART4_DMA_RX.buf_half_size;//-__HAL_DMA_GET_COUNTER(UART4_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART4_DMA_RX.read_pos)
			{
				BSP_UART4_DMA_RX.read_len=dma_rx_dl-BSP_UART4_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART4_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART4_DMA_RX.read_len>0)
			{
				while(BSP_UART4_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART4_DMA_RX.buf[BSP_UART4_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART4_DMA_RX.read_pos=(BSP_UART4_DMA_RX.read_pos+1)%(BSP_UART4_DMA_RX.buf_size);						
					BSP_UART4_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART4_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
					    BSP_USART4_RX_USR_CALL(res);
					#endif
					#if(BSP_UART4_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART4_RX,&res,1);
					#endif
					
				}			
			}		
		#endif			
	}	
	#endif

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
/*
 *函数名：HAL_UART_RxCpltCallback
 *描述  ：串口接收完成回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_UART1_EN	
	//-----串口1接收完成回调函数-----
	if(huart->Instance==USART1)//如果是串口1
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART1_RX_DMA_EN==1)||(BSP_UART1_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART1_DMA_RX.buf_size;//-__HAL_DMA_GET_COUNTER(UART1_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART1_DMA_RX.read_pos)
			{
				BSP_UART1_DMA_RX.read_len=dma_rx_dl-BSP_UART1_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART1_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART1_DMA_RX.read_len>0)
			{
				while(BSP_UART1_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART1_DMA_RX.buf[BSP_UART1_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART1_DMA_RX.read_pos=(BSP_UART1_DMA_RX.read_pos+1)%(BSP_UART1_DMA_RX.buf_size);						
					BSP_UART1_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART1_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
						BSP_USART1_RX_USR_CALL(res);
					#endif
					#if(BSP_UART1_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART1_RX,&res,1);
					#endif

				}			
			}		
		#endif	
	}
	#endif
	#ifdef BSP_UART2_EN	
	//-----串口2接收完成回调函数-----
	if(huart->Instance==USART2)//如果是串口2
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART2_RX_DMA_EN==1)||(BSP_UART2_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART2_DMA_RX.buf_size;//-__HAL_DMA_GET_COUNTER(UART2_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART2_DMA_RX.read_pos)
			{
				BSP_UART2_DMA_RX.read_len=dma_rx_dl-BSP_UART2_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART2_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART2_DMA_RX.read_len>0)
			{
				while(BSP_UART2_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART2_DMA_RX.buf[BSP_UART2_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART2_DMA_RX.read_pos=(BSP_UART2_DMA_RX.read_pos+1)%(BSP_UART2_DMA_RX.buf_size);						
					BSP_UART2_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART2_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
						BSP_USART2_RX_USR_CALL(res);
					#endif
					#if(BSP_UART2_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART2_RX,&res,1);
					#endif

				}			
			}		
		#endif			
	}
	#endif
	#ifdef BSP_UART3_EN
	//-----串口3接收完成回调函数-----
	if(huart->Instance==USART3)//如果是串口3
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART3_RX_DMA_EN==1)||(BSP_UART3_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART3_DMA_RX.buf_size;//-__HAL_DMA_GET_COUNTER(UART3_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART3_DMA_RX.read_pos)
			{
				BSP_UART3_DMA_RX.read_len=dma_rx_dl-BSP_UART3_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART3_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART3_DMA_RX.read_len>0)
			{
				while(BSP_UART3_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART3_DMA_RX.buf[BSP_UART3_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART3_DMA_RX.read_pos=(BSP_UART3_DMA_RX.read_pos+1)%(BSP_UART3_DMA_RX.buf_size);						
					BSP_UART3_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART3_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
						BSP_USART3_RX_USR_CALL(res);
					#endif
					#if(BSP_UART3_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART3_RX,&res,1);
					#endif

				}			
			}		
		#endif		
	}	
	#endif
	#ifdef BSP_UART4_EN	
	//-----串口4接收完成回调函数-----
	if(huart->Instance==UART4)//如果是串口4
	{
		unsigned short int dma_rx_dl=0; //DMA接收缓冲区中存在的数据量
		#if((BSP_UART4_RX_DMA_EN==1)||(BSP_UART4_RX_DMA_EN==2))   //使用DMA方式接收
			//----获取需要提取的数据的数量--
			dma_rx_dl=BSP_UART4_DMA_RX.buf_size;//-__HAL_DMA_GET_COUNTER(UART4_Handler.hdmarx);
		    if(dma_rx_dl>BSP_UART4_DMA_RX.read_pos)
			{
				BSP_UART4_DMA_RX.read_len=dma_rx_dl-BSP_UART4_DMA_RX.read_pos;				
			}
			else
			{
				BSP_UART4_DMA_RX.read_len=0;  //正常情况不会出现，若出现说明有问题
			}
			//----对数据进行提取--
			if(BSP_UART4_DMA_RX.read_len>0)
			{
				while(BSP_UART4_DMA_RX.read_len)
				{
					unsigned char res=0;       //读到的数据					
					//---读数据---
					res=BSP_UART4_DMA_RX.buf[BSP_UART4_DMA_RX.read_pos];
					//----修改状态---					
					BSP_UART4_DMA_RX.read_pos=(BSP_UART4_DMA_RX.read_pos+1)%(BSP_UART4_DMA_RX.buf_size);						
					BSP_UART4_DMA_RX.read_len--;					
					//---处理数据--
					#if(BSP_UART4_RX_BUF_MODE==0)
						/******以下可以添加用户程序*******/
						BSP_USART4_RX_USR_CALL(res);
					#endif
					#if(BSP_UART4_RX_BUF_MODE==1)
						//----将接收到的数据提取到串口环形缓冲区内---
						ringbuf_write(&BSP_UART4_RX,&res,1);
					#endif

				}			
			}		
		#endif			
	}	
	#endif

}

/*****************串口发送回调函数*********************/
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{
/*
 *函数名：HAL_UART_TxHalfCpltCallback
 *描述  ：串口发送一半回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_UART1_EN	
	//-----串口1发送一半回调函数----
	if(huart->Instance==USART1)//如果是串口1
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART1_TX_DMA_EN==2)	    
		BSP_UART1_TX_MARK=2;   //发送完成一半
				
		#endif			
	}
	#endif
	#ifdef BSP_UART2_EN	
	//-----串口2发送一半回调函数----
	if(huart->Instance==USART2)//如果是串口2
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART2_TX_DMA_EN==2)	    
		BSP_UART2_TX_MARK=2;   //发送完成一半				
				
		#endif			
	}
	#endif
	#ifdef BSP_UART3_EN	
	//-----串口3发送一半回调函数----
	if(huart->Instance==USART3)//如果是串口3
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART3_TX_DMA_EN==2)	    
		BSP_UART3_TX_MARK=2;   //发送完成一半				
				
		#endif			
	}
	#endif
	#ifdef BSP_UART4_EN	
	//-----串口4发送一半回调函数----
	if(huart->Instance==UART4)//如果是串口4
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART4_TX_DMA_EN==2)	    
		BSP_UART4_TX_MARK=2;   //发送完成一半				
				
		#endif			
	}	
	#endif
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
/*
 *函数名：HAL_UART_TxCpltCallback
 *描述  ：串口发送完成回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_UART1_EN	
	//-----串口1发送完成回调函数-----
	if(huart->Instance==USART1)//如果是串口1
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART1_TX_DMA_EN==2)	   
		BSP_UART1_TX_MARK=3;   //发送完成	
		HAL_UART_AbortTransmit(&UART1_Handler);      //传输完成以后关闭串口DMA	
			#if(BSP_UART1_TX_DISABLE_EN==1)
			USART1->CR1&=(~UART_MODE_TX);   //禁止发送 
			#endif
		#endif			
	}
	#endif
	#ifdef BSP_UART2_EN
	//-----串口2发送完成回调函数-----
	if(huart->Instance==USART2)//如果是串口2
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART2_TX_DMA_EN==2)	   
		BSP_UART2_TX_MARK=3;   //发送完成		
		HAL_UART_AbortTransmit(&UART2_Handler);      //传输完成以后关闭串口DMA	
			#if(BSP_UART2_TX_DISABLE_EN==1)		
			USART2->CR1&=(~UART_MODE_TX);   //禁止发送 
			#endif		
		#endif			
	}
	#endif
	#ifdef BSP_UART3_EN
	//-----串口3发送完成回调函数-----
	if(huart->Instance==USART3)//如果是串口3
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART3_TX_DMA_EN==2)	   
		BSP_UART3_TX_MARK=3;   //发送完成		
		HAL_UART_AbortTransmit(&UART3_Handler);      //传输完成以后关闭串口DMA
			#if(BSP_UART3_TX_DISABLE_EN==1)		
			USART3->CR1&=(~UART_MODE_TX);   //禁止发送 		
			#endif		
		#endif			
	}
	#endif
	#ifdef BSP_UART4_EN
	//-----串口4发送完成回调函数-----
	if(huart->Instance==UART4)//如果是串口4
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_UART4_TX_DMA_EN==2)	   
		BSP_UART4_TX_MARK=3;   //发送完成		
		HAL_UART_AbortTransmit(&UART4_Handler);      //传输完成以后关闭串口DMA	
			#if(BSP_UART4_TX_DISABLE_EN==1)		
			UART4->CR1&=(~UART_MODE_TX);   //禁止发送 	
			#endif		
		#endif			
	}	
	#endif
}

/*****************串口传输出错回调函数*********************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	
	
	
	
	
}

/*****************环形缓冲区数据集中处理函数****************/

#if(BSP_UART1_RX_BUF_MODE==1)   //使用环形缓冲区
	void BSP_USART1_RX_RINGBUF_PROCESS_TASK(unsigned char pl)                	
	{ 
	/*
	 *函数名：BSP_USART1_RINGBUF_PROCESS_TASK
	 *描述  ：串口1环形缓冲区处理函数
	 *输入  ：处理频率
	 *输出  ：无 
	 *调用  ：外部调用
	*/ 	  
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据
		if(pl==1)
		{
			//--获取数据个数---
			d_l=ringbuf_get_len(&BSP_UART1_RX);
			if(d_l>0)
			{
				while(d_l)
				{
					//---读数据---
					if(ringbuf_read(&BSP_UART1_RX,&res)==0)
					{
						/******以下可以添加用户程序*******/
						BSP_USART1_RX_USR_CALL(res);						
					}
					else
					{
						break;
					}
					d_l--;
				}			
			}
		}
		
	}
#endif	

#if(BSP_UART2_RX_BUF_MODE==1)   //使用环形缓冲区
	void BSP_USART2_RX_RINGBUF_PROCESS_TASK(unsigned char pl)                	
	{ 
	/*
	 *函数名：BSP_USART2_RINGBUF_PROCESS_TASK
	 *描述  ：串口2环形缓冲区处理函数
	 *输入  ：处理频率
	 *输出  ：无 
	 *调用  ：外部调用
	*/ 	  
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据
		if(pl==1)
		{
			//--获取数据个数---
			d_l=ringbuf_get_len(&BSP_UART2_RX);
			if(d_l>0)
			{
				while(d_l)
				{
					//---读数据---
					if(ringbuf_read(&BSP_UART2_RX,&res)==0)
					{
						/******以下可以添加用户程序*******/
						BSP_USART2_RX_USR_CALL(res);						
					}
					else
					{
						break;
					}
					d_l--;
				}			
			}
		}
		
	}
#endif	

#if(BSP_UART3_RX_BUF_MODE==1)   //使用环形缓冲区
	void BSP_USART3_RX_RINGBUF_PROCESS_TASK(unsigned char pl)                	
	{ 
	/*
	 *函数名：BSP_USART3_RINGBUF_PROCESS_TASK
	 *描述  ：串口3环形缓冲区处理函数
	 *输入  ：处理频率
	 *输出  ：无 
	 *调用  ：外部调用
	*/ 	  
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据
		if(pl==1)
		{
			//--获取数据个数---
			d_l=ringbuf_get_len(&BSP_UART3_RX);
			if(d_l>0)
			{
				while(d_l)
				{
					//---读数据---
					if(ringbuf_read(&BSP_UART3_RX,&res)==0)
					{
						/******以下可以添加用户程序*******/
						BSP_USART3_RX_USR_CALL(res);						
					}
					else
					{
						break;
					}
					d_l--;
				}			
			}
		}
		
	}
#endif	

#if(BSP_UART4_RX_BUF_MODE==1)   //使用环形缓冲区
	void BSP_USART4_RX_RINGBUF_PROCESS_TASK(unsigned char pl)                	
	{ 
	/*
	 *函数名：BSP_USART4_RINGBUF_PROCESS_TASK
	 *描述  ：串口4环形缓冲区处理函数
	 *输入  ：处理频率
	 *输出  ：无 
	 *调用  ：外部调用
	*/ 	  
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据
		if(pl==1)
		{
			//--获取数据个数---
			d_l=ringbuf_get_len(&BSP_UART4_RX);
			if(d_l>0)
			{
				while(d_l)
				{
					//---读数据---
					if(ringbuf_read(&BSP_UART4_RX,&res)==0)
					{
						/******以下可以添加用户程序*******/
						BSP_USART4_RX_USR_CALL(res);						
					}
					else
					{
						break;
					}
					d_l--;
				}			
			}
		}
		
	}
#endif	

#if(BSP_UART5_RX_BUF_MODE==1)   //使用环形缓冲区
	void BSP_USART5_RX_RINGBUF_PROCESS_TASK(unsigned char pl)                	
	{ 
	/*
	 *函数名：BSP_USART5_RINGBUF_PROCESS_TASK
	 *描述  ：串口5环形缓冲区处理函数
	 *输入  ：处理频率
	 *输出  ：无 
	 *调用  ：外部调用
	*/ 	  
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据
		if(pl==1)
		{
			//--获取数据个数---
			d_l=ringbuf_get_len(&BSP_UART5_RX);
			if(d_l>0)
			{
				while(d_l)
				{
					//---读数据---
					if(ringbuf_read(&BSP_UART5_RX,&res)==0)
					{
						/******以下可以添加用户程序*******/
						BSP_USART5_RX_USR_CALL(res);						
					}
					else
					{
						break;
					}
					d_l--;
				}			
			}
		}
		
	}
#endif	
/*****************************各串口功能函数****************************/
#ifdef BSP_UART1_EN
void BSP_USART1_RX_USR_CALL(unsigned char res)
{
/*
 *函数名：BSP_USART1_RX_USR_CALL
 *描述  : 当串口接收到新的数据调用的函数，
	      当串口接收未使用环形缓冲区时此函数需简短
 *输入  ：数据
 *输出  ：
 *调用  ：外部调用
*/  
	/******以下可以添加用户程序*******/
//	USART1->DR =res;
//	BSP_SYSTICK_DELAY_MS(10);	
	FUNC_PC_INTERFACE_COM_UART_RX_ISR(&FUNC_PC_INTERFACE_COM1,res);	
}	

#endif	


#ifdef BSP_UART2_EN	
void BSP_USART2_RX_USR_CALL(unsigned char res)
{
/*
 *函数名：BSP_USART2_RX_USR_CALL
 *描述  : 当串口接收到新的数据调用的函数，
	      当串口接收未使用环形缓冲区时此函数需简短
 *输入  ：数据
 *输出  ：
 *调用  ：外部调用
*/  
	/******以下可以添加用户程序*******/
//	USART2->DR =res;
//	FUNC_DELAY_MS(10);	
//	FUNC_INTERFACE_COM_UART_RX_ISR(&FUNC_INTERFACE_COM1,res);
//	FUNC_IAP_INTERFACE_COM_UART2_RX_IRQ(res);   
}		

#endif	


#ifdef BSP_UART3_EN	
void BSP_USART3_RX_USR_CALL(unsigned char res)
{
/*
 *函数名：BSP_USART3_RX_USR_CALL
 *描述  : 当串口接收到新的数据调用的函数，
	      当串口接收未使用环形缓冲区时此函数需简短
 *输入  ：数据
 *输出  ：
 *调用  ：外部调用
*/  
	/******以下可以添加用户程序*******/
//	USART3->DR =res;
//	FUNC_DELAY_MS(10);	
//	FUNC_XY_MBD07A_CON_UART_RX_ISR(&BLUE_MODULE3,res);		
}	

#endif	


#ifdef BSP_UART4_EN
void BSP_USART4_RX_USR_CALL(unsigned char res)
{
/*
 *函数名：BSP_USART4_RX_USR_CALL
 *描述  : 当串口接收到新的数据调用的函数，
	      当串口接收未使用环形缓冲区时此函数需简短
 *输入  ：数据
 *输出  ：
 *调用  ：外部调用
*/  
	/******以下可以添加用户程序*******/
//	UART4->DR =res;
//	FUNC_DELAY_MS(10);	
//	FUNC_XY_MBD07A_CON_UART_RX_ISR(&BLUE_MODULE4,res);		
}	

#endif	


#ifdef BSP_UART5_EN
void BSP_USART5_RX_USR_CALL(unsigned char res)
{
/*
 *函数名：BSP_USART5_RX_USR_CALL
 *描述  : 当串口接收到新的数据调用的函数，
	      当串口接收未使用环形缓冲区时此函数需简短
 *输入  ：数据
 *输出  ：
 *调用  ：外部调用
*/  
	/******以下可以添加用户程序*******/
	UART5->DR =res;
//	FUNC_DELAY_MS(10);	
	
}	

#endif	


#ifdef BSP_UART1_EN

void BSP_USART1_SEND_BUF(unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：BSP_USART1_SEND_BUF
 *描述  ：硬件串口1发送一个数据缓冲区
 *输入  ：数据指针，数据长度
 *输出  ：
 *调用  ：外部调用
*/  

#if(BSP_UART1_TX_DMA_EN==0)		//不使用DMA方式发送 
	unsigned short int i=0;
    __HAL_UART_DISABLE_IT(&UART1_Handler, USART_IT_TC);     //禁止发送中断
    USART1->CR1|=UART_MODE_TX;   //允许发送    
    for(i=0;i<b_l;i++)    //发送指定长度的数据
    {
        while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
        {
        }                   
        USART1->DR=*b;  //发送1个字节         
        b++;
    } 
    while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
    }              
    while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
    }  
	#if(BSP_UART1_TX_DISABLE_EN==1)
    USART1->CR1&=(~UART_MODE_TX);   //禁止发送    //某些应用不能禁止发送，视情况而定 
	#endif
#endif	
	

#if(BSP_UART1_TX_DMA_EN==1)	   //DMA方式发送（不开DMA传输中断）
	USART1->CR1|=UART_MODE_TX;   //允许发送
	//开启 DMA 传输
	HAL_DMA_Start(UART1_Handler.hdmatx,(uint32_t)b,(uint32_t)(&(UART1_Handler.Instance->DR)), b_l);
	UART1_Handler.Instance->CR3 |= USART_CR3_DMAT;//使能串口 DMA 发送
    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_TC);	
//	HAL_UART_Transmit_DMA(&UART1_Handler,b,b_l);//启动传输
	
	//等待传输完成           
    while(1)   //等待tsr中接到数据发送出去
    {
		if(__HAL_DMA_GET_FLAG(UART1_Handler.hdmatx,DMA_FLAG_TC4))//等待DMA1通道4传输完成
		{
			__HAL_DMA_CLEAR_FLAG(UART1_Handler.hdmatx,DMA_FLAG_TC4);//清除DMA1通道4传输完成标志
			HAL_UART_AbortTransmit(&UART1_Handler);      //传输完成以后关闭串口DMA	
			break;
		}	
	}
    while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
			
	}		
    while(__HAL_UART_GET_FLAG(&UART1_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
	
	}		
	#if(BSP_UART1_TX_DISABLE_EN==1)
    USART1->CR1&=(~UART_MODE_TX);   //禁止发送    //某些应用不能禁止发送，视情况而定 
	#endif
//	__HAL_UART_CLEAR_FLAG(&UART1_Handler,USART_FLAG_TXE); 
//	__HAL_UART_CLEAR_FLAG(&UART1_Handler,USART_FLAG_TC); 		
#endif	
	
#if(BSP_UART1_TX_DMA_EN==2)	   //DMA方式发送（开DMA传输中断） 
	if(
		(BSP_UART1_TX_MARK==0)
		||(BSP_UART1_TX_MARK==3)
	)
	{
		USART1->CR1|=UART_MODE_TX;   //允许发送
		//开启 DMA 传输	
		HAL_UART_Transmit_DMA(&UART1_Handler,b,b_l);//启动传输,此函数中会开启相应的DMA传输中断
		//开始发送
		BSP_UART1_TX_MARK=1; 
	}	
#endif	
		
	
}







/**********发送一个字符串**************************/
void BSP_USART1_FA_STRING(unsigned char*str)
{
/*
 *函数名：BSP_USART1_FA_STRING
 *描述  ：通过串口发送一组字符串常数，不使用中断
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
    unsigned short int len=0;
    unsigned char *s=str;
    while((*s)!=0)    //当不等于空字符时发送数据
    {
        s++;  //指向下一字符          
        len++;
    }     
    BSP_USART1_SEND_BUF(str,len);    
}


#endif	


#ifdef BSP_UART2_EN

void BSP_USART2_SEND_BUF(unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：BSP_USART2_SEND_BUF
 *描述  ：硬件串口1发送一个数据缓冲区
 *输入  ：数据指针，数据长度
 *输出  ：
 *调用  ：外部调用
*/    


#if(BSP_UART2_TX_DMA_EN==0)		//不使用DMA方式发送 
    unsigned short int i=0;	
    __HAL_UART_DISABLE_IT(&UART2_Handler, USART_IT_TC);     //禁止发送中断
    USART2->CR1|=UART_MODE_TX;   //允许发送    
    for(i=0;i<b_l;i++)    //发送指定长度的数据
    {
        while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
        {
        }                   
        USART2->DR=*b;  //发送1个字节         
        b++;
    } 
    while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
    }              
    while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
    }                 
	#if(BSP_UART2_TX_DISABLE_EN==1)
    USART2->CR1&=(~UART_MODE_TX);   //禁止发送 
	#endif
#endif	
	

#if(BSP_UART2_TX_DMA_EN==1)	   //DMA方式发送（不开DMA传输中断）
	USART2->CR1|=UART_MODE_TX;   //允许发送
	//开启 DMA 传输
	HAL_DMA_Start(UART2_Handler.hdmatx,(uint32_t)b,(uint32_t)(&(UART2_Handler.Instance->DR)), b_l);
	UART2_Handler.Instance->CR3 |= USART_CR3_DMAT;//使能串口 DMA 发送
    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_UART_CLEAR_FLAG(&UART2_Handler, UART_FLAG_TC);	
//	HAL_UART_Transmit_DMA(&UART1_Handler,b,b_l);//启动传输
	
	//等待传输完成           
    while(1)   //等待tsr中接到数据发送出去
    {
		if(__HAL_DMA_GET_FLAG(UART2_Handler.hdmatx,DMA_FLAG_TC7))//等待DMA1通道7传输完成
		{
			__HAL_DMA_CLEAR_FLAG(UART2_Handler.hdmatx,DMA_FLAG_TC7);//清除DMA1通道7传输完成标志
			HAL_UART_AbortTransmit(&UART2_Handler);      //传输完成以后关闭串口DMA	
			break;
		}	
	}
    while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
		
	}		
    while(__HAL_UART_GET_FLAG(&UART2_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
		
	}	
	#if(BSP_UART2_TX_DISABLE_EN==1)
    USART2->CR1&=(~UART_MODE_TX);   //禁止发送 
	#endif
//	__HAL_UART_CLEAR_FLAG(&UART2_Handler,USART_FLAG_TXE); 
//	__HAL_UART_CLEAR_FLAG(&UART2_Handler,USART_FLAG_TC); 	
#endif	
	
#if(BSP_UART2_TX_DMA_EN==2)	   //DMA方式发送（开DMA传输中断）
	if(
		(BSP_UART2_TX_MARK==0)
		||(BSP_UART2_TX_MARK==3)
	)
	{
		USART2->CR1|=UART_MODE_TX;   //允许发送
		//开启 DMA 传输	
		HAL_UART_Transmit_DMA(&UART2_Handler,b,b_l);//启动传输,此函数中会开启相应的DMA传输中断
		//开始发送
		BSP_UART2_TX_MARK=1; 
	}		
#endif		
	
	
	
}



/**********发送一个字符串**************************/
void BSP_USART2_FA_STRING(unsigned char*str)
{
/*
 *函数名：BSP_USART2_FA_STRING
 *描述  ：通过串口发送一组字符串常数，不使用中断
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
    unsigned short int len=0;
    unsigned char *s=str;
    while((*s)!=0)    //当不等于空字符时发送数据
    {
        s++;  //指向下一字符          
        len++;
    }     
    BSP_USART2_SEND_BUF(str,len);    
}

#endif	


#ifdef BSP_UART3_EN

void BSP_USART3_SEND_BUF(unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：BSP_USART3_SEND_BUF
 *描述  ：硬件串口1发送一个数据缓冲区
 *输入  ：数据指针，数据长度
 *输出  ：
 *调用  ：外部调用
*/    

#if(BSP_UART3_TX_DMA_EN==0)		//不使用DMA方式发送 
	unsigned short int i=0;
    __HAL_UART_DISABLE_IT(&UART3_Handler, USART_IT_TC);     //禁止发送中断
    USART3->CR1|=UART_MODE_TX;   //允许发送    
    for(i=0;i<b_l;i++)    //发送指定长度的数据
    {
        while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
        {
        }                   
        USART3->DR=*b;  //发送1个字节         
        b++;
    } 
    while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
    }              
    while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
    }             
 
	#if(BSP_UART3_TX_DISABLE_EN==1)
    USART3->CR1&=(~UART_MODE_TX);   //禁止发送      //某些应用不能禁止发送，视情况而定  
	#endif
#endif	
	

#if(BSP_UART3_TX_DMA_EN==1)	   //DMA方式发送（不开DMA传输中断）
	USART3->CR1|=UART_MODE_TX;   //允许发送
	//开启 DMA 传输
	HAL_DMA_Start(UART3_Handler.hdmatx,(uint32_t)b,(uint32_t)(&(UART3_Handler.Instance->DR)), b_l);
	UART3_Handler.Instance->CR3 |= USART_CR3_DMAT;//使能串口 DMA 发送
    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_UART_CLEAR_FLAG(&UART3_Handler, UART_FLAG_TC);	
//	HAL_UART_Transmit_DMA(&UART1_Handler,b,b_l);//启动传输
	
	//等待传输完成           
    while(1)   //等待tsr中接到数据发送出去
    {
		if(__HAL_DMA_GET_FLAG(UART3_Handler.hdmatx,DMA_FLAG_TC2))//等待DMA1通道2传输完成
		{
			__HAL_DMA_CLEAR_FLAG(UART3_Handler.hdmatx,DMA_FLAG_TC2);//清除DMA1通道2传输完成标志
			HAL_UART_AbortTransmit(&UART3_Handler);      //传输完成以后关闭串口DMA	
			break;
		}	
	}
    while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
		
	}		
    while(__HAL_UART_GET_FLAG(&UART3_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
		
	}	
	#if(BSP_UART3_TX_DISABLE_EN==1)
    USART3->CR1&=(~UART_MODE_TX);   //禁止发送      //某些应用不能禁止发送，视情况而定  
	#endif
//	__HAL_UART_CLEAR_FLAG(&UART3_Handler,USART_FLAG_TXE); 
//	__HAL_UART_CLEAR_FLAG(&UART3_Handler,USART_FLAG_TC); 	
#endif	
	
#if(BSP_UART3_TX_DMA_EN==2)	   //DMA方式发送（开DMA传输中断） 
	if(
		(BSP_UART3_TX_MARK==0)
		||(BSP_UART3_TX_MARK==3)
	)
	{
		USART3->CR1|=UART_MODE_TX;   //允许发送
		//开启 DMA 传输	
		HAL_UART_Transmit_DMA(&UART3_Handler,b,b_l);//启动传输,此函数中会开启相应的DMA传输中断
		//开始发送
		BSP_UART3_TX_MARK=1; 
	}		
#endif		
	
		
	
	
}



/**********发送一个字符串**************************/
void BSP_USART3_FA_STRING(unsigned char*str)
{
/*
 *函数名：BSP_USART3_FA_STRING
 *描述  ：通过串口发送一组字符串常数，不使用中断
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
    unsigned short int len=0;
    unsigned char *s=str;
    while((*s)!=0)    //当不等于空字符时发送数据
    {
        s++;  //指向下一字符          
        len++;
    }     
    BSP_USART3_SEND_BUF(str,len);    
}

#endif	


#ifdef BSP_UART4_EN

void BSP_USART4_SEND_BUF(unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：BSP_USART4_SEND_BUF
 *描述  ：硬件串口4发送一个数据缓冲区
 *输入  ：数据指针，数据长度
 *输出  ：
 *调用  ：外部调用
*/            

#if(BSP_UART4_TX_DMA_EN==0)		//不使用DMA方式发送 
    unsigned short int i=0;	
    __HAL_UART_DISABLE_IT(&UART4_Handler, USART_IT_TC);     //禁止发送中断
    UART4->CR1|=UART_MODE_TX;   //允许发送    
    for(i=0;i<b_l;i++)    //发送指定长度的数据
    {
        while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
        {
        }                   
        UART4->DR=*b;  //发送1个字节         
        b++;
    } 
    while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
    }              
    while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
    }             
	
	#if(BSP_UART4_TX_DISABLE_EN==1)
    UART4->CR1&=(~UART_MODE_TX);   //禁止发送  //某些应用不能禁止发送，视情况而定 
	#endif
#endif	
	

#if(BSP_UART4_TX_DMA_EN==1)	   //DMA方式发送（不开DMA传输中断）
	UART4->CR1|=UART_MODE_TX;   //允许发送
	//开启 DMA 传输
	HAL_DMA_Start(UART4_Handler.hdmatx,(uint32_t)b,(uint32_t)(&(UART4_Handler.Instance->DR)), b_l);
	UART4_Handler.Instance->CR3 |= USART_CR3_DMAT;//使能串口 DMA 发送
    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_UART_CLEAR_FLAG(&UART4_Handler, UART_FLAG_TC);	
//	HAL_UART_Transmit_DMA(&UART1_Handler,b,b_l);//启动传输
	
	//等待传输完成           
    while(1)   //等待tsr中接到数据发送出去
    {
		if(__HAL_DMA_GET_FLAG(UART4_Handler.hdmatx,DMA_FLAG_TC5))//等待DMA2通道5传输完成
		{
			__HAL_DMA_CLEAR_FLAG(UART4_Handler.hdmatx,DMA_FLAG_TC5);//清除DMA2通道5传输完成标志
			HAL_UART_AbortTransmit(&UART4_Handler);      //传输完成以后关闭串口DMA	
			break;
		}	
	}
    while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
		
	}		
    while(__HAL_UART_GET_FLAG(&UART4_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
		
	}	
	#if(BSP_UART4_TX_DISABLE_EN==1)
    UART4->CR1&=(~UART_MODE_TX);   //禁止发送  //某些应用不能禁止发送，视情况而定 
	#endif
//	__HAL_UART_CLEAR_FLAG(&UART4_Handler,USART_FLAG_TXE); 
//	__HAL_UART_CLEAR_FLAG(&UART4_Handler,USART_FLAG_TC); 	
#endif	
	
#if(BSP_UART4_TX_DMA_EN==2)	   //DMA方式发送（开DMA传输中断） 
	if(
		(BSP_UART4_TX_MARK==0)
		||(BSP_UART4_TX_MARK==3)
	)
	{
		UART4->CR1|=UART_MODE_TX;   //允许发送
		//开启 DMA 传输	
		HAL_UART_Transmit_DMA(&UART4_Handler,b,b_l);//启动传输,此函数中会开启相应的DMA传输中断
		//开始发送
		BSP_UART4_TX_MARK=1; 
	}		
#endif		
	
		
	
		
	
	
}



/**********发送一个字符串**************************/
void BSP_USART4_FA_STRING(unsigned char*str)
{
/*
 *函数名：BSP_USART4_FA_STRING
 *描述  ：通过串口发送一组字符串常数，不使用中断
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
    unsigned short int len=0;
    unsigned char *s=str;
    while((*s)!=0)    //当不等于空字符时发送数据
    {
        s++;  //指向下一字符          
        len++;
    }     
    BSP_USART4_SEND_BUF(str,len);    
}

#endif



#ifdef BSP_UART5_EN

void BSP_USART5_SEND_BUF(unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：BSP_USART5_SEND_BUF
 *描述  ：硬件串口5发送一个数据缓冲区
 *输入  ：数据指针，数据长度
 *输出  ：
 *调用  ：外部调用
*/    
    unsigned short int i=0;
          
    __HAL_UART_DISABLE_IT(&UART5_Handler, USART_IT_TC);     //禁止发送中断
    UART5->CR1|=UART_MODE_TX;   //允许发送    
    for(i=0;i<b_l;i++)    //发送指定长度的数据
    {
        while(__HAL_UART_GET_FLAG(&UART5_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
        {
        }                   
        UART5->DR=*b;  //发送1个字节         
        b++;
    } 
    while(__HAL_UART_GET_FLAG(&UART5_Handler,USART_FLAG_TXE)==RESET)   //等待发送数据寄存器为空
    {
    }              
    while(__HAL_UART_GET_FLAG(&UART5_Handler,USART_FLAG_TC)==RESET)   //等待tsr中接到数据发送出去
    {
    }             
 
	#if(BSP_UART5_TX_DISABLE_EN==1)
    UART5->CR1&=(~UART_MODE_TX);   //禁止发送
	#endif
}



/**********发送一个字符串**************************/
void BSP_USART5_FA_STRING(unsigned char*str)
{
/*
 *函数名：BSP_USART5_FA_STRING
 *描述  ：通过串口发送一组字符串常数，不使用中断
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
    unsigned short int len=0;
    unsigned char *s=str;
    while((*s)!=0)    //当不等于空字符时发送数据
    {
        s++;  //指向下一字符          
        len++;
    }     
    BSP_USART5_SEND_BUF(str,len);    
}


#endif

















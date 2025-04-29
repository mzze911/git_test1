#include "bsp_spi.h"
#include "bsp_systick.h"
#include "bsp_dma.h"
#include "bsp_led.h"
   
/******************变量定义***********************/
#ifdef BSP_SPI1_EN
//----SPI1相关变量定义---
SPI_HandleTypeDef SPI1_Handler; //SPI配置句柄


#if(BSP_SPI1_TRX_DMA_EN==1)|(BSP_SPI1_TRX_DMA_EN==2)  //使用DMA
volatile unsigned char BSP_SPI1_TRX_DMA_MARK=0;         //0->无意义   1->发送接收未完成   2->发送接收完成一半   3->发送接收完成	 	
#endif

#endif


#ifdef BSP_SPI2_EN
//----SPI2相关变量定义---
SPI_HandleTypeDef SPI2_Handler; //SPI配置句柄


#if(BSP_SPI2_TRX_DMA_EN==1)|(BSP_SPI2_TRX_DMA_EN==2)  //使用DMA
volatile unsigned char BSP_SPI2_TRX_DMA_MARK=0;         //0->无意义   1->发送接收未完成   2->发送接收完成一半   3->发送接收完成		
#endif

#endif





/***********SPI初始化*******************/
#ifdef BSP_SPI1_EN
void BSP_SPI1_INIT(void)
{
/*
 *函数名：BSP_SPI1_INIT
 *描述  ：SPI1初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/     

    //SPI初始化

	SPI1_Handler.Instance = SPI1;
	SPI1_Handler.Init.Mode = SPI_MODE_MASTER;
	SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES;
	SPI1_Handler.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI1_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;
	#if(BSP_SPI1_SOFT_CS==0)
	SPI1_Handler.Init.NSS = SPI_NSS_HARD_OUTPUT;
	#endif 		
	#if(BSP_SPI1_SOFT_CS==1)
	SPI1_Handler.Init.NSS = SPI_NSS_SOFT;
	#endif 	
	SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI1_Handler.Init.CRCPolynomial = 10;
	
	
	HAL_SPI_Init(&SPI1_Handler);
	
}
#endif


#ifdef BSP_SPI2_EN
void BSP_SPI2_INIT(void)
{
/*
 *函数名：BSP_SPI2_INIT
 *描述  ：SPI2初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/     


    //SPI初始化
	
	SPI2_Handler.Instance = SPI2;
	SPI2_Handler.Init.Mode = SPI_MODE_MASTER;
	SPI2_Handler.Init.Direction = SPI_DIRECTION_2LINES;
	SPI2_Handler.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI2_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI2_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;
	#if(BSP_SPI2_SOFT_CS==0)
	SPI2_Handler.Init.NSS = SPI_NSS_HARD_OUTPUT;
	#endif 		
	#if(BSP_SPI2_SOFT_CS==1)
	SPI2_Handler.Init.NSS = SPI_NSS_SOFT;
	#endif 
	SPI2_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	SPI2_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI2_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI2_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI2_Handler.Init.CRCPolynomial = 10;
	
	
	HAL_SPI_Init(&SPI2_Handler);
	
}
#endif

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;

	#ifdef BSP_SPI1_EN    
    /***************进行SPI1相关的设置*********************/
	if(hspi->Instance==SPI1)//如果是SPI1，进行SPI1 BSP初始化
	{
		
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_SPI1_CLK_ENABLE();			//使能SPI1时钟

		
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;		//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//复用输入		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
//		HAL_NVIC_EnableIRQ(SPI1_IRQn);		//使能SPI1中断通道
//		HAL_NVIC_SetPriority(SPI1_IRQn,0,2);	//抢占优先级3，子优先级3
		
		//-----配置DMA-----------		
#if(BSP_SPI1_TRX_DMA_EN==1)|(BSP_SPI1_TRX_DMA_EN==2)
		BSP_DMA_SPI1_TX_INIT(&SPI1_Handler);
		BSP_DMA_SPI1_RX_INIT(&SPI1_Handler);		
#endif	

	}
	#endif
	#ifdef BSP_SPI2_EN    	
    /***************进行SPI2相关的设置*********************/
	if(hspi->Instance==SPI2)//如果是SPI2，进行SPI2 BSP初始化
	{
		/**SPI2 GPIO Configuration    
		PB7     ------> SPI2_NSS
		PB13     ------> SPI2_SCK
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI 
		*/
		__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOB时钟
		__HAL_RCC_SPI2_CLK_ENABLE();			//使能SPI2时钟
		
	
		GPIO_Initure.Pin = GPIO_PIN_13|GPIO_PIN_15;
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);

		GPIO_Initure.Pin = GPIO_PIN_14;
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;
		GPIO_Initure.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);


		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		GPIO_Initure.Pin = GPIO_PIN_7;
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);

		
//		HAL_NVIC_EnableIRQ(SPI2_IRQn);		//使能SPI2中断通道
//		HAL_NVIC_SetPriority(SPI2_IRQn,0,2);	//抢占优先级3，子优先级3
		
		//-----配置DMA-----------		
#if(BSP_SPI2_TRX_DMA_EN==1)|(BSP_SPI2_TRX_DMA_EN==2)
		BSP_DMA_SPI2_TX_INIT(&SPI2_Handler);
		BSP_DMA_SPI2_RX_INIT(&SPI2_Handler);		
#endif	

	}	
	#endif	
	
}


/*****************SPI接收回调函数*********************/
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
/*
 *函数名：HAL_SPI_RxHalfCpltCallback
 *描述  ：SPI接收一半回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_SPI1_EN	
	//-----SPI1接收一半回调函数----
	if(hspi->Instance==SPI1)//如果是SPI1
	{

	}
	#endif
	#ifdef BSP_SPI2_EN	
	//-----SPI2接收一半回调函数----
	if(hspi->Instance==SPI2)//如果是SPI2
	{
		
	}
	#endif

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
/*
 *函数名：HAL_SPI_RxCpltCallback
 *描述  ：SPI接收完成回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_SPI1_EN	
	//-----SPI1接收完成回调函数-----
	if(hspi->Instance==SPI1)//如果是SPI1
	{

	}
	#endif
	#ifdef BSP_SPI2_EN	
	//-----SPI2接收完成回调函数-----
	if(hspi->Instance==SPI2)//如果是SPI2
	{
		
	}
	#endif


}

/*****************SPI发送回调函数*********************/
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
/*
 *函数名：HAL_SPI_TxHalfCpltCallback
 *描述  ：SPI发送一半回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_SPI1_EN	
	//-----SPI1发送一半回调函数----
	if(hspi->Instance==SPI1)//如果是SPI1
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_SPI1_TRX_DMA_EN==2)	    
		BSP_SPI1_TRX_DMA_MARK=2;   //发送完成一半
				
		#endif			
	}
	#endif
	#ifdef BSP_SPI2_EN	
	//-----SPI2发送一半回调函数----
	if(hspi->Instance==SPI2)//如果是SPI2
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_SPI2_TRX_DMA_EN==2)	    
		BSP_SPI2_TRX_DMA_MARK=2;   //发送完成一半				
				
		#endif			
	}
	#endif
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
/*
 *函数名：HAL_SPI_TxCpltCallback
 *描述  ：SPI发送完成回调函数
 *输入  ：
 *输出  ：无 
 *调用  ：外部调用
*/ 	
	#ifdef BSP_SPI1_EN	
	//-----SPI1发送完成回调函数-----
	if(hspi->Instance==SPI1)//如果是SPI1
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_SPI1_TRX_DMA_EN==2)	   
		BSP_SPI1_TRX_DMA_MARK=3;   //发送接收完成	
		HAL_SPI_AbortTransmit(&SPI1_Handler);      //传输完成以后关闭SPIDMA
		#endif			
	}
	#endif
	#ifdef BSP_SPI2_EN
	//-----SPI2发送完成回调函数-----
	if(hspi->Instance==SPI2)//如果是SPI2
	{
		//DMA方式发送（开DMA传输中断）
		#if(BSP_SPI2_TRX_DMA_EN==2)	   
		BSP_SPI2_TRX_DMA_MARK=3;   //发送接收完成
		BSP_IO_LED1=0;
//		HAL_SPI_AbortTransmit(&SPI2_Handler);      //传输完成以后关闭SPIDMA		
		#endif			
	}
	#endif

}

/*****************SPI传输出错回调函数*********************/
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	
	
	
	
	
}




#ifdef BSP_SPI1_EN  

unsigned char BSP_SPI1_WRITE_BYTES(unsigned char*data,unsigned short int size)
{
/*
 *函数名：BSP_SPI1_WRITE_BYTES
 *描述  ：SPI1写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=data;
	unsigned char *rp=data;
	
	if(size>0)
	{	
			
		res=HAL_SPI_Transmit(&SPI1_Handler,tp,size,1000);   //超时时间1s
	}
	return res;
}

unsigned char BSP_SPI1_WRITE_READ_BYTES(unsigned char*wdata,unsigned char*rdata,unsigned short int size)
{
/*
 *函数名：BSP_SPI1_WRITE_READ_BYTE
 *描述  ：SPI1读写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=wdata;
	unsigned char *rp=rdata;
	
	if(size>0)
	{	
		
		res=HAL_SPI_TransmitReceive(&SPI1_Handler,tp,rp,size,1000);   //超时时间1s
	}
	return res;
}

#if(BSP_SPI1_TRX_DMA_EN==1)|(BSP_SPI1_TRX_DMA_EN==2)


unsigned char BSP_SPI1_WRITE_READ_GET_DMA_TRANS_STATE()
{
/*
 *函数名：BSP_SPI1_WRITE_READ_BYTE
 *描述  ：SPI1读写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	#if(BSP_SPI1_TRX_DMA_EN==1)
	if(__HAL_DMA_GET_COUNTER(SPI1_Handler.hdmatx)==0)
	{
		BSP_SPI1_TRX_DMA_MARK=3;
	}
	#endif
	return BSP_SPI1_TRX_DMA_MARK;
}

unsigned char BSP_SPI1_WRITE_BYTES_DMA(unsigned char*data,unsigned short int size)
{
/*
 *函数名：BSP_SPI1_WRITE_READ_BYTE
 *描述  ：SPI1写字节
 *输入  ：无
 *输出  ：0-正常 1-发送忙
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=data;
	unsigned char *rp=data;
	
	if(size>0)
	{	
		if(__HAL_DMA_GET_COUNTER(SPI1_Handler.hdmatx)==0)   //确保发送结束
		{		
			#if(BSP_SPI1_TRX_DMA_EN==1)
			SPI1_Handler.hdmatx->State = HAL_DMA_STATE_READY;			
			SPI1_Handler.State=HAL_SPI_STATE_READY;
			__HAL_UNLOCK(SPI1_Handler.hdmatx);
			#endif
			res=HAL_SPI_Transmit_DMA(&SPI1_Handler,tp,size);
		}
		else
		{
			res=1;
		}		
	}
	return res;
}

unsigned char BSP_SPI1_WRITE_READ_BYTES_DMA(unsigned char*wdata,unsigned char*rdata,unsigned short int size)
{
/*
 *函数名：BSP_SPI1_WRITE_READ_BYTE
 *描述  ：SPI1读写字节
 *输入  ：无
 *输出  ：0-正常 1-发送忙
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=wdata;
	unsigned char *rp=rdata;
	
	if(size>0)
	{	
		if(__HAL_DMA_GET_COUNTER(SPI1_Handler.hdmatx)==0)   //确保发送结束
		{		
			#if(BSP_SPI1_TRX_DMA_EN==1)
			SPI1_Handler.hdmatx->State = HAL_DMA_STATE_READY;			
			SPI1_Handler.State=HAL_SPI_STATE_READY;
			__HAL_UNLOCK(SPI1_Handler.hdmatx);
			#endif			
			res=HAL_SPI_TransmitReceive_DMA(&SPI1_Handler,tp,rp,size);   
		}
		else
		{
			res=1;
		}		
	}
	return res;
}
#endif


#endif



#ifdef BSP_SPI2_EN  

unsigned char BSP_SPI2_WRITE_BYTES(unsigned char*data,unsigned short int size)
{
/*
 *函数名：BSP_SPI2_WRITE_BYTES
 *描述  ：SPI2写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=data;
	unsigned char *rp=data;
	
	if(size>0)
	{				
		res=HAL_SPI_Transmit(&SPI2_Handler,tp,size,1000);   //超时时间1s
	}
	return res;
}


unsigned char BSP_SPI2_WRITE_READ_BYTES(unsigned char*wdata,unsigned char*rdata,unsigned short int size)
{
/*
 *函数名：BSP_SPI2_WRITE_READ_BYTE
 *描述  ：SPI2读写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	unsigned long int tick=0;
	unsigned char res=0;
	unsigned char *tp=wdata;
	unsigned char *rp=rdata;
	
	tick=bsp_systick_count;
	if(size>0)
	{				
		res=HAL_SPI_TransmitReceive(&SPI2_Handler,tp,rp,size,1000);   //超时时间1s
	}
	return res;
}

#if(BSP_SPI2_TRX_DMA_EN==1)|(BSP_SPI2_TRX_DMA_EN==2)

unsigned char BSP_SPI2_WRITE_READ_GET_DMA_TRANS_STATE()
{
/*
 *函数名：BSP_SPI2_WRITE_READ_BYTE
 *描述  ：SPI2读写字节
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	#if(BSP_SPI2_TRX_DMA_EN==1)
	if(__HAL_DMA_GET_COUNTER(SPI2_Handler.hdmatx)==0)
	{
		BSP_SPI2_TRX_DMA_MARK=3;
	}
	#endif
	return BSP_SPI2_TRX_DMA_MARK;
}

unsigned char BSP_SPI2_WRITE_BYTES_DMA(unsigned char*data,unsigned short int size)
{
/*
 *函数名：BSP_SPI2_WRITE_READ_BYTE
 *描述  ：SPI2写字节
 *输入  ：无
 *输出  ：0-正常 1-发送忙
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=data;
	unsigned char *rp=data;
	
	if(size>0)
	{	
		if(__HAL_DMA_GET_COUNTER(SPI2_Handler.hdmatx)==0)   //确保发送结束
		{
			#if(BSP_SPI2_TRX_DMA_EN==1)
			SPI2_Handler.hdmatx->State = HAL_DMA_STATE_READY;			
			SPI2_Handler.State=HAL_SPI_STATE_READY;
			__HAL_UNLOCK(SPI2_Handler.hdmatx);
			#endif
			res=HAL_SPI_Transmit_DMA(&SPI2_Handler,tp,size);
		}
		else
		{
			res=1;
		}

	}
	return res;
}


unsigned char BSP_SPI2_WRITE_READ_BYTES_DMA(unsigned char*wdata,unsigned char*rdata,unsigned short int size)
{
/*
 *函数名：BSP_SPI2_WRITE_READ_BYTE
 *描述  ：SPI2读写字节
 *输入  ：无
 *输出  ：0-正常 1-发送忙
 *调用  ：外部调用
*/   
	unsigned char res=0;
	unsigned char *tp=wdata;
	unsigned char *rp=rdata;
	
	if(size>0)
	{	
		if(__HAL_DMA_GET_COUNTER(SPI2_Handler.hdmatx)==0)   //确保发送结束
		{		
			#if(BSP_SPI2_TRX_DMA_EN==1)
			SPI2_Handler.hdmatx->State = HAL_DMA_STATE_READY;			
			SPI2_Handler.State=HAL_SPI_STATE_READY;
			__HAL_UNLOCK(SPI2_Handler.hdmatx);
			#endif		
			res=HAL_SPI_TransmitReceive_DMA(&SPI2_Handler,tp,rp,size);  
		}
		else
		{
			res=1;
		}	
	}
	return res;
}


#endif


#endif





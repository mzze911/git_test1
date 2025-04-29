#include "bsp_dma.h"
#include "bsp_uart.h"
#include "bsp_spi.h"

//----ADC相关DMA配置---
DMA_HandleTypeDef hdma_adc1;
//----TIME1相关DMA配置---
DMA_HandleTypeDef hdma_tim1_ch1;
DMA_HandleTypeDef hdma_tim1_ch2;
//----UART相关DMA配置----
DMA_HandleTypeDef hdma_uart1tx;
DMA_HandleTypeDef hdma_uart1rx;
DMA_HandleTypeDef hdma_uart2tx;
DMA_HandleTypeDef hdma_uart2rx;
DMA_HandleTypeDef hdma_uart3tx;
DMA_HandleTypeDef hdma_uart3rx;
DMA_HandleTypeDef hdma_uart4tx;
DMA_HandleTypeDef hdma_uart4rx;

//----SPI相关DMA配置----
DMA_HandleTypeDef hdma_spi1tx;
DMA_HandleTypeDef hdma_spi1rx;
DMA_HandleTypeDef hdma_spi2tx;
DMA_HandleTypeDef hdma_spi2rx;




void BSP_DMA_ADC1_INIT(ADC_HandleTypeDef* hadc)
{
/*
 *函数名：BSP_DMA_ADC1_INIT
 *描述  ：DMA ADC1初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	__HAL_RCC_DMA1_CLK_ENABLE();
  	
    hdma_adc1.Instance = DMA1_Channel1;               //DMA1 通道1
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;    //外设数据字对齐
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;       //内存数据字对齐
    hdma_adc1.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&hdma_adc1);
    
    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);	

	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn); 

}




void BSP_DMA_TIME1_INIT(TIM_HandleTypeDef* htim)
{
/*
 *函数名：BSP_DMA_TIME1_INIT
 *描述  ：DMA TIME1初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/

  	/*通道1 配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();	
	//--设置--
    hdma_tim1_ch1.Instance = DMA1_Channel2;               //DMA1 通道2
    hdma_tim1_ch1.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_tim1_ch1.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_tim1_ch1.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_tim1_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;    //外设数据字对齐
    hdma_tim1_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;       //内存数据字对齐
    hdma_tim1_ch1.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_tim1_ch1.Init.Priority = DMA_PRIORITY_HIGH;      //优先级

    HAL_DMA_Init(&hdma_tim1_ch1);
    //--链接--
    __HAL_LINKDMA(htim,hdma[1],hdma_tim1_ch1);	
//	//--中断--
//	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 3, 2);
//	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn); 

  	/*通道2 配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();	
	//--设置--
    hdma_tim1_ch2.Instance = DMA1_Channel3;               //DMA1 通道3
    hdma_tim1_ch2.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_tim1_ch2.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_tim1_ch2.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_tim1_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;    //外设数据字对齐
    hdma_tim1_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;       //内存数据字对齐
    hdma_tim1_ch2.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_tim1_ch2.Init.Priority = DMA_PRIORITY_HIGH;      //优先级


    HAL_DMA_Init(&hdma_tim1_ch2);
    //--链接--
    __HAL_LINKDMA(htim,hdma[2],hdma_tim1_ch2);	
//	//--中断--
//	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 3, 2);
//	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn); 	

   
}

void BSP_DMA_UART1_TX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART1_TX_INIT
 *描述  ：DMA UART1 发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口1发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart1tx.Instance = DMA1_Channel4;               //DMA1 通道4
    HAL_DMA_DeInit(&hdma_uart1tx);		      //复位对象
    hdma_uart1tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_uart1tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart1tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart1tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart1tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart1tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_uart1tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart1tx);
    
    __HAL_LINKDMA(huart,hdmatx,hdma_uart1tx);	

#if(BSP_UART1_TX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn); 
#endif
}

void BSP_DMA_UART1_RX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART1_RX_INIT
 *描述  ：DMA UART1 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart1rx.Instance = DMA1_Channel5;               //DMA1 通道5
    HAL_DMA_DeInit(&hdma_uart1rx);		      //复位对象
    hdma_uart1rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_uart1rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart1rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart1rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart1rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart1rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_uart1rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart1rx);
    
    __HAL_LINKDMA(huart,hdmarx,hdma_uart1rx);	

	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 1, 2);       //DMA的中断优先级要高于串口中断优先级
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn); 

}



void BSP_DMA_UART2_TX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART2_TX_INIT
 *描述  ：DMA UART2 发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口2发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart2tx.Instance = DMA1_Channel7;               //DMA1 通道7
    HAL_DMA_DeInit(&hdma_uart2tx);		      //复位对象
    hdma_uart2tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_uart2tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart2tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart2tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart2tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart2tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_uart2tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart2tx);
    
    __HAL_LINKDMA(huart,hdmatx,hdma_uart2tx);	
#if(BSP_UART2_TX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn); 
#endif
}

void BSP_DMA_UART2_RX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART2_RX_INIT
 *描述  ：DMA UART2 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart2rx.Instance = DMA1_Channel6;               //DMA1 通道6
    HAL_DMA_DeInit(&hdma_uart2rx);		      //复位对象
    hdma_uart2rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_uart2rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart2rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart2rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart2rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart2rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_uart2rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart2rx);
    
    __HAL_LINKDMA(huart,hdmarx,hdma_uart2rx);	

	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 1, 2);       //DMA的中断优先级要高于串口中断优先级
	HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn); 

}

void BSP_DMA_UART3_TX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART3_TX_INIT
 *描述  ：DMA UART3 发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口3发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart3tx.Instance = DMA1_Channel2;               //DMA1 通道2
    HAL_DMA_DeInit(&hdma_uart3tx);		      //复位对象	
    hdma_uart3tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_uart3tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart3tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart3tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart3tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart3tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_uart3tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级

    HAL_DMA_Init(&hdma_uart3tx);
    
    __HAL_LINKDMA(huart,hdmatx,hdma_uart3tx);	
#if(BSP_UART3_TX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn); 
#endif
}


void BSP_DMA_UART3_RX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART3_RX_INIT
 *描述  ：DMA UART3 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_uart3rx.Instance = DMA1_Channel3;               //DMA1 通道3
    HAL_DMA_DeInit(&hdma_uart3rx);		      //复位对象
    hdma_uart3rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_uart3rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart3rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart3rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart3rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart3rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_uart3rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart3rx);
    
    __HAL_LINKDMA(huart,hdmarx,hdma_uart3rx);	

	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 1, 2);       //DMA的中断优先级要高于串口中断优先级
	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn); 

}

#ifdef BSP_UART4_EN
void BSP_DMA_UART4_TX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART4_TX_INIT
 *描述  ：DMA UART4发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口4发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA2_CLK_ENABLE();
  	//--设置--
    hdma_uart4tx.Instance = DMA2_Channel5;               //DMA2 通道5
    HAL_DMA_DeInit(&hdma_uart4tx);		      //复位对象	
    hdma_uart4tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_uart4tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart4tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart4tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart4tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart4tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_uart4tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级

    HAL_DMA_Init(&hdma_uart4tx);
    
    __HAL_LINKDMA(huart,hdmatx,hdma_uart4tx);	
#if(BSP_UART4_TX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn); 
#endif
}

void BSP_DMA_UART4_RX_INIT(UART_HandleTypeDef* huart)
{
/*
 *函数名：BSP_DMA_UART4_RX_INIT
 *描述  ：DMA UART4 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*串口1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA2_CLK_ENABLE();
  	//--设置--
    hdma_uart4rx.Instance = DMA2_Channel3;               //DMA2 通道3
    HAL_DMA_DeInit(&hdma_uart4rx);		      //复位对象
    hdma_uart4rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_uart4rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_uart4rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_uart4rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_uart4rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_uart4rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_uart4rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_uart4rx);
    
    __HAL_LINKDMA(huart,hdmarx,hdma_uart4rx);	

	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 1, 2);       //DMA的中断优先级要高于串口中断优先级
	HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn); 

}
#endif

#ifdef BSP_SPI1_EN
void BSP_DMA_SPI1_TX_INIT(SPI_HandleTypeDef* hspi)
{
/*
 *函数名：BSP_DMA_SPI1_TX_INIT
 *描述  ：DMA SPI1 发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*SPI1发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_spi1tx.Instance = DMA1_Channel2;               //DMA1 通道2
    HAL_DMA_DeInit(&hdma_spi1tx);		      //复位对象
    hdma_spi1tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_spi1tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_spi1tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_spi1tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_spi1tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_spi1tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_spi1tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_spi1tx);
    
    __HAL_LINKDMA(hspi,hdmatx,hdma_spi1tx);	
#if(BSP_SPI1_TRX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn); 
#endif
}

void BSP_DMA_SPI1_RX_INIT(SPI_HandleTypeDef* hspi)
{
/*
 *函数名：BSP_DMA_SPI1_RX_INIT
 *描述  ：DMA SPI1 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*SPI1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_spi1rx.Instance = DMA1_Channel3;               //DMA1 通道3
    HAL_DMA_DeInit(&hdma_spi1rx);		      //复位对象
    hdma_spi1rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_spi1rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_spi1rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_spi1rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_spi1rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_spi1rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_spi1rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_spi1rx);
    
    __HAL_LINKDMA(hspi,hdmarx,hdma_spi1rx);	
#if(BSP_SPI1_TRX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 1, 2);       //DMA的中断优先级要高于SPI中断优先级
	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn); 
#endif
}
#endif


#ifdef BSP_SPI2_EN
void BSP_DMA_SPI2_TX_INIT(SPI_HandleTypeDef* hspi)
{
/*
 *函数名：BSP_DMA_SPI2_TX_INIT
 *描述  ：DMA SPI2 发送初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  
	/*SPI2发送DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_spi2tx.Instance = DMA1_Channel5;               //DMA1 通道5
    HAL_DMA_DeInit(&hdma_spi2tx);		      //复位对象
    hdma_spi2tx.Init.Direction = DMA_MEMORY_TO_PERIPH; //方向内存到外设
    hdma_spi2tx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_spi2tx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_spi2tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_spi2tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_spi2tx.Init.Mode = DMA_NORMAL;               //DMA普通模式           
    hdma_spi2tx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_spi2tx);
    
    __HAL_LINKDMA(hspi,hdmatx,hdma_spi2tx);	
#if(BSP_SPI2_TRX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn); 
#endif
}

void BSP_DMA_SPI2_RX_INIT(SPI_HandleTypeDef* hspi)
{
/*
 *函数名：BSP_DMA_SPI2_RX_INIT
 *描述  ：DMA SPI2 接收初始化函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	/*SPI1接收DMA配置*/
	//--时钟--
	__HAL_RCC_DMA1_CLK_ENABLE();
  	//--设置--
    hdma_spi2rx.Instance = DMA1_Channel4;               //DMA1 通道4
    HAL_DMA_DeInit(&hdma_spi2rx);		      //复位对象
    hdma_spi2rx.Init.Direction = DMA_PERIPH_TO_MEMORY; //方向外设到内存
    hdma_spi2rx.Init.PeriphInc = DMA_PINC_DISABLE;     //外设增长失能
    hdma_spi2rx.Init.MemInc = DMA_MINC_ENABLE;         //内存增长使能
    hdma_spi2rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;    //外设数据字节对齐
    hdma_spi2rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;       //内存数据字节对齐
    hdma_spi2rx.Init.Mode = DMA_CIRCULAR;               //DMA循环模式           
    hdma_spi2rx.Init.Priority = DMA_PRIORITY_MEDIUM;   //中优先级
	

    HAL_DMA_Init(&hdma_spi2rx);
    
    __HAL_LINKDMA(hspi,hdmarx,hdma_spi2rx);	
#if(BSP_SPI2_TRX_DMA_EN==2)
	/* 外设中断优先级配置和使能中断 */
	HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 1, 2);       //DMA的中断优先级要高于SPI中断优先级
	HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn); 
#endif
}

#endif




/*-------DMA1传输中断函数------------*/
void DMA1_Channel1_IRQHandler(void)
{
	//--------DMA中断函数-----
//	HAL_DMA_IRQHandler(&hdma_adc1);   //用于ADC


}


void DMA1_Channel2_IRQHandler(void)
{
	//--------DMA中断函数-----
//	HAL_DMA_IRQHandler(&hdma_uart3tx);   //用于UART3发送处理

	HAL_DMA_IRQHandler(&hdma_spi1tx);   //用于SPI1发送处理
}


void DMA1_Channel3_IRQHandler(void)
{
	//--------DMA中断函数-----
//	HAL_DMA_IRQHandler(&hdma_tim1_ch2);   //用于TIM1 CH2
//	HAL_DMA_IRQHandler(&hdma_uart3rx);   //用于UART3接收处理
	HAL_DMA_IRQHandler(&hdma_spi1rx);   //用于SPI1接收处理
}

void DMA1_Channel4_IRQHandler(void)
{
	//--------DMA中断函数-----
//	HAL_DMA_IRQHandler(&hdma_uart1tx);   //用于UART1发送处理
	HAL_DMA_IRQHandler(&hdma_spi2rx);   //用于SPI2接收处理

}


void DMA1_Channel5_IRQHandler(void)
{
	//--------DMA中断函数-----
//	HAL_DMA_IRQHandler(&hdma_uart1rx);   //用于UART1接收处理
	HAL_DMA_IRQHandler(&hdma_spi2tx);   //用于SPI2发送处理
}

void DMA1_Channel6_IRQHandler(void)
{
	//--------DMA中断函数-----
	HAL_DMA_IRQHandler(&hdma_uart2rx);   //用于UART2接收处理


}


void DMA1_Channel7_IRQHandler(void)
{
	//--------DMA中断函数-----
	HAL_DMA_IRQHandler(&hdma_uart2tx);   //用于UART2发送处理


}

/*-------DMA2传输中断函数------------*/
#ifdef BSP_UART4_EN
void DMA2_Channel3_IRQHandler(void)
{
	//--------DMA中断函数-----
	HAL_DMA_IRQHandler(&hdma_uart4rx);   //用于UART4接收处理


}


void DMA2_Channel4_5_IRQHandler(void)
{
	//--------DMA中断函数-----
	HAL_DMA_IRQHandler(&hdma_uart4tx);   //用于UART4发送处理


}
#endif











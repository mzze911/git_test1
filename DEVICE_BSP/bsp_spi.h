#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__


#include "bsp_stm32f1_mzze.h"

//-----SPI使用宏定义----
//#define BSP_SPI1_EN  1      //使用SPI1，注释掉不使用
#define BSP_SPI2_EN  1


//-----SPI配置宏定义----
#ifdef BSP_SPI1_EN
    #define BSP_SPI1_SOFT_CS            1     //---0->硬件控制CS         1->软件控制CS
	#define BSP_SPI1_TRX_DMA_EN         1     //---0->不使用DMA方式发送接收  1->DMA方式发送接收（不开DMA传输中断）   2->DMA方式发送接收（开DMA传输中断）
#endif

#ifdef BSP_SPI2_EN
    #define BSP_SPI2_SOFT_CS            1     //---0->硬件控制CS         1->软件控制CS
	#define BSP_SPI2_TRX_DMA_EN         2     //---0->不使用DMA方式发送接收  1->DMA方式发送接收（不开DMA传输中断）   2->DMA方式发送接收（开DMA传输中断）
#endif





//---------------对外接口变量--------------
#ifdef BSP_SPI1_EN  
#if(BSP_SPI1_TRX_DMA_EN==1)|(BSP_SPI1_TRX_DMA_EN==2)   //使用DMA
	extern volatile unsigned char BSP_SPI1_TRX_DMA_MARK;         //0->无意义   1->发送接收未完成   2->发送接收完成	   3->发送接收完成	 	
#endif

#endif

#ifdef BSP_SPI2_EN  
#if(BSP_SPI2_TRX_DMA_EN==1)|(BSP_SPI2_TRX_DMA_EN==2)  //使用DMA
	extern volatile unsigned char BSP_SPI2_TRX_DMA_MARK;         //0->无意义   1->发送接收未完成   2->发送接收完成	   3->发送接收完成	
#endif

#endif
//---------------对外接口函数---------------

#ifdef BSP_SPI1_EN   
//--------SPI1-----
#if(BSP_SPI1_SOFT_CS==1)
#define FLASH_SPI1_CS_ENABLE()       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define FLASH_SPI1_CS_DISABLE()      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#endif 

extern void BSP_SPI1_INIT(void);
extern unsigned char BSP_SPI1_WRITE_BYTES(unsigned char*data,unsigned short int size);
extern unsigned char BSP_SPI1_WRITE_READ_BYTES(unsigned char*wdata,unsigned char*rdata,unsigned short int size);
#if(BSP_SPI1_TRX_DMA_EN==1)|(BSP_SPI1_TRX_DMA_EN==2)
extern unsigned char BSP_SPI1_WRITE_READ_GET_DMA_TRANS_STATE(void);
extern unsigned char BSP_SPI1_WRITE_BYTES_DMA(unsigned char*data,unsigned short int size);
extern unsigned char BSP_SPI1_WRITE_READ_BYTES_DMA(unsigned char*wdata,unsigned char*rdata,unsigned short int size);
#endif

#endif

#ifdef BSP_SPI2_EN    
//--------SPI2-----
#if(BSP_SPI2_SOFT_CS==1)
#define FLASH_SPI2_CS_ENABLE()       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define FLASH_SPI2_CS_DISABLE()      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#endif 

extern void BSP_SPI2_INIT(void);
extern unsigned char BSP_SPI2_WRITE_BYTES(unsigned char*data,unsigned short int size);
extern unsigned char BSP_SPI2_WRITE_READ_BYTES(unsigned char*wdata,unsigned char*rdata,unsigned short int size);
#if(BSP_SPI2_TRX_DMA_EN==1)|(BSP_SPI2_TRX_DMA_EN==2)
extern unsigned char BSP_SPI2_WRITE_READ_GET_DMA_TRANS_STATE(void);
extern unsigned char BSP_SPI2_WRITE_BYTES_DMA(unsigned char*data,unsigned short int size);
extern unsigned char BSP_SPI2_WRITE_READ_BYTES_DMA(unsigned char*wdata,unsigned char*rdata,unsigned short int size);
#endif

#endif


#endif





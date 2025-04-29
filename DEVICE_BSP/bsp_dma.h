#ifndef __BSP_DMA_H__
#define __BSP_DMA_H__

#include "bsp_stm32f1_mzze.h"


extern void BSP_DMA_ADC1_INIT(ADC_HandleTypeDef* hadc);

extern void BSP_DMA_TIME1_INIT(TIM_HandleTypeDef* htim);

extern void BSP_DMA_UART1_TX_INIT(UART_HandleTypeDef* huart);
extern void BSP_DMA_UART1_RX_INIT(UART_HandleTypeDef* huart);

extern void BSP_DMA_UART2_TX_INIT(UART_HandleTypeDef* huart);
extern void BSP_DMA_UART2_RX_INIT(UART_HandleTypeDef* huart);

extern void BSP_DMA_UART3_TX_INIT(UART_HandleTypeDef* huart);
extern void BSP_DMA_UART3_RX_INIT(UART_HandleTypeDef* huart);

extern void BSP_DMA_UART4_TX_INIT(UART_HandleTypeDef* huart);
extern void BSP_DMA_UART4_RX_INIT(UART_HandleTypeDef* huart);

extern void BSP_DMA_SPI1_TX_INIT(SPI_HandleTypeDef* hspi);
extern void BSP_DMA_SPI1_RX_INIT(SPI_HandleTypeDef* hspi);

extern void BSP_DMA_SPI2_TX_INIT(SPI_HandleTypeDef* hspi);
extern void BSP_DMA_SPI2_RX_INIT(SPI_HandleTypeDef* hspi);

#endif



#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#include "bsp_stm32f1_mzze.h"


//---------STM32F103RCT6---------
#define STM32_PAGE_SIZE  2048        //2K单位字节
#define STM32_FLASH_BASE 0x08000000  //STM32 FLASH的起始地址
#define STM32_FLASH_SIZE 0x40000     //256k
#define FLASH_WAITETIME  50000       //FLASH等待超时时间



//---------对外接口函数----------
extern uint32_t BSP_FLASH_READ_WORD(uint32_t faddr);                                      //读出字
extern void BSP_FLASH_READ_NWORD(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t Num);    //从指定地址开始读出指定长度的数据
extern uint8_t BSP_FLASH_WRITE_NWORD(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t Num); //从指定地址开始写入指定长度的数据




#endif



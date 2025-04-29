#include "bsp_flash.h"



static uint32_t bsp_flash_getflashpageadd(uint32_t addr)
{
	uint32_t page_add=0;
	page_add=addr/STM32_PAGE_SIZE;
	page_add=page_add*STM32_PAGE_SIZE+STM32_FLASH_BASE;
	return page_add;
}

uint32_t BSP_FLASH_READ_WORD(uint32_t faddr)
{
    return *(__IO uint32_t *)faddr;
}

void BSP_FLASH_READ_NWORD(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t Num)
{
    uint32_t i;
    for (i = 0; i < Num; i++)
    {
        pBuffer[i] = BSP_FLASH_READ_WORD(ReadAddr); //读取4个字节.
        ReadAddr += 4;                              //偏移4个字节.
    }
}

uint8_t BSP_FLASH_WRITE_NWORD(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t Num)
{
	uint8_t r = HAL_OK;
    uint32_t addrx = 0;
    uint32_t endaddr = 0;
    if ((WriteAddr < STM32_FLASH_BASE)||(WriteAddr % 4))
	{
        return HAL_ERROR; //非法地址
	}
    HAL_FLASH_Unlock();            //解锁
    addrx = WriteAddr;             //写入的起始地址
    endaddr = WriteAddr + Num * 4; //写入的结束地址

	//-----判断数据是否需要擦除----
	while (addrx < endaddr)
	{
		if (BSP_FLASH_READ_WORD(addrx) != 0XFFFFFFFF)
		{
			uint32_t PageError = 0;
			FLASH_EraseInitTypeDef FlashEraseInit;			
			FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;        //擦除类型，页擦除
			FlashEraseInit.PageAddress = bsp_flash_getflashpageadd(addrx); //要擦除的页地址
			FlashEraseInit.NbPages = 1;                           //一次只擦除一个页
			r=HAL_FLASHEx_Erase(&FlashEraseInit, &PageError);
			if(r==HAL_OK)   //擦除成功
			{
					
			}
			else
			{
				return r; //擦除异常
			}	
		}
		else
		{
			addrx += 4;
		}
	}
	//------进行数据的写入------------
	while (WriteAddr < endaddr) //写数据
	{
		r= HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddr, *pBuffer);   //写入数据
		if (r == HAL_OK) 
		{
			WriteAddr += 4;
			pBuffer++;
		}
		else
		{
			return r; //写入异常				
		}
	}
    HAL_FLASH_Lock(); //上锁
	return r;
}







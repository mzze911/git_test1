#include "bsp_dht11_io.h"



#ifdef BSP_DHT11_1_EN
/******************温湿度传感器1相关函数********************/
void BSP_DHT11_IO_1_MODE_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

//	GPIO_InitStruct.Pin = GPIO_PIN_15;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

//	GPIO_InitStruct.Pin = GPIO_PIN_0;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 
	
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 	
	
}

void BSP_DHT11_IO_1_MODE_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

//	GPIO_InitStruct.Pin   = GPIO_PIN_15;
//	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull  = GPIO_PULLUP;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//	GPIO_InitStruct.Pin   = GPIO_PIN_0;
//	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull  = GPIO_PULLUP;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin   = GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
}

void BSP_DHT11_IO_1_INIT(void)
{

	//----温湿度传感器 DHT11,数据口---
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOA时钟	
	BSP_DHT11_IO_1_MODE_IN();           //设置为输入
	
}
#endif
#ifdef BSP_DHT11_2_EN
/******************温湿度传感器2相关函数********************/
void BSP_DHT11_IO_2_MODE_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); 	 
}

void BSP_DHT11_IO_2_MODE_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin   = GPIO_PIN_7;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}

void BSP_DHT11_IO_2_INIT(void)
{

	//----温湿度传感器 DHT11,数据口---
    __HAL_RCC_GPIOC_CLK_ENABLE();           //开启GPIOC时钟	
	BSP_DHT11_IO_2_MODE_IN();           //设置为输入
	
}
#endif
#ifdef BSP_DHT11_3_EN
/******************温湿度传感器3相关函数********************/
void BSP_DHT11_IO_3_MODE_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 	 
}

void BSP_DHT11_IO_3_MODE_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin   = GPIO_PIN_15;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void BSP_DHT11_IO_3_INIT(void)
{

	//----温湿度传感器 DHT11,数据口---
    __HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOA时钟	
	BSP_DHT11_IO_3_MODE_IN();           //设置为输入
	
}
#endif
#ifdef BSP_DHT11_4_EN
/******************温湿度传感器4相关函数********************/
void BSP_DHT11_IO_4_MODE_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 	 
}

void BSP_DHT11_IO_4_MODE_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin   = GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void BSP_DHT11_IO_4_INIT(void)
{

	//----温湿度传感器 DHT11,数据口---
    __HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOB时钟	
	BSP_DHT11_IO_4_MODE_IN();           //设置为输入
	
}
#endif



//------统一操作函数---

void BSP_DHT11_IO_MODE_OUT(unsigned char id)
{
	switch(id)
	{
		case 1:
		{
            #ifdef BSP_DHT11_1_EN			
			BSP_DHT11_IO_1_MODE_OUT();
            #endif
		}break;
		case 2:
		{
			#ifdef BSP_DHT11_2_EN
			BSP_DHT11_IO_2_MODE_OUT();
			#endif
		}break;
		case 3:
		{
			#ifdef BSP_DHT11_3_EN
			BSP_DHT11_IO_3_MODE_OUT();
			#endif
		}break;
		case 4:
		{
			#ifdef BSP_DHT11_4_EN
			BSP_DHT11_IO_4_MODE_OUT();
			#endif
		}break;
		default:break;		
		
	}	
	
}


void BSP_DHT11_IO_MODE_IN(unsigned char id)
{
	switch(id)
	{
		case 1:
		{
			#ifdef BSP_DHT11_1_EN
			BSP_DHT11_IO_1_MODE_IN();
            #endif
		}break;
		case 2:
		{
			#ifdef BSP_DHT11_2_EN
			BSP_DHT11_IO_2_MODE_IN();
			#endif
		}break;
		case 3:
		{
			#ifdef BSP_DHT11_3_EN
			BSP_DHT11_IO_3_MODE_IN();
			#endif
		}break;
		case 4:
		{
			#ifdef BSP_DHT11_4_EN
			BSP_DHT11_IO_4_MODE_IN();
			#endif
		}break;
		default:break;		
		
	}	
	
}

void BSP_DHT11_IO_D_WRITE(unsigned char id,unsigned char n)
{
	switch(id)
	{
		case 1:
		{
			#ifdef BSP_DHT11_1_EN
			BSP_DHT11_IO_1_DOUT=n;
            #endif
		}break;
		case 2:
		{
			#ifdef BSP_DHT11_2_EN
			BSP_DHT11_IO_2_DOUT=n;
			#endif
		}break;
		case 3:
		{
			#ifdef BSP_DHT11_3_EN
			BSP_DHT11_IO_3_DOUT=n;
			#endif
		}break;
		case 4:
		{
			#ifdef BSP_DHT11_4_EN
			BSP_DHT11_IO_4_DOUT=n;
			#endif
		}break;
		default:break;		
		
	}	
	
}

unsigned char BSP_DHT11_IO_D_READ(unsigned char id)
{
	unsigned char i=0;
	switch(id)
	{
		case 1:
		{
			#ifdef BSP_DHT11_1_EN
			i=BSP_DHT11_IO_1_DIN;
            #endif
		}break;
		case 2:
		{
			#ifdef BSP_DHT11_2_EN
			i=BSP_DHT11_IO_2_DIN;
			#endif
		}break;
		case 3:
		{
			#ifdef BSP_DHT11_3_EN
			i=BSP_DHT11_IO_3_DIN;
			#endif
		}break;
		case 4:
		{
			#ifdef BSP_DHT11_4_EN
			i=BSP_DHT11_IO_4_DIN;
			#endif
		}break;
		default:break;		
		
	}	
	return i;
}

void BSP_DHT11_IO_INIT(unsigned char id)
{
	switch(id)
	{
		case 1:
		{
			#ifdef BSP_DHT11_1_EN
			BSP_DHT11_IO_1_INIT();
            #endif
		}break;
		case 2:
		{
			#ifdef BSP_DHT11_2_EN
			BSP_DHT11_IO_2_INIT();
			#endif
		}break;
		case 3:
		{
			#ifdef BSP_DHT11_3_EN
			BSP_DHT11_IO_3_INIT();
			#endif
		}break;
		case 4:
		{
			#ifdef BSP_DHT11_4_EN
			BSP_DHT11_IO_4_INIT();
			#endif
		}break;
		default:break;		
		
	}	
	
}



















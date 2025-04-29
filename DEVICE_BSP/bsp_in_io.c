#include "bsp_in_io.h"







void BSP_IN_IO_INIT(void)
{
       
	GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();           //开启GPIOE时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1;    //PIN
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  //输入
    GPIO_Initure.Pull=GPIO_NOPULL;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;     //低速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);

}



























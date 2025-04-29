#include "bsp_out_io.h"







void BSP_OUT_IO_INIT(void)
{
       
	GPIO_InitTypeDef GPIO_Initure;
	
//	//----485通讯相关-----
//    __HAL_RCC_GPIOH_CLK_ENABLE();           //开启GPIOH时钟
//	
//    GPIO_Initure.Pin=GPIO_PIN_8; //PIN8
//    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
	
	//----电磁阀相关----
    __HAL_RCC_GPIOE_CLK_ENABLE();           //开启GPIOE时钟
	BSP_AIR_SWITCH1_IO=BSP_AIR_SWITCH_OFF;
	BSP_AIR_SWITCH2_IO=BSP_AIR_SWITCH_OFF; 
	BSP_AIR_SWITCH3_IO=BSP_AIR_SWITCH_OFF; 
	BSP_AIR_SWITCH4_IO=BSP_AIR_SWITCH_OFF; 	
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6; //PIN3,PIN4,PIN5,PIN6
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;     //低速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    	
	
	BSP_AIR_SWITCH1_IO=BSP_AIR_SWITCH_OFF;
	BSP_AIR_SWITCH2_IO=BSP_AIR_SWITCH_OFF; 
	BSP_AIR_SWITCH3_IO=BSP_AIR_SWITCH_OFF; 
	BSP_AIR_SWITCH4_IO=BSP_AIR_SWITCH_OFF; 

	//----WIFI模块通讯相关-----
    __HAL_RCC_GPIOC_CLK_ENABLE();           //开启GPIOC时钟
	BSP_WIFI_NREST_IO=BSP_WIFI_NREST_H;
    GPIO_Initure.Pin=GPIO_PIN_9; //PIN9
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;  //开漏输出
    GPIO_Initure.Pull=GPIO_NOPULL;          //无上拉下拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW;     //低速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);


}















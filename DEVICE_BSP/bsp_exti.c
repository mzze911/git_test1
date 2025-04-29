#include "bsp_exti.h"
#include "bsp_led.h"
#include "func_ir_decode.h"





//外部中断初始化
void BSP_EXTI_INIT(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    
//    //中断线0-PA0
//    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
//    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //下降沿触发
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
//    
//    HAL_NVIC_SetPriority(EXTI0_IRQn,1,1);       //抢占优先级为2，子优先级为0
//    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0

    //中断线1-PA1
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    GPIO_Initure.Pin=GPIO_PIN_1;                //PA1
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    HAL_NVIC_SetPriority(EXTI1_IRQn,1,1);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);             //使能中断线0
    
//    //中断线2-PH2
//    __HAL_RCC_GPIOH_CLK_ENABLE();               //开启GPIOH时钟
//    GPIO_Initure.Pin=GPIO_PIN_2;                //PH2
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
//    
//    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //抢占优先级为2，子优先级为1
//    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //使能中断线2
//    
//    //中断线3-PH3
//    __HAL_RCC_GPIOH_CLK_ENABLE();               //开启GPIOH时钟
//    GPIO_Initure.Pin=GPIO_PIN_3;                //PH3
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);

//    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //抢占优先级为2，子优先级为2
//    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //使能中断线2
//    
//    //中断线13-PC13
//    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
//    GPIO_Initure.Pin=GPIO_PIN_13;               //PC13
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
//    
//    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //抢占优先级为2，子优先级为3
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //使能中断线13  
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
        /*********用户函数*********/
	
    }    
}

void EXTI1_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
        /*********用户函数*********/
		FUNC_IR_DECODE_WORK_EXTI();		
    }    
}


void EXTI2_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
        /*********用户函数*********/

    }  
}

void EXTI3_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
        /*********用户函数*********/
        
    }  
}

void EXTI4_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
        /*********用户函数*********/
        
    }  
}


void EXTI15_10_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
        /*********用户函数*********/
        
    }  
    
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
        /*********用户函数*********/
        
    }  

    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
        /*********用户函数*********/
        
    }  

    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
        /*********用户函数*********/
        
    }  

    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
        /*********用户函数*********/
        
    }      
    
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
        /*********用户函数*********/
        
    }      
}


































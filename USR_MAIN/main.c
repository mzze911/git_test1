/***************************************程序版本说明************************************************
此程序版本号：program-v1.00
旧程序版本号：

修改人：  mzze

修改内容：初版

对应硬件版本：无
*****************************************************************************************************/
#include "main.h"
#include "bsp_stm32f1_mzze.h"
#include "bsp_sysclock_config.h"
#include "bsp_led.h"
#include "bsp_systick.h"
#include "bsp_exti.h"
#include "bsp_uart.h"
#include "bsp_iwdg.h"
#include "bsp_crc.h"
#include "bsp_out_io.h"
#include "bsp_in_io.h"
#include "bsp_flash.h"
#include "bsp_timer.h"
#include "bsp_key.h"
#include "bsp_beep.h"



#include "func_s_delay.h"
#include "func_oled.h"
#include "func_alone_key.h"
#include "func_beep.h"
#include "func_time_mark.h"
#include "func_ir_decode.h"
#include "func_ir_nec_key.h"
#include "func_dht11.h"
#include "func_pc_interface_com.h"

#include "app_oled_display.h"


/**************变量定义******************/
static STRUCT_FUNC_S_NB_DELAY main_nb_delay_ms1;
//---主状态机-----
STRUCT_FUNC_STATE_MACHINE1 MAIN_CON_SM;


int main(void)
{ 
/************禁止JTAG，允许swd***************/
    __HAL_RCC_AFIO_CLK_ENABLE();    
//    AFIO->MAPR&=~AFIO_MAPR_SWJ_CFG;
//    AFIO->MAPR|=AFIO_MAPR_SWJ_CFG_JTAGDISABLE; 
	__HAL_AFIO_REMAP_SWJ_NOJTAG();    ////禁止JTAG，允许SWD从而释放部分IO口   
/*******HAL库初始化************/       
    HAL_Init();                      //初始化HAL库    
/*******BSP初始化************/     
    BSP_SYSCLOCK_INIT(RCC_PLL_MUL9);   //设置时钟,72Mhz  
    BSP_SYSTICK_INIT();
    BSP_LED_INIT(); 
	BSP_KEY_INIT();
	BSP_BEEP_INIT();
	BSP_EXTI_INIT();
	BSP_UART1_INIT(); 
//	BSP_UART2_INIT();	
//	BSP_OUT_IO_INIT();
//	BSP_IN_IO_INIT();	
    BSP_TIM2_INIT(1000-1,720-1);    //定时器2初始化，定时器周期10ms	
    BSP_TIM3_INIT(100-1,720-1);     //定时器3初始化，定时器周期1ms
//	BSP_TIM4_INIT(20000-1,720-1);   //定时器4初始化，定时器周期200ms
//    BSP_CRC_INIT();
//    BSP_IWDG_INIT(IWDG_PRESCALER_64,1000);  	//分频数为64,重载值为1000,溢出时间为2s

	//----延时500ms等待各设备稳定---
	BSP_SYSTICK_DELAY_MS(500); 
/*******FUNC初始化************/ 
	FUNC_BEEP_INIT();
	FUNC_ALONE_KEY_INIT();
	FUNC_OLED_INIT();
	FUNC_IR_DECODE_INIT();
	FUNC_IR_NEC_KEY_INIT();
	FUNC_DHT11_INIT();
	FUNC_PC_INTERFACE_COM_INIT();
/*******上电执行程序************/
	FUNC_S_NB_DELAY_MS_START(&main_nb_delay_ms1,2,500);
	//---初始化主状态机--
	FUNC_S_STATE_MACHINE1_INIT(&MAIN_CON_SM,MCS_ID_0);
	
/*******主循环************/   
	while(1)
	{		
//		BSP_IWDG_FEED();               //喂狗
        //-----更新OLED显示-------
		if(MAIN_CON_SM.state_m!=255)
		{	
			if(FUNC_OLED_GRAM_REFRESH()==0)//刷新OLED RAM
			{
				APP_OLED_DISPLAY_PICTURE(MAIN_CON_SM.state_m,MAIN_CON_SM.s_step); 
			}		
		}		
		//-----处理串口接收数据---
		BSP_USART1_RX_RINGBUF_PROCESS_TASK(1); 
//		BSP_USART2_RX_RINGBUF_PROCESS_TASK(1); 		
//		BSP_USART3_RX_RINGBUF_PROCESS_TASK(1); 	
        //------PC INTERFACE 工作---
		FUNC_PC_INTERFACE_COM_WORK_MAIN(1);
		//------温湿度传感器更新----
		FUNC_DHT11_REFRESH_MAIN();
		//------500ms定时工作任务---
		if(FUNC_S_NB_DELAY_MS_STATE(&main_nb_delay_ms1)==1)
		{
//			BSP_IO_LED1=!BSP_IO_LED1;	
//			BSP_IO_LED2=!BSP_IO_LED2;
//			BSP_IO_LED3=!BSP_IO_LED3;				
			
		}
		if(R_time_mark_500ms_mark1_b1==1)
		{
			CLR_time_mark_500ms_mark1_b1;
//			BSP_IO_LED1=!BSP_IO_LED1;	
//			BSP_IO_LED2=!BSP_IO_LED2;
//			BSP_IO_LED3=!BSP_IO_LED3;				
			
			
		}
		
        //-----主状态机-----    
        switch(MAIN_CON_SM.state)  //判断串口屏处于哪种工作模式
        {
			static STRUCT_FUNC_S_NB_DELAY nb_delay_ms1;
/***************************************************************************************************************/   
//           case MCS_ID_POWER_SLEEP:     //休眠模式状态
//			 {
//                MAIN_CON_SM.state_m=MCS_ID;
//                switch(MAIN_CON_SM.s_step)
//                {
//                    case 0:  //进入此状态的第一步
//                    {
//                     
//                        MAIN_CON_SM.s_step=1;                                             
//                    }break;	
//                    case 1:
//                    {

//                    };break;
//                    
//                    default:break;
//                }
//             }break;							 
/*********************************************************************************开机或复位状态**********************/
            case MCS_ID_POWER_UP:   //上电状态
            {
                /*******第一次进入此状态的处理*********/   
                switch(MAIN_CON_SM.state_m)     
                {
                    case MCS_ID_POWER_UP:
                    {
                        
                    }break;
                    case 255:   //代表为设备上电后第一次进入此状态
                    {
                        MAIN_CON_SM.s_step=0;   //需要做一些设备的初始化                       
                        
                    }break;
                    default:       //从其他界面跳转到此界面的
                    {
                        MAIN_CON_SM.s_step=0;                        
                    }break;
                }                   
                MAIN_CON_SM.state_m=MCS_ID_POWER_UP;
                /*****************************/                 
                switch(MAIN_CON_SM.s_step)
                {
                    case FUNC_S_SM1_STEP_IN:    //进入流程
                    {

						//-----进行蓝牙模块的初始配置---					
                        MAIN_CON_SM.s_step=1;       //进入下一步                         
                    }break;
                    case 1:    //在流程中,进行蓝牙模块的初始化设置
                    {
                        /**********状态跳转判断*******************/						
						if(1)
						{

                            MAIN_CON_SM.s_out_num=1;   //赋值退出号                              
                            MAIN_CON_SM.s_step=FUNC_S_SM1_STEP_OUT;       //进入下一步   						
						}						
                    }break;					
                    case FUNC_S_SM1_STEP_OUT:    //退出流程
                    {
                        //-----针对不同的退出号需要做的处理------
                        switch(MAIN_CON_SM.s_out_num)
                        {
                            case 0:
                            {
                                //非法操作
                            };break;                             
                            case 1:
                            {							
                                MAIN_CON_SM.state_n=MCS_ID_1;        //空闲状态
                                MAIN_CON_SM.s_step=0;                    //清0流程步数                                  
                                
                            };break;                                   
                            default:
                            {
                                //非法操作
                            };break;
                        }
                        //-----针对所有的退出号需要做的处理------
						FUNC_S_STATE_MACHINE1_SCHANGE(&MAIN_CON_SM); 
                      
                    };break;
                    default:break;
                }
            }break;           
            case MCS_ID_1:          //状态1
            {					
                /*******第一次进入此状态的处理*********/   
                switch(MAIN_CON_SM.state_m)     
                {
                    case MCS_ID_1:
                    {
                        
                    }break;
                    default:
                    {
                        MAIN_CON_SM.s_step=0;                        
                    }break;
                }                   
                MAIN_CON_SM.state_m=MCS_ID_1;
                /*****************************/                    
                switch(MAIN_CON_SM.s_step)  //独立流程控制状态机
                {
                    case FUNC_S_SM1_STEP_IN:   //进入流程
                    {
                        //------初始化一些状态-----

						MAIN_CON_SM.s_step=1;							 
                    }break;
                    case 1:
                    {						
                        //-------状态跳转----
//						if(1)     //判断
//						{			
//                            MAIN_CON_SM.s_out_num=1;   //赋值退出号                              
//                            MAIN_CON_SM.s_step=FUNC_S_SM1_STEP_OUT;       //进入下一步   							
//						}
						if(KEY_2==ALONE_KEY_ON)     //判断
						{	
							KEY_2=ALONE_KEY_IDLE;
                            MAIN_CON_SM.s_out_num=1;   //赋值退出号                              
                            MAIN_CON_SM.s_step=FUNC_S_SM1_STEP_OUT;       //进入下一步   							
						} 					
                    }break; 				
                    case FUNC_S_SM1_STEP_OUT:    //退出流程
                    {
                        //-----针对不同的退出号需要做的处理------
                        switch(MAIN_CON_SM.s_out_num)
                        {
                            case 0:
                            {
                                //非法操作
                            };break;                             
                            case 1:
                            {
                                MAIN_CON_SM.state_n=MCS_ID_2;            //跳转                                     
                                
                            };break; 
                            case 2:
                            {
                                MAIN_CON_SM.state_n=MCS_ID_2;            //跳转                                     
                                
                            };break; 							
                            default:
                            {
                                //非法操作
                            };break;
                        }
                        //-----针对所有的退出号需要做的处理------
						FUNC_S_STATE_MACHINE1_SCHANGE(&MAIN_CON_SM); 
                      
                    };break;
                    default:break;
                }                
            };break; 	
            case MCS_ID_2:          //状态2
            {
                /*******第一次进入此状态的处理*********/   
                switch(MAIN_CON_SM.state_m)     
                {
                    case MCS_ID_2:
                    {
                        
                    }break;
                    default:
                    {
                        MAIN_CON_SM.s_step=0;                        
                    }break;
                }                   
                MAIN_CON_SM.state_m=MCS_ID_2;
                /*****************************/                    
                switch(MAIN_CON_SM.s_step)  //独立流程控制状态机
                {
                    case FUNC_S_SM1_STEP_IN:   //进入流程
                    {
                        //------初始化一些状态-----
						
						MAIN_CON_SM.s_step=1;							 
                    }break;
                    case 1:
                    {	
						if(KEY_2==ALONE_KEY_ON)     //判断
						{	
							KEY_2=ALONE_KEY_IDLE;							
                            MAIN_CON_SM.s_out_num=1;   //赋值退出号                              
                            MAIN_CON_SM.s_step=FUNC_S_SM1_STEP_OUT;       //进入下一步   							
						}						
                    }break; 				
                    case FUNC_S_SM1_STEP_OUT:    //退出流程
                    {
                        //-----针对不同的退出号需要做的处理------
                        switch(MAIN_CON_SM.s_out_num)
                        {
                            case 0:
                            {
                                //非法操作
                            };break;
                            case 1:
                            {
                                MAIN_CON_SM.state_n=MCS_ID_3;            //跳转                                     
                                
                            };break; 							
                            default:
                            {
                                //非法操作
                            };break;
                        }
                        //-----针对所有的退出号需要做的处理------
						FUNC_S_STATE_MACHINE1_SCHANGE(&MAIN_CON_SM); 
                      
                    };break;
                    default:break;
                }                
            };break; 
            case MCS_ID_3:          //状态3
            {
                /*******第一次进入此状态的处理*********/   
                switch(MAIN_CON_SM.state_m)     
                {
                    case MCS_ID_3:
                    {
                        
                    }break;
                    default:
                    {
                        MAIN_CON_SM.s_step=0;                        
                    }break;
                }                   
                MAIN_CON_SM.state_m=MCS_ID_3;
                /*****************************/                    
                switch(MAIN_CON_SM.s_step)  //独立流程控制状态机
                {
                    case FUNC_S_SM1_STEP_IN:   //进入流程
                    {
                        //------初始化一些状态-----
						
						MAIN_CON_SM.s_step=1;							 
                    }break;
                    case 1:
                    {	
						if(KEY_2==ALONE_KEY_ON)     //判断
						{		
							KEY_2=ALONE_KEY_IDLE;							
                            MAIN_CON_SM.s_out_num=1;   //赋值退出号                              
                            MAIN_CON_SM.s_step=FUNC_S_SM1_STEP_OUT;       //进入下一步   							
						}						
                    }break; 				
                    case FUNC_S_SM1_STEP_OUT:    //退出流程
                    {
                        //-----针对不同的退出号需要做的处理------
                        switch(MAIN_CON_SM.s_out_num)
                        {
                            case 0:
                            {
                                //非法操作
                            };break;
                            case 1:
                            {
                                MAIN_CON_SM.state_n=MCS_ID_1;            //跳转                                     
                                
                            };break; 							
                            default:
                            {
                                //非法操作
                            };break;
                        }
                        //-----针对所有的退出号需要做的处理------
						FUNC_S_STATE_MACHINE1_SCHANGE(&MAIN_CON_SM); 
                      
                    };break;
                    default:break;
                }                
            };break; 			
			default:break;
		}		
	}
}

    


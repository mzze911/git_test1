#ifndef _BSP_OUT_IO_H_
#define _BSP_OUT_IO_H_

#include "bsp_stm32f1_mzze.h"

////-------485通讯收发控制端口--------
//#define BSP_OUT_IO_485_1 PHout(8)
//#define BSP_485_1_TX  1
//#define BSP_485_1_RX  0

//-------电磁阀控制端口--------
#define BSP_AIR_SWITCH1_IO PEout(3)
#define BSP_AIR_SWITCH2_IO PEout(4)
#define BSP_AIR_SWITCH3_IO PEout(5)
#define BSP_AIR_SWITCH4_IO PEout(6)


#define BSP_AIR_SWITCH_ON   0     //打开
#define BSP_AIR_SWITCH_OFF  1     //关闭


//-------WIFI模块控制--------
#define BSP_WIFI_NREST_IO PCout(9)

#define BSP_WIFI_NREST_L  0     //复位低
#define BSP_WIFI_NREST_H  1     //复位高



extern void BSP_OUT_IO_INIT(void);















#endif



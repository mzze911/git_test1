#ifndef _BSP_DHT11_IO_H_
#define _BSP_DHT11_IO_H_

#include "bsp_stm32f1_mzze.h"

/*******DHT11使能********/
#define BSP_DHT11_1_EN 1
//#define BSP_DHT11_2_EN 1
//#define BSP_DHT11_3_EN 1
//#define BSP_DHT11_4_EN 1



//-------DHT11温湿度数据端口--------
#ifdef BSP_DHT11_1_EN
//#define BSP_DHT11_IO_1_DIN PAin(15)          //温湿度1
//#define BSP_DHT11_IO_1_DOUT PAout(15)        //温湿度1

//#define BSP_DHT11_IO_1_DIN PBin(0)          //温湿度1
//#define BSP_DHT11_IO_1_DOUT PBout(0)        //温湿度1

#define BSP_DHT11_IO_1_DIN PBin(3)          //温湿度1
#define BSP_DHT11_IO_1_DOUT PBout(3)        //温湿度1
#endif
#ifdef BSP_DHT11_2_EN
#define BSP_DHT11_IO_2_DIN PCin(7)          //温湿度2
#define BSP_DHT11_IO_2_DOUT PCout(7)        //温湿度2
#endif
#ifdef BSP_DHT11_3_EN
#define BSP_DHT11_IO_3_DIN PAin(15)          //温湿度3
#define BSP_DHT11_IO_3_DOUT PAout(15)        //温湿度3
#endif
#ifdef BSP_DHT11_4_EN
#define BSP_DHT11_IO_4_DIN PBin(3)          //温湿度4
#define BSP_DHT11_IO_4_DOUT PBout(3)        //温湿度4
#endif



#define BSP_DHT11_D_ON   1   //数据高电平
#define BSP_DHT11_D_OFF  0   //数据低电平



extern void BSP_DHT11_IO_MODE_OUT(unsigned char id);

extern void BSP_DHT11_IO_MODE_IN(unsigned char id);

extern void BSP_DHT11_IO_D_WRITE(unsigned char id,unsigned char n);

extern unsigned char BSP_DHT11_IO_D_READ(unsigned char id);

extern void BSP_DHT11_IO_INIT(unsigned char id);












#endif



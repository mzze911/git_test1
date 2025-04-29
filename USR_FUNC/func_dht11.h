#ifndef __FUNC_DHT11_H__
#define __FUNC_DHT11_H__


#include "bsp_stm32f1_mzze.h"


//---结构体---
typedef struct
{
	//--参数---
	unsigned char par_as_num;          //传感器号
    unsigned short int par_ic_temp_data;  //读到的温度数据
	unsigned short int par_ic_humi_data;  //读到的湿度数据
	//--状态---
	unsigned char state_err;    //0-无意义  1-无故障  2-有故障
	float state_temp_c;    //温度    摄氏度，单位0.1度
	float state_temp_f;    //温度    华氏度，单位0.1度
	float state_humi;      //湿度    单位0.1%
    //---------延时控制------------
	unsigned long int con_sys_tick_count;   //系统节拍记录     //单位ms
	unsigned long int con_time_delay;        //延时，单位为系统节拍	//单位ms	
    //---------采样时间控制------------
	unsigned long int con_time_samp_tick_count;   //系统节拍记录     //单位ms
	unsigned long int con_time_samp;        //采样频率，单位为系统节拍	
	//---------读取控制------------	
	unsigned char con_get_temp_humi_state;       //获取温度湿度状态	
	unsigned short int con_get_data_suce_count;       //成功计数	
	unsigned short int con_get_data_fail_count;       //失败计数	
	
}FUNC_DHT11_INF_STRUCT;



//---温度传感器构体定义----
extern FUNC_DHT11_INF_STRUCT  FUNC_DHT11_1_INF;    //温度传感器1信息
//extern FUNC_DHT11_INF_STRUCT  FUNC_DHT11_2_INF;    //温度传感器2信息
//extern FUNC_DHT11_INF_STRUCT  FUNC_DHT11_3_INF;    //温度传感器3信息
//extern FUNC_DHT11_INF_STRUCT  FUNC_DHT11_4_INF;    //温度传感器4信息







extern void FUNC_DHT11_INIT(void);

extern void FUNC_DHT11_GET_TEMP_HUMI(FUNC_DHT11_INF_STRUCT*as);

extern void FUNC_DHT11_REFRESH_MAIN(void);



#endif



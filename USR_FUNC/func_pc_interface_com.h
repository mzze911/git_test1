#ifndef __FUNC_PC_INTERFACE_COM_H__
#define __FUNC_PC_INTERFACE_COM_H__

#include "bsp_stm32f1_mzze.h"
#include "func_s_ring_queue.h"
#include "func_s_data_flow_process.h"



//-------结构体变量定义-----

//----对外通讯模块对象结构体定义---
typedef struct{
    
	//--参数---	
	unsigned char par_module_id;                //模块ID

	//--状态---
	unsigned char state_err;         //故障  0:无意义   1:无故障   2:有故障

	//--控制---
	//---------临时寄存器----------
	unsigned short int con_u16_r[5];
	unsigned char con_u8_r[5];
	
    //---------延时控制------------
	unsigned long int con_sys_tick_count;   //系统节拍记录     //单位ms
	unsigned long int con_time_delay;        //延时，单位为系统节拍	//单位ms	
	//---------接收数据帧标志----
	unsigned char con_get_frame_id_mark[0xff];  //收到的帧	 
	

	//---------被动通讯控制--------	
#define FIN_SHOU_BUFFER_BYTE_NUM 50	
	unsigned char con_pscom_shou_buffer[FIN_SHOU_BUFFER_BYTE_NUM];  //接收缓冲区
	FUNC_S_STRUCT_RING_QUEUE8 con_pscom_shou_que;               //定义一个接收环形队列		
	unsigned char con_pscom_en_shou;                            //接收控制位 0--->不允许接收   1----->允许接受	  

	//------------被动通讯检查--------
//	unsigned char con_pscom_shou_state;                         //被动通讯接收状态机		
//	unsigned char con_pscom_shou_ok;
	unsigned char con_pscom_fa_buf[512];                 //接收检查缓冲区
	unsigned char con_pscom_shou_check_buf[30];                 //接收检查缓冲区
	STRUCT_FUNC_SDF_FIND_FORMAT5_DATA con_pscom_shou_check;




}STRUCT_FUNC_PC_INTERFACE_COM;




//-------对外接口变量---------
extern STRUCT_FUNC_PC_INTERFACE_COM  FUNC_PC_INTERFACE_COM1;        //通讯模块数据变量
//-----对外通讯接口接收到的数据定义----
//-----系统相关数据----
extern unsigned char FUNC_PC_INTERFACE_COM1_SYS_DEV_CON_CMD;    //控制下位机设备

//-----传感器相关数据-----
extern unsigned char FUNC_PC_INTERFACE_COM1_SENSOR1_GET_CMD_MARK;   //获取到命令标志
extern unsigned char FUNC_PC_INTERFACE_COM1_SENSOR2_GET_CMD_MARK;   //获取到命令标志
extern _16_union FUNC_PC_INTERFACE_COM1_SENSOR1_UPDATA_CMD;  //一类传感器数据更新命令
extern _16_union FUNC_PC_INTERFACE_COM1_SENSOR2_UPDATA_CMD;  //二类传感器数据更新命令


//-----电磁阀相关数据-----
extern unsigned char FUNC_PC_INTERFACE_COM1_SWITCH1_CON_CMD;  //控制电磁阀1
extern unsigned char FUNC_PC_INTERFACE_COM1_SWITCH2_CON_CMD;  //控制电磁阀2

//-----风机相关数据-----
extern unsigned char FUNC_PC_INTERFACE_COM1_FLOW_FAN_CON_CMD;  //控制流量风机
extern _16_union FUNC_PC_INTERFACE_COM1_FLOW_FAN_SPEED_CMD;  //控制流量风机速度

//-------对外接口函数---------
extern void FUNC_PC_INTERFACE_COM_UART_RX_ISR(STRUCT_FUNC_PC_INTERFACE_COM* ic,unsigned char res);


extern void FUNC_PC_INTERFACE_COM_INIT(void);
extern unsigned char FUNC_PC_INTERFACE_COM_WORK_MAIN(unsigned char p1);






#endif

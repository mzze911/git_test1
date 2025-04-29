#ifndef _FUNC_S_DATA_FLOW_PROCESS_H_
#define _FUNC_S_DATA_FLOW_PROCESS_H_

#include "bsp_stm32f1_mzze.h"



//---从数据流中找到符合条件的一串数据---
//----结构体定义----------
typedef struct{
    
	//--参数---	
	unsigned char *find_data;             //需要寻找的数据格式
	unsigned char find_pos;               //寻找到的位置
	unsigned char find_result;            //寻找结果  0未找到 1找到
	unsigned short int find_data_flow_pos;    //寻找到的数据在数据流中的位置
	unsigned char *store_d;               //保存找到的数据
	unsigned char store_d_size;		      //保存空间大小
}STRUCT_FUNC_SDF_FIND_DATA;


typedef struct{
    
	//--参数---	
	unsigned char *frame_buf;              //缓冲区
	unsigned char frame_buf_size;          //缓冲区大小

	unsigned char frame_head1;             //帧头1
	unsigned char frame_head2;             //帧头2

	unsigned char frame_buf_write_pos;     //写索引
	unsigned char frame_find_state;        //寻找状态
	_16_union frame_data_size;         //帧数据大小	
	unsigned char find_result;             //寻找结果  0未找到 1找到

}STRUCT_FUNC_SDF_FIND_FORMAT1_DATA;



typedef struct{
    
	//--参数---	
	unsigned char *frame_buf;              //缓冲区
	unsigned char frame_buf_size;          //缓冲区大小

	unsigned char data1_bit_format;             //数据1位格式
	unsigned char data2_bit_format;             //数据2位格式
	unsigned char data3_bit_format;             //数据3位格式
	unsigned char data4_bit_format;             //数据4位格式
	unsigned char data5_bit_format;             //数据5位格式

	unsigned char data1_bit_format_mask;             //数据1位格式掩码
	unsigned char data2_bit_format_mask;             //数据2位格式掩码
	unsigned char data3_bit_format_mask;             //数据3位格式掩码
	unsigned char data4_bit_format_mask;             //数据4位格式掩码
	unsigned char data5_bit_format_mask;             //数据5位格式掩码
	
	unsigned char frame_find_state;        //寻找状态
	unsigned char find_result;             //寻找结果  0未找到 1找到

}STRUCT_FUNC_SDF_FIND_FORMAT2_DATA;


typedef struct{
    
	//--参数---	
	unsigned char *frame_buf;              //缓冲区
	unsigned char frame_buf_size;          //缓冲区大小

	unsigned char frame_head1;             //帧头1
	unsigned char frame_head2;             //帧头2
	
	unsigned char frame_buf_write_pos;     //写索引
	unsigned char frame_find_state;        //寻找状态
	_16_union frame_data_size;         //帧数据大小	
	unsigned char find_result;             //寻找结果  0未找到 1找到

}STRUCT_FUNC_SDF_FIND_FORMAT3_DATA;


typedef struct{
    
	//--参数---	
	unsigned char *frame_buf;              //缓冲区
	unsigned short int frame_buf_size;          //缓冲区大小

	unsigned char frame_head1;             //帧头1
	
	unsigned short int frame_buf_write_pos;     //写索引
	unsigned char frame_find_state;        //寻找状态
	_16_union frame_data_size;         //帧数据大小	
	unsigned char find_result;             //寻找结果  0未找到 1找到

}STRUCT_FUNC_SDF_FIND_FORMAT4_DATA;


typedef struct{
    
	//--参数---	
	unsigned char *frame_buf;              //缓冲区
	unsigned char frame_buf_size;          //缓冲区大小

	unsigned char frame_head1;             //帧头1
	unsigned char frame_head2;             //帧头2

	unsigned char frame_buf_write_pos;     //写索引
	unsigned char frame_find_state;        //寻找状态
	_16_union frame_data_size;         //帧数据大小	
	unsigned char find_result;             //寻找结果  0未找到 1找到

}STRUCT_FUNC_SDF_FIND_FORMAT5_DATA;




//----寻找数据定长比对------
extern void FUNC_SDF_FIND_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_DATA *fd,unsigned char *find_d,unsigned char*store_d,unsigned char store_d_size);
extern void FUNC_SDF_FIND_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_DATA *fd);
extern void FUNC_SDF_FIND_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_DATA *fd,unsigned char r,unsigned short int r_pos);


//----寻找数据规定格式1-------
extern void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2);
extern void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d);
extern void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d,unsigned char r);


//----寻找数据规定格式2-------
extern void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA *f2d,unsigned char*store_d,unsigned char store_d_size);
extern void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA *f2d);
extern void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA *f2d,unsigned char r);

//----寻找数据规定格式3-------
extern void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2);
extern void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d);
extern void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d,unsigned char r);

//----寻找数据规定格式4-------
extern void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d,unsigned char*store_d,unsigned short int store_d_size,unsigned char h1);
extern void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d);
extern void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d,unsigned char r);

//----寻找数据规定格式5-------
extern void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2);
extern void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d);
extern void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d,unsigned char r);





#endif







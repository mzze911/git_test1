#include "func_s_data_flow_process.h"
#include "func_s_crc8.h"
#include "func_s_crc16.h"
#include "func_s_xorc8.h"







/*------数据流处理功能函数--------*/

//---从数据流中找到符合条件的一串数据---
void FUNC_SDF_FIND_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_DATA *fd,unsigned char *find_d,unsigned char*store_d,unsigned char store_d_size)
{
	fd->find_data=find_d;
	fd->find_pos=0;
	fd->find_data_flow_pos=0xffff;
	fd->find_result=0;
	fd->store_d=store_d;
	fd->store_d_size=store_d_size;	
}



void FUNC_SDF_FIND_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_DATA *fd)
{
	
	fd->find_pos=0;
	fd->find_data_flow_pos=0xffff;
	fd->find_result=0;
	
}


void FUNC_SDF_FIND_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_DATA *fd,unsigned char r ,unsigned short int r_pos)
{
	if(fd->find_result==0)
	{
		//-------正在寻找-------------
		if(
			((r)== fd->find_data[fd->find_pos])
			||(fd->find_data[fd->find_pos]=='*')
		)
		{
			//----记录信息起始地址---
			if(fd->find_data_flow_pos==0xffff)
			{
				fd->find_data_flow_pos=r_pos;
			}
			//----记录数据----
			if(
				(fd->store_d!=0)
				&&(fd->find_pos<fd->store_d_size)
			)
			{
				fd->store_d[fd->find_pos]=r;
			}
			//----改变状态----
			(fd->find_pos)++;

		}
		else
		{
			fd->find_data_flow_pos=0xffff;  //清楚有用信息
			fd->find_pos = 0;
			//---------判断当前数据是否是第一个数据------
			if(
				((r)== fd->find_data[fd->find_pos])
				||(fd->find_data[fd->find_pos]=='*')
			)
			{
				//----记录信息起始地址---
				if(fd->find_data_flow_pos==0xffff)
				{
					fd->find_data_flow_pos=r_pos;
				}
				//----记录数据----
				if(
					(fd->store_d!=0)
					&&(fd->find_pos<fd->store_d_size)
				)
				{
					fd->store_d[fd->find_pos]=r;					
				}				
				//----改变状态----
				(fd->find_pos)++;
			}			
		}
		//------判断是否需要结束寻找-------
		if(fd->find_data[fd->find_pos]=='\0')   
		{
			//----成功找到---
			fd->find_result=1;	
		}		
	}
}


//---从数据流中找到符合一定格式1要求的一串数据---
void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2)
{
	unsigned char i=0;
	f1d->frame_buf=store_d;              //缓冲区
	f1d->frame_buf_size=store_d_size;          //缓冲区大小
	for(i=0;i<f1d->frame_buf_size;i++)
	{
		f1d->frame_buf[i]=0;
	}
	f1d->frame_head1=h1;             //帧头1
	f1d->frame_head2=h2;             //帧头2

	f1d->frame_buf_write_pos=0;     //写索引
	f1d->frame_find_state=0;        //寻找状态
	f1d->frame_data_size.all=0;         //帧数据大小	
	f1d->find_result=0;             //寻找结果  0未找到 1找到
}



void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d)
{
	unsigned char i=0;
	for(i=0;i<f1d->frame_buf_size;i++)
	{
		f1d->frame_buf[i]=0;
	}	
	f1d->frame_buf_write_pos=0;     //写索引
	f1d->frame_find_state=0;        //寻找状态
	f1d->frame_data_size.all=0;         //帧数据大小	
	f1d->find_result=0;             //寻找结果  0未找到 1找到
	
}


void FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT1_DATA *f1d,unsigned char r)
{
	if(f1d->find_result==0)
	{
		//----接收状态机-----
		switch(f1d->frame_find_state)
		{
			case 0:      //寻找帧头
			{
				f1d->frame_buf[1]=r;    //提取数据
				if(
					(f1d->frame_buf[0]==f1d->frame_head1)
					&&(f1d->frame_buf[1]==f1d->frame_head2)
				)     //找到帧头                               
				{
					f1d->frame_find_state=1;
				}
				else
				{
					f1d->frame_buf[0]=f1d->frame_buf[1];
				}
				
			}break;	
			case 1:      //接收命令字
			{
				f1d->frame_buf[2]=r;  
				f1d->frame_find_state=2;
			}break;				
			case 2:      //接收数据字节数1
			{
				f1d->frame_buf[3]=r;  
				f1d->frame_find_state=3;
			}break;	
			case 3:      //接收数据字节数2
			{
				f1d->frame_buf[4]=r;
				f1d->frame_data_size.h_l.l=f1d->frame_buf[3];
				f1d->frame_data_size.h_l.h=f1d->frame_buf[4];
				if(f1d->frame_data_size.all<=(f1d->frame_buf_size-7))
				{
					f1d->frame_find_state=4;
					f1d->frame_buf_write_pos=0;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_RESET(f1d);
					
				}
			}break;			
			case 4:      //接收字节
			{
				f1d->frame_buf[f1d->frame_buf_write_pos+5]=r;
				f1d->frame_buf_write_pos++;	
				
				if(f1d->frame_buf_write_pos==((f1d->frame_data_size.all)+2))  //接收完成
				{
                    //----进行crc校验---
                    if(
						(FUNC_S_CRC16_MODBUS_CHECK(&(f1d->frame_buf[2]),((f1d->frame_data_size.all)+5))==0x0000)  //如果校验成功
					)
                    {						
						f1d->find_result=1;						
                    }
                    else  
                    {
						FUNC_SDF_FIND_FORMAT1_DATA_FROM_FLOW_RESET(f1d);
                    } 										
				}
			}break;			
			default:break;

		}		
	}
}



//---从数据流中找到符合一定格式2要求的一串数据---
void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA *f2d,unsigned char*store_d,unsigned char store_d_size)	
{
	unsigned char i=0;
	f2d->frame_buf=store_d;              //缓冲区
	f2d->frame_buf_size=store_d_size;          //缓冲区大小
	for(i=0;i<f2d->frame_buf_size;i++)
	{
		f2d->frame_buf[i]=0;
	}
	
	f2d->data1_bit_format=0x80;             //数据1位格式
	f2d->data2_bit_format=0x00;             //数据2位格式
	f2d->data3_bit_format=0x00;             //数据3位格式
	f2d->data4_bit_format=0x00;             //数据4位格式
	f2d->data5_bit_format=0x00;             //数据5位格式

	f2d->data1_bit_format_mask=0x80;             //数据1位格式掩码
	f2d->data2_bit_format_mask=0x80;             //数据2位格式掩码
	f2d->data3_bit_format_mask=0x80;             //数据3位格式掩码
	f2d->data4_bit_format_mask=0x80;             //数据4位格式掩码
	f2d->data5_bit_format_mask=0x80;             //数据5位格式掩码

	f2d->frame_find_state=0;        //寻找状态	
	f2d->find_result=0;             //寻找结果  0未找到 1找到
}



void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA *f2d)
{
	unsigned char i=0;
	for(i=0;i<f2d->frame_buf_size;i++)
	{
		f2d->frame_buf[i]=0;
	}	
	f2d->frame_find_state=0;        //寻找状态
	f2d->find_result=0;             //寻找结果  0未找到 1找到
	
}


void FUNC_SDF_FIND_FORMAT2_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT2_DATA  *f2d,unsigned char r)
{
	unsigned char r_bit_format=0;
	if(f2d->find_result==0)
	{
		//----接收状态机-----
		switch(f2d->frame_find_state)
		{
			case 0:      //寻找data1
			{
				//--提取特征--
				r_bit_format=r&(f2d->data1_bit_format_mask);
				f2d->data1_bit_format&=(f2d->data1_bit_format_mask);
				//--比较特征--
				if(r_bit_format==(f2d->data1_bit_format))//找到                              
				{
					f2d->frame_buf[f2d->frame_find_state]=r;    //提取数据
					f2d->frame_find_state=1;
				}
				else
				{
					f2d->frame_find_state=0;
				}				
			}break;	
			case 1:      //寻找data2
			{
				//--提取特征--
				r_bit_format=r&(f2d->data2_bit_format_mask);
				f2d->data2_bit_format&=(f2d->data2_bit_format_mask);
				//--比较特征--
				if(r_bit_format==(f2d->data2_bit_format))//找到                              
				{
					f2d->frame_buf[f2d->frame_find_state]=r;    //提取数据
					f2d->frame_find_state=2;
				}
				else
				{
					f2d->frame_find_state=0;
				}				
			}break;	
			case 2:      //寻找data3
			{
				//--提取特征--
				r_bit_format=r&(f2d->data3_bit_format_mask);
				f2d->data3_bit_format&=(f2d->data3_bit_format_mask);
				//--比较特征--
				if(r_bit_format==(f2d->data3_bit_format))//找到                              
				{
					f2d->frame_buf[f2d->frame_find_state]=r;    //提取数据
					f2d->frame_find_state=3;
				}
				else
				{
					f2d->frame_find_state=0;
				}				
			}break;
			case 3:      //寻找data4
			{
				//--提取特征--
				r_bit_format=r&(f2d->data4_bit_format_mask);
				f2d->data4_bit_format&=(f2d->data4_bit_format_mask);
				//--比较特征--
				if(r_bit_format==(f2d->data4_bit_format))//找到                              
				{
					f2d->frame_buf[f2d->frame_find_state]=r;    //提取数据
					f2d->frame_find_state=4;
				}
				else
				{
					f2d->frame_find_state=0;
				}				
			}break;			
			case 4:      //寻找data5
			{
				//--提取特征--
				r_bit_format=r&(f2d->data5_bit_format_mask);
				f2d->data5_bit_format&=(f2d->data5_bit_format_mask);
				//--比较特征--
				if(r_bit_format==(f2d->data5_bit_format))//找到                              
				{
					f2d->frame_buf[f2d->frame_find_state]=r;    //提取数据
					f2d->frame_find_state=5;
					f2d->find_result=1;             //寻找结果  0未找到 1找到
				}
				else
				{
					f2d->frame_find_state=0;
				}				
			}break;			
			default:break;

		}		
	}
}


//---从数据流中找到符合一定格式3要求的一串数据---
void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2)
{
	unsigned char i=0;
	f3d->frame_buf=store_d;              //缓冲区
	f3d->frame_buf_size=store_d_size;          //缓冲区大小
	for(i=0;i<f3d->frame_buf_size;i++)
	{
		f3d->frame_buf[i]=0;
	}
	f3d->frame_head1=h1;             //帧头1
	f3d->frame_head2=h2;             //帧头2

	f3d->frame_buf_write_pos=0;     //写索引
	f3d->frame_find_state=0;        //寻找状态
	f3d->frame_data_size.all=0;         //帧数据大小	
	f3d->find_result=0;             //寻找结果  0未找到 1找到
}



void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d)
{
	unsigned char i=0;
	for(i=0;i<f3d->frame_buf_size;i++)
	{
		f3d->frame_buf[i]=0;
	}	
	f3d->frame_buf_write_pos=0;     //写索引
	f3d->frame_find_state=0;        //寻找状态
	f3d->frame_data_size.all=0;         //帧数据大小	
	f3d->find_result=0;             //寻找结果  0未找到 1找到
	
}


void FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT3_DATA *f3d,unsigned char r)
{
	if(f3d->find_result==0)
	{
		//----接收状态机-----
		switch(f3d->frame_find_state)
		{
			case 0:      //寻找帧头
			{
				f3d->frame_buf[1]=r;    //提取数据
				if(
					(f3d->frame_buf[0]==f3d->frame_head1)
					&&(f3d->frame_buf[1]==f3d->frame_head2)
				)     //找到帧头                               
				{
					f3d->frame_find_state=1;
				}
				else
				{
					f3d->frame_buf[0]=f3d->frame_buf[1];
				}
				
			}break;	
			case 1:      //接收命令字
			{
				f3d->frame_buf[2]=r;  
				if(r==0x02)
				{
					f3d->frame_find_state=2;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_RESET(f3d);
					
				}				

			}break;				
			case 2:      //接收数据字节数
			{
				f3d->frame_buf[3]=r;  
				f3d->frame_data_size.h_l.l=f3d->frame_buf[3];
				f3d->frame_data_size.h_l.h=0;
				if(f3d->frame_data_size.all<=(f3d->frame_buf_size-5))
				{
					f3d->frame_find_state=3;
					f3d->frame_buf_write_pos=0;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_RESET(f3d);
					
				}
			}break;			
			case 3:      //接收字节
			{
				f3d->frame_buf[f3d->frame_buf_write_pos+4]=r;
				f3d->frame_buf_write_pos++;	
				
				if(f3d->frame_buf_write_pos==((f3d->frame_data_size.all)+1))  //接收完成
				{
                    //----进行异或校验---
                    if(
						(FUNC_S_XORC8_CHECK(&(f3d->frame_buf[2]),((f3d->frame_data_size.all)+3))==0x01)  //如果校验成功
					)
                    {						
						f3d->find_result=1;						
                    }
                    else  
                    {
						FUNC_SDF_FIND_FORMAT3_DATA_FROM_FLOW_RESET(f3d);
                    } 										
				}
			}break;			
			default:break;

		}		
	}
}



//---从数据流中找到符合一定格式4要求的一串数据---
void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d,unsigned char*store_d,unsigned short int store_d_size,unsigned char h1)		
{
	unsigned short int i=0;
	f4d->frame_buf=store_d;              //缓冲区
	f4d->frame_buf_size=store_d_size;          //缓冲区大小
	for(i=0;i<f4d->frame_buf_size;i++)
	{
		f4d->frame_buf[i]=0;
	}
	f4d->frame_head1=h1;             //帧头1

	f4d->frame_buf_write_pos=0;     //写索引
	f4d->frame_find_state=0;        //寻找状态
	f4d->frame_data_size.all=0;         //帧数据大小	
	f4d->find_result=0;             //寻找结果  0未找到 1找到
}



void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d)
{
	unsigned short int i=0;
	for(i=0;i<f4d->frame_buf_size;i++)
	{
		f4d->frame_buf[i]=0;
	}	
	f4d->frame_buf_write_pos=0;     //写索引
	f4d->frame_find_state=0;        //寻找状态
	f4d->frame_data_size.all=0;         //帧数据大小	
	f4d->find_result=0;             //寻找结果  0未找到 1找到
	
}


void FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT4_DATA *f4d,unsigned char r)
{
	if(f4d->find_result==0)
	{
		//----接收状态机-----
		switch(f4d->frame_find_state)
		{
			case 0:      //寻找帧头
			{
				f4d->frame_buf[3]=r;    //提取数据
				if(
					(f4d->frame_buf[0]==f4d->frame_head1)
					&&((f4d->frame_buf[1]+f4d->frame_buf[2])==0xff)   //cmd ~cmd
					&&(f4d->frame_buf[3]==0x01)	  //pa_type		
				)     //找到帧头                               
				{
					f4d->frame_find_state=1;
				}
				else
				{
					f4d->frame_buf[0]=f4d->frame_buf[1];
					f4d->frame_buf[1]=f4d->frame_buf[2];
					f4d->frame_buf[2]=f4d->frame_buf[3];				
				}
				
			}break;	
			case 1:      //接收包号
			{
				f4d->frame_buf[4]=r;  
				if(r!=0xff)
				{
					f4d->frame_find_state=2;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_RESET(f4d);
					
				}				

			}break;				
			case 2:      //接收数据字节数
			{
				f4d->frame_buf[5]=r;  
				f4d->frame_data_size.h_l.l=f4d->frame_buf[5];
				f4d->frame_find_state=3;				
			}break;		
			case 3:      //接收数据字节数
			{
				f4d->frame_buf[6]=r;  
				f4d->frame_data_size.h_l.h=f4d->frame_buf[6];
				if(f4d->frame_data_size.all<=(f4d->frame_buf_size-7))
				{
					f4d->frame_find_state=4;
					f4d->frame_buf_write_pos=0;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_RESET(f4d);
					
				}
			}break;					
			case 4:      //接收字节
			{
				f4d->frame_buf[f4d->frame_buf_write_pos+7]=r;
				f4d->frame_buf_write_pos++;	
				
				if(f4d->frame_buf_write_pos==((f4d->frame_data_size.all)+1))  //接收完成
				{
                    //----进行异或校验---
                    if(
						(FUNC_S_CRC8_CHECK(&(f4d->frame_buf[0]),((f4d->frame_data_size.all)+8))==0x00)  //如果校验成功
					)
                    {						
						f4d->find_result=1;						
                    }
                    else  
                    {
						FUNC_SDF_FIND_FORMAT4_DATA_FROM_FLOW_RESET(f4d);
                    } 										
				}
			}break;			
			default:break;

		}		
	}
}


//---从数据流中找到符合一定格式5要求的一串数据---
void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_INIT(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d,unsigned char*store_d,unsigned char store_d_size,unsigned char h1,unsigned char h2)
{
	unsigned char i=0;
	f1d->frame_buf=store_d;              //缓冲区
	f1d->frame_buf_size=store_d_size;          //缓冲区大小
	for(i=0;i<f1d->frame_buf_size;i++)
	{
		f1d->frame_buf[i]=0;
	}
	f1d->frame_head1=h1;             //帧头1
	f1d->frame_head2=h2;             //帧头2

	f1d->frame_buf_write_pos=0;     //写索引
	f1d->frame_find_state=0;        //寻找状态
	f1d->frame_data_size.all=0;         //帧数据大小	
	f1d->find_result=0;             //寻找结果  0未找到 1找到
}



void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_RESET(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d)
{
	unsigned char i=0;
	for(i=0;i<f1d->frame_buf_size;i++)
	{
		f1d->frame_buf[i]=0;
	}	
	f1d->frame_buf_write_pos=0;     //写索引
	f1d->frame_find_state=0;        //寻找状态
	f1d->frame_data_size.all=0;         //帧数据大小	
	f1d->find_result=0;             //寻找结果  0未找到 1找到
	
}


void FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_ON(STRUCT_FUNC_SDF_FIND_FORMAT5_DATA *f1d,unsigned char r)
{
	if(f1d->find_result==0)
	{
		//----接收状态机-----
		switch(f1d->frame_find_state)
		{
			case 0:      //寻找帧头
			{
				f1d->frame_buf[1]=r;    //提取数据
				if(
					(f1d->frame_buf[0]==f1d->frame_head1)
					&&(f1d->frame_buf[1]==f1d->frame_head2)
				)     //找到帧头                               
				{
					f1d->frame_find_state=1;
				}
				else
				{
					f1d->frame_buf[0]=f1d->frame_buf[1];
				}
				
			}break;	
			case 1:      //接收命令字
			{
				f1d->frame_buf[2]=r;  
				f1d->frame_find_state=2;
			}break;				
			case 2:      //接收数据字节数1
			{
				f1d->frame_buf[3]=r;
				f1d->frame_data_size.all=f1d->frame_buf[3];
				if(f1d->frame_data_size.all<=(f1d->frame_buf_size-6))
				{
					f1d->frame_find_state=3;
					f1d->frame_buf_write_pos=0;
				}
				else
				{
					FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_RESET(f1d);
					
				}
			}break;			
			case 3:      //接收字节
			{
				f1d->frame_buf[f1d->frame_buf_write_pos+4]=r;
				f1d->frame_buf_write_pos++;	
				
				if(f1d->frame_buf_write_pos==((f1d->frame_data_size.all)+2))  //接收完成
				{
                    //----进行crc校验---
                    if(
						(FUNC_S_CRC16_MODBUS_CHECK(&(f1d->frame_buf[2]),((f1d->frame_data_size.all)+4))==0x0000)  //如果校验成功
					)
                    {						
						f1d->find_result=1;						
                    }
                    else  
                    {
						FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_RESET(f1d);
                    } 										
				}
			}break;			
			default:break;

		}		
	}
}



















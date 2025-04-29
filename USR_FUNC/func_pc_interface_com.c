#include "func_pc_interface_com.h"
#include "bsp_uart.h"
#include "bsp_led.h"

#include "func_s_crc16.h"
#include "func_s_version_con.h"



//#include "func_air_switch_con.h"
//#include "func_flow_fan_con.h"
//#include "func_co2_sensor.h"
//#include "func_o2_detect.h"
//#include "func_spi_ad7683.h"
//#include "func_ntc_temp_detect.h"
//#include "func_ms5540c.h"
//#include "func_temp_humi_detect.h"
//#include "app_local_con.h"

//#include "func_bat_con.h"
//#include "func_hsc_press.h"
#include "main.h"


/**********变量定义***************/

//-----各对象变量定义-----
STRUCT_FUNC_PC_INTERFACE_COM  FUNC_PC_INTERFACE_COM1;        //对外通讯接口1

//-----对外通讯接口接收到的数据定义----
//-----系统相关数据----
unsigned char FUNC_PC_INTERFACE_COM1_SYS_DEV_CON_CMD=0;    //控制下位机设备

//-----传感器相关数据-----
unsigned char FUNC_PC_INTERFACE_COM1_SENSOR1_GET_CMD_MARK;   //获取到命令标志
unsigned char FUNC_PC_INTERFACE_COM1_SENSOR2_GET_CMD_MARK;   //获取到命令标志
_16_union FUNC_PC_INTERFACE_COM1_SENSOR1_UPDATA_CMD;  //一类传感器数据更新命令
_16_union FUNC_PC_INTERFACE_COM1_SENSOR2_UPDATA_CMD;  //二类传感器数据更新命令


//-----电磁阀相关数据-----
unsigned char FUNC_PC_INTERFACE_COM1_SWITCH1_CON_CMD=0;  //控制电磁阀1
unsigned char FUNC_PC_INTERFACE_COM1_SWITCH2_CON_CMD=0;  //控制电磁阀2

//-----风机相关数据-----
unsigned char FUNC_PC_INTERFACE_COM1_FLOW_FAN_CON_CMD=0;  //控制流量风机
_16_union FUNC_PC_INTERFACE_COM1_FLOW_FAN_SPEED_CMD;  //控制流量风机速度

/**********发送一个字符串**************************/
static void interface_fa_buf(STRUCT_FUNC_PC_INTERFACE_COM*ic,unsigned char *b,unsigned short int b_l)
{
/*
 *函数名：interface_fa_buf
 *描述  ：通过串口发送一组数据
 *输入  ：字符串
 *输出  ：无
 *调用  ：内部调用
*/    
	switch(ic->par_module_id)
	{
		case 1:  
		{			
			BSP_USART1_SEND_BUF(b,b_l);
		}break;
		default:break;
	}		
}

/**********获取发送状态**************************/
static unsigned char get_interface_fa_state(STRUCT_FUNC_PC_INTERFACE_COM*ic)
{
/*
 *函数名：get_interface_fa_state
 *描述  ：获取发送状态
 *输入  ：
 *输出  ：无
 *调用  ：内部调用
*/    
	unsigned char r=0;
	switch(ic->par_module_id)
	{
		case 1:  
		{	
			r=2;//BSP_UART1_TX_MARK;
		}break;
		default:break;
	}	
	return r;
}







/**********接收数据**************************/
void FUNC_PC_INTERFACE_COM_UART_RX_ISR(STRUCT_FUNC_PC_INTERFACE_COM* ic,unsigned char res)
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_UART_RX_ISR
 *描述  ：通过串口接收数据，使用中断
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  
	
	//---------被动通讯控制函数-----------
    if(ic->con_pscom_en_shou==1)  //允许接收
    {
		FUNC_S_RING_QUEUE8_WRITE(&(ic->con_pscom_shou_que),&res,1);  //接收数据
    } 	
	
}


/**********接收数据处理**************************/
void FUNC_PC_INTERFACE_COM_PSCOM_RX_RINGBUF_PROCESS_TASK(STRUCT_FUNC_PC_INTERFACE_COM* ic)
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_PSCOM_RX_RINGBUF_PROCESS_TASK
 *描述  ：接收数据处理
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  

    if(ic->con_pscom_en_shou==1)  //允许接收
    {
		unsigned short int d_l=0;  //需要读取的数据个数
		unsigned char res=0;       //读到的数据

		//--获取数据个数---
		d_l=FUNC_S_RING_QUEUE8_GET_LEN(&(ic->con_pscom_shou_que));
		if(d_l>0)
		{
			while(d_l)
			{
				//---读数据---
				if(FUNC_S_RING_QUEUE8_READ(&(ic->con_pscom_shou_que),&res)==0)   //提取数据
				{
					/******以下可以添加用户程序*******/
					//-----获取该数据的位置------------
					unsigned char pos=0;
					if(ic->con_pscom_shou_que.head>0)
					{
						pos=ic->con_pscom_shou_que.head-1;
					}
					else
					{
						pos=ic->con_pscom_shou_que.que_size-1;
					}					
					//----判断是否收到帧数据---
					FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_ON(&(ic->con_pscom_shou_check),res);
					if(ic->con_pscom_shou_check.find_result==1)
					{
						//-----处理帧数据-------
						if((ic->con_pscom_shou_check.frame_buf[2])<0x50)
						{
							//----赋值接收标志---
							if(ic->con_get_frame_id_mark[ic->con_pscom_shou_check.frame_buf[2]]<0xff)
							{
								ic->con_get_frame_id_mark[ic->con_pscom_shou_check.frame_buf[2]]++;
							}
							//-----提取接收到的数据---
							switch(ic->par_module_id)
							{
								case 1:
								{
									switch(ic->con_pscom_shou_check.frame_buf[2])
									{
										case 0x01:     //读取下位机版本信息
										{

										}break;	
										case 0x02:     //读取下位机设备信息
										{
											
										}break;										
										case 0x03:     //控制下位机设备
										{
											FUNC_PC_INTERFACE_COM1_SYS_DEV_CON_CMD=ic->con_pscom_shou_check.frame_buf[4];											
										}break;
										
										case 0x11:     //允许/禁止上传一类传感器数据
										{
											FUNC_PC_INTERFACE_COM1_SENSOR1_GET_CMD_MARK=1;
											FUNC_PC_INTERFACE_COM1_SENSOR1_UPDATA_CMD.h_l.l=ic->con_pscom_shou_check.frame_buf[4];
											FUNC_PC_INTERFACE_COM1_SENSOR1_UPDATA_CMD.h_l.h=ic->con_pscom_shou_check.frame_buf[5];											
										}break;
										case 0x12:     //允许/禁止上传二类传感器数据
										{
											FUNC_PC_INTERFACE_COM1_SENSOR2_GET_CMD_MARK=1;
											FUNC_PC_INTERFACE_COM1_SENSOR2_UPDATA_CMD.h_l.l=ic->con_pscom_shou_check.frame_buf[4];
											FUNC_PC_INTERFACE_COM1_SENSOR2_UPDATA_CMD.h_l.h=ic->con_pscom_shou_check.frame_buf[5];											  											
										}break;	
										case 0x21:     //读取电磁阀信息
										{
											
										}break;
										case 0x22:     //控制电磁阀
										{
											FUNC_PC_INTERFACE_COM1_SWITCH1_CON_CMD=ic->con_pscom_shou_check.frame_buf[4];
											FUNC_PC_INTERFACE_COM1_SWITCH2_CON_CMD=ic->con_pscom_shou_check.frame_buf[5];												
										}break;	
										case 0x31:     //读取风机信息
										{
											
										}break;
										case 0x32:     //控制风机
										{
											FUNC_PC_INTERFACE_COM1_FLOW_FAN_CON_CMD=ic->con_pscom_shou_check.frame_buf[4];
											FUNC_PC_INTERFACE_COM1_FLOW_FAN_SPEED_CMD.h_l.l=ic->con_pscom_shou_check.frame_buf[5];
											FUNC_PC_INTERFACE_COM1_FLOW_FAN_SPEED_CMD.h_l.h=ic->con_pscom_shou_check.frame_buf[6];												
											
										}break;										
										default:break;
									}
								}break;
								default:break;
							}
						}
						//--------重新接收-----
						FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_RESET(&(ic->con_pscom_shou_check));
					}					
				}
				else
				{
					break;
				}
				d_l--;
			}			
		}			
    }	
}
void FUNC_PC_INTERFACE_COM_PSCOM_RX_RESPOND_TASK(STRUCT_FUNC_PC_INTERFACE_COM* ic)
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_PSCOM_RX_RESPOND_TASK
 *描述  ：接收数据回复
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  
	unsigned char *fa_zheng_buffer;
	_16_union value;
	_16_union fa_zheng_data_num; 
	_16_union fa_crc16;
	unsigned char frame_mark_num=0;
	//------赋值发送缓冲--------
	fa_zheng_buffer=ic->con_pscom_fa_buf;
	//------查找收到了哪些帧----
	for(frame_mark_num=0;frame_mark_num<sizeof(ic->con_get_frame_id_mark);frame_mark_num++)
	{
		if(
			(ic->con_get_frame_id_mark[frame_mark_num]!=0)
			&&(get_interface_fa_state(ic)!=1)
		)
		{			
			//----清0帧的有效数据--
			fa_zheng_buffer[0]=0;
			//----赋值帧头------
			fa_zheng_buffer[1]=0x55;
			fa_zheng_buffer[2]=0xaa;        
			fa_zheng_buffer[0]+=2;        
			//----赋值帧ID----
			fa_zheng_buffer[3]=frame_mark_num;
			fa_zheng_buffer[0]+=1;
			//----赋值帧数据--------
			//----复位帧数据字节数--
			fa_zheng_data_num.all=0;
			switch(ic->par_module_id)
			{
				case 1:
				{
					switch(frame_mark_num)
					{
						case 0x01:     //读取下位机版本信息
						{
							//----赋值硬件版本---
							value.all=FUNC_S_VERSION_CON.hard_ver_u16mzze.all;
							fa_zheng_buffer[5]=value.h_l.l;
							fa_zheng_buffer[6]=value.h_l.h;
							//----赋值软件版本---	
							value.all=FUNC_S_VERSION_CON.soft_ver_u16mzze.all;							
							fa_zheng_buffer[7]=value.h_l.l;
							fa_zheng_buffer[8]=value.h_l.h;
							//----赋值保留-----
							fa_zheng_buffer[9]=0;
							fa_zheng_buffer[10]=0;
							
							fa_zheng_data_num.all+=6;
							fa_zheng_buffer[0]+=6;   								
															
													
						}break;						
						case 0x02:     //读取下位机设备信息
						{
							//----工作状态---
							fa_zheng_buffer[5]=0;
							//----电池电量---							
							fa_zheng_buffer[6]=100; //FUNC_BAT_CON_MODUL1.state_elevel;
							//----热机时间---
							value.all=10; //APP_LOCAL_CON_WARMUP_TIME;
							fa_zheng_buffer[7]=value.h_l.l;
							fa_zheng_buffer[8]=value.h_l.h;
							//----故障码-----
							fa_zheng_buffer[9]=4;
							
							fa_zheng_data_num.all+=5;
							fa_zheng_buffer[0]+=5;  								
													
						}break;
						case 0x03:     //控制下位机设备
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;
							
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;  							
							
						}break;	
						case 0x11:     //允许禁止上传一类传感器数据
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;
							
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;  								
													
						}break;
						case 0x12:     //允许/禁止上传二类传感器数据
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;
							
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;  							
							
						}break;	
						case 0x21:     //读取电磁阀信息
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;//FUNC_AIR_SWITCH_CON_MODUL1.state_cur_onoff_state;   //电磁阀1信息
							fa_zheng_buffer[6]=1;//FUNC_AIR_SWITCH_CON_MODUL2.state_cur_onoff_state;   //电磁阀2信息						
							fa_zheng_data_num.all+=2;
							fa_zheng_buffer[0]+=2;  								
													
						}break;
						case 0x22:     //控制电磁阀
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;
							
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;  							
							
						}break;
						case 0x31:     //读取流量风机信息
						{
							value.all=32; //FUNC_FLOW_FAN_CON_MODUL1.state_fan_cur_speed*100;	//两位小数							
							//--赋值风机状态--
							fa_zheng_buffer[5]=0;
							if(value.all==0)
							{
								fa_zheng_buffer[5]=1; //停机
							}								
							else
							{
//								if(FUNC_FLOW_FAN_CON_MODUL1.state_fan_cur_fr==1)    
//								{
									fa_zheng_buffer[5]=2;  //正转
//								}
//								if(FUNC_FLOW_FAN_CON_MODUL1.state_fan_cur_fr==2)
//								{
//									fa_zheng_buffer[5]=3;  //反转								
//								}
							}
							//--赋值风机速度--
							fa_zheng_buffer[6]=value.h_l.l; 	
							fa_zheng_buffer[7]=value.h_l.h; 

								
							fa_zheng_data_num.all+=3;
							fa_zheng_buffer[0]+=3;  								
													
						}break;
						case 0x32:     //控制流量风机
						{
							//----赋值回应---
							fa_zheng_buffer[5]=1;
							
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;  							
							
						}break;											
						case 0x81:    //发送下位机启动完成通知
						{
							//----赋值硬件版本---
							value.all=FUNC_S_VERSION_CON.hard_ver_u16mzze.all;
							fa_zheng_buffer[5]=value.h_l.l;
							fa_zheng_buffer[6]=value.h_l.h;
							//----赋值软件版本---	
							value.all=FUNC_S_VERSION_CON.soft_ver_u16mzze.all;							
							fa_zheng_buffer[7]=value.h_l.l;
							fa_zheng_buffer[8]=value.h_l.h;
							//----赋值保留-----
							fa_zheng_buffer[9]=0;
							fa_zheng_buffer[10]=0;
							
							fa_zheng_data_num.all+=6;
							fa_zheng_buffer[0]+=6;   								
							
							
						}break;
						case 0x82:    //设备心跳帧
						{
							//----工作状态---
							fa_zheng_buffer[5]=0;
							//----电池电量---							
//							fa_zheng_buffer[6]=FUNC_BAT_CON_MODUL1.state_elevel;
							//----热机时间---					
//							value.all=APP_LOCAL_CON_WARMUP_TIME;
							fa_zheng_buffer[7]=value.h_l.l;
							fa_zheng_buffer[8]=value.h_l.h;
							//----故障码-----
							fa_zheng_buffer[9]=0;
							
							fa_zheng_data_num.all+=5;
							fa_zheng_buffer[0]+=5;  	
							
						}break;										
						case 0x91:    //上传一类传感器数据
						{
							bit_hl_all_16bit_union cmd;
							unsigned char i=5;
							unsigned char j=0;
							//---提取命令----
//							cmd.all=APP_LOCAL_CON_SENSOR1_UPDATA_CMD;
							//----赋值环境温度-----
							if(cmd.bit_16.bit0==1)
							{
//								value.all=FUNC_TEMP_HUMI_DETECT_1_INF.state_temp_c;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;								
							}
							//----赋值环境湿度-----	
							if(cmd.bit_16.bit1==1)
							{
//								value.all=FUNC_TEMP_HUMI_DETECT_1_INF.state_humi;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值大气压------								
							if(cmd.bit_16.bit2==1)
							{
//								value.all=FUNC_MS5540C_1_INF.state_pres;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值电磁阀1-----
							if(cmd.bit_16.bit3==1)
							{
//								fa_zheng_buffer[i]=FUNC_AIR_SWITCH_CON_MODUL1.state_cur_onoff_state;   //电磁阀1信息									
								i+=1;
								j+=1;									
							}							
							//----赋值电磁阀2-----	
							if(cmd.bit_16.bit4==1)
							{
//								fa_zheng_buffer[i]=FUNC_AIR_SWITCH_CON_MODUL2.state_cur_onoff_state;   //电磁阀2信息							
								i+=1;
								j+=1;									
							}	
							//----赋值定标流量-----
							if(cmd.bit_16.bit5==1)
							{
//								value.all=FUNC_HSC_PRESS_1_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}							
							//----赋值采集低流量-----
							if(cmd.bit_16.bit6==1)
							{
//								value.all=FUNC_HSC_PRESS_2_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}	
							//----赋值采集高流量数据-----
							if(cmd.bit_16.bit7==1)
							{
//								value.all=FUNC_HSC_PRESS_3_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}							
							//----赋值CO2数据-----
							if(cmd.bit_16.bit8==1)
							{
//								value.all=CO2_SENSOR_MODULE1.state_co2;    //CO2浓度2位小数，百分比							
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值O2数据-----
							if(cmd.bit_16.bit9==1)
							{
//								value.all=FUNC_O2_DETECT1.state_filter_o2;
//								value.all=FUNC_SPI_AD76831_1.state_filter_v_ad;								
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}
							//----赋值O2温度数据(有符号)----
							if(cmd.bit_16.bit10==1)
							{
								s16_u16_union s16_value;
//								s16_value.sall=FUNC_NTC_TEMP_DETECT1.state_filter_temp;
								fa_zheng_buffer[i]=s16_value.h_l.l;
								fa_zheng_buffer[i+1]=s16_value.h_l.h;	
								i+=2;
								j+=2;									
							}							

							fa_zheng_data_num.all+=j;
							fa_zheng_buffer[0]+=j;  
						}break;
						case 0x92:    //上传二类传感器数据
						{
							bit_hl_all_16bit_union cmd;
							unsigned char i=5;
							unsigned char j=0;
							//---提取命令----
//							cmd.all=APP_LOCAL_CON_SENSOR2_UPDATA_CMD;
							//----赋值环境温度-----
							if(cmd.bit_16.bit0==1)
							{
//								value.all=FUNC_TEMP_HUMI_DETECT_1_INF.state_temp_c;								
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;								
							}
							//----赋值环境湿度-----	
							if(cmd.bit_16.bit1==1)
							{
//								value.all=FUNC_TEMP_HUMI_DETECT_1_INF.state_humi;								
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值大气压------								
							if(cmd.bit_16.bit2==1)
							{
//								value.all=FUNC_MS5540C_1_INF.state_pres;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值电磁阀1-----
							if(cmd.bit_16.bit3==1)
							{
//								fa_zheng_buffer[i]=FUNC_AIR_SWITCH_CON_MODUL1.state_cur_onoff_state;   //电磁阀1信息									
								i+=1;
								j+=1;									
							}							
							//----赋值电磁阀2-----	
							if(cmd.bit_16.bit4==1)
							{
//								fa_zheng_buffer[i]=FUNC_AIR_SWITCH_CON_MODUL2.state_cur_onoff_state;   //电磁阀2信息							
								i+=1;
								j+=1;									
							}	
							//----赋值定标流量-----
							if(cmd.bit_16.bit5==1)
							{
//								value.all=FUNC_HSC_PRESS_1_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}							
							//----赋值采集低流量-----
							if(cmd.bit_16.bit6==1)
							{
//								value.all=FUNC_HSC_PRESS_2_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}
							//----赋值采集高流量-----
							if(cmd.bit_16.bit7==1)
							{
//								value.all=FUNC_HSC_PRESS_3_INF.state_press_d;
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;
								i+=2;
								j+=2;									
							}							
							//----赋值CO2数据-----
							if(cmd.bit_16.bit8==1)
							{
//								value.all=CO2_SENSOR_MODULE1.state_co2;    //CO2浓度2位小数，百分比							
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							//----赋值O2数据-----
							if(cmd.bit_16.bit9==1)
							{
//								value.all=FUNC_O2_DETECT1.state_filter_o2;
//								value.all=FUNC_SPI_AD76831_1.state_filter_v_ad;									
								fa_zheng_buffer[i]=value.h_l.l;
								fa_zheng_buffer[i+1]=value.h_l.h;	
								i+=2;
								j+=2;									
							}
							//----赋值O2温度数据(有符号)----
							if(cmd.bit_16.bit10==1)
							{
								s16_u16_union s16_value;
//								s16_value.sall=FUNC_NTC_TEMP_DETECT1.state_filter_temp;
								fa_zheng_buffer[i]=s16_value.h_l.l;
								fa_zheng_buffer[i+1]=s16_value.h_l.h;	
								i+=2;
								j+=2;									
							}							
							

							fa_zheng_data_num.all+=j;
							fa_zheng_buffer[0]+=j;  							
						}break;
						default:
						{
							//----赋值回应信息----
							fa_zheng_buffer[6]=0xff;   //非法命令字	
							fa_zheng_data_num.all+=1;
							fa_zheng_buffer[0]+=1;					
						}break;
					}
				}break;
				default:break;
			}
			//-----------赋值帧数据字节数------
			fa_zheng_buffer[4]=fa_zheng_data_num.all;
			fa_zheng_buffer[0]+=1;			
			//-----------生成CRC校验值-------------
			fa_crc16.all=FUNC_S_CRC16_MODBUS_CAL(&fa_zheng_buffer[3], fa_zheng_buffer[0]-2); 
			//-----------赋值CRC校验值-------------
			fa_zheng_buffer[fa_zheng_buffer[0]+1]=fa_crc16.h_l.l;        //赋值校验低字节
			fa_zheng_buffer[fa_zheng_buffer[0]+2]=fa_crc16.h_l.h;   //赋值校验高字节
			fa_zheng_buffer[0]+=2; 
			/******将生成的帧发送出去*****/  
			if(get_interface_fa_state(ic)!=1)   //发送空闲		
			{
//				BSP_IO_LED1=1;  //等待发送发送时间约1ms
				interface_fa_buf(ic,&fa_zheng_buffer[1],fa_zheng_buffer[0]);
//				BSP_IO_LED1=0;
				/******清除标志************/
				ic->con_get_frame_id_mark[frame_mark_num]--;
			}
			else
			{
				break;
			}
		}	
	}	
}
 


/********模块初始化*************/
void FUNC_PC_INTERFACE_COM_IC_DATA_INIT(STRUCT_FUNC_PC_INTERFACE_COM* ic,unsigned char ic_id)
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_IC_DATA_INIT
 *描述  ：对外通讯对象数据初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  
	unsigned char i=0;
	//--参数---	
	ic->par_module_id=1;                //模块ID
	//--状态---
	ic->state_err=0;         //故障  0:无意义   1:无故障   2:有故障
	//--控制---
	//---------临时寄存器----------
	for(i=0;i<sizeof(ic->con_u16_r);i++)
	{
		ic->con_u16_r[i]=0;           
	}	
	for(i=0;i<sizeof(ic->con_u8_r);i++)
	{
		ic->con_u8_r[i]=0;           
	}
    //---------延时控制------------
	ic->con_sys_tick_count=0;   //系统节拍记录     //单位ms
	ic->con_time_delay=0;        //延时，单位为系统节拍	//单位ms	
	//---------接收数据帧标志----

	for(i=0;i<sizeof(ic->con_get_frame_id_mark);i++)
	{
		ic->con_get_frame_id_mark[i]=0;  //收到的帧			
	}	

	//---------被动通讯控制--------	
	FUNC_S_RING_QUEUE8_INIT(&(ic->con_pscom_shou_que),ic->con_pscom_shou_buffer,sizeof(ic->con_pscom_shou_buffer));  //定义一个接收环形队列 
	ic->con_pscom_en_shou=1;                            //接收控制位 0--->不允许接收   1----->允许接受	  


	//------------被动通讯检查--------
//	unsigned char con_pscom_shou_state;                         //被动通讯接收状态机		
//	unsigned char con_pscom_shou_ok;
	FUNC_SDF_FIND_FORMAT5_DATA_FROM_FLOW_INIT(&(ic->con_pscom_shou_check),ic->con_pscom_shou_check_buf,sizeof(ic->con_pscom_shou_check_buf),0x55,0xaa);	


}


/**************模块工作MAIN************************/
unsigned char FUNC_PC_INTERFACE_COM_WORK_MAIN(unsigned char p1)
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_WORK_MAIN
 *描述  ：模块工作函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/   
	//----------定时调用------------
    if(p1==1)
    {
        //------处理对象1接收数据--
        FUNC_PC_INTERFACE_COM_PSCOM_RX_RINGBUF_PROCESS_TASK(&FUNC_PC_INTERFACE_COM1);
		//------回复对象1收到的数据--
		FUNC_PC_INTERFACE_COM_PSCOM_RX_RESPOND_TASK(&FUNC_PC_INTERFACE_COM1);
		
		
    }
    return 0;
}




void FUNC_PC_INTERFACE_COM_INIT()
{
/*
 *函数名：FUNC_PC_INTERFACE_COM_INIT
 *描述  ：对外通讯模块初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  
	unsigned char i=0;

	//---通讯对象初始化---
	FUNC_PC_INTERFACE_COM_IC_DATA_INIT(&FUNC_PC_INTERFACE_COM1,1);
	
	//-----系统相关数据----
	FUNC_PC_INTERFACE_COM1_SYS_DEV_CON_CMD=0;    //控制下位机设备

	//-----传感器相关数据-----
	FUNC_PC_INTERFACE_COM1_SENSOR1_GET_CMD_MARK=0;   //获取到命令标志
	FUNC_PC_INTERFACE_COM1_SENSOR2_GET_CMD_MARK=0;   //获取到命令标志	
	FUNC_PC_INTERFACE_COM1_SENSOR1_UPDATA_CMD.all=0;  //一类传感器数据更新命令
	FUNC_PC_INTERFACE_COM1_SENSOR2_UPDATA_CMD.all=0;  //二类传感器数据更新命令


	//-----电磁阀相关数据-----
	FUNC_PC_INTERFACE_COM1_SWITCH1_CON_CMD=0;  //控制电磁阀1
	FUNC_PC_INTERFACE_COM1_SWITCH2_CON_CMD=0;  //控制电磁阀2

	//-----风机相关数据-----
	FUNC_PC_INTERFACE_COM1_FLOW_FAN_CON_CMD=0;  //控制流量风机
	FUNC_PC_INTERFACE_COM1_FLOW_FAN_SPEED_CMD.all=0;  //控制流量风机速度
		
		
		
	
}










#include "func_dht11.h"
#include "bsp_dht11_io.h"
#include "bsp_systick.h"
#include "bsp_led.h"

//---变量定义----
FUNC_DHT11_INF_STRUCT  FUNC_DHT11_1_INF;    //温湿度传感器1信息
//FUNC_DHT11_INF_STRUCT  FUNC_DHT11_2_INF;    //温湿度传感器2信息
//FUNC_DHT11_INF_STRUCT  FUNC_DHT11_3_INF;    //温湿度传感器3信息
//FUNC_DHT11_INF_STRUCT  FUNC_DHT11_4_INF;    //温湿度传感器4信息




static uint8_t Read_Byte(FUNC_DHT11_INF_STRUCT *as)
{	  
	uint8_t i, temp=0;
	uint16_t tout=0;
	for(i=0;i<8;i++)    
	{	 
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/
		tout=0;			
		while(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_OFF)
		{
			tout++;
			if(tout>500)
			{			
				break;
			}			
		}
		/*DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
		 通过检测40us后的电平即可区别这两个状态*/
		BSP_SYSTICK_DELAY_US(40); //延时40us		   	  
		if(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_ON)//40us后仍为高电平表示数据“1”
		{
			/*轮询直到从机发出的剩余的 30us 高电平结束*/
			tout=0;
			while(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_ON)
			{
				tout++;
				if(tout>500)
				{				
					break;
				}				
			}	
			temp|=(uint8_t)(0x01<<(7-i));  //把第7-i位置1 
		}
		else	 //60us后为低电平表示数据“0”
		{			   
			temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0
		}
	}
	return temp;
}

uint8_t func_dht11_get_temp_humi(FUNC_DHT11_INF_STRUCT *as)
{  
	unsigned char data[5];
	unsigned short int check=0;
	unsigned short int tout=0;	
	switch(as->con_get_temp_humi_state)
	{
		case 1:     //初始
		{
			//---初始引脚状态---
			BSP_DHT11_IO_MODE_OUT(as->par_as_num);    	//输出模式
			BSP_DHT11_IO_D_WRITE(as->par_as_num,BSP_DHT11_D_ON);	//主机拉高
			//-----记录时间---
			as->con_sys_tick_count=bsp_systick_count;
			as->con_time_delay=50;
			//-----跳转-----
			as->con_get_temp_humi_state=2;	
			
		}break;			
		case 2:     //开始发送测量命令,step1低电平
		{
			//-------超时判断------
			if(bsp_systick_count-(as->con_sys_tick_count)>=as->con_time_delay)
			{	
				BSP_DHT11_IO_D_WRITE(as->par_as_num,BSP_DHT11_D_OFF);	//主机拉低
				//-----记录时间---
				as->con_sys_tick_count=bsp_systick_count;
				as->con_time_delay=20;
				//-----跳转-----
				as->con_get_temp_humi_state=3;					
			}			
		}break;		
		case 3:     //开始发送测量命令,step2高电平，并接收数据
		{
			//-------超时判断------
			if(bsp_systick_count-(as->con_sys_tick_count)>=as->con_time_delay)
			{	
				BSP_DHT11_IO_D_WRITE(as->par_as_num,BSP_DHT11_D_ON);	//主机拉高
				
				BSP_DHT11_IO_MODE_IN(as->par_as_num);                   //主机设为输入 判断从机响应信号
				
				BSP_SYSTICK_DELAY_US(40);   //延时40us 
				
				if(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_OFF)   //判断从机是否有低电平响应信号   
				{
					/*轮询直到从机发出 的80us 低电平 响应信号结束*/  
					tout=0;				
					while(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_OFF)
					{
						tout++;
						if(tout>500)
						{		
							break;
						}				
					}
					/*轮询直到从机发出的 80us 高电平 标置信号结束*/
					tout=0;			
					while(BSP_DHT11_IO_D_READ(as->par_as_num)==BSP_DHT11_D_ON)
					{
						tout++;			
						if(tout>500)
						{			
							break;
						}				
					}

					/*开始接收数据*/   
					data[0]= Read_Byte(as);
					data[1]= Read_Byte(as);
					data[2]= Read_Byte(as);
					data[3]= Read_Byte(as);
					data[4]= Read_Byte(as);		

					/*检查读取的数据是否正确*/
					check=data[0]+data[1]+data[2]+data[3];
					check&=0x00ff;
					if(data[4]==check)
					{
						//赋值
						as->par_ic_humi_data=(((unsigned short int)data[0])<<8)+data[1];		
						as->par_ic_temp_data=(((unsigned short int)data[2])<<8)+data[3];
						as->state_humi=(unsigned short int)data[0]*10;      //这里只取了整数，单位0.1
						as->state_temp_c=(unsigned short int)data[2]*10;	 //这里只取了整数，单位0.1					
						
						as->con_get_temp_humi_state=47;
					}
					else 
					{
						as->con_get_temp_humi_state=48;
					}
				}
				else
				{		
					as->con_get_temp_humi_state=48;
	
				}	
				
				BSP_DHT11_IO_MODE_OUT(as->par_as_num);                  //读取结束，引脚改为输出模式				
				BSP_DHT11_IO_D_WRITE(as->par_as_num,BSP_DHT11_D_ON);	//主机拉高				
			}			
		}break;			
		case 47:   //成功
		{		
			as->state_err=1;	
			as->con_get_data_suce_count++;       //成功计数			
			as->con_get_temp_humi_state=49;			
		}break;
		case 48:   //失败
		{	
			as->state_err=2;	
			as->con_get_data_fail_count++;       //失败计数	
			//--赋值
			as->par_ic_temp_data=0xffff;
			as->par_ic_humi_data=0xffff;			
			as->state_temp_c=0xffff;	   //无效						
			as->state_humi=0xffff;				
			as->con_get_temp_humi_state=50;					
		}break;				
		default:break;
	}
	return as->con_get_temp_humi_state;	
	
	
	
	
	
}




void FUNC_DHT11_GET_TEMP_HUMI(FUNC_DHT11_INF_STRUCT*as)
{
/*
 *函数名：FUNC_DHT11_GET_TEMPERATURE
 *描述  ：获取温湿度传感器的温湿度
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/ 	
	func_dht11_get_temp_humi(as);		
	if(bsp_systick_count-(as->con_time_samp_tick_count)>=as->con_time_samp)   //间隔时间到
	{
		if(
			(as->con_get_temp_humi_state==0)
		    ||(as->con_get_temp_humi_state==49)
		    ||(as->con_get_temp_humi_state==50)		
		)
		{
			as->con_get_temp_humi_state=1;
		}
		//---记录时间--
		as->con_time_samp_tick_count=bsp_systick_count;		
		
	}		
	
	
}


void FUNC_DHT11_MODULE_DATA_INIT(FUNC_DHT11_INF_STRUCT*as,unsigned char num,unsigned short int samp_time)
{
/*
 *函数名：FUNC_DHT11_MODULE_DATA_INIT
 *描述  ：温湿度传感器数据初始化
 *输入  ：as:传感器句柄，num:对应传感器号 samp_time:采样时间，单位ms
 *输出  ：无
 *调用  ：main函数中调用
*/ 
	unsigned char i=0;	
	//--参数---
	as->par_as_num=num;
	as->par_ic_temp_data=0xffff;       
	as->par_ic_humi_data=0xffff;     	    
	//--状态---
	as->state_err=0;
	as->state_temp_c=0;    //摄氏温度
	as->state_temp_f=0;    //华氏温度
	as->state_humi=0;      //湿度
	//--控制---
    //---------延时控制------------
	as->con_sys_tick_count=0;   //系统节拍记录     //单位ms
	as->con_time_delay=0;        //延时，单位为系统节拍	//单位ms	
    //---------采样时间控制------------
	as->con_time_samp_tick_count=bsp_systick_count;   //系统节拍记录
	as->con_time_samp=samp_time;        //采样频率，单位为系统节拍		
	//---------读取控制------------	
	as->con_get_temp_humi_state=0;       //获取温度湿度状态	
	as->con_get_data_suce_count=0;       //成功计数	
	as->con_get_data_fail_count=0;       //失败计数	
	

}


void FUNC_DHT11_INIT()
{
/*
 *函数名：FUNC_DHT11_INIT
 *描述  ：温湿度传感器初始化
 *输入  ：as:传感器句柄，num:对应传感器号 samp_time:采样时间，单位ms
 *输出  ：无
 *调用  ：main函数中调用
*/ 
	unsigned char i=0;
	FUNC_DHT11_MODULE_DATA_INIT(&FUNC_DHT11_1_INF,1,2200);
	//IO初始化	
	BSP_DHT11_IO_INIT(FUNC_DHT11_1_INF.par_as_num);		
}



void FUNC_DHT11_REFRESH_MAIN()
{
/*
 *函数名：FUNC_DHT11_REFRESH_MAIN
 *描述  ：温湿度传感器刷新函数
 *输入  ：无
 *输出  ：无
 *调用  ：main函数中调用
*/ 	

    //读取温湿度	
	FUNC_DHT11_GET_TEMP_HUMI(&FUNC_DHT11_1_INF);

}





























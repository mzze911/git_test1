#include "app_oled_display.h"
#include "func_oled.h"
#include "func_time_mark.h"
#include "main.h"
#include "func_ir_decode.h"
#include "bsp_led.h"

unsigned char APP_OLED_REFRESH_OLED_RAM_MARK=0;    //更新OLED_RAM标志位  0-->代表更新完成 1-->代表正在更新

/*****与外部对接的需要显示的变量*******/





/****************空闲画面显示*******************/
void show_idle_picture_value()
{
/*
 *函数名：show_idle_picture_value
 *描述  ：显示空闲界面相关的数值 
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/  
	unsigned long int value=0;	
	char s[60];
	unsigned char clear[]="                        ";
	/******复位显示变量*********/
	memset(s,0,sizeof(s));
	/******清显示*********/    
    FUNC_OLED_Show_Str(0,12,128,12,clear,OLED_STRING_12,0,0);
	FUNC_OLED_Show_Str(0,24,128,12,clear,OLED_STRING_12,0,0);
    FUNC_OLED_Show_Str(0,36,128,12,clear,OLED_STRING_12,0,0);
	FUNC_OLED_Show_Str(0,48,128,12,clear,OLED_STRING_12,0,0);	
	//----显示红外码----
  	sprintf(s,"ADD:%d CMD:%d",FUNC_IR_DECODE_NEC_CCMD.add,FUNC_IR_DECODE_NEC_CCMD.cmd);	
    FUNC_OLED_Show_Str(0,12,128,12,(u8*)s,OLED_STRING_12,0,0);	
  	sprintf(s,"REPEAT:%d",FUNC_IR_DECODE_NEC_CCMD.repeat);	
    FUNC_OLED_Show_Str(0,24,128,12,(u8*)s,OLED_STRING_12,0,0);	

}



/****************调试画面显示*******************/
void show_debug_picture_value()
{
/*
 *函数名：show_debug_picture_value
 *描述  ：显示debug界面相关的数值 
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/  
////	float f_value;
//	static unsigned char show_step=0;
//	unsigned long int value=0;
//	char s[60];
//	unsigned char clear[]="                        ";
////	//---温湿度显示--
////    unsigned char s6[]="T:00.0℃";		  //0.1摄氏度
////    unsigned char s6[]="H:00.0%";		  //0.1%	
////	//---大气压显示---
////    unsigned char s1[]="AP:0000.0mbar";       //0.1mbar
////    //---CO2采集显示-----	
////    unsigned char s3[]="CO2:00000%"; 	//二氧化碳浓度	
////    //---O2采集显示-----	
////    unsigned char s2[]="O2:00000kg";    //氧气浓度ADC值
////    //---O2温度显示-----	
////    unsigned char s2[]="O2T:00.0℃";   //氧气温度0.1摄氏度
////    //---流量1采集显示-----	
////    unsigned char s2[]="FL1:00000";    //流量1数字值
////    //---流量2采集显示-----	
////    unsigned char s2[]="FL2:00000";    //流量2数字值
////	//---电磁阀1,2状态显示-- 
////    unsigned char s4[]="S1/2:0/1";	   //电磁阀12
////	//---流量风机状态显示--
////    unsigned char s4[]="FFL:L00 S00";	//流量风机	
//	
//	/******复位显示变量*********/
//	memset(s,0,sizeof(s));
//	/******清显示*********/    
//    FUNC_OLED_Show_Str(0,12,128,12,clear,OLED_STRING_12,0,0);
//	FUNC_OLED_Show_Str(0,24,128,12,clear,OLED_STRING_12,0,0);
//    FUNC_OLED_Show_Str(0,36,128,12,clear,OLED_STRING_12,0,0);
//	FUNC_OLED_Show_Str(0,48,128,12,clear,OLED_STRING_12,0,0);	
//	/*---电池显示--*/
//	//电池电量显示
//    if(FUNC_BAT_CON_MODUL1.state_elevel<=100)
//	{		
//		sprintf(s,"%03d%%",FUNC_BAT_CON_MODUL1.state_elevel);	
//	}
//	else
//	{
//		sprintf(s,"---%%");			
//	}
//    FUNC_OLED_Show_Str(104,0,24,12,(u8*)s,OLED_STRING_12,0,0);	

//	/*---O2传感器显示--*/
//	//O2浓度显示	
////  	sprintf(s,"O2AD:%d",FUNC_O2_DETECT1.state_filter_v_ad);	
////  	sprintf(s,"O2AD:%d",FUNC_SPI_AD76831_1.state_filter_v_ad);	
//	sprintf(s,"O2V:%.3f",FUNC_SPI_AD76831_1.state_filter_v/1000.0f);
//    FUNC_OLED_Show_Str(0,12,128,12,(u8*)s,OLED_STRING_12,0,0);
//	//O2温度显示	
//  	sprintf(s,"O2T:%.1f",FUNC_NTC_TEMP_DETECT1.state_temp/10.0f);	
//    FUNC_OLED_Show_Str(64,12,128,12,(u8*)s,OLED_STRING_12,0,0);
//	
//	/*---CO2传感器显示--*/
//	//CO2浓度显示	
//  	sprintf(s,"CO2:%0.2f%%",CO2_SENSOR_MODULE1.state_co2/100.0f);	
//    FUNC_OLED_Show_Str(0,24,128,12,(u8*)s,OLED_STRING_12,0,0);	
//	
//	/*---流量传感器显示--*/
//	//流量1,2,3显示	
//  	sprintf(s,"FL:%d %d %d",FUNC_HSC_PRESS_1_INF.state_press_d,FUNC_HSC_PRESS_2_INF.state_press_d,FUNC_HSC_PRESS_3_INF.state_press_d);	
//    FUNC_OLED_Show_Str(0,36,128,12,(u8*)s,OLED_STRING_12,0,0);	
//	
//	/*******轮流显示区**************/
//	if(R_time_mark_1000ms_mark_b4==1)
//	{
//		CLR_time_mark_1000ms_mark_b4;				
//		if(show_step<3)
//		{
//			show_step++;
//		}
//		else
//		{
//			show_step=0;
//		}
//	}
//	switch(show_step)
//	{
//		case 0:
//		{
//			
//			/*---温湿度显示--*/
//			//温度显示	
//			sprintf(s,"T:%.1f",FUNC_TEMP_HUMI_DETECT_1_INF.state_temp_c/10.0f);	
//			FUNC_OLED_Show_Str(0,48,128,12,(u8*)s,OLED_STRING_12,0,0);
//			//湿度显示	
//			sprintf(s,"H:%.1f%%",FUNC_TEMP_HUMI_DETECT_1_INF.state_humi/10.0f);
//			FUNC_OLED_Show_Str(64,48,128,12,(u8*)s,OLED_STRING_12,0,0);
//		}break;
//		case 1:
//		{
//			/*---大气压显示--*/
//			//温度显示	
//			sprintf(s,"AP:%.1fmbar",FUNC_MS5540C_1_INF.state_pres/10.0f);	
//			FUNC_OLED_Show_Str(0,48,128,12,(u8*)s,OLED_STRING_12,0,0);		
//		}break;
//		case 2:
//		{
//			/*---电磁阀显示--*/
//			//电磁阀1/2显示	
//			sprintf(s,"S1:%d  S2:%d",FUNC_AIR_SWITCH_CON_MODUL1.state_cur_onoff_state,FUNC_AIR_SWITCH_CON_MODUL1.state_cur_onoff_state);	
//			FUNC_OLED_Show_Str(0,48,128,12,(u8*)s,OLED_STRING_12,0,0);		
//		}break;
//		case 3:
//		{
//			/*---流量风机显示--*/
//			//流量风机显示	
//			sprintf(s,"FFL:%.2f",FUNC_FLOW_FAN_CON_MODUL1.state_fan_cur_speed);	
//			FUNC_OLED_Show_Str(0,48,128,12,(u8*)s,OLED_STRING_12,0,0);				
//		}break;
//		case 4:
//		{
//			
//		}break;
//		case 5:
//		{
//			
//		}break;
//		case 6:
//		{
//			
//		}break;	
//		default:break;		
//	}	
}



/****************获得需要显示的数据****************/
void GET_OLED_DATA()
{
/*
 *函数名：GET_OLED_DATA
 *描述  ：获取需要显示的数据，在此处可以根据需要进行一些数据格式的转换 
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/        
 
     /**********本地控制相关的变量***********/  
    
    
    
    
}
/**********oled_画面切换显示函数************/
unsigned char APP_OLED_DISPLAY_PICTURE(unsigned char arg_picture_id,unsigned char arg_mod_step)
{
/*
 *函数名：OLED_DISPLAY_PICTURE
 *描述  ：切换OLED显示画面的函数
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/
	    static unsigned char arg_picture_id_last=255;
	    static unsigned char static_pic_refresh_mark=1;
    
//-----------获得需要显示的的数据----------
        GET_OLED_DATA();
//-----------进入此函数的第一步-----------
		//---禁止更新OLEDRAM----	
	    APP_OLED_REFRESH_OLED_RAM_MARK=1;    //标记此时正在更新RAM,禁止将RAM中的数据写入OLED驱动芯片中	  
		//---清RAM-----
	    if(arg_picture_id_last!=arg_picture_id)
        {
              FUNC_OLED_GRAM_ALL_CLEAR();            
              static_pic_refresh_mark=1;
              arg_picture_id_last=arg_picture_id;
        }
	  //---判断是否处于以下界面，若处于则有些画面需要共同显示
//        if((arg_picture_id>=PICTURE_ID_1)&&(arg_picture_id!=PICTURE_ID_25))
//        {        

		
//        }
		switch(arg_picture_id)
		{
            case MCS_ID_0:                                     //OLED上电全显画面
            {
                if(static_pic_refresh_mark==1)   //看是否第一次进入
                {
                    static_pic_refresh_mark=0;	  	
                    FUNC_OLED_GRAM_ALL_SET();       //全显                 
                }				

            }break;
            case MCS_ID_1:                                      //空闲画面
            {
                if(static_pic_refresh_mark==1)   //看是否第一次进入
                {
                    static_pic_refresh_mark=0;  
                    FUNC_OLED_Show_Str(0,0,64,12,"state1",OLED_STRING_12,0,0);  
//					FUNC_OLED_Show_Str(30,0,64,12,FUNC_S_VERSION_CON.soft_sver_u16mzze,OLED_STRING_12,0,0); 
                }
				show_idle_picture_value();
            }break;					
            case MCS_ID_2:                                      //调试画面
            {
                if(static_pic_refresh_mark==1)   //看是否第一次进入
                {
                    static_pic_refresh_mark=0;  

                }
				FUNC_OLED_Show_Str(0,0,64,12,"state2",OLED_STRING_12,0,0);  
//				FUNC_OLED_Show_Str(30,0,64,12,FUNC_S_VERSION_CON.soft_sver_u16mzze,OLED_STRING_12,0,0); 				
				show_debug_picture_value();
            }break;	
            case MCS_ID_3:                                      //空闲画面 	
            {
                if(static_pic_refresh_mark==1)   //看是否第一次进入
                {
                    static_pic_refresh_mark=0;  
                    FUNC_OLED_Show_Str(0,0,64,12,"state3",OLED_STRING_12,0,0);  
//					FUNC_OLED_Show_Str(30,0,64,12,FUNC_S_VERSION_CON.soft_sver_u16mzze,OLED_STRING_12,0,0); 
                }
				
				show_idle_picture_value();
            }break;					
            case MCS_ID_4:                                      //调试画面
            {
                if(static_pic_refresh_mark==1)   //看是否第一次进入
                {
                    static_pic_refresh_mark=0;  

                }
				FUNC_OLED_Show_Str(0,0,64,12,"state4",OLED_STRING_12,0,0);  
//				FUNC_OLED_Show_Str(30,0,64,12,FUNC_S_VERSION_CON.soft_sver_u16mzze,OLED_STRING_12,0,0); 				
				show_debug_picture_value();
            }break;				
			/*************************************************************/			
            default:break;
		}
    //----------优先级高于所有的显示-------
      


		
	//---允许向OLED更新RAM----	
	  APP_OLED_REFRESH_OLED_RAM_MARK=0;      
	  return arg_picture_id;            
}






 

































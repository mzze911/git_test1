#ifndef __FUNC_S_VERSION_CON_H__
#define __FUNC_S_VERSION_CON_H__

#include "bsp_stm32f1_mzze.h"

//---宏定义选择-----
#define VER_MZZE_TYPE_S  0    //版本格式选择  0->16位 1->32位
#define VER_CUSTOM_TYPE_S  0    //自定义版本格式选择  0->ZXJ



//---结构体---
typedef struct
{
	unsigned short int beta_num   :5;        //测试号：  0-31仅对测试版有用，发布版填0 举例测试版0x8000+(123<<5)+beta_num("B1.2.3_beta_num"),
	unsigned short int ver        :10;       //版本号:   0-1023 举例123("1.2.3"),1234("12.3.4")
	unsigned short int ver_type   :1; 	     //版本类型：0->发布版 1->测试版	
}MZZE_VERSION_U16_BIT;  //MZZE格式的版本


typedef struct
{
	unsigned long int beta_num   :10;       //测试号：  0-1023 仅对测试版有用，发布版填0 举例测试版0x40000000+(123<<10)+beta_num("B0.1.23_beta_num"),
	unsigned long int ver        :20;       //版本号:   0-1048576 举例123("0.1.23"),1234("0.12.34"),12345("1.23.45"),123456("12.34.56"),1023456("102.34.56")
	unsigned long int ver_type   :2; 	    //版本类型：0->发布版 1->测试版	
}MZZE_VERSION_U32_BIT;  //MZZE格式的版本



typedef union {
	MZZE_VERSION_U16_BIT bit_16;
	unsigned short int all;
}MZZE_VERSION_U16_UNION;   //共用体


typedef union {
	MZZE_VERSION_U32_BIT bit_32;
	unsigned long int all;
}MZZE_VERSION_U32_UNION;   //共用体



typedef struct
{
	
	//-----MZZE格式的版本号----
	#if(VER_MZZE_TYPE_S==0)
	MZZE_VERSION_U16_UNION hard_ver_u16mzze;    //数字形式的硬件版本
	MZZE_VERSION_U16_UNION soft_ver_u16mzze;    //数字形式的软件版本
	unsigned char hard_sver_u16mzze[15];      //字符串形式的硬件版本
	unsigned char soft_sver_u16mzze[15];      //字符串形式的软件版本
	#endif
	#if(VER_MZZE_TYPE_S==1)
	MZZE_VERSION_U32_UNION hard_ver_u32mzze;    //数字形式的硬件版本
	MZZE_VERSION_U32_UNION soft_ver_u32mzze;    //数字形式的软件版本
	unsigned char hard_sver_u32mzze[25];      //字符串形式的硬件版本
	unsigned char soft_sver_u32mzze[25];      //字符串形式的软件版本	
	#endif
	//针对于各公司
	#if(VER_CUSTOM_TYPE_S==0)
	//-----ZXJ格式的版本号----  
	unsigned char hard_sver_zxj[25];      //字符串形式的硬件版本
	unsigned char soft_sver_zxj[25];      //字符串形式的软件版本 举例，发布版本"V1.2.3_20231103" 测试版本"Beta1.2.3_20231103"	
	#endif
	
}FUNC_S_VERSION_CON_STRUCT;





//-----------变量定义--------
extern FUNC_S_VERSION_CON_STRUCT  FUNC_S_VERSION_CON;




extern void FUNC_S_VERSION_CON_INIT(void);









#endif




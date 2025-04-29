#include "func_s_version_con.h"

#define RELEASE_EN  1     //发布\测试模式选择 0->发布  1->测试

#if(RELEASE_EN==0)   //发布
	#define SOFT_VER  (100)          //软件版本号
	#define BETA_NUM  (000)          //测试号,无用保持为0	
	#define HARD_VER  (100)          //硬件版本号
#endif


#if(RELEASE_EN==1)   //测试
	#define SOFT_VER  (101)          //软件版本号
	#define BETA_NUM  (004)          //测试号,有用	
	#define HARD_VER  (100)          //硬件版本号
#endif


//-----------变量定义--------
FUNC_S_VERSION_CON_STRUCT  FUNC_S_VERSION_CON;




void FUNC_S_VERSION_CON_INIT()
{
	unsigned long int soft_ver=0;
	unsigned long int hard_ver=0;
	int beta_num=0;
	unsigned char m1=0;
	unsigned char m2=0;
	unsigned char m3=0;
	//---MZZE_U16格式赋值----
	#if(VER_MZZE_TYPE_S==0)
        //---赋值硬件---
		hard_ver=HARD_VER%1024;
		FUNC_S_VERSION_CON.hard_ver_u16mzze.bit_16.ver=hard_ver;
		FUNC_S_VERSION_CON.hard_ver_u16mzze.bit_16.beta_num=0;	
		FUNC_S_VERSION_CON.hard_ver_u16mzze.bit_16.ver_type=0;
		m1=hard_ver/100;
		m2=(hard_ver%100)/10;
		m3=hard_ver%10;	
		sprintf((char*)(&FUNC_S_VERSION_CON.hard_sver_u16mzze[0]),"V%d.%d.%d",m1,m2,m3);
	    //---赋值软件---
		soft_ver=SOFT_VER%1024;
		beta_num=BETA_NUM%32;
		FUNC_S_VERSION_CON.soft_ver_u16mzze.bit_16.ver=soft_ver;
		FUNC_S_VERSION_CON.soft_ver_u16mzze.bit_16.beta_num=beta_num;	
		FUNC_S_VERSION_CON.soft_ver_u16mzze.bit_16.ver_type=RELEASE_EN%2;
		m1=soft_ver/100;
		m2=(soft_ver%100)/10;
		m3=soft_ver%10;	
		#if(RELEASE_EN==0)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_u16mzze[0]),"V%d.%d.%d",m1,m2,m3);
		#endif
		#if(RELEASE_EN==1)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_u16mzze[0]),"B%d.%d.%d_%d",m1,m2,m3,beta_num);
		#endif	
	#endif		
	//---MZZE_U32格式赋值----
	#if(VER_MZZE_TYPE_S==1)	
        //---赋值硬件---
		hard_ver=HARD_VER%1048576;
		FUNC_S_VERSION_CON.hard_ver_u32mzze.bit_32.ver=hard_ver;
		FUNC_S_VERSION_CON.hard_ver_u32mzze.bit_32.beta_num=0;	
		FUNC_S_VERSION_CON.hard_ver_u32mzze.bit_32.ver_type=0;
		m1=hard_ver/10000;
		m2=(hard_ver%10000)/100;
		m3=hard_ver%100;	
		sprintf((char*)(&FUNC_S_VERSION_CON.hard_sver_u32mzze[0]),"V%d.%d.%d",m1,m2,m3);
	    //---赋值软件---		
		soft_ver=SOFT_VER%1048576;
		beta_num=BETA_NUM%1024;
		FUNC_S_VERSION_CON.soft_ver_u32mzze.bit_32.ver=soft_ver;
		FUNC_S_VERSION_CON.soft_ver_u32mzze.bit_32.beta_num=beta_num;	
		FUNC_S_VERSION_CON.soft_ver_u32mzze.bit_32.ver_type=RELEASE_EN%4;
		m1=soft_ver/10000;
		m2=(soft_ver%10000)/100;
		m3=soft_ver%100;	
		#if(RELEASE_EN==0)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_u32mzze[0]),"V%d.%d.%d",m1,m2,m3);
		#endif
		#if(RELEASE_EN==1)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_u32mzze[0]),"B%d.%d.%d_%d",m1,m2,m3,beta_num);
		#endif	
	#endif
	//针对于各公司
	#if(VER_CUSTOM_TYPE_S==0)
		//-----ZXJ格式的版本号----  
        //---赋值硬件---
		hard_ver=HARD_VER%1024;
		m1=hard_ver/100;
		m2=(hard_ver%100)/10;
		m3=hard_ver%10;	
		sprintf((char*)(&FUNC_S_VERSION_CON.hard_sver_zxj[0]),"V%d.%d.%d_20231023",m1,m2,m3);
	    //---赋值软件---		
		soft_ver=SOFT_VER%1024;
		m1=soft_ver/100;
		m2=(soft_ver%100)/10;
		m3=soft_ver%10;	
		#if(RELEASE_EN==0)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_zxj[0]),"V%d.%d.%d_20231023",m1,m2,m3);
		#endif
		#if(RELEASE_EN==1)
			sprintf((char*)(&FUNC_S_VERSION_CON.soft_sver_zxj[0]),"Beta%d.%d.%d_20231023",m1,m2,m3);
		#endif			
	#endif


}





//**************************************程序版本变更记录************************************************
/**100**//**********发布日期：未发布   版本号：V1.00  硬件版本：通用 作者：MZZE************************/
	    //修改内容：初版
		
		
		
		
//******************************************************************************************************






















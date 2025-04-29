#include "bsp_soft_oled.h"
#include "bsp_systick.h"
#include "func_oled.h"

//--IO口操作宏定义---
#if(BSP_SOFT_OLED_TYPE==1)    //IIC接口


#define	OLED_IIC_SDA_Set()   PBout(15)=1
#define	OLED_IIC_SDA_Clr()   PBout(15)=0

#define	OLED_IIC_SCL_Set()   PBout(13)=1
#define	OLED_IIC_SCL_Clr()   PBout(13)=0

#endif

#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口

#define OLED_SPI_SCLK_Set()   PBout(13)=1
#define OLED_SPI_SCLK_Clr()   PBout(13)=0

#define OLED_SPI_MOSI_Set()  PBout(15)=1
#define OLED_SPI_MOSI_Clr()  PBout(15)=0


#define OLED_DC_Set()		PBout(12)=1     //命令数据选择线宏定义
#define	OLED_DC_Clr()		PBout(12)=0


#define OLED_CS_Set() 		PBout(7)=1      //片选宏定义
#define OLED_CS_Clr() 		PBout(7)=0


#define	OLED_RST_Set()		PBout(6)=1      //复位管脚宏定义
#define	OLED_RST_Clr()		PBout(6)=0

#endif



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据




//延时
static void bsp_oled_delay(void)  //1us
{
	u8 t=10;
	while(t--);
}

static void bsp_oled_delay2(void)  //500ns
{
	u8 t=3;
	while(t--);
}


static void bsp_oled_io_config(void)
{
	
	GPIO_InitTypeDef GPIO_Initure;
	

	
	#if(BSP_SOFT_OLED_TYPE==1)    //IIC接口

    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟

    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_15; //PIN13,15
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	OLED_IIC_SCL_Set();
	OLED_IIC_SDA_Set();
	
	#endif

	#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口

    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟

    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15; //PIN6,7,12,13,15
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	OLED_SPI_SCLK_Clr();
	OLED_SPI_MOSI_Set();
	OLED_RST_Set();
	OLED_CS_Clr();
	#endif	
}

#if(BSP_SOFT_OLED_TYPE==1)    //IIC接口


//起始信号
static void bsp_iic_start(void)
{
	OLED_IIC_SDA_Set();
	OLED_IIC_SCL_Set();
	bsp_oled_delay();
	OLED_IIC_SDA_Clr();
	bsp_oled_delay();
	OLED_IIC_SCL_Clr();
	bsp_oled_delay();
}

//结束信号
static void bsp_iic_stop(void)
{
	OLED_IIC_SDA_Clr();
	OLED_IIC_SCL_Set();
	bsp_oled_delay();
	OLED_IIC_SDA_Set();
}

//等待信号响应
static void bsp_iic_waitack(void) //测数据信号的电平
{
	OLED_IIC_SDA_Set();
	bsp_oled_delay();
	OLED_IIC_SCL_Set();
	bsp_oled_delay();
	OLED_IIC_SCL_Clr();
	bsp_oled_delay();
}

//写入一个字节
static void bsp_iic_send_byte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			OLED_IIC_SDA_Set();
		}
		else
		{
			OLED_IIC_SDA_Clr();
		}
		bsp_oled_delay();
		OLED_IIC_SCL_Set();
		bsp_oled_delay();
		OLED_IIC_SCL_Clr();//将时钟信号设置为低电平
		dat<<=1;
	}
}

#endif


#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口

static void bsp_spi_send_byte(u8 dat)
{
	u8 i;
	bsp_oled_delay2();	
	for(i=0;i<8;i++)
	{
		OLED_SPI_SCLK_Clr();        //拉低时钟线，主机可以写数据
		if(dat & 0x80)
		{
			OLED_SPI_MOSI_Set();
		}
		else
		{
			OLED_SPI_MOSI_Clr();
		}
		bsp_oled_delay2();		
		OLED_SPI_SCLK_Set();      	//产生上升沿，帮助从机接收	
		dat<<=1;     				//发送下一位数据
		bsp_oled_delay2();			
	}	
}

#endif





//发送一个字节
//mode:数据/命令标志 0,表示命令;1,表示数据;
static void bsp_oled_wr_byte(u8 dat,u8 mode)
{
#if(BSP_SOFT_OLED_TYPE==1)    //IIC接口	
	bsp_iic_start();
	bsp_iic_send_byte(0x78);
	bsp_iic_waitack();
	if(mode)
	{bsp_iic_send_byte(0x40);}
	else
	{bsp_iic_send_byte(0x00);}
	bsp_iic_waitack();
	bsp_iic_send_byte(dat);
	bsp_iic_waitack();
	bsp_iic_stop();
#endif
#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口	
	if(mode)
	{
		OLED_DC_Set();
	}
	else
	{
		OLED_DC_Clr();	
	}
	bsp_spi_send_byte(dat);
	//DC线空闲时拉高
	OLED_DC_Set();	

#endif 
}


void BSP_SOFT_OLED_RST(void)
{
	
	#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口		
	OLED_RST_Clr();
	BSP_SYSTICK_DELAY_MS(100);
	OLED_RST_Set();
	#endif 
	BSP_SYSTICK_DELAY_MS(100);
}

//开启OLED显示 
void BSP_SOFT_OLED_DISPLAY_ON(void)
{
	bsp_oled_wr_byte(0x8D,OLED_CMD);//电荷泵使能
	bsp_oled_wr_byte(0x14,OLED_CMD);//开启电荷泵
	bsp_oled_wr_byte(0xAF,OLED_CMD);//点亮屏幕
}

//关闭OLED显示 
void BSP_SOFT_OLED_DISPLAY_OFF(void)
{
	bsp_oled_wr_byte(0x8D,OLED_CMD);//电荷泵使能
	bsp_oled_wr_byte(0x10,OLED_CMD);//关闭电荷泵
	bsp_oled_wr_byte(0xAE,OLED_CMD);//关闭屏幕
}


//反显函数
void BSP_SOFT_OLED_COLORTURN(u8 i)
{
	if(i==0)
	{
		bsp_oled_wr_byte(0xA6,OLED_CMD);//正常显示
	}
	if(i==1)
	{
		bsp_oled_wr_byte(0xA7,OLED_CMD);//反色显示
	}
}

//屏幕旋转180度
void BSP_SOFT_OLED_DISPLAYTURN(u8 i)
{
	if(i==0)
	{
		bsp_oled_wr_byte(0xC8,OLED_CMD);//正常显示
		bsp_oled_wr_byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		bsp_oled_wr_byte(0xC0,OLED_CMD);//反转显示
		bsp_oled_wr_byte(0xA0,OLED_CMD);
	}
}


//更新显存到OLED	
void BSP_SOFT_OLED_REFRESH_GRAM(void)
{
	u8 i,n;
	#if(BSP_SOFT_OLED_TYPE==1)    //IIC接口			
	bsp_iic_start();
	bsp_iic_send_byte(0x78);
	bsp_iic_waitack();
	bsp_iic_send_byte(0x40);
	bsp_iic_waitack();
	for(i=0;i<8;i++)
	{	
		for(n=0;n<128;n++)
		{
			bsp_iic_send_byte(FUNC_OLED_GRAM[i][n]);
			bsp_iic_waitack();
		}
	}
	bsp_iic_stop();
	#endif
	#if(BSP_SOFT_OLED_TYPE==2)    //SPI接口
	for(i=0;i<8;i++)
	{	
		for(n=0;n<128;n++)
		{
			bsp_oled_wr_byte(FUNC_OLED_GRAM[i][n],OLED_DATA);
		}
	}
	#endif			
}



//初始化SSD1315					    
void BSP_SOFT_OLED_INIT(void)
{ 	
    //-----配置IO口----------- 
    bsp_oled_io_config();
  							  
	BSP_SOFT_OLED_RST();
	
	bsp_oled_wr_byte(0xAE,OLED_CMD);//--turn off oled panel

	bsp_oled_wr_byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	//---设置亮度---
	bsp_oled_wr_byte(0x81,OLED_CMD);//--set contrast control register
	bsp_oled_wr_byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	
	
	bsp_oled_wr_byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	bsp_oled_wr_byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	bsp_oled_wr_byte(0xA6,OLED_CMD);//--set normal display
	bsp_oled_wr_byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	bsp_oled_wr_byte(0x3f,OLED_CMD);//--1/64 duty
	bsp_oled_wr_byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	bsp_oled_wr_byte(0x00,OLED_CMD);//-not offset
	bsp_oled_wr_byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	bsp_oled_wr_byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	bsp_oled_wr_byte(0xD9,OLED_CMD);//--set pre-charge period
	bsp_oled_wr_byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	bsp_oled_wr_byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	bsp_oled_wr_byte(0x12,OLED_CMD);
	bsp_oled_wr_byte(0xDB,OLED_CMD);//--set vcomh
	bsp_oled_wr_byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	
	//-----寻址模式设置---
	bsp_oled_wr_byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)	
	bsp_oled_wr_byte(0x00,OLED_CMD);//

	//---针对于水平寻址模式的设置--
	bsp_oled_wr_byte(0x21,OLED_CMD);//---设置列起始地址
	bsp_oled_wr_byte(0x00,OLED_CMD);//--起始
	bsp_oled_wr_byte(0x7F,OLED_CMD);//--结束	
		
	bsp_oled_wr_byte(0x22,OLED_CMD);//---设置行起始地址
	bsp_oled_wr_byte(0x00,OLED_CMD);//--起始
	bsp_oled_wr_byte(0x07,OLED_CMD);//--结束	


	bsp_oled_wr_byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	bsp_oled_wr_byte(0x14,OLED_CMD);//--set(0x10) disable
	bsp_oled_wr_byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	bsp_oled_wr_byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	bsp_oled_wr_byte(0xAF,OLED_CMD);
	bsp_oled_wr_byte(0xAF,OLED_CMD);
}  
































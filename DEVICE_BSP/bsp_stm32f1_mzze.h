#ifndef __MZZE_H__
#define __MZZE_H__

#include "stm32f1xx.h"
#include "string.h"
#include "stdio.h"
//#include "arm_math.h"

/********二进制代表十六进制宏定义*****/
#define 	B0000_0000   0x00
#define 	B0000_0001   0x01
#define 	B0000_0010   0x02
#define 	B0000_0011   0x03
#define 	B0000_0100	0x04
#define 	B0000_0101	0x05
#define 	B0000_0110	0x06
#define 	B0000_0111	0x07
#define 	B0000_1000	0x08
#define 	B0000_1001	0x09
#define 	B0000_1010	0x0A
#define 	B0000_1011	0x0B
#define 	B0000_1100	0x0C
#define 	B0000_1101	0x0D
#define		B0000_1110	0x0E
#define		B0000_1111	0x0F
#define 	B0001_0000	0x10
#define 	B0001_0001	0x11
#define 	B0001_0010	0x12
#define 	B0001_0011	0x13
#define 	B0001_0100	0x14
#define 	B0001_0101	0x15
#define 	B0001_0110	0x16
#define 	B0001_0111	0x17
#define 	B0001_1000	0x18
#define 	B0001_1001	0x19
#define 	B0001_1010	0x1A
#define 	B0001_1011	0x1B
#define 	B0001_1100	0x1C
#define 	B0001_1101	0x1D
#define 	B0001_1110	0x1E
#define 	B0001_1111	0x1F
#define 	B0010_0000	0x20
#define 	B0010_0001	0x21
#define 	B0010_0010	0x22
#define 	B0010_0011	0x23
#define 	B0010_0100	0x24
#define 	B0010_0101	0x25
#define 	B0010_0110	0x26
#define 	B0010_0111	0x27
#define 	B0010_1000	0x28
#define 	B0010_1001	0x29
#define 	B0010_1010	0x2A
#define 	B0010_1011	0x2B
#define 	B0010_1100	0x2C
#define 	B0010_1101	0x2D
#define 	B0010_1110	0x2E
#define 	B0010_1111	0x2F
#define 	B0011_0000	0x30
#define 	B0011_0001	0x31
#define 	B0011_0010	0x32
#define 	B0011_0011	0x33
#define		B0011_0100	0x34
#define 	B0011_0101	0x35
#define 	B0011_0110	0x36
#define 	B0011_0111	0x37
#define 	B0011_1000	0x38
#define		B0011_1001	0x39
#define 	B0011_1010	0x3A
#define 	B0011_1011	0x3B
#define 	B0011_1100	0x3C
#define 	B0011_1101	0x3D
#define 	B0011_1110	0x3E
#define 	B0011_1111	0x3F
#define 	B0100_0000	0x40
#define 	B0100_0001	0x41
#define 	B0100_0010	0x42
#define 	B0100_0011	0x43
#define 	B0100_0100	0x44
#define 	B0100_0101	0x45
#define 	B0100_0110	0x46
#define 	B0100_0111	0x47
#define 	B0100_1000	0x48
#define 	B0100_1001	0x49
#define 	B0100_1010	0x4A
#define 	B0100_1011	0x4B
#define 	B0100_1100	0x4C
#define 	B0100_1101	0x4D
#define 	B0100_1110	0x4E
#define 	B0100_1111	0x4F
#define 	B0101_0000	0x50
#define 	B0101_0001	0x51
#define 	B0101_0010	0x52
#define 	B0101_0011	0x53
#define 	B0101_0100	0x54
#define 	B0101_0101	0x55
#define 	B0101_0110	0x56
#define 	B0101_0111	0x57
#define 	B0101_1000	0x58
#define 	B0101_1001	0x59
#define 	B0101_1010	0x5A
#define 	B0101_1011	0x5B
#define 	B0101_1100	0x5C
#define 	B0101_1101	0x5D
#define 	B0101_1110	0x5E
#define 	B0101_1111	0x5F
#define 	B0110_0000	0x60
#define 	B0110_0001	0x61
#define 	B0110_0010	0x62
#define 	B0110_0011	0x63
#define 	B0110_0100	0x64
#define 	B0110_0101	0x65
#define 	B0110_0110	0x66
#define 	B0110_0111	0x67
#define 	B0110_1000	0x68
#define 	B0110_1001	0x69
#define 	B0110_1010	0x6A
#define 	B0110_1011	0x6B
#define 	B0110_1100	0x6C
#define 	B0110_1101	0x6D
#define 	B0110_1110	0x6E
#define 	B0110_1111	0x6F
#define 	B0111_0000	0x70
#define 	B0111_0001	0x71
#define 	B0111_0010	0x72
#define 	B0111_0011	0x73
#define 	B0111_0100	0x74
#define 	B0111_0101	0x75
#define 	B0111_0110	0x76
#define 	B0111_0111	0x77
#define 	B0111_1000	0x78
#define 	B0111_1001	0x79
#define 	B0111_1010	0x7A
#define 	B0111_1011	0x7B
#define 	B0111_1100	0x7C
#define 	B0111_1101	0x7D
#define 	B0111_1110	0x7E
#define 	B0111_1111	0x7F
#define 	B1000_0000	0x80
#define 	B1000_0001	0x81
#define 	B1000_0010	0x82
#define 	B1000_0011	0x83
#define 	B1000_0100	0x84
#define 	B1000_0101	0x85
#define 	B1000_0110	0x86
#define 	B1000_0111	0x87
#define 	B1000_1000	0x88
#define 	B1000_1001	0x89
#define 	B1000_1010	0x8A
#define 	B1000_1011	0x8B
#define 	B1000_1100	0x8C
#define 	B1000_1101	0x8D
#define 	B1000_1110	0x8E
#define 	B1000_1111	0x8F
#define 	B1001_0000	0x90
#define 	B1001_0001	0x91
#define 	B1001_0010	0x92
#define 	B1001_0011	0x93
#define 	B1001_0100	0x94
#define 	B1001_0101	0x95
#define 	B1001_0110	0x96
#define 	B1001_0111	0x97
#define 	B1001_1000	0x98
#define 	B1001_1001	0x99
#define 	B1001_1010	0x9A
#define 	B1001_1011	0x9B
#define 	B1001_1100	0x9C
#define 	B1001_1101	0x9D
#define 	B1001_1110	0x9E
#define 	B1001_1111	0x9F
#define 	B1010_0000	0xA0
#define 	B1010_0001	0xA1
#define 	B1010_0010	0xA2
#define 	B1010_0011	0xA3
#define 	B1010_0100	0xA4
#define 	B1010_0101	0xA5
#define 	B1010_0110	0xA6
#define 	B1010_0111	0xA7
#define 	B1010_1000	0xA8
#define 	B1010_1001	0xA9
#define 	B1010_1010	0xAA
#define 	B1010_1011	0xAB
#define 	B1010_1100	0xAC
#define 	B1010_1101	0xAD
#define 	B1010_1110	0xAE
#define 	B1010_1111	0xAF
#define 	B1011_0000	0xB0
#define 	B1011_0001	0xB1
#define 	B1011_0010	0xB2
#define 	B1011_0011	0xB3
#define 	B1011_0100	0xB4
#define 	B1011_0101	0xB5
#define 	B1011_0110	0xB6
#define 	B1011_0111	0xB7
#define 	B1011_1000	0xB8
#define 	B1011_1001	0xB9
#define 	B1011_1010	0xBA
#define 	B1011_1011	0xBB
#define 	B1011_1100	0xBC
#define 	B1011_1101	0xBD
#define 	B1011_1110	0xBE
#define 	B1011_1111	0xBF
#define 	B1100_0000	0xC0
#define 	B1100_0001	0xC1
#define 	B1100_0010	0xC2
#define 	B1100_0011	0xC3
#define 	B1100_0100	0xC4
#define 	B1100_0101	0xC5
#define 	B1100_0110	0xC6
#define 	B1100_0111	0xC7
#define 	B1100_1000	0xC8
#define 	B1100_1001	0xC9
#define 	B1100_1010	0xCA
#define 	B1100_1011	0xCB
#define 	B1100_1100	0xCC
#define 	B1100_1101	0xCD
#define 	B1100_1110	0xCE
#define 	B1100_1111	0xCF
#define 	B1101_0000	0xD0
#define 	B1101_0001	0xD1
#define 	B1101_0010	0xD2
#define 	B1101_0011	0xD3
#define 	B1101_0100	0xD4
#define 	B1101_0101	0xD5
#define 	B1101_0110	0xD6
#define 	B1101_0111	0xD7
#define 	B1101_1000	0xD8
#define 	B1101_1001	0xD9
#define 	B1101_1010	0xDA
#define 	B1101_1011	0xDB
#define 	B1101_1100	0xDC
#define 	B1101_1101	0xDD
#define 	B1101_1110	0xDE
#define 	B1101_1111	0xDF
#define 	B1110_0000	0xE0
#define 	B1110_0001	0xE1
#define 	B1110_0010	0xE2
#define 	B1110_0011	0xE3
#define 	B1110_0100	0xE4
#define 	B1110_0101	0xE5
#define 	B1110_0110	0xE6
#define 	B1110_0111	0xE7
#define 	B1110_1000	0xE8
#define 	B1110_1001	0xE9
#define 	B1110_1010	0xEA
#define 	B1110_1011	0xEB
#define 	B1110_1100	0xEC
#define 	B1110_1101	0xED
#define 	B1110_1110	0xEE
#define 	B1110_1111	0xEF
#define 	B1111_0000	0xF0
#define 	B1111_0001	0xF1
#define 	B1111_0010	0xF2
#define 	B1111_0011	0xF3
#define 	B1111_0100	0xF4
#define 	B1111_0101	0xF5
#define 	B1111_0110	0xF6
#define 	B1111_0111	0xF7
#define 	B1111_1000	0xF8
#define 	B1111_1001	0xF9
#define 	B1111_1010	0xFA
#define 	B1111_1011	0xFB
#define 	B1111_1100	0xFC
#define 	B1111_1101	0xFD
#define 	B1111_1110	0xFE
#define 	B1111_1111	0xFF
/*********************************/

/*************ascii字符表***********/
#define AS_NUT    0        //空字符
#define AS_SOH    1        //标题开始
#define AS_STX    2        //正文开始
#define AS_ETX    3        //正文结束
#define AS_EOT    4        //传输结束
#define AS_ENQ    5        //请求
#define AS_ACK    6        //收到通知
#define AS_BEL    7        //响铃
#define AS_BS     8        //退格
#define AS_HT     9        //水平制表符
#define AS_LF     10       //换行键
#define AS_VT     11       //垂直制表符
#define AS_FF     12       //换页键
#define AS_CR     13       //回车键
#define AS_SO     14       //不用切换
#define AS_SI     15       //启用切换
#define AS_DLE    16       //数据链路转义
#define AS_DC1    17       //设备控制1
#define AS_DC2    18       //设备控制2
#define AS_DC3    19       //设备控制3
#define AS_DC4    20       //设备控制4
#define AS_NAK    21       //拒绝接收
#define AS_SYN    22       //同步空闲
#define AS_ETB    23       //结束传输块
#define AS_CAN    24       //取消
#define AS_EM     25       //媒介结束
#define AS_SUB    26       //代替
#define AS_ESC    27       //换码（溢出）
#define AS_FS     28       //文件分隔符
#define AS_GS     29       //分组符
#define AS_RS     30       //记录分隔符
#define AS_US     31       //单元分隔符
#define AS_SPACE  32       //空格
#define AS_gantan         33       // !  叹号
#define AS_shuangyin      34       // "  双引号
#define AS_jinhao         35       // #  井号
#define AS_jueduiyinyong  36       // $  美元符
#define AS_baifenhao      37       // %  百分号
#define AS_yu             38       // &  和号
#define AS_danyin         39       // '  闭单引号
#define AS_zuokuohao      40       // (  开括号
#define AS_youkuohao      41       // )  闭括号
#define AS_xinhao         42       // *  星号
#define AS_jiahao         43       // +  加号
#define AS_douhao         44       // ,  逗号
#define AS_jian           45       // -  减号/破折号
#define AS_dian           46       // .  句号
#define AS_youxiegang     47       // /  斜杠
#define AS_0      48    //0
#define AS_1      49    //1
#define AS_2      50    //2
#define AS_3      51    //3
#define AS_4      52    //4
#define AS_5      53    //5
#define AS_6      54    //6
#define AS_7      55    //7
#define AS_8      56    //8
#define AS_9      57    //9
#define AS_maohao         58       // :  冒号
#define AS_fenhao         59       // ;  分号
#define AS_xiaoyuhao      60       // <  小于
#define AS_dengyuhao      61       // =  等于
#define AS_dayuhao        62       // >  大于
#define AS_wenhao         63       // ?  问号
#define AS_aquanhao       64       // @  电子邮件符
#define AS_A      65    //A
#define AS_B      66    //B
#define AS_C      67    //C
#define AS_D      68    //D
#define AS_E      69    //E
#define AS_F      70    //F
#define AS_G      71    //G
#define AS_H      72    //H
#define AS_I      73    //I
#define AS_J      74    //J
#define AS_K      75    //K
#define AS_L      76    //L
#define AS_M      77    //M
#define AS_N      78    //N
#define AS_O      79    //O
#define AS_P      80    //P
#define AS_Q      81    //Q
#define AS_R      82    //R
#define AS_S      83    //S
#define AS_T      84    //T
#define AS_U      85    //U
#define AS_V      86    //V
#define AS_W      87    //W
#define AS_X      88    //X
#define AS_Y      89    //Y
#define AS_Z      90    //Z
#define AS_zuofangkuohao  91      // [  开方括号
#define AS_zuoxiegang     92      // \  反斜杠
#define AS_youfangkuohao  93      // ]  闭方括号
#define AS_tuozifu        94      // ^  脱字符 
#define AS_xiahuaxian     95      // _  下划线
#define AS_kaidanyinhao   96      // `   开单引号
#define AS_a      97    //a
#define AS_b      98    //b
#define AS_c      99    //c
#define AS_d      100   //d
#define AS_e      101   //e
#define AS_f      102   //f
#define AS_g      103   //g
#define AS_h      104   //h
#define AS_i      105   //i
#define AS_j      106   //j
#define AS_k      107   //k
#define AS_l      108   //l
#define AS_m      109   //m
#define AS_n      110   //n
#define AS_o      111   //o
#define AS_p      112   //P
#define AS_q      113   //q
#define AS_r      114   //r
#define AS_s      115   //s
#define AS_t      116   //t
#define AS_u      117   //u
#define AS_v      118   //v
#define AS_w      119   //w
#define AS_x      120   //x
#define AS_y      121   //y
#define AS_z      122   //z
#define AS_zuodakuohao    123    // {  开花括号
#define AS_huohao         124    // |  垂线
#define AS_youdakuohao    125    // }  闭花括号
#define AS_BOLANGHAO      126    // ~  波浪号
#define AS_DEL    127   //删除

/**********位操作函数*********************************/
#define GET_8BIT(m,n)    ((m&(0X01<<n))==(0X01<<n))     //获得8位字节m,的第n位数，从0开始计数
#define SET_8BIT(m,n)    (m|=(0X01<<n))        //置位8位字节m,的第n位数
#define CLR_8BIT(m,n)    (m&=(~(0X01<<n)))     //清08位字节m,的第n位数



/*************数据类型宏定义***********/
//定义一些常用的数据类型短关键字 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  
/********32位结构体以及共用体***********************/
typedef struct {					//32位结构体
		unsigned short int bit0   :1;  
		unsigned short int bit1   :1;  
		unsigned short int bit2   :1;  
		unsigned short int bit3   :1;  
		unsigned short int bit4   :1;  
		unsigned short int bit5   :1;  
		unsigned short int bit6   :1;  
		unsigned short int bit7   :1;  		
		unsigned short int bit8   :1;  
		unsigned short int bit9   :1;  
		unsigned short int bit10   :1;  
		unsigned short int bit11   :1;  
		unsigned short int bit12   :1;  
		unsigned short int bit13   :1;  
		unsigned short int bit14   :1;  
		unsigned short int bit15   :1;  
		unsigned short int bit16   :1;  
		unsigned short int bit17   :1;  
		unsigned short int bit18   :1;  
		unsigned short int bit19   :1;  
		unsigned short int bit20   :1;  
		unsigned short int bit21   :1;  
		unsigned short int bit22   :1;  
		unsigned short int bit23   :1;  		
		unsigned short int bit24   :1;  
		unsigned short int bit25   :1;  
		unsigned short int bit26   :1;  
		unsigned short int bit27   :1;  
		unsigned short int bit28   :1;  
		unsigned short int bit29   :1;  
		unsigned short int bit30   :1;  
		unsigned short int bit31   :1;  	
}struct_32_bit;
typedef union {
	  struct_32_bit bit_32;
		struct {					//16位结构体
		unsigned char ll;
		unsigned char lh;
		unsigned char hl;			
		unsigned char hh;
		}hh_ll;
		unsigned long int all;
}bit_hl_all_32bit_union;	      //对16位数据，可进行按位读写或按字节读写或整个读写的共用体





/********16位定义结构体以及共用体*******************/
typedef struct {					//16位结构体
		unsigned short int bit0   :1;  
		unsigned short int bit1   :1;  
		unsigned short int bit2   :1;  
		unsigned short int bit3   :1;  
		unsigned short int bit4   :1;  
		unsigned short int bit5   :1;  
		unsigned short int bit6   :1;  
		unsigned short int bit7   :1;  		
		unsigned short int bit8   :1;  
		unsigned short int bit9   :1;  
		unsigned short int bit10   :1;  
		unsigned short int bit11   :1;  
		unsigned short int bit12   :1;  
		unsigned short int bit13   :1;  
		unsigned short int bit14   :1;  
		unsigned short int bit15   :1;  	
}struct_16_bit;

typedef union {
	  struct_16_bit bit_16;
		struct {					//16位结构体
		unsigned char l;
		unsigned char h;
		}h_l;
		unsigned short int all;
}bit_hl_all_16bit_union;	      //对16位数据，可进行按位读写或按字节读写或整个读写的共用体

typedef union {
	    short int sall;
		struct {					//16位结构体
		unsigned char l;
		unsigned char h;
		}h_l;
		unsigned short int all;
}s16_u16_union;	      //有符号无符号16位数据共用体

/********8位定义结构体以及共用体*******************/
typedef struct {					//8位结构体
		unsigned char bit0   :1;  
		unsigned char bit1   :1;  
		unsigned char bit2   :1;  
		unsigned char bit3   :1;  
		unsigned char bit4   :1;  
		unsigned char bit5   :1;  
		unsigned char bit6   :1;  
		unsigned char bit7   :1;  		 
}struct_8_bit;

typedef union {
	  struct_8_bit bit_8;
		unsigned char all;
}bit_all_8bit_union;	      //对8位数据，可进行按位读写或整个读写的共用体

/********16位定义结构体以及共用体*******************/
typedef union    			//16位共用体
{

struct {					//16位结构体
unsigned char l;
unsigned char h;
}h_l;
unsigned short int all;
}_16_union;
/************************此部分注意和STC在存放顺序上有区别*************/
/***********************************/

typedef struct
{
    unsigned char u16_2;     //低字节在前  //低地址
    unsigned char u16_1;    
} u16_2byte_struct;

union u16_union
{
    u16_2byte_struct u16_2_byte;
    u16 all;       
};
typedef struct
{
    unsigned char u32_4;    //低字节在前
    unsigned char u32_3;
    unsigned char u32_2;
    unsigned char u32_1;    
}u32_4byte_struct;

union u32_union
{
    u32_4byte_struct u32_4_byte;
    u32 all;        
};
/***********************************************************************/

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入








#endif



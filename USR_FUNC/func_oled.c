#include "func_oled.h"
#include "func_oledfont.h"
//#include "bsp_soft_oled.h"
#include "bsp_hard_oled.h"



//------宏定义，lcd屏的物理分辨率--
#define FUNC_OLED_H_NUM  128    //行的像素点数
#define FUNC_OLED_l_NUM  64    //列的像素点数

//------旋转后显示分辨率--
#define FUNC_OLED_DIS_H_NUM  128    //行的像素点数
#define FUNC_OLED_DIS_l_NUM  64    //列的像素点数

/*********************变量定义***********************/
//----局部变量定义----

                                                                      
//----全局变量-----
//OLED的显存		   	 
unsigned char FUNC_OLED_GRAM[8][128]={0};


            
                                    
                                    
/*************RAM区整体操作***********/
void FUNC_OLED_GRAM_ALL_CLEAR(void)
{
/*
 *函数名：FUNC_OLED_GRAM_ALL_CLEAR
 *描述  ：显示芯片RAM区清0
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/	
	unsigned short int i=0;
	for(i=0;i<1024;i++)
	{
		(*((&FUNC_OLED_GRAM[0][0])+i))=0x00;		
	}	
	
}

void FUNC_OLED_GRAM_ALL_SET(void)
{
/*
 *函数名：FUNC_OLED_GRAM_ALL_SET
 *描述  ：显示芯片RAM区置1
 *输入  ：无
 *输出  ：无
 *调用  ：内部调用
*/	
	unsigned short int i=0;
	for(i=0;i<1024;i++)
	{
		(*((&FUNC_OLED_GRAM[0][0])+i))=0xff;		
	}				
}

void FUNC_OLED_GRAM_INIT(void)
{
/*
 *函数名：FUNC_OLED_GRAM_INIT
 *描述  ：显示芯片RAM区初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/		  
      //----清0RAM----
	  FUNC_OLED_GRAM_ALL_CLEAR();
	
	  //----赋1RAM----
//	  FUNC_OLED_GRAM_ALL_SET();
}





//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空	
void FUNC_OLED_DRAWPOINT(u8 x,u8 y,u8 t)
{
	
    unsigned char x_local;
    unsigned char y_local;    

    //记录
    x_local=x; 
    y_local=y;       
    
//    //x镜像
//    x_local=FUNC_OLED_H_NUM-1-x; 
//    y_local=y;     
 
//    //y镜像
//    x_local=x; 
//    y_local=FUNC_OLED_l_NUM-1-y;  
    
    //旋转0度
    x=x_local; 
    y=y_local;    
    
//    //旋转90度
//    x=y_local; 
//    y=FUNC_OLED_l_NUM-1-x_local;    
    
//    //旋转180度
//    x=FUNC_OLED_H_NUM -1-x_local; 
//    y=FUNC_OLED_l_NUM-1-y_local; 

//    //旋转270度
//    x=FUNC_OLED_H_NUM -1-y_local; 
//    y=x_local; 	
	
    //-----根据坐标，定位需要修改的RAM-----
    if((x<FUNC_OLED_DIS_H_NUM)&&(y<FUNC_OLED_DIS_l_NUM))     //判断点的坐标是否有效
    {	
		u8 i,m,n;
		i=y/8;
		m=y%8;
		n=1<<m;
		if(t){FUNC_OLED_GRAM[i][x]|=n;}
		else
		{
			FUNC_OLED_GRAM[i][x]=~FUNC_OLED_GRAM[i][x];
			FUNC_OLED_GRAM[i][x]|=n;
			FUNC_OLED_GRAM[i][x]=~FUNC_OLED_GRAM[i][x];
		}
	}
}




//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void FUNC_OLED_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		FUNC_OLED_DRAWPOINT(uRow,uCol,1);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

//画白线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void FUNC_OLED_DrawLine_f(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		FUNC_OLED_DRAWPOINT(uRow,uCol,0);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void FUNC_OLED_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	FUNC_OLED_DrawLine(x1,y1,x2,y1);
	FUNC_OLED_DrawLine(x1,y1,x1,y2);
	FUNC_OLED_DrawLine(x1,y2,x2,y2);
	FUNC_OLED_DrawLine(x2,y1,x2,y2);
}

//清0一个矩形区域	  
//(x1,y1)起始点 x_wide:x轴宽度 y_wide:y轴宽度
void FUNC_OLED_clearRectangle(u16 x1, u16 y1, u16 x_wide, u16 y_wide)
{
    unsigned char y=0; 
    for(y=0;y<y_wide;y++)      //逐行画白线
    {
        FUNC_OLED_DrawLine_f(x1,y1+y,x1+x_wide,y1+y); 		
    }
}

//填充一个矩形区域	  
//(x1,y1)起始点 x_wide:x轴宽度 y_wide:y轴宽度
void FUNC_OLED_fillRectangle(u16 x1, u16 y1, u16 x_wide, u16 y_wide)
{
    unsigned char y=0; 
    for(y=0;y<y_wide;y++)      //逐行画线
    {
        FUNC_OLED_DrawLine(x1,y1+y,x1+x_wide,y1+y);                
    }
}





//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void FUNC_OLED_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		FUNC_OLED_DRAWPOINT(x0+a,y0-b,1);             //5
 		FUNC_OLED_DRAWPOINT(x0+b,y0-a,1);             //0           
		FUNC_OLED_DRAWPOINT(x0+b,y0+a,1);             //4               
		FUNC_OLED_DRAWPOINT(x0+a,y0+b,1);             //6 
		FUNC_OLED_DRAWPOINT(x0-a,y0+b,1);             //1       
 		FUNC_OLED_DRAWPOINT(x0-b,y0+a,1);             
		FUNC_OLED_DRAWPOINT(x0-a,y0-b,1);             //2             
  		FUNC_OLED_DRAWPOINT(x0-b,y0-a,1);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 	


 
    
void FUNC_OLED_Show_ASCII_Mat(u16 x,u16 y,u8 *ascii,u8 size,u8 mode)
{
/*
 *函数名：Show_ASCII_Mat
 *描述  ：显示一个ASCII字符
 *输入  ：x: 显示坐标x
          y:显示坐标y
          font:汉字GBK码
          size:字符大小
          mode:0,正常显示,1,叠加显示	    
 *输出  ：无
 *调用  ：外部调用
*/       
	u8 temp,t,t1,chr;
	u8 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	chr=(*ascii)-' ';//得到偏移后的值		 
    for(t=0;t<csize;t++)
    {   
		if(size==12)temp=asc2_1206[chr][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[chr][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[chr][t];	//调用2412字体
		else return;								//没有的字库
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
            {
                FUNC_OLED_DRAWPOINT(x,y,1);
            }
            else
            {
                if(mode==0)
                {
                    FUNC_OLED_DRAWPOINT(x,y,0);
                }
            }
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }     
    
}


  	   		   
void FUNC_OLED_Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode,u8 ascii_ypy)
{
/*
 *函数名：Show_Str
 *描述  ：在指定位置开始显示一个字符串,此字符串显示在指定的区域内,支持自动换行
 *输入  ：x:字符的起始位置 x
          y:字符的起始位置 y
          width:显示的区域宽度，从x开始
          height:显示的区域高度，从y开始
          str: 字符串数据指针
          size: 字符的大小   目前只支持12 16 的字符串显示
          mode: 显示模式 0，非叠加方式 1，叠加方式
          ascii_ypy: ASCII字符,y轴偏移 正为向下偏移 
 *输出  ：无
 *调用  ：外部调用
*/  
    u16 x_start=x;
    u16 y_start=y;
	u16 x_max=x+width;       //最大X值
	u16 y_max=y+height;		 //最大Y值
    if(height<size)return;    //显示高度不足字符高度        
    while(*str!=0)//数据未结束
    { 
        if(*str>0x80)       //若是汉字
        { 
            if((x+size)>x_max)//换行
			{	    
				y+=size;
				x=x_start;		  
			}
	        if((y+size)>y_max)break;//越界返回  
            switch(size)
            {
                case OLED_STRING_12:
                {
//                    Show_GB2312_Mat(x,y,str,OLED_GB2312_12X12,mode);//写入GB2312字符            //暂不支持                                     
                }break; 
                case OLED_STRING_16:
                {
//                    Show_GB2312_Mat(x,y,str,OLED_GB2312_16X16,mode);//写入GB2312字符                          
                }break;
            }            
	        str+=2; 
	        x+=size;//下一个字符偏移	            
   
        }
        else
        {
            if(*str==13)//判断换行符号
            {         
                y+=size;
                x=x_start;
                if((y+size)>y_max)break;//越界返回 
                str++;                 
            }
            else        //不是换行符号
            {
                if((x+size/2)>x_max)//换行
                {				   
                    y+=size;
                    x=x_start;	   
                }	
                if((y+size)>y_max)break;//越界返回
                switch(size)
                {
                    case OLED_STRING_12:
                    {
                        FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_12X12,mode);//写入ASCII字符                                                 
                    }break; 
                    case OLED_STRING_16:
                    {
                        FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_16X16,mode);//写入ASCII字符                           
                    }break;
                    case OLED_STRING_24:
                    {
                        FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_24X24,mode);//写入ASCII字符                           
                    }break;                    
                }
                str++;      //得到下一个内码 
                x+=size/2; //字符,为全字的一半         
            }                    
        }					 
    }   
}  		



unsigned short int FUNC_OLED_Show_Str_gundon(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode,u16 str_hang_py,u8 ascii_ypy)
{
/*
 *函数名：Show_Str
 *描述  ：在指定位置开始显示一个字符串,此字符串显示在指定的区域内,支持自动换行
 *输入  ：x:字符的起始位置 x
          y:字符的起始位置 y
          width:显示的区域宽度，从x开始
          height:显示的区域高度，从y开始
          str: 字符串数据指针
          size: 字符的大小   目前只支持12 16 的字符串显示
          mode: 显示模式 0，非叠加方式 1，叠加方式
          ascii_ypy: ASCII字符,y轴偏移 正为向下偏移 
          str_hang_py: 字符串显示行偏移，即从字符串的第几行开始显示
 *输出  ：高四位： 0-显示完成  1-显示未完成  2-显示高度不足字符高度
          低十二位 当前显示完成的行数
 *调用  ：外部调用
*/ 
    u16 hang_num=0;         //当前字符显示位于的行数
    u16 x_start=x;
    u16 y_start=y;
	u16 x_max=x+width;       //最大X值
	u16 y_max=y+height;		 //最大Y值
    u16 xianshi_state=0;
    u16 xianshi_hang=0;
    u16 r_code=0;              //返回显示
    if(height>size)          //显示高度需要大于字符高度
    {
        while(*str!=0)//数据未结束
        { 
            if(*str>0x80)       //若是汉字
            { 
                if((x+size)>x_max)//换行
                {	    
                    x=x_start;
                    hang_num++;   //行数加1    
                } 
                //----判断当前行是否需要显示-----------
                if(hang_num>=str_hang_py)  //判断此行是否需要显示
                {

                    //-----根据行计算Y轴显示偏移----------
                    y=y_start+size*(hang_num-str_hang_py); 
                    //判断是否超出显示区域，若超出说明还有未完成显示的字符
                    if((y+size)>y_max)
                    {                    
                        xianshi_state=1;  //显示未完成
                        break;//越界返回
                    }                    
                    switch(size)
                    {
                        case OLED_STRING_12:
                        {
//                            Show_GB2312_Mat(x,y,str,OLED_GB2312_12X12,mode);//写入GB2312字符               //暂不支持                                  
                        }break; 
                        case OLED_STRING_16:
                        {
//                            Show_GB2312_Mat(x,y,str,OLED_GB2312_16X16,mode);//写入GB2312字符                          
                        }break;
                    }  
                    //-----获得当前显示的行--------------
                    xianshi_hang=hang_num;          //在此处获得是为了避开无效的退出行的计入
                } 
                x+=size;//下一个字符偏移 	                
                str+=2; 
            }
            else
            {
                if(*str==13)//判断换行符号
                {         
                    x=x_start;
                    hang_num++;   //行数加1                                
                }
                else        //不是换行符号
                {
                    if((x+size/2)>x_max)//换行
                    {				   
                        x=x_start;
                        hang_num++;   //行数加1                     
                    }	
                }
                if(*str==13)
                {
                    str++;      //得到下一个内码  
                }                
                else
                {                    
                    if(hang_num>=str_hang_py)      //判断此行是否需要显示
                    { 
                        //-----根据行计算Y轴显示偏移----------                        
                        y=y_start+size*(hang_num-str_hang_py); 
                        //判断是否超出显示区域，若超出说明还有未完成显示的字符
                        if((y+size)>y_max)
                        {
                            xianshi_state=1;  //显示未完成                            
                            break;//越界返回
                        }                            
                        switch(size)
                        {
                            case OLED_STRING_12:
                            {
                                FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_12X12,mode);//写入ASCII字符                                                 
                            }break; 
                            case OLED_STRING_16:
                            {
                                FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_16X16,mode);//写入ASCII字符                           
                            }break;
                            case OLED_STRING_24:
                            {
                                FUNC_OLED_Show_ASCII_Mat(x,y+ascii_ypy,str,OLED_ASCII_24X24,mode);//写入ASCII字符                           
                            }break;                               
                        }
                        //-----获得当前显示的行--------------
                        xianshi_hang=hang_num;          //在此处获得是为了避开无效的退出行的计入  
                    }
                    x+=size/2; //字符,为全字的一半                    
                    str++;      //得到下一个内码                 
                }                    
            }					 
        }
    }
    else
    {
        xianshi_state=2;       //显示高度小于字符高度
    }
    //-----合成显示返回数据---------
    r_code=((xianshi_state&0x000f)<<12)+xianshi_hang;
    //-----返回代码--------
    return r_code;
}  		




void FUNC_OLED_Show_time(u16 x, u16 y,unsigned char h,unsigned char m,unsigned char s,u8 size)
{
/*
 *函数名：Show_time
 *描述  ：在指定位置以xx:xx:xx 的格式显示时间
 *输入  ：x:字符的起始位置 x
          y:字符的起始位置 y
          h:小时
          m:分钟
          s:秒
          size: 字符的大小   目前只支持12 16 的字符串显示
 *输出  ：无
 *调用  ：外部调用
*/      
    u8 time_ascii[]="06:07:12";
    if((h<=60)&&(m<=60)&&(s<=60))       //判断需要显示的时间参数是否满足要求
    {
        //-----更新时间-----
        time_ascii[0]=0x30+h/10;     //更新小时十位
        time_ascii[1]=0x30+h%10;     //更新小时个位
        time_ascii[3]=0x30+m/10;     //更新分钟十位
        time_ascii[4]=0x30+m%10;     //更新分钟个位 
        time_ascii[6]=0x30+s/10;     //更新秒钟十位 
        time_ascii[7]=0x30+s%10;     //更新秒钟个位 
        switch(size)
        {
            case OLED_STRING_12:
            {
                FUNC_OLED_Show_Str(x,y,48,12,time_ascii,OLED_STRING_12,0,1);
            }break;
            case OLED_STRING_16:
            {
                FUNC_OLED_Show_Str(x,y,64,16,time_ascii,OLED_STRING_16,0,1);                
            }break;
        }
    }    
}






unsigned char FUNC_OLED_GRAM_REFRESH(void)
{
/*
 *函数名：DISPLAY_OLED_GRAM_REFRESH
 *描述  ：刷新OLED的显示RAM
 *输入  ：刷新显示
 *输出  ：0->更新结束 1->正在更新
 *调用  ：外部调用
*/  
	unsigned char res=0;
//    BSP_SOFT_OLED_REFRESH_GRAM();    
	res=BSP_HARD_OLED_REFRESH_GRAM();  
	return res;
}





void FUNC_OLED_INIT(void)
{
/*
 *函数名：FUNC_OLED_INIT
 *描述  ：OLED显示初始化
 *输入  ：无
 *输出  ：无
 *调用  ：外部调用
*/  

//    BSP_SOFT_OLED_INIT();
	BSP_HARD_OLED_INIT();
    FUNC_OLED_GRAM_INIT();
    FUNC_OLED_GRAM_REFRESH();     //刷新OLED RAM
    
}
    
















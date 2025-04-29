#ifndef __FUNC_S_STRING_PROCESS_H__
#define __FUNC_S_STRING_PROCESS_H__

#include "bsp_stm32f1_mzze.h"





extern unsigned char FUNC_S_SP_GET_MATCH_POS(unsigned char*str1,unsigned char mask,unsigned char str1_size);

extern unsigned char FUNC_S_SP_COMPAR_STR1_STR2(char*str1,char*str2,unsigned char bidui_mode);

extern unsigned char FUNC_S_SP_CUT_OUT_STR(unsigned char*n_str,unsigned char n_str_size,unsigned char*str,unsigned char cut_mask);

extern unsigned char FUNC_S_SP_COPY_STR(unsigned char*n_str,unsigned char n_str_size,unsigned char*str);










#endif



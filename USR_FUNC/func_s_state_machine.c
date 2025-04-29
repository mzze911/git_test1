#include "func_s_state_machine.h"












//--------状态机1相关-------------
void FUNC_S_STATE_MACHINE1_INIT(STRUCT_FUNC_STATE_MACHINE1 *sm1,unsigned char init_state)
{
	sm1->state=init_state;
	sm1->state_m=FUNC_S_SM1_STATE_INVALID;
	sm1->state_l=FUNC_S_SM1_STATE_INVALID;
	sm1->state_n=FUNC_S_SM1_STATE_INVALID;
	sm1->s_step=FUNC_S_SM1_STEP_IN;
	sm1->s_out_num=0;
	
}

void FUNC_S_STATE_MACHINE1_SCHANGE(STRUCT_FUNC_STATE_MACHINE1 *sm1)
{
	sm1->state_l=sm1->state;     //更新上一状态 
	sm1->state=sm1->state_n;     //跳转进入下一状态                      
	sm1->s_out_num=0;	         //清0退出号
}

























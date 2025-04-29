#ifndef __FUNC_S_STATE_MACHINE_H__
#define __FUNC_S_STATE_MACHINE_H__




/*************状态机1相关定义*********/
//---结构体定义-----------------
typedef struct{
	unsigned char state;         //状态，
	unsigned char state_m;       //状态记忆，和主状态的区别，只有执行过该状态的内容后，此变量更新为该状态
	unsigned char state_l;       //上一状态
	unsigned char state_n;       //下一状态

	unsigned char s_step;         //状态步骤
	unsigned char s_out_num;      //状态退出号
}STRUCT_FUNC_STATE_MACHINE1;
//----无意义状态定义------------------
#define FUNC_S_SM1_STATE_INVALID 255  //无效的状态


//----必要状态步骤定义----------------
#define FUNC_S_SM1_STEP_IN   0   //进入状态步骤
#define FUNC_S_SM1_STEP_OUT  255 //退出状态步骤



//---接口函数-------------------------
extern void FUNC_S_STATE_MACHINE1_INIT(STRUCT_FUNC_STATE_MACHINE1 *sm1,unsigned char init_state);   //状态机1初始化
extern void FUNC_S_STATE_MACHINE1_SCHANGE(STRUCT_FUNC_STATE_MACHINE1 *sm1);                         //状态机1状态切换
















#endif




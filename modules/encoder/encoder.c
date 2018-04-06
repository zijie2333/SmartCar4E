#include <project.h>
#include "encoder.h"

static int16 speed_L = 0;
static float linear_velocity_L = 0;
static uint16 num_L = 0;
static int16 speed_R = 0;
static float linear_velocity_R = 0;
static uint16 num_R = 0;
static int8 n = 1;

CY_ISR(InterruptHandler)
{
	//Timer_ClearInterrupt(Timer_INTR_MASK_TC);		//中断标志复位
  Timer_ReadStatusRegister();
	if(n==1) //不要在初始化的时候初始化这个组件，因为会产生中断中调用同时main函数调用从而有warning
	{
	QuadDec_L_Start();
    QuadDec_L_TriggerCommand(QuadDec_L_MASK, QuadDec_L_CMD_RELOAD);
	QuadDec_L_WriteCounter(0);
    QuadDec_R_Start();
    QuadDec_R_TriggerCommand(QuadDec_R_MASK, QuadDec_R_CMD_RELOAD);
    QuadDec_R_WriteCounter(0);
		n = 0;
	}
	num_L = QuadDec_L_ReadCounter()-32768; //每166.67ms从正交解码器的计数中读回数值
	QuadDec_L_WriteCounter(0);//计数器清零
	speed_L = num_L/(1); 	//speed = num*6*60/360
	linear_velocity_L = 0.01*R*speed_L*(2*PI);//单位是 m/min

  num_R = QuadDec_R_ReadCounter()-32768; //每166.67ms从正交解码器的计数中读回数值
  QuadDec_R_WriteCounter(0);//计数器清零
  speed_R = num_R/(1); 	//speed = num*6*60/360
  linear_velocity_R = 0.01*R*speed_R*(2*PI);//单位是 m/min

	PWM_WriteCompare(6000);
}

void encoder_init(){
  CyGlobalIntEnable;//允许全局中断
  isr_StartEx(InterruptHandler);// 初始化中断
  PWM_Start();
  PWM_WriteCompare(4500);
  Timer_Enable();
  Timer_Start();		//最后启动时钟，否则定时中断可能先于正交解码器运作开始而来
}

float encoder_query(ID){
  if(ID==0){
    return linear_velocity_L;
  } else if(ID==1){
    return linear_velocity_R;
  } else { }
}

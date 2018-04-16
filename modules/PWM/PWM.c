#include "PWM.h"
#include <project.h>

// deprecated
void PWM_init(){
    PWM_L_Start();
    PWM_R_Start();

}
// deprecated
void PWM_set(float PWM_left, float PWM_right)
{

    PWM_L_WriteCompare(PWM_left);
    PWM_R_WriteCompare(PWM_right);
}

void motor_init(){
    PWM_L_Start();
    PWM_R_Start();

}
void update_motors(float PWM_left, float PWM_right)
{
    float PWM_L;
    float PWM_R;
    PWM_L = 4600 - PWM_left * (4600 - 3000);
    PWM_R = 4600 + PWM_right * (6200 - 4600);
    PWM_L_WriteCompare(PWM_L);
    PWM_R_WriteCompare(PWM_R);
}
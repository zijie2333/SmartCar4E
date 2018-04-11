#include "PWM.h"
#include <project.h>

void PWM_init(){
    PWM_L_Start();
    PWM_R_Start();

}
void PWM_set(float PWM_left, float PWM_right)
{

    PWM_L_WriteCompare(PWM_left);
    PWM_R_WriteCompare(PWM_right);
}

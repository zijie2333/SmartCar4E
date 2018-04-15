#ifndef _PWM_H_
#define _PWM_H_

void motor_init();
void update_motors(float PWM_left, float PWM_right);

void PWM_init(); // deprecated
void PWM_set(float PWM_left, float PWM_right); // deprecated

#endif

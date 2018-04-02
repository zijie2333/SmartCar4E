#ifndef __PID_H
#define __PID_H

struct PID_params{
float kp;
float ki;
float kd;
float int_e; // integral error
float last_e; // last error
}; 

void PIDinit(float kp, float ki, float kd, PID_params* param);
float PIDupdate(float err, PID_params* param);

#endif

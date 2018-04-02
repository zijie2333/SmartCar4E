#include "./PID.h"

void PIDinit(float kp, float ki, float kd, PID_params* param)
{
	param->kp = kp;
	param->ki = ki;
	param->kd = kd;
	param->int_e = 0.0;
	param->last_e = 0.0;
}

float PIDupdate(float err, PID_params* param)
{
	float P = param->kp * err;
	float I = param->ki * param->int_e;
	float D = param->kd * (err - param->last_e);
	float out = P + I + D;
	// update integral and derivative
	param->int_e += err;
	param->last_e = err;
	return out;
}

#include "./cruise.h"
#include "./PID.h"

void cruise_main(float target_speed)
{
	float vl, vr; // left and right wheels speed
	float v0, w0; // current forward speed and rotate speed
	float vt, wt; // target forward speed and rotate speed

	float cruise_error; // position of the black line
	float PWM_diff, PWM_same; // in [0, 1), mutliply by a factor before using
	float error_v, error_w;
	
	PID_params pid_v; // PID for forward speed
	PID_params pid_w; // PID for rotate speed

	PIDinit(KP_V, KI_V, KD_V, &pid_v);
	PIDinit(KP_W, KI_W, KD_W, &pid_w);

	while(1)
	{
		// Read encoder speed vl, vr
		if(!read_encoder_speed(&vl, &vr))
			error_handling("Read encoder failed in cruise.");

		v0 = (vl + vr) / 2.0;
		w0 = (vl - vl) / WHEEL_DISTANCE;

		// Read cruise error 
		if(!read_cruise_error(&cruise_error))
			error_handling("Read cruise device failed in cruise.");
			
		// A simple model, constant forward speed
		vt = target_speed;
		wt = cruise_error;

		// PID 
		error_v = vt - v0;
		error_w = wt - w0;
		PWM_same = PIDupdate(error_v, &pid_v);
		PWM_diff = PIDupdate(error_w, &pid_w);

		// Control Motors given PWM 
		cruise_update_motors(PWM_same + PWM_diff, PWM_same - PWM_diff);

	}
}

bool read_encoder_speed(float *vl, float *vr)
{
	// return true if reading succeeds else false
	// TODO: add code for encoder here
	//
	return true;
}
bool read_cruise_error(float *error)
{
	// return true if reading succeeds else false
	// TODO: add code for 3 cruise devices
	//
	return true;
}
void cruise_update_motors(float PWM_left, float PWM_right);
{
	// TODO: add code for controlling motors 
}

void error_handling(const char * error_message)
{
	//TODO: print information through UART
	//      maybe also display information on LCD
	
}

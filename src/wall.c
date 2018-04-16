#include <stdbool.h> //support bool type on C
#include "./wall.h"
#include "./PID.h"
//#include "./box_filter.h"
#include "../modules/Sonar/Sonar.h"

/*
	Posc4 walking through mazed by walking along the wall

	float threshold;  to determine whether there is a wall foreward.
*/
void wall(const int left_or_right, const float threshold_side, const float threshold_front, const float target_distance, const float target_speed)
{
	// Posc states
	bool has_front_wall = false;
	bool has_side_wall = false;
	bool collision = false;

	// Detect wall
	float side_wall_error = 0.0;
	float side_wall_dst = 0.0;
	float front_wall_error = 0.0;
	float front_wall_dst = 0.0;

	// PWM and motor speed
	float PWM_diff, PWM_same; // in [0, 1), mutliply by a factor before using
	float PWM_left, PWM_right;
	float error_v, error_w;
	float vl, vr;
	float v0, w0;

	// PIDs
	struct PID_params pid_v; // PID for forward speed
	struct PID_params pid_w; // PID for rotate speed

	PIDinit(KP_V, KI_V, KD_V, &pid_v);
	PIDinit(KP_W, KI_W, KD_W, &pid_w);

	// Box filters
	struct box_filter_params box_filter1;
	box_filter_init(5, &box_filter1);

	struct box_filter_params box_filter2;
	box_filter_init(5, &box_filter2);

	// Global init
	wall_components_init();

	while(1)
	{
		if(!read_collision(&collision)) error_handling("Error while reading collision");
		if(collision)
		{
			error_handling("Collision!");
			open_loop_go_back(5);
		}

		detect_front_wall(&front_wall_dst, threshold_front, &has_front_wall, &box_filter1);
		detect_side_wall(&side_wall_dst, threshold_side, &has_side_wall, left_or_right, &box_filter2);

		// Read encoder speed vl, vr
		if(!read_encoder_speed(&vl, &vr))
			error_handling("Read encoder failed in cruise.");


		if (!has_front_wall && has_side_wall) // follow the wall
		{	
			v0 = (vl + vr) / 2.0;
			w0 = (vl - vr) / WHEEL_DISTANCE; // turning right if w0 > 0

			error_v = target_speed - v0; // should accelerate if error_v > 0
			error_w = (target_distance - side_wall_dst) * left_or_right; // should turn left if error_w > 0

			PWM_same = PIDupdate(error_v, &pid_v);
			PWM_diff = PIDupdate(error_w, &pid_w);

			PWM_left = PWM_same - PWM_diff;
			PWM_right = PWM_same + PWM_diff;

		} else if (!has_front_wall && !has_side_wall) // open loop turn left_or_right
		{
			open_loop_turn_angle(left_or_right); // if following left turn left
		} else if (has_front_wall && has_side_wall) // open loop turn left_or_right
		{
			open_loop_turn_angle(left_or_right);
		} else if (has_front_wall && !has_side_wall) // cannot happen 
		{
			error_handling("Impossible.");
		}
		// Delay some time

	}

	box_filter_release(&box_filter1);
	box_filter_release(&box_filter2);
}


void wall_components_init()
{
	LCD_init();
	PWM_init();
	encoder_init();
    IR_init();
}


bool open_loop_turn_angle(int left_or_right)
{
	/*  By ZK Wang and XX Feng
		TODO: 
			turn 90 degree 
			DO NOT return until open_loop is done
		Input: 
			bool left_or_right;  turn left or turn right
		Output:
			bool success;
	*/
	if(left_or_right == LEFT)
	{
		// Set PWM
		update_motor(0.25, 0.75);
	} else if (left_or_right == RIGHT){
		// Set PWM
		update_motor(0.75, 0.25);
	}
	// hold for some time 
	// Delay Time
	return true;
}

bool read_radar_dst(float *distance, bool left_or_right)
{
	/*  By 
		TODO:
			read radar on the left or right
		Input:
			float *distance;  set to detected distance
			bool left_or_right;  read left or right radar
		Ouput:
			bool success;   return false if some errors occur while reading 
	*/
	return true;
}

bool read_collision(bool *collision)
{
	/* By ZT Liu
	   TODO:
	   		detect collision
	   	Input: 
	   		bool* collision; set to true if collision happened.
	   	Ouput:
	   		bool success;   return false if some errors occur while reading 
	*/
	return true;
}


bool read_front_dst(float * distance)
{
	/* By ZY Wang
	   TODO: 
			read distance provided by sonar
		Input: 
			float* distance;  set value here
		Output:
			bool success; reading succeeded or not
	*/
	*distance = Sonar_query();
	if(*distance==-10086) return false;
	return true;
}

bool detect_side_wall(float *distance, float threshold, bool * has_wall, int left_or_right, struct box_filter_params *box_filter)
{
	float tmp_dst = 0.0;
	if(!read_radar_dst(&tmp_dst, left_or_right))
	{
		error_handling("Error while reading radar");
		return false;
	}
	*distance = box_filter_update(tmp_dst, box_filter);
	*has_wall = *distance < threshold;
	return true;
}

bool detect_front_wall(float *distance, float threshold, bool * has_wall, struct box_filter_params *box_filter)
{
	// Doing box smoothing to avoid errors
	float tmp_dst = 0.0;
	if(!read_front_dst(&tmp_dst))
	{
		error_handling("Error while reading sonar");
		return false;
	}
	*distance = box_filter_update(tmp_dst, box_filter);
	*has_wall = *distance < threshold;

	return true;
}

bool read_encoder_speed(float *vl, float *vr)
{
    *vl = encoder_query(0);
    *vr = -encoder_query(1);

    if (*vl==-10086 || *vr==-10086) {
        return false;
    }
	return true;
}
void update_motor(float PWM_left, float PWM_right)
{
	/* By XX Feng

	*/
}
void error_handling(const char * error_message)
{
    LCD_disp(error_message);
}



void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}

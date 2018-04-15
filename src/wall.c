#include <stdbool.h> //support bool type on C
#include "./wall.h"
#include "./PID.h"
#include "./box_filter.h"

/*
	Posc4 walking through mazed by walking along the wall

	float threshold;  to determine whether there is a wall foreward.
*/
void wall(bool left_or_right, float threshold, float target_speed)
{
	bool has_front_wall = false;
	bool collision = false;
	bool wall_error = 0.0;

	float PWM_diff, PWM_same; // in [0, 1), mutliply by a factor before using
	float error_v, error_w;

	// PIDs
	struct PID_params pid_v; // PID for forward speed
	struct PID_params pid_w; // PID for rotate speed

	PIDinit(KP_V, KI_V, KD_V, &pid_v);
	PIDinit(KP_W, KI_W, KD_W, &pid_w);

	// Box filter
	struct box_filter_params box_filter;
	box_filter_init(5, &box_filter);

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

		detect_front_wall(&has_front_wall);
		read_wall_error()

	}

	box_filter_destroy(&box_filter);

}


void wall_components_init()
{
	LCD_init();
	PWM_init();
	encoder_init();
    IR_init();
}


bool open_loop_turn_angle(bool left_or_right)
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
	} else{
		// Set PWM
	}
	// hold for some time 
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
	return true;
}

bool read_wall_error(float *error, bool left_or_right)
{
	if(!read_radar_dst(error, left_or_right))
	{
		error_handling("Error while reading radar");
		return false;
	}
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

void error_handling(const char * error_message)
{
    LCD_disp(error_message);
}



void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}
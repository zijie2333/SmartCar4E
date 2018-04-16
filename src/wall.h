#ifndef __WALL_H
#define __WALL_H

#define LEFT -1
#define RIGHT 1

#define WHEEL_DISTANCE 10

#define KP_V 4.0
#define KI_V 0.0
#define KD_V 0.0

#define KP_W 400.0
#define KI_W 0.0
#define KD_W 0.0

#include "./box_filter.h"

void wall_components_init();
void wall(const int left_or_right, const float threshold_side, const float threshold_front, const float target_distance, const float target_speed);

// Hardware API
bool open_loop_turn_angle(int left_or_right);
bool read_radar_dst(float *distance, bool left_or_right);
bool read_collision(bool *collision);
bool read_front_dst(float * distance);
bool read_encoder_speed(float *vl, float *vr);
void error_handling(const char * error_message);
void update_motor(float PWM_left, float PWM_right);

// Wall API
bool detect_front_wall(float *distance, float threshold, bool * has_wall, struct box_filter_params *box_filter);
bool detect_side_wall(float *distance, float threshold, bool * has_wall, int left_or_right, struct box_filter_params *box_filter);

// other
void IntToString(char *str, int number);

#endif

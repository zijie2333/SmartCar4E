#ifndef __WALL_H
#define __WALL_H

#define LEFT -1
#define RIGHT 1

#define WHEEL_DISTANCE 10

void wall_components_init();
void wall(bool left_or_right, float threshold, float target_speed);

// Hardware API
bool open_loop_turn_angle(bool left_or_right);
bool read_radar_dst(float *distance, bool left_or_right);
bool read_collision(bool *collision);
bool read_front_dst(float * distance);
bool read_encoder_speed(float *vl, float *vr);
void error_handling(const char * error_message);
void update_motor(float PWM_left, float PWM_right);

// Wall API
bool detect_front_wall(float *distance, float threshold, bool * has_wall);
bool read_wall_error(float *error, bool left_or_right);

// other
void IntToString(char *str, int number);

#endif
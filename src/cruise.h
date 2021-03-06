#ifndef __CRUISE_H
#define __CRUISE_H

#include <stdbool.h> //support bool type on C

#define WHEEL_DISTANCE 5.0

#define KP_V 4.0
#define KI_V 0.0
#define KD_V 0.0

#define KP_W 400.0
#define KI_W 0.0
#define KD_W 0.0

// MAIN for cruise
void cruise_main(float target_speed);

// Read Devices
bool read_encoder_speed(float *vl, float *vr);
bool read_cruise_error(float *error);

// Motors control
void cruise_update_motors(float PWM_left, float PWM_right);

// Error handling
void error_handling(const char * error_message);

// Init components
void components_init();

void test_cruise_error();
void test_encoder();
void IntToString(char *str, int number);



#endif

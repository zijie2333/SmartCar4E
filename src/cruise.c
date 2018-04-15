#include <stdbool.h> //support bool type on C
#include "./cruise.h"
#include "./PID.h"
#include "../modules/LCD/LCD.h"
#include "../modules/encoder/encoder.h"
#include "../modules/IR/IR.h"
#include "../modules/PWM/PWM.h"


int main() {
	//PWM_L_Start();
	//components_init();
	//PWM_L_WriteCompare(5000);
	//PWM_set(4200, 5000);
	cruise_main(200);
	return 0;
}

void cruise_main(float target_speed)
{
	float vl, vr; // left and right wheels speed
	float v0, w0; // current forward speed and rotate speed
	float vt, wt; // target forward speed and rotate speed

	float cruise_error; // position of the black line
	float PWM_diff, PWM_same; // in [0, 1), mutliply by a factor before using
	float error_v, error_w;

	struct PID_params pid_v; // PID for forward speed
	struct PID_params pid_w; // PID for rotate speed

	PIDinit(KP_V, KI_V, KD_V, &pid_v);
	PIDinit(KP_W, KI_W, KD_W, &pid_w);

	components_init();
	PWM_set(4600, 4600);

	while(1)
	{

		// Read encoder speed vl, vr
		if(!read_encoder_speed(&vl, &vr))
			error_handling("Read encoder failed in cruise.");

		v0 = (vl + vr) / 2.0;
		w0 = (vl - vr) / WHEEL_DISTANCE;


		// Read cruise error
		if(!read_cruise_error(&cruise_error)){
			error_handling("Read cruise device failed in cruise.");
			cruise_update_motors(4600, 4600);
			while (!read_cruise_error(&cruise_error)) {
				LCD_Char_ClearDisplay();
				LCD_disp("error: 100860");
			}
		}

		test_cruise_error();
		//test_encoder();

		// A simple model, constant forward speed
		vt = target_speed;
		wt = cruise_error;

		// PID
		error_v = vt - v0;
		error_w = wt - w0;
		PWM_same = PIDupdate(error_v, &pid_v);
		PWM_diff = PIDupdate(error_w, &pid_w);

		// Control Motors given PWM
		cruise_update_motors(4600- (PWM_same + PWM_diff), 4600 + (PWM_same - PWM_diff) );
		CyDelay(50);
	}

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

bool read_cruise_error(float *error)
{
	*error = IR_normal_rst();
    if (*error ==-10086) {
        return false;
    }
	return true;
}

void cruise_update_motors(float PWM_left, float PWM_right)
{
		PWM_set(PWM_left, PWM_right);
}

void error_handling(const char * error_message)
{
    LCD_disp(error_message);
}

void components_init()
{
		LCD_init();
		PWM_init();
		encoder_init();
    IR_init();
}

void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}

void test_cruise_error()
{
	LCD_Char_ClearDisplay();
	int num_int_l = (int)(IR_query(0));
	char str_l[50];
	IntToString(str_l,num_int_l);

	int num_int_m = (int)(IR_query(2));
	char str_m[50];
	IntToString(str_m,num_int_m);

	int num_int_r = (int)(IR_query(1));
	char str_r[50];
	IntToString(str_r,num_int_r);

	int num_int_n = (int)(10*IR_normal_rst());
	char str_n[50];
	IntToString(str_n,num_int_n);

	char str[150] = "x";
	strcat(str, str_l);
	strcat(str, "a");
	strcat(str, str_m);
	strcat(str, "b");
	strcat(str, str_r);
	strcat(str, "c");

	LCD_disp(str);
	LCD_Char_Position(1,0);
	LCD_Char_PrintString(str_n);
}

void test_encoder(){
	LCD_Char_ClearDisplay();
	float vl, vr;
	read_encoder_speed(&vl, &vr);
	char str_vl[50];
	char str_vr[50];
	int int_vl = (int)(vl);
	int int_vr = (int)(vr);
	IntToString(str_vl,int_vl);
	IntToString(str_vr,int_vr);

	char str[150] = "x";
	strcat(str, str_vl);
	strcat(str, "a");
	strcat(str, str_vr);
	strcat(str, "b");
	LCD_disp(str);

}

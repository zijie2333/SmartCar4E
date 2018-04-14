#ifndef ENCODER_H_
#define ENCODER_H_

#include <project.h>
#include <stdio.h>

#define PI 3.14
#define R 5.4	//轮子的半径，根据轮子实际情况调整

CY_ISR(InterruptHandler); //   #define CY_ISR(FuncName)        void FuncName (void)
void encoder_init();

// 0 for left; 1 for right
float encoder_query(int ID);

#endif

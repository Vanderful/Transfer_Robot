#ifndef _Motor_H_
#define _Motor_H_

#include "headfile.h"


void Moto_Init();
void Position_Calculate(float Px,float Py,float Pw,float Ax,float Ay,float Aw);
void Speed_Calculate(float Px,float Py,float Pw,float Ax,float Ay,float Aw);
void Moto_Output(void);
void Pos_Hold(void);

extern Car_Ctr_Struct Position;
extern Wheel_struct Speed_R1, Speed_R2, Speed_R3, Speed_R4;
extern int Duty_MAX, Duty_MIN;
extern char Grasp_flag;
extern double Speed_Kp, Speed_Kd;






























#endif
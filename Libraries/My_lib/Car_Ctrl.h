#ifndef _Car_ctrl_
#define _Car_Ctrl_

#include "headfile.h"

extern Task_Ctr_Strcuct Task;
extern Carry_Obj_Struct Carry;

extern float Pos_Accuracy;

extern char MODE;
extern float Correction_W,Correction_X,Correction_Y;
extern float ANGLEP;
extern float Xp[2],Yp[2];

void Parament_Init(void);
void Task_Init(void);
void Colour_Position_Init(void);

void Servo_Position_Init(void);
void Area_Recognition_Init(void);
void Circle_color_Recongnition_init(void);

void Task_Ctrl(void);
void Task_Switch(void);
void Task_Departure(void);
void Task_Pattern_Recognition(void);
void Task_MH1(void);
void Task_MH2(void);

void Information_Match_Grasp1(void);
void Information_Match_Place1(void);
void Information_Match_Grasp2(void);
void Information_Match_Place2(void);

void PlaceArea_Colour_Rec(Carry_Obj_Struct struct_carry);
void Path_Planer(Carry_Obj_Struct struct_carry);
void Grasping(Carry_Obj_Struct struct_carry);
void Placing(Carry_Obj_Struct struct_carry);

void Scan_QR_Code1(void);
void Scan_QR_Code2(void);
void Colour_Recognition(void);
#endif
#ifndef _MAP_H_
#define _MAP_H_

#include "headfile.h"





void Area_Init(void);
void Area_Material_Init(float x,float y,int dir);
void Area_Process_Init(float x,float y,int dir);
void Area_Final_Init(float x,float y,int dir);
void Last_Correction();
void CYS_Transfer(float X_I,float Y_I,float X_Exp,float Y_Exp);
void CYS_Transfer_Without_Corr(float X_Exp,float Y_Exp);

extern Area_Pos_Struct  Area;
extern float Process_tiny_err[3][2], Final_tiny_err[3][2];
























#endif
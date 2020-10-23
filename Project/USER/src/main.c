#include "headfile.h"


/*
直上直下步进电机供电8V



*/


uint8 TTT;
   int main()
   {
     Init_Finish = CAR_Init();
     Task.Finish = 0;
     
     Task.Pos_X = 3000;
     Task.Pos_Y = 0;
     Task.Pos_Hold = 0;
     while(!Task.Pos_Hold);
     Task.STOP = 1;
//     Led_set(LED1.pin, 1, 255, 255, 255);
     while (1)
     {
//       Task_Ctrl();//任务规划
     }
   }










void RIT_DriverIRQHandler(void)
{
  PIT_FLAG_CLEAR;
  Moto_Output();//电机输出
//  LED_change_color(LED1);
  oled_printf_int32(0,0,(int)Ops9.Pos_X,5);
  oled_printf_int32(0,1,(int)Ops9.Pos_Y,5);
  oled_printf_int32(0,2,(int)Ops9.Angle_Z,5);
//  oled_printf_float(0,0,Ops9.Pos_X,4,3);
//  oled_printf_float(0,1,Ops9.Pos_Y,4,3);
//  oled_printf_float(0,2,Ops9.Angle_Z,4,3);
  
}
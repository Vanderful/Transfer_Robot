#include "Motor.h"



//                                  //                              \\
//                           R1   //                                  \\  R2
//                              //||||||||||||||||||||||||||||||||||||| \\
//                            //  |                                   |   \\
//                                |                   X               |
//                                |               | \                 |
//                                |                \                  |
//                                |                \                  |
//                                |                \                  |
//                                |                *-------> Y        |
//                                |                                   |
//                                |                                   |
//                                |                                   |
//                                |                                   |
//                                |                                   |
//                                |                                   |
//                           \\   |                                   |   //
//                             \\ ||||||||||||||||||||||||||||||||||||| //
//                          R4   \\                                   //  R3
//                                 \\                               //


Car_Ctr_Struct Position;
Wheel_struct Speed_R1, Speed_R2, Speed_R3, Speed_R4;

int Duty_MAX;
int Duty_MIN;
int W1_Duty,W2_Duty,W3_Duty,W4_Duty;

char Grasp_flag;

//�����ʼ��
void Moto_Init()
{
  sct_pwm_init(Motor_R1_PWM, Motor_Freq,0);
  gpio_init(Motor_R1_DIR, GPO, 1, NOPULL);
  
  sct_pwm_init(Motor_R2_PWM, Motor_Freq,0);
  gpio_init(Motor_R2_DIR, GPO, 1, NOPULL);
  
  sct_pwm_init(Motor_R3_PWM, Motor_Freq,0);
  gpio_init(Motor_R3_DIR, GPO, 1, NOPULL);
  
  sct_pwm_init(Motor_R4_PWM, Motor_Freq,0);
  gpio_init(Motor_R4_DIR, GPO, 1, NOPULL);
}

float Exp_V_X, Exp_V_Y, Exp_V_W;
float Cur_V_X, Cur_V_Y, Cur_V_W;
double Speed_Kp, Speed_Kd;
double Last_pos[2], Cur_pos[2], Exp_Speed_R1, Exp_Speed_R2, Exp_Speed_R3, Exp_Speed_R4;
double Cur_Speed_R1, Cur_Speed_R2, Cur_Speed_R3, Cur_Speed_R4;
double Err_Speed_R1[2], Err_Speed_R2[2], Err_Speed_R3[2], Err_Speed_R4[2];
double Dif_Speed_R1, Dif_Speed_R2, Dif_Speed_R3, Dif_Speed_R4;
double Out_Speed_R1, Out_Speed_R2, Out_Speed_R3, Out_Speed_R4;
//�ٶȻ�
void Speed_Calculate(float Px,float Py,float Pw,float Ax,float Ay,float Aw)
{
  //λ�û�PID����
  Position_Calculate(Px, Py, Pw, Ax, Ay, Aw);
  
  Exp_V_X = Position.Out[NEW].x;
  Exp_V_Y = Position.Out[NEW].y;
//  Exp_V_X = 5;
  
  Last_pos[X] = Cur_pos[X];
  Cur_pos[X] = Ax;
  Last_pos[Y] = Cur_pos[Y];
  Cur_pos[Y] = Ay;
  
  Cur_V_X = (Cur_pos[X] - Last_pos[X]) * 200.0f;
  Cur_V_Y = (Cur_pos[Y] - Last_pos[Y]) * 200.0f;
  
  Exp_Speed_R1 = -0.3536f * (Exp_V_X + Exp_V_Y);
  Exp_Speed_R2 =  0.3536f * (Exp_V_X - Exp_V_Y);
  Exp_Speed_R3 =  0.3536f * (Exp_V_X + Exp_V_Y);
  Exp_Speed_R4 = -0.3536f * (Exp_V_X - Exp_V_Y);
  
  Cur_Speed_R1 = -0.3536f * (Cur_V_X + Cur_V_Y);
  Cur_Speed_R2 =  0.3536f * (Cur_V_X - Cur_V_Y);
  Cur_Speed_R3 =  0.3536f * (Cur_V_X + Cur_V_Y);
  Cur_Speed_R4 = -0.3536f * (Cur_V_X - Cur_V_Y);
  
  Err_Speed_R1[OLD] = Err_Speed_R1[NEW];
  Err_Speed_R2[OLD] = Err_Speed_R2[NEW];
  Err_Speed_R3[OLD] = Err_Speed_R3[NEW];
  Err_Speed_R4[OLD] = Err_Speed_R4[NEW];
  
  Err_Speed_R1[NEW] = Exp_Speed_R1 - Cur_Speed_R1;
  Err_Speed_R2[NEW] = Exp_Speed_R2 - Cur_Speed_R2;
  Err_Speed_R3[NEW] = Exp_Speed_R3 - Cur_Speed_R3;
  Err_Speed_R4[NEW] = Exp_Speed_R4 - Cur_Speed_R4;
  
  Dif_Speed_R1 = Err_Speed_R1[NEW] - Err_Speed_R1[OLD];
  Dif_Speed_R2 = Err_Speed_R2[NEW] - Err_Speed_R2[OLD];
  Dif_Speed_R3 = Err_Speed_R3[NEW] - Err_Speed_R3[OLD];
  Dif_Speed_R4 = Err_Speed_R4[NEW] - Err_Speed_R4[OLD];
  
  Out_Speed_R1 += Err_Speed_R1[NEW] * Speed_Kp + Dif_Speed_R1 * Speed_Kd;
  Out_Speed_R2 += Err_Speed_R2[NEW] * Speed_Kp + Dif_Speed_R2 * Speed_Kd;
  Out_Speed_R3 += Err_Speed_R3[NEW] * Speed_Kp + Dif_Speed_R3 * Speed_Kd;
  Out_Speed_R4 += Err_Speed_R4[NEW] * Speed_Kp + Dif_Speed_R4 * Speed_Kd;
  
    if(Task.STOP==1)
  {
    Out_Speed_R1 = 0.0f;
    Out_Speed_R2 = 0.0f;
    Out_Speed_R3 = 0.0f;
    Out_Speed_R4 = 0.0f;
  }
  
  if(Out_Speed_R1 > Duty_MAX)    Out_Speed_R1 = Duty_MAX;
  if(Out_Speed_R1 < Duty_MIN)    Out_Speed_R1 = Duty_MIN;
  
  if(Out_Speed_R2 > Duty_MAX)    Out_Speed_R2 = Duty_MAX;
  if(Out_Speed_R2 < Duty_MIN)    Out_Speed_R2 = Duty_MIN;
  
  if(Out_Speed_R3 > Duty_MAX)    Out_Speed_R3 = Duty_MAX;
  if(Out_Speed_R3 < Duty_MIN)    Out_Speed_R3 = Duty_MIN;
  
  if(Out_Speed_R4 > Duty_MAX)    Out_Speed_R4 = Duty_MAX;
  if(Out_Speed_R4 < Duty_MIN)    Out_Speed_R4 = Duty_MIN;
}

/******************************************************************************/
//�˶�����
/******************************************************************************/
void Position_Calculate(float Px,float Py,float Pw,float Ax,float Ay,float Aw)//λ�ý���PID
{
  ////////////////////////////////////////////////////////////////////////////
  /********************************������************************************/
  ////////////////////////////////////////////////////////////////////////////
  Position.Exp.x=Px;
  Position.Exp.y=Py;
  Position.Exp.w=Pw;
  
  Position.Act.x=Ax;
  Position.Act.y=Ay; 
  Position.Act.w=Aw;
  
  ////////////////////////////////////////////////////////////////////////////
  /********************************������************************************/
  ////////////////////////////////////////////////////////////////////////////
  //X����������
  Position.Err[9].x = Position.Err[8].x;
  Position.Err[8].x = Position.Err[7].x;
  Position.Err[7].x = Position.Err[6].x;
  Position.Err[6].x = Position.Err[5].x;
  Position.Err[5].x = Position.Err[4].x;
  Position.Err[4].x = Position.Err[3].x;
  Position.Err[3].x = Position.Err[PREv].x;
  Position.Err[PREv].x = Position.Err[OLD].x;
  Position.Err[OLD].x = Position.Err[NEW].x;
  Position.Err[NEW].x = Position.Exp.x-Position.Act.x;
  //Y����������
  Position.Err[9].y = Position.Err[8].y;
  Position.Err[8].y = Position.Err[7].y;
  Position.Err[7].y = Position.Err[6].y;
  Position.Err[6].y = Position.Err[5].y;
  Position.Err[5].y = Position.Err[4].y;
  Position.Err[4].y = Position.Err[3].y;
  Position.Err[3].y = Position.Err[PREv].y;
  Position.Err[PREv].y = Position.Err[OLD].y;
  Position.Err[OLD].y = Position.Err[NEW].y;
  Position.Err[NEW].y = Position.Exp.y-Position.Act.y;
  //W����ƫ��
  Position.Err[9].w = Position.Err[8].w;
  Position.Err[8].w = Position.Err[7].w;
  Position.Err[7].w = Position.Err[6].w;
  Position.Err[6].w = Position.Err[5].w;
  Position.Err[5].w = Position.Err[4].w;
  Position.Err[4].w = Position.Err[3].w;
  Position.Err[3].w = Position.Err[PREv].w;
  Position.Err[PREv].w = Position.Err[OLD].w;
  Position.Err[OLD].w = Position.Err[NEW].w;
  Position.Err[NEW].w = Position.Exp.w-Position.Act.w;
  
  ////////////////////////////////////////////////////////////////////////////
  /********************************΢����************************************/
  ////////////////////////////////////////////////////////////////////////////
  //���΢��ֵ
  Position.Dif.x = Position.Err[NEW].x-Position.Err[OLD].x;
  Position.Dif.y = Position.Err[NEW].y-Position.Err[OLD].y;
  Position.Dif.w = Position.Err[NEW].w-Position.Err[OLD].w;
//  Position.Dif.w=-Ops9.Palstance_Z;
  ////////////////////////////////////////////////////////////////////////////
  /********************************������************************************/
  //////////////////////////////////////////////////////////////////////////
  //����������
  Position.Int.x=0.0f;
  Position.Int.y=0.0f;
  Position.Int.w=0.0f;
  
//  //ֻ��ˮƽλ�û��֣�������Ҫ����ǶȻ��֣���ʡ�����л�����
  if(Position.Err[NEW].x<50.0f&&Position.Err[NEW].y<50.0f)
  {
    for(uint8 i=0;i<10;i++)//����ֻ�ۼ����10�����
    {   
      Position.Int.x+=Position.Err[i].x;
      Position.Int.y+=Position.Err[i].y;
    }      
  }
  
  if(my_abs(Position.Err[NEW].w)<2.0f)
  {
    for(uint8 i=0;i<10;i++)//����ֻ�ۼ����10�����
    {
      Position.Int.w+=Position.Err[i].w;
    }
  }
  
  Position.Int.x = (Position.Int.x >  2800) ?  2800:Position.Int.x;
  Position.Int.y = (Position.Int.y >  2800) ?  2800:Position.Int.y;
  Position.Int.w = (Position.Int.x >  2800) ?  2800:Position.Int.w;
  
  Position.Int.x = (Position.Int.x < -2800) ? -2800:Position.Int.x;
  Position.Int.y = (Position.Int.y < -2800) ? -2800:Position.Int.y;
  Position.Int.w = (Position.Int.w < -2800) ? -2800:Position.Int.w;
  
  ////////////////////////////////////////////////////////////////////////////
  /********************************�����************************************/
  ////////////////////////////////////////////////////////////////////////////
  //�����
  //����PID�󣬸�������λ�õõ������ٶ�
  Position.Out[NEW].x=Position.Pid[X].Kp*Position.Err[NEW].x+Position.Pid[X].Ki*Position.Int.x+Position.Pid[X].Kd*Position.Dif.x;
  Position.Out[NEW].y=Position.Pid[Y].Kp*Position.Err[NEW].y+Position.Pid[Y].Ki*Position.Int.y+Position.Pid[Y].Kd*Position.Dif.y;
  Position.Out[NEW].w=Position.Pid[W].Kp*Position.Err[NEW].w+Position.Pid[W].Ki*Position.Int.w+Position.Pid[W].Kd*Position.Dif.w;
}

void Moto_Output()//������
{
  //PID����
  Speed_Calculate(Task.Pos_X, Task.Pos_Y, Task.Pos_W, Ops9.Pos_X, Ops9.Pos_Y, Ops9.Angle_Z);
  //��ת
  W1_Duty = (int)(  Out_Speed_R1 - Position.Out[NEW].w);
  W2_Duty = (int)(  Out_Speed_R2 - Position.Out[NEW].w);
  W3_Duty = (int)(  Out_Speed_R3 - Position.Out[NEW].w);
  W4_Duty = (int)(  Out_Speed_R4 - Position.Out[NEW].w);
  //�޷�
  if(W1_Duty > Duty_MAX)    W1_Duty = Duty_MAX;
  if(W1_Duty < Duty_MIN)    W1_Duty = Duty_MIN;
  
  if(W2_Duty > Duty_MAX)    W2_Duty = Duty_MAX;
  if(W2_Duty < Duty_MIN)    W2_Duty = Duty_MIN;
  
  if(W3_Duty > Duty_MAX)    W3_Duty = Duty_MAX;
  if(W3_Duty < Duty_MIN)    W3_Duty = Duty_MIN;
  
  if(W4_Duty > Duty_MAX)    W4_Duty = Duty_MAX;
  if(W4_Duty < Duty_MIN)    W4_Duty = Duty_MIN;
  //R1
  if(W1_Duty >= 0)
  {
    gpio_set(Motor_R1_DIR,0);//��ʱ��
    sct_pwm_duty(Motor_R1_PWM, W1_Duty);
  }
  else
  {
    gpio_set(Motor_R1_DIR,1);//˳ʱ��
    sct_pwm_duty(Motor_R1_PWM,-W1_Duty);
  }
  //R2
  if(W2_Duty >= 0)
  {
    gpio_set(Motor_R2_DIR,0);
    sct_pwm_duty(Motor_R2_PWM, W2_Duty);
  }
  else
  {
    gpio_set(Motor_R2_DIR,1);
    sct_pwm_duty(Motor_R2_PWM,-W2_Duty);
  }
  //R3
  if(W3_Duty >= 0)
  {
    gpio_set(Motor_R3_DIR,0);
    sct_pwm_duty(Motor_R3_PWM, W3_Duty);
  }
  else
  {
    gpio_set(Motor_R3_DIR,1);
    sct_pwm_duty(Motor_R3_PWM,-W3_Duty);
  }
  //R4
  if(W4_Duty >= 0)
  {
    gpio_set(Motor_R4_DIR,0);
    sct_pwm_duty(Motor_R4_PWM, W4_Duty);
  }
  else
  {
    gpio_set(Motor_R4_DIR,1);
    sct_pwm_duty(Motor_R4_PWM,-W4_Duty);
  }
  Pos_Hold();
}

////////////////////////////////////////////////////////////////////////////////////
//��׼��λ����
void Pos_Hold()
{
  if((my_abs(Ops9.Pos_X-Task.Pos_X)<Pos_Accuracy&&my_abs(Ops9.Pos_Y-Task.Pos_Y)<Pos_Accuracy))
  { 
    //ÿ�� ��ǰ���� �� �������� �Ĳ�ֵС�� ��λ���ȣ���λ��ʱ+5ms
    Task.Acu_Time+=5;
    if((my_abs(Ops9.Pos_X-Task.Pos_X)<Pos_Accuracy&&my_abs(Ops9.Pos_Y-Task.Pos_Y)<Pos_Accuracy))
    {  
      //ץȡ���϶�λ��ʱ����̫��
      if(Grasp_flag ==1)
      {
        if(Task.Acu_Time==200)
        {
          Task.Acu_Time=0;
          Task.Pos_Hold=1; 
        }
      }
      //��λ��ʱ����500ʱͣ��
      else 
      {
        if(Task.Acu_Time==500)
        {
          Task.Acu_Time=0;
          Task.Pos_Hold=1; 
        }
      }
    }            
  }
  else Task.Acu_Time=0;
}


















#ifndef _PARAMETER_H_
#define _PARAMETER_H_

////////////////////////////////////////////////////////////////////////////////////
////WS2812灯带设置
#define WS2812B_LED1 B18
////////////////////////////////////////////////////////////////////////////////////
////从单片机设置
#define Conection_UART             USART_8        //配置从单片机所使用到的串口
#define Conection_UART_TX          UART8_TX_B18   //定义Conection_UART_TX引脚
#define Conection_UART_RX          UART8_RX_B17   //定义Conection_UART_RX引脚
////////////////////////////////////////////////////////////////////////////////////
////舵机控制器设置
#define ServoMotor_COF_UART        USART_1        //配置舵机控制器所使用到的串口
#define ServoMotor_COF_TX          UART1_TX_A10   //定义ServoMotor_COF_TX引脚
#define ServoMotor_COF_RX          UART1_RX_B10   //定义ServoMotor_COF_RX引脚
////////////////////////////////////////////////////////////////////////////////////
////OpenMV设置
#define OpenMV_COF_UART            USART_3        //配置OpenMV所使用到的串口     
#define OpenMV_COF_TX              UART3_TX_A2    //定义OpenMV_COF_TX引脚
#define OpenMV_COF_RX              UART3_RX_A3    //定义OpenMV_COF_RX引脚
////////////////////////////////////////////////////////////////////////////////////
////全平面定位系统设置
#define Ops9_COF_UART              USART_0         //配置Ops9所使用到的串口
#define Ops9_COF_TX                UART0_TX_A25    //定义Ops9_COF_TX引脚
#define Ops9_COF_RX                UART0_RX_A24    //定义Ops9_COF_RX引脚
////////////////////////////////////////////////////////////////////////////////////
////二维码模块设置
#define Barcode_Scanner_COF_UART   USART_2         //配置二维码模块所使用到的串口
#define Barcode_Scanner_COF_TX     UART2_TX_B25    //定义Barcode_Scanner_COF_TX引脚
#define Barcode_Scanner_COF_RX     UART2_RX_B24    //定义Barcode_Scanner_COF_RX引脚
////////////////////////////////////////////////////////////////////////////////////
////显示设置（SPI通信）
#define  SCREEN_Type    0   //0:OLED  
                            //1:TFT
#define  SCREEN_SCL_PIN	  B19    //B9
#define  SCREEN_SDA_PIN	  B7     //B8
#define  SCREEN_RST_PIN	  B4     //B10
#define  SCREEN_DC_PIN	  B6     //B19
#define  SCREEN_CS_PIN	  B5     //B21
////////////////////////////////////////////////////////////////////////////////////
////电机设置
//X轴
#define Motor_X_F_PWM   SCT0_OUT6_B31  //W4,正
#define Motor_X_F_DIR   A28
#define Motor_X_B_PWM   SCT0_OUT2_A19  //W2,反
#define Motor_X_B_DIR   A31
//Y轴
#define Motor_Y_F_PWM   SCT0_OUT8_A29  //W1,正
#define Motor_Y_F_DIR   A30
#define Motor_Y_B_PWM   SCT0_OUT4_B3   //W3,反
#define Motor_Y_B_DIR   A26

#define Motor_R1_DIR    A31
#define Motor_R1_PWM    SCT0_OUT2_A19

#define Motor_R2_DIR    A26
#define Motor_R2_PWM    SCT0_OUT4_B3

#define Motor_R3_DIR    A28
#define Motor_R3_PWM    SCT0_OUT6_B31

#define Motor_R4_DIR    A30
#define Motor_R4_PWM    SCT0_OUT8_A29

#define Motor_Freq 10000
////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
  float Kp;
  float Kd;
  float Ki;
  float Kdamp;
  
}pid_t;

enum
{
  NEW,
  OLD,
  PREv,
};

enum
{
  X,
  Y,
  W,
};

typedef struct
{
  float x;
  float y;
  float w;
}xyz_f_struct;

typedef struct
{
  float W1;
  float W2;
  float W3;
  float W4;
}Wheel_f_struct;

typedef struct {
  uint8 data[8];
  signed char x;
  signed char y;
  float angle_err;
}M_receive;

typedef struct {
  float Exp;
  float Act;
  float Err[10];
  float Dif;
  float Int;
  float Out[2];
  pid_t Pid;
}Wheel_struct;

void get_data();

extern M_receive Receive_data;

////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
  xyz_f_struct Exp;
  xyz_f_struct Act;
  xyz_f_struct Err[10];
  xyz_f_struct Dif;
  xyz_f_struct Int;
  xyz_f_struct Out[2];
  pid_t Pid[3];
}Car_Ctr_Struct;

typedef struct
{
  uint16 ID;//任务ID
            //（任务0；回到出发点；
            //  任务1：识别二维码；
            //  任务2：移动到物料区；
            //  任务3：搬运物块）
  
  int16 Status;//任务总线状态
               //（未进行任务；       -1：
               //  当前有任务正在进行；0；
               //  上次任务已完成：    1）
  
  int16 Flag[4];//子任务状态标志位
                     //未开始：-1；
                     //进行中： 0；
                     //完成：   1；
  
  int16 Enable[4];//子任务使能
                  //使能：1；
                  //禁止：0；
  
  int16 Bingo;//任务校验通过
  int16 ID_MEM[4];//对应任务0，1，2，3；若已完成对应位为1，校验用
  
  uint8 Code1[3];//二维码1
  uint8 Code2[3];//二维码2
  
  uint8 Colour1[6];//颜色1
  uint8 Colour2[6];//颜色2
  uint8 Colour3[6];//颜色3
  
  uint8 Target1[3];//搬运目标1
  uint8 Target2[3];//搬运目标2
  uint8 Target3[3];//搬运目标3
  
  float Pos_X,Pos_Y,Pos_W,Pos_Hold_X,Pos_Hold_Y;
  
  uint8 Start;
  uint8 Finish;
  uint8 Pos_Acu;
  uint8 Pos_Hold;
  uint8 Pos_Check_Flag;
  
  uint8 STOP;
  uint32 Acu_Time;
  uint32 Hold_Time;
  
}Task_Ctr_Strcuct;

typedef struct
{
  uint8 Step;//搬运步骤，总共六步
  
  int16 Step_Flag[6];//-1,0,1;未开始，进行中，完成
  
  uint8 Step_Enable[6];//
}Carry_Obj_Struct;

typedef struct
{
  float X;
  float Y;
}X_Y_Struct;

typedef struct
{
  float W;
  float H;
}W_H_Struct;

typedef struct
{
  
  X_Y_Struct Departure[3];//出发准备区
  X_Y_Struct Recognition;//识别区
  
  X_Y_Struct Color_Recognition1[2];
  X_Y_Struct Color_Recognition2[2];

  X_Y_Struct Material[3];//物料区
  X_Y_Struct Process[3];//加工区（放置）
  X_Y_Struct Process_B[3];//加工区（抓取）
  X_Y_Struct Final[3];//成品区
  
  X_Y_Struct Pos_Check;
  
  X_Y_Struct Home[3];//出发点
  
  X_Y_Struct Original_Point;
}Area_Pos_Struct;

#define _X_ 0
#define _Y_ 1


























#endif
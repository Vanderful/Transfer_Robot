#ifndef _PARAMETER_H_
#define _PARAMETER_H_

////////////////////////////////////////////////////////////////////////////////////
////WS2812�ƴ�����
#define WS2812B_LED1 B18
////////////////////////////////////////////////////////////////////////////////////
////�ӵ�Ƭ������
#define Conection_UART             USART_8        //���ôӵ�Ƭ����ʹ�õ��Ĵ���
#define Conection_UART_TX          UART8_TX_B18   //����Conection_UART_TX����
#define Conection_UART_RX          UART8_RX_B17   //����Conection_UART_RX����
////////////////////////////////////////////////////////////////////////////////////
////�������������
#define ServoMotor_COF_UART        USART_1        //���ö����������ʹ�õ��Ĵ���
#define ServoMotor_COF_TX          UART1_TX_A10   //����ServoMotor_COF_TX����
#define ServoMotor_COF_RX          UART1_RX_B10   //����ServoMotor_COF_RX����
////////////////////////////////////////////////////////////////////////////////////
////OpenMV����
#define OpenMV_COF_UART            USART_3        //����OpenMV��ʹ�õ��Ĵ���     
#define OpenMV_COF_TX              UART3_TX_A2    //����OpenMV_COF_TX����
#define OpenMV_COF_RX              UART3_RX_A3    //����OpenMV_COF_RX����
////////////////////////////////////////////////////////////////////////////////////
////ȫƽ�涨λϵͳ����
#define Ops9_COF_UART              USART_0         //����Ops9��ʹ�õ��Ĵ���
#define Ops9_COF_TX                UART0_TX_A25    //����Ops9_COF_TX����
#define Ops9_COF_RX                UART0_RX_A24    //����Ops9_COF_RX����
////////////////////////////////////////////////////////////////////////////////////
////��ά��ģ������
#define Barcode_Scanner_COF_UART   USART_2         //���ö�ά��ģ����ʹ�õ��Ĵ���
#define Barcode_Scanner_COF_TX     UART2_TX_B25    //����Barcode_Scanner_COF_TX����
#define Barcode_Scanner_COF_RX     UART2_RX_B24    //����Barcode_Scanner_COF_RX����
////////////////////////////////////////////////////////////////////////////////////
////��ʾ���ã�SPIͨ�ţ�
#define  SCREEN_Type    0   //0:OLED  
                            //1:TFT
#define  SCREEN_SCL_PIN	  B19    //B9
#define  SCREEN_SDA_PIN	  B7     //B8
#define  SCREEN_RST_PIN	  B4     //B10
#define  SCREEN_DC_PIN	  B6     //B19
#define  SCREEN_CS_PIN	  B5     //B21
////////////////////////////////////////////////////////////////////////////////////
////�������
//X��
#define Motor_X_F_PWM   SCT0_OUT6_B31  //W4,��
#define Motor_X_F_DIR   A28
#define Motor_X_B_PWM   SCT0_OUT2_A19  //W2,��
#define Motor_X_B_DIR   A31
//Y��
#define Motor_Y_F_PWM   SCT0_OUT8_A29  //W1,��
#define Motor_Y_F_DIR   A30
#define Motor_Y_B_PWM   SCT0_OUT4_B3   //W3,��
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
  uint16 ID;//����ID
            //������0���ص������㣻
            //  ����1��ʶ���ά�룻
            //  ����2���ƶ�����������
            //  ����3��������飩
  
  int16 Status;//��������״̬
               //��δ��������       -1��
               //  ��ǰ���������ڽ��У�0��
               //  �ϴ���������ɣ�    1��
  
  int16 Flag[4];//������״̬��־λ
                     //δ��ʼ��-1��
                     //�����У� 0��
                     //��ɣ�   1��
  
  int16 Enable[4];//������ʹ��
                  //ʹ�ܣ�1��
                  //��ֹ��0��
  
  int16 Bingo;//����У��ͨ��
  int16 ID_MEM[4];//��Ӧ����0��1��2��3��������ɶ�ӦλΪ1��У����
  
  uint8 Code1[3];//��ά��1
  uint8 Code2[3];//��ά��2
  
  uint8 Colour1[6];//��ɫ1
  uint8 Colour2[6];//��ɫ2
  uint8 Colour3[6];//��ɫ3
  
  uint8 Target1[3];//����Ŀ��1
  uint8 Target2[3];//����Ŀ��2
  uint8 Target3[3];//����Ŀ��3
  
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
  uint8 Step;//���˲��裬�ܹ�����
  
  int16 Step_Flag[6];//-1,0,1;δ��ʼ�������У����
  
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
  
  X_Y_Struct Departure[3];//����׼����
  X_Y_Struct Recognition;//ʶ����
  
  X_Y_Struct Color_Recognition1[2];
  X_Y_Struct Color_Recognition2[2];

  X_Y_Struct Material[3];//������
  X_Y_Struct Process[3];//�ӹ��������ã�
  X_Y_Struct Process_B[3];//�ӹ�����ץȡ��
  X_Y_Struct Final[3];//��Ʒ��
  
  X_Y_Struct Pos_Check;
  
  X_Y_Struct Home[3];//������
  
  X_Y_Struct Original_Point;
}Area_Pos_Struct;

#define _X_ 0
#define _Y_ 1


























#endif
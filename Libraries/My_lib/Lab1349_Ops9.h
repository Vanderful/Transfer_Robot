#ifndef _OPS9_
#define _OPS9_

#include "headfile.h"

typedef struct
{
   float Pos_X;
   float Pos_Y;
   
   float Angle_X;
   float Angle_Y;
   float Angle_Z;
   
   float Palstance_Z;
   
   char  receiveComplete;
   uint8  Ops9_rec[28];
   uint8  Ops9_recnum;
   
}Ops_Struct;

static union
    {
        uint8 data[12];
        float ActVal[3];
    }Ops_Command;


extern Ops_Struct Ops9;


//#define Ops9_COF_UART        USART_0         //��������ͷ��ʹ�õ��Ĵ���     
//#define Ops9_COF_TX          UART0_TX_A25    //����IMU_9250_WIT_TX����  ���������Ϊ����IO
//#define Ops9_COF_RX          UART0_RX_A24    //����IMU_9250_WIT_RX����  ���������Ϊ����IO

void Ops9_uart_init(void);
void Ops9_uart_interrupt(void);
void Ops9_Command(char data);


#endif
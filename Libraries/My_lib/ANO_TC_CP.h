#ifndef _ANO_TC_CP_
#define _ANO_TC_CP_

#include "headfile.h"

#define ANO_DT_USE_NRF2401
//#define ANO_DT_USE_USART0

//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       (*((char *)(&dwTemp)))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp)+1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp)+2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp)+3))

extern uint8 send_buff[32];//发送数据缓存

void AON_TC_CP_Initial(void);
void STATUS_SendDate(int16 roll,int16 pitch,int16 yaw);
void MPU_SendDate(int16 accx,int16 accy,int16 accz,int16 gyrox,int16 gyroy,int16 gyroz,int16 magx,int16 magy,int16 magz);
void NRF2401_SenDate(uint8 *p,uint8 cnt);
void Comunication_Type(uint8 *dataToSend , uint8 length);




#endif
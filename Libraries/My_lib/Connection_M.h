#ifndef _Connection_M_
#define _Connection_M_

#include "headfile.h"

typedef struct{
  int AX,BX,CX,DX;
  uint8 Connection_Rec[20];
  uint8 Connection_Recnum;
  char receiveComplete;
}Connection_Struct;

extern Connection_Struct Connection_Data;
extern int DATAx,DATAy;
extern float DATAw,DATAw1;



void Get_S_Info_Init();
void Connection_interrupt();










#endif

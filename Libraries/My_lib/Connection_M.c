#include "Connection_M.h"


//#define Conection_UART  USART_8
//#define Conection_UART_TX  UART8_TX_B18
//#define Conection_UART_RX  UART8_RX_B17

#define L_AC  318
#define L_BD  258

Connection_Struct Connection_Data = {0}; 
int DATAx,DATAy;
float DATAw,DATAw1;

void Get_S_Info_Init()
{
  uart_init(Conection_UART,115200,Conection_UART_TX,Conection_UART_RX);
  uart_rx_irq(Conection_UART,1); 
}

void FLEXCOMM8_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART8_FIFO_FLAG;
    DisableInterrupts;
    
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
        Connection_interrupt();
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        
        USART8->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
        USART8->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
    }
    EnableInterrupts;
}

void Connection_interrupt()
{
  uart_query(Conection_UART,&Connection_Data.Connection_Rec[Connection_Data.Connection_Recnum]);
  if(Connection_Data.Connection_Rec[0] != 0x41) //字符A
   { 	Connection_Data.Connection_Recnum = 0;  }
  else if(Connection_Data.Connection_Recnum == 15  && Connection_Data.Connection_Rec[4]== 0x42) //字符B
   {
     Connection_Data.Connection_Recnum = 0; 
     
     if(Connection_Data.Connection_Rec[1]== '-')
       Connection_Data.AX = -(Connection_Data.Connection_Rec[2] * 10 + Connection_Data.Connection_Rec[3]);
     else Connection_Data.AX = (Connection_Data.Connection_Rec[2] * 10 + Connection_Data.Connection_Rec[3]);
     
     if(Connection_Data.Connection_Rec[5]== '-')
       Connection_Data.BX = -(Connection_Data.Connection_Rec[6] * 10 + Connection_Data.Connection_Rec[7]);
     else Connection_Data.BX = (Connection_Data.Connection_Rec[6] * 10 + Connection_Data.Connection_Rec[7]);
     
     if(Connection_Data.Connection_Rec[9]== '-')
       Connection_Data.CX = -(Connection_Data.Connection_Rec[10] * 10 + Connection_Data.Connection_Rec[11]);
     else Connection_Data.CX = (Connection_Data.Connection_Rec[10] * 10 + Connection_Data.Connection_Rec[11]);
     
     if(Connection_Data.Connection_Rec[13]== '-')
       Connection_Data.DX = -(Connection_Data.Connection_Rec[14] * 10 + Connection_Data.Connection_Rec[15]);
     else Connection_Data.DX = (Connection_Data.Connection_Rec[14] * 10 + Connection_Data.Connection_Rec[15]);
     
     Connection_Data.receiveComplete = 1;
     DATAx = (int)((Connection_Data.AX+Connection_Data.CX)/2);
     DATAy = (int)((Connection_Data.BX+Connection_Data.DX)/2);
     DATAw = -(asin((Connection_Data.AX-Connection_Data.CX)/(float)L_AC)*180.0/3.1415926);
     DATAw1 = (asin((Connection_Data.BX-Connection_Data.DX)/(float)L_BD)*180.0/3.1415926);
   }
     else 
   {  Connection_Data.Connection_Recnum++;    }
}



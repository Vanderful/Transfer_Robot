//#include "common.h"
#include "ANO_TC_CP.h"
//#include "SEEKFREE_NRF24L01.h"
//#include "LPC546XX_uart.h"



uint8 send_buff[32];//发送数据缓存

void AON_TC_CP_Initial()
{
  #ifdef ANO_DT_USE_NRF2401
  nrf_init();
#endif
#ifdef ANO_DT_USE_USART0
  uart_init(USART_0, 115200, UART0_TX_A25, UART0_RX_A24);
#endif
}
void STATUS_SendDate(int16 roll,int16 pitch,int16 yaw)
{
  
  uint8 i,cnt=0;
  
  send_buff[cnt++]=0XAA;//0xAA为帧头
  send_buff[cnt++]=0X05;//0x05为数据发送源本,可以随意更改
  send_buff[cnt++]=0XAF;//0xAF为数据目的地，AF表示上位机
  send_buff[cnt++]=0X01;//0xF1，表示本帧为F1用户自定义帧，对应高级收码的F1功能帧；0X01表示上传姿态数据
  send_buff[cnt++]=0;   //本字节表示数据长度
  
  send_buff[cnt++]=BYTE1(roll);
  send_buff[cnt++]=BYTE0(roll);
  
  send_buff[cnt++]=BYTE1(pitch);
  send_buff[cnt++]=BYTE0(pitch);
  
  send_buff[cnt++]=BYTE1(yaw);
  send_buff[cnt++]=BYTE0(yaw);
  
  send_buff[4] = cnt-5;                          //cnt用来计算数据长度，减5为减去帧开头5个非数据字节
  
  uint8 sum=0;                                  
  for(i=0;i<cnt;i++)    sum+=send_buff[i];      //计算sum校验字节，从0xAA也就是首字节，一直到sum字节前一字节
  
  send_buff[cnt++]=sum;   //将sum校验数据放置最后一字节
  
  //发送方式
  Comunication_Type(send_buff, cnt);
  //uart_putbuff(USART_0,send_buff,cnt);          //调用数据发送函数
  //NRF2401_SenDate(send_buff,cnt);
}

void MPU_SendDate(int16 accx,int16 accy,int16 accz,int16 gyrox,int16 gyroy,int16 gyroz,int16 magx,int16 magy,int16 magz)
{
  
  uint8 i,cnt=0;
  
  send_buff[cnt++]=0XAA;//0xAA为帧头
  send_buff[cnt++]=0X05;//0x05为数据发送源本,可以随意更改
  send_buff[cnt++]=0XAF;//0xAF为数据目的地，AF表示上位机
  send_buff[cnt++]=0X02;//0xF1，表示本帧为F1用户自定义帧，对应高级收码的F1功能帧
  send_buff[cnt++]=0;   //本字节表示数据长度
  
  send_buff[cnt++]=BYTE1(accx);
  send_buff[cnt++]=BYTE0(accx);
  
  send_buff[cnt++]=BYTE1(accy);
  send_buff[cnt++]=BYTE0(accy);
  
  send_buff[cnt++]=BYTE1(accz);
  send_buff[cnt++]=BYTE0(accz);
  
  send_buff[cnt++]=BYTE1(gyrox);
  send_buff[cnt++]=BYTE0(gyrox);
  
  send_buff[cnt++]=BYTE1(gyroy);
  send_buff[cnt++]=BYTE0(gyroy);
  
  send_buff[cnt++]=BYTE1(gyroz);
  send_buff[cnt++]=BYTE0(gyroz);
  
  send_buff[cnt++]=BYTE1(magx);
  send_buff[cnt++]=BYTE0(magx);
  
  send_buff[cnt++]=BYTE1(magy);
  send_buff[cnt++]=BYTE0(magy);
  
  send_buff[cnt++]=BYTE1(magz);
  send_buff[cnt++]=BYTE0(magz);
  
  send_buff[4] = cnt-5;                          //cnt用来计算数据长度，减5为减去帧开头5个非数据字节
  
  uint8 sum=0;                                  
  for(i=0;i<cnt;i++)    sum+=send_buff[i];      //计算sum校验字节，从0xAA也就是首字节，一直到sum字节前一字节
  
  send_buff[cnt++]=sum;   //将sum校验数据放置最后一字节
  
  //发送方式
  Comunication_Type(send_buff, cnt);
  
  
  //uart_putbuff(USART_0,send_buff,cnt);          //调用数据发送函数
  //NRF2401_SenDate(send_buff,cnt);
}


void NRF2401_SenDate(uint8 *date,uint8 cnt)//数据地址，数据长度
{
  nrf_tx_buff[0]=cnt;
  for(uint8 i=0;i<cnt;i++)
  {
    nrf_tx_buff[i+1]=date[i];
  }
  nrf_send_packet(nrf_tx_buff);
}

void Comunication_Type(uint8 *DataToSend , uint8 length)
{
#ifdef ANO_DT_USE_NRF2401
  NRF2401_SenDate(DataToSend,length);
#endif
#ifdef ANO_DT_USE_USART0
    uart_putbuff(USART_0,DataToSend,length); 
#endif
}
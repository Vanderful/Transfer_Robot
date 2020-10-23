/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,上海工程技术大学 工程实训中心 1349实验室
 * All rights reserved.
 * 技术讨论QQ群：320746302  实训智能车队报名群
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留 上海工程技术大学 实训智能车队 的版权声明。
 *
 * @file       		TFmini Plus
 * @company	   		上海工程技术大学 工程实训中心 1349实验室
 * @author     		实训智能车(QQ320746302)
 * @version    		
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100                      
 * @Taobao   		https://item.taobao.com/item.htm?_u=btl46298f3&id=570692840004   微雪电子官方旗舰店
                        www.waveshare.net/wiki/Barcode_Scanner_Module                 微雪百科
 * @date       		2019-04-11
 * @note		
					接线定义：
					------------------------------------ 
		      模块引脚		            单片机引脚
                 PIN-1 Vcc   cable(+5V)	+5V
                 PIN-2 TXD                        UART6_RX_B13
                 PIN-3 RXD                        UART6_TX_A22 
                 PIN-4 GND            	          GND               

					------------------------------------ 
程序参考网址：
 ********************************************************************************************************************/
#include "Lab1349_Barcode_Scanner.h"

void  Barcode_Scanner_uart_interrupt(void);

static unsigned char Command[9];
unsigned char tempCRCarray[5];
unsigned int tempcrc = 0;
BarcodeQRCode getQRCode;
/*const char8 font8x5[ 0x60 ][ 5 ] =  只要看ascii码就可以
{
    {0x00,0x00,0x00,0x00,0x00},     // ASCII -  32 space
    {0x00,0x00,0xF9,0x00,0x00},     // ASCII -  33 !
    {0x00,0xE0,0x00,0xE0,0x00},     // ASCII -  34 "
    {0x24,0x7E,0x24,0x7E,0x24},     // ASCII -  35 #
    {0x34,0x4A,0xFF,0x49,0x26},     // ASCII -  36 $
    {0x22,0x04,0x08,0x10,0x22},     // ASCII -  37 %
    {0x26,0x59,0x4D,0x52,0x25},     // ASCII -  38 &
    {0x00,0x00,0xE0,0x00,0x00},     // ASCII -  39 '
    {0x00,0x3C,0x42,0x81,0x00},     // ASCII -  40 (
    {0x00,0x81,0x42,0x3C,0x00},     // ASCII -  41 )
    {0x28,0x30,0xE0,0x30,0x28},     // ASCII -  42 *
    {0x08,0x08,0x3E,0x08,0x08},     // ASCII -  43 +
    {0x00,0x01,0x02,0x00,0x00},     // ASCII -  44 ,
    {0x08,0x08,0x08,0x08,0x08},     // ASCII -  45 -
    {0x00,0x00,0x01,0x00,0x00},     // ASCII -  46 .
    {0x02,0x04,0x08,0x10,0x20},     // ASCII -  47 /
    {0x7E,0x81,0x81,0x81,0x7E},     // ASCII -  48 0
    {0x00,0x21,0xFF,0x01,0x00},     // ASCII -  49 1
    {0x41,0x83,0x85,0x89,0x71},     // ASCII -  50 2
    {0x42,0x91,0x91,0x91,0x6E},     // ASCII -  51 3
    {0xF0,0x10,0x10,0x10,0xFF},     // ASCII -  52 4
    {0xF2,0x91,0x91,0x91,0x8E},     // ASCII -  53 5
    {0x3E,0x51,0x91,0x91,0x8E},     // ASCII -  54 6
    {0x87,0x88,0x90,0xA0,0xC0},     // ASCII -  55 7
    {0x76,0x89,0x89,0x89,0x76},     // ASCII -  56 8
    {0x62,0x91,0x91,0x91,0x7e},     // ASCII -  57 9
    {0x00,0x00,0x24,0x00,0x00},     // ASCII -  58 :
    {0x00,0x01,0x12,0x00,0x00},     // ASCII -  59 ;
    {0x00,0x08,0x14,0x22,0x41},     // ASCII -  60 <
    {0x14,0x14,0x14,0x14,0x14},     // ASCII -  61 =
    {0x00,0x41,0x22,0x14,0x08},     // ASCII -  62 >
    {0x40,0x80,0x8D,0x90,0x60},     // ASCII -  63 ?
    {0x7E,0x81,0xBD,0xA5,0x78},     // ASCII -  64 @
    {0x3F,0x48,0x88,0x48,0x3F},     // ASCII -  65 A
    {0xFF,0x91,0x91,0x99,0x66},     // ASCII -  66 B
    {0x3C,0x42,0x81,0x81,0x42},     // ASCII -  67 C
    {0xFF,0x81,0x81,0x42,0x3C},     // ASCII -  68 D
    {0xFF,0x91,0x91,0x91,0x81},     // ASCII -  69 E
    {0xFF,0x90,0x90,0x90,0x80},     // ASCII -  70 F
    {0X3E,0x41,0x8F,0x88,0x4F},     // ASCII -  71 G
    {0xFF,0x10,0x10,0x10,0xFF},     // ASCII -  72 H
    {0x00,0x81,0xFF,0x81,0x00},     // ASCII -  73 I
    {0x06,0x01,0x81,0xFE,0x80},     // ASCII -  74 J
    {0xFF,0x18,0x24,0x42,0x81},     // ASCII -  75 K
    {0xFF,0x01,0x01,0x01,0x01},     // ASCII -  76 L
    {0xFF,0x40,0x30,0x40,0xFF},     // ASCII -  77 M
    {0xFF,0x40,0x20,0x10,0xFF},     // ASCII -  78 N
    {0x7E,0x81,0x81,0x81,0x7E},     // ASCII -  79 O
    {0xFF,0x90,0x90,0x90,0x60},     // ASCII -  80 P
    {0x7E,0x81,0x85,0x82,0x7D},     // ASCII -  81 Q
    {0xFF,0x98,0x94,0x92,0x61},     // ASCII -  82 R
    {0x72,0x89,0x89,0x89,0x46},     // ASCII -  83 S
    {0x80,0x80,0xFF,0x80,0x80},     // ASCII -  84 T
    {0xFE,0x01,0x01,0x01,0xFE},     // ASCII -  85 U
    {0xFC,0x02,0x01,0x02,0xFC},     // ASCII -  86 V
    {0xFF,0x02,0x1C,0x02,0xFF},     // ASCII -  87 W
    {0xC3,0x24,0x18,0x24,0xC3},     // ASCII -  88 X
    {0xC0,0x20,0x1F,0x20,0xC0},     // ASCII -  89 Y
    {0x87,0x89,0x91,0xA1,0xC1},     // ASCII -  90 Z
    {0x00,0xFF,0x81,0x81,0x00},     // ASCII -  91 [
    {0x20,0x10,0x08,0x04,0x02},     // ASCII -  92 '\'
    {0x00,0x81,0x81,0xFF,0x00},     // ASCII -  93 ]
    {0x20,0x40,0x80,0x40,0x20},     // ASCII -  94 ^
    {0x01,0x01,0x01,0x01,0x01},     // ASCII -  95 _
    {0x00,0x80,0x40,0x20,0x00},     // ASCII -  96 `
    {0x26,0x29,0x29,0x1F,0x01},     // ASCII -  97 a
    {0xFF,0x11,0x11,0x11,0x0E},     // ASCII -  98 b
    {0x0E,0x11,0x11,0x11,0x11},     // ASCII -  99 c
    {0x0E,0x11,0x11,0x11,0xFF},     // ASCII - 100 d
    {0x0E,0x15,0x15,0x15,0x0D},     // ASCII - 101 e
    {0x10,0x10,0x7F,0x90,0x90},     // ASCII - 102 f
    {0x08,0x15,0x15,0x15,0x0E},     // ASCII - 103 g
    {0xFF,0x08,0x08,0x08,0x07},     // ASCII - 104 h
    {0x00,0x00,0x9F,0x00,0x00},     // ASCII - 105 i
    {0x02,0x01,0x01,0x9F,0x00},     // ASCII - 106 j
    {0xFF,0x04,0x0A,0x11,0x00},     // ASCII - 107 k
    {0x00,0x01,0xFF,0x01,0x00},     // ASCII - 108 l
    {0x1F,0x10,0x0F,0x10,0x0F},     // ASCII - 109 m
    {0x10,0x0F,0x10,0x10,0x0F},     // ASCII - 110 n
    {0x0E,0x11,0x11,0x11,0x0E},     // ASCII - 111 o
    {0x1F,0x14,0x14,0x14,0x08},     // ASCII - 112 p
    {0x08,0x14,0x14,0x14,0x1F},     // ASCII - 113 q
    {0x1F,0x08,0x10,0x10,0x08},     // ASCII - 114 r
    {0x09,0x15,0x15,0x15,0x12},     // ASCII - 115 s
    {0x10,0x10,0x7F,0x11,0x12},     // ASCII - 116 t
    {0x1F,0x01,0x01,0x1F,0x01},     // ASCII - 117 u
    {0x1C,0x02,0x01,0x02,0x1C},     // ASCII - 118 v
    {0x1E,0x01,0x0F,0x01,0x1E},     // ASCII - 119 w
    {0x11,0x0A,0x04,0x0A,0x11},     // ASCII - 120 x
    {0x11,0x0A,0x04,0x08,0x10},     // ASCII - 121 y
    {0x11,0x13,0x15,0x19,0x11},     // ASCII - 122 z
    {0x18,0x66,0x81,0x81,0x00},     // ASCII - 123 {
    {0x00,0x00,0xFF,0x00,0x00},     // ASCII - 124 |
    {0x00,0x81,0x81,0x66,0x18},     // ASCII - 125 }
    {0x0C,0x10,0x08,0x04,0x18},     // ASCII - 126 ~
};*/
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Barcode_uart_init串口初始化函数 8，N，1，9600
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:            串口USART_6，接收中断使能
//-------------------------------------------------------------------------------------------------------------------
void Barcode_uart_init(void)
{
    uart_init(Barcode_Scanner_COF_UART,9600,Barcode_Scanner_COF_TX,Barcode_Scanner_COF_RX);
    uart_rx_irq(Barcode_Scanner_COF_UART,1);                               // 打开串口0接收中断
}


//CRC_CCITT 校验值（2 bytes）算法
unsigned int crc_cal_by_bit(unsigned char* ptr, unsigned int len)
{
  unsigned int crc = 0;
  while(len-- != 0)
  {
    for(unsigned char i = 0x80; i != 0; i /= 2)
    {
      crc *= 2;
      if((crc&0x10000) !=0)    //上一位 CRC 乘 2 后，若首位是 1，则除以 0x11021
      crc ^= 0x11021;
      if((*ptr&i) != 0)        //如果本位是 1，那么 CRC = 上一位的 CRC + 本位/CRC_CCITT
      crc ^= 0x1021;
    }
  ptr++;
  }
  return crc;
}

//基本功能设置（写），寄存器地址0x0000
void Barcode_Common_Setting(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = (Addr_Functions >> 8) & 0xFF;
  Command[5] = (Addr_Functions << 8) & 0xFF;
  Command[6] = LED_Indicator_En + Buz_Indicator_En + Focus_Com + Light_Com + Command_Mode;
//不用CRC_CCITT校验
  Command[7] = 0xAB;
  Command[8] = 0xCD;
//使用CRC_CCITT校验，高低位已经验证 
//  for(int i=0;i<5;i++)    tempCRCarray[i]=Command[i+2];
//  tempcrc=crc_cal_by_bit();
//  Command[7] = tempcrc>>8;
//  Command[8] = tempcrc;  
    uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); //串口6，若更改一起修改
}

//基本功能设置（写），寄存器地址0x000D，Bit1-0 00：串口输出 01：USB PC 键盘 10：保留 11：USB 虚拟串口（保留）
void Barcode_Set_Interface(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = (Addr_OutputMode >> 8) & 0xFF;
  Command[5] = ((Addr_OutputMode << 8) >> 8) & 0xFF;
  Command[6] = UART_Output;
//不用CRC_CCITT校验
  Command[7] = 0xAB;
  Command[8] = 0xCD;
//使用CRC_CCITT校验，高低位已经验证
//  for(int i=0;i<5;i++)    tempCRCarray[i]=Command[i+2];
//  tempcrc=crc_cal_by_bit();
//  Command[7] = tempcrc>>8;
//  Command[8] = tempcrc;  
  uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); 
}

//基本功能设置（写），寄存器地址0x0005
void Barcode_Scan_Interval_Setting(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = (Addr_IntervalSetting >> 8) & 0xFF;
  Command[5] = ((Addr_OutputMode << 8) >> 8) & 0xFF;
  Command[6] = 0xFA;//Max:25.5s, FA=25s., 64=10s
//不用CRC_CCITT校验
  Command[7] = 0xAB;
  Command[8] = 0xCD;
//使用CRC_CCITT校验，高低位已经验证 
//  for(int i=0;i<5;i++)    tempCRCarray[i]=Command[i+2];
//  tempcrc=crc_cal_by_bit();
//  Command[7] = tempcrc>>8;
//  Command[8] = tempcrc;  
    uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); 
}

//基本功能设置（写），保存设置
void Barcode_SaveEEPROM(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_SaveEEPROM;
  Command[3] = 0x01;
  Command[4] = 0x00;
  Command[5] = 0x00;
  Command[6] = 0x00;//Max:25.5s, FA=25s., 64=10s
//不用CRC_CCITT校验
//  Command[7] = 0xAB;
//  Command[8] = 0xCD;
//使用CRC_CCITT校验，高低位已经验证 
  for(int i=0;i<5;i++)    tempCRCarray[i]=Command[i+2];
  tempcrc=crc_cal_by_bit(tempCRCarray,5);
  Command[7] = tempcrc>>8;
  Command[8] = tempcrc;  
  uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); 
}


//基本功能设置（读），寄存器地址0x002A 0x002B，查询波特率
void Barcode_Read_Baud(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_Read;
  Command[3] = 0x01;
  Command[4] = 0x00;
  Command[5] = 0x2a;
  Command[6] = 0x02;//Max:25.5s, FA=25s., 64=10s
//不用CRC_CCITT校验
//  Command[7] = 0xAB;
//  Command[8] = 0xCD;
//使用CRC_CCITT校验，高低位已经验证 
  for(int i=0;i<5;i++)    tempCRCarray[i]=Command[i+2];
  tempcrc=crc_cal_by_bit(tempCRCarray,5);
  Command[7] = tempcrc>>8;
  Command[8] = tempcrc;  
    uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); 
}  
  
/*
注：在命令触发模式下，触发扫描的串口指令为：7E 00 08 01 00 02 01 AB CD；识读模
块收到触发指令后，会先输出七个字节的回应信息并同步启动扫描（回应信息内容：02 00 00
01 00 33 31）
*/
void Barcode_Scan_Command(void)
{
  Command[0] = Command_Head;
  Command[1] = 0x00;
  Command[2] = Command_Write;
  Command[3] = 0x01;
  Command[4] = 0x00;
  Command[5] = 0x02;
  Command[6] = 0x01;
  Command[7] = 0xAB;
  Command[8] = 0xCD;
  for(uint8 i=0;i<15;i++) getQRCode.Barcode_rec_data[i]=0;
        getQRCode.receiveComplete=0; 
        getQRCode.first[0]=0;
        getQRCode.second[0]=0;
        getQRCode.third[0]=0;
        getQRCode.first[1]=0;
        getQRCode.second[1]=0;
        getQRCode.third[1]=0;
        getQRCode.Barcode_rec_num=0;
  uart_putbuff(Barcode_Scanner_COF_UART,&Command[0],sizeof(Command)); 
}


/*---------------------------------------------------


1） 写成功
2） 保存成功
3）恢复出厂成功
4） 擦除成功
5） 串口命令触发成功
返回
Head2 ：0x02 0x00
Types ：0x00（写成功）
Lens ：0x01
Data ：0x00
CRC ：CRC_CCITT 校验值（0x33 0x31）

注：在命令触发模式下，触发扫描的串口指令为：7E 00 08 01 00 02 01 AB CD；识读模
块收到触发指令后，会先输出七个字节的回应信息并同步启动扫描（回应信息内容：02 00 00
01 00 33 31）

*/



void Barcode_uart_interrupt(void)
{

    uart_query(Barcode_Scanner_COF_UART,&getQRCode.Barcode_rec_data[getQRCode.Barcode_rec_num]);
    
   if(getQRCode.Barcode_rec_data[0] != 0x02) //0x59
   {   	getQRCode.Barcode_rec_num = 0;  }
   else if(getQRCode.Barcode_rec_num == 1 && getQRCode.Barcode_rec_data[1]!= 0x00) //0x59
   {   	getQRCode.Barcode_rec_num = 0;  } 
   else if(getQRCode.Barcode_rec_num == 14&& getQRCode.Barcode_rec_data[14]== 0x0D) 
   {   
        getQRCode.receiveComplete=1; 
        getQRCode.first[0]=getQRCode.Barcode_rec_data[7]-0x30;
        getQRCode.second[0]=getQRCode.Barcode_rec_data[8]-0x30;
        getQRCode.third[0]=getQRCode.Barcode_rec_data[9]-0x30;
        getQRCode.first[1]=getQRCode.Barcode_rec_data[11]-0x30;
        getQRCode.second[1]=getQRCode.Barcode_rec_data[12]-0x30;
        getQRCode.third[1]=getQRCode.Barcode_rec_data[13]-0x30;
        getQRCode.Barcode_rec_num = 0; 
   }   

   else 
   {    getQRCode.Barcode_rec_num++;    }
}

//串口2中断函数，需要主函数打开中断，此函数复制到isr.c也可以实用
void FLEXCOMM2_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART2_FIFO_FLAG;   
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
        Barcode_uart_interrupt();//uart_query(USART_2,&ddf[fg]);读取数据
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//发送FIFO达到设定水平（库默认设定水平 当发送FIFO为空的时候触发中断）
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        USART2->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART2->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
    }
}



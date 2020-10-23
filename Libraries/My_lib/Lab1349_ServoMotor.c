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
#include "Lab1349_ServoMotor.h"



unsigned char Command[16];

ROBOT_Position POSItion;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Barcode_uart_init串口初始化函数 8，N，1，9600
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:            串口USART_0，接收中断使能
//-------------------------------------------------------------------------------------------------------------------
void ServoMotor_uart_init(void)
{
    uart_init(ServoMotor_COF_UART,57600,ServoMotor_COF_TX,ServoMotor_COF_RX);
  //  uart_rx_irq(ServoMotor_COF_UART,1);                               // 打开串口0接收中断
}

void Servo_Position_Init()
{
    ////////////////////////////////////////////////////////////////////////////////
    /*********************************************************************/
    /**************************机械臂姿态*********************************/
    /*********************************************************************/
    POSItion.first.Start = Start_Dir;
    ////////////////////////////////////////////
    POSItion.second.START = Servo2_PosA;
    POSItion.second.Color_Recognition[0] = Servo2_PosB;
    POSItion.second.Color_Recognition[1] = Servo2_PosE;
    POSItion.second.Color_Recognition[2] = Servo2_PosH;
    POSItion.second.Material.Grasp[0] = Servo2_PosC;
    POSItion.second.Material.Grasp[1] = Servo2_PosD;
    
    POSItion.second.Process.Grasp[0] = Servo2_PosL;
    POSItion.second.Process.Grasp[1] = Servo2_PosK;
    POSItion.second.Process.Grasp[2] = Servo2_PosD;
    
    POSItion.second.Process.place[0] = Servo2_PosF;
    POSItion.second.Process.place[1] = Servo2_PosG;
    POSItion.second.Process.place[2] = Servo2_PosD;
    
    POSItion.second.Final.place[0] = Servo2_PosI;
    POSItion.second.Final.place[1] = Servo2_PosJ;
    POSItion.second.Final.place[2] = Servo2_PosD;
    
    /////////////////////////////////////////////  
    POSItion.third.START = Servo3_PosA;
    POSItion.third.Color_Recognition[0] = Servo3_PosB;
    POSItion.third.Color_Recognition[1] = Servo3_PosE;
    POSItion.third.Color_Recognition[2] = Servo3_PosH;
    POSItion.third.Material.Grasp[0] = Servo3_PosC;
    POSItion.third.Material.Grasp[1] = Servo3_PosD;
    
    POSItion.third.Process.Grasp[0] = Servo3_PosL;
    POSItion.third.Process.Grasp[1] = Servo3_PosK;
    POSItion.third.Process.Grasp[2] = Servo3_PosD;
    
    POSItion.third.Process.place[0] = Servo3_PosF;
    POSItion.third.Process.place[1] = Servo3_PosG;
    POSItion.third.Process.place[2] = Servo3_PosD;
    
    POSItion.third.Final.place[0] = Servo3_PosI;
    POSItion.third.Final.place[1] = Servo3_PosJ;
    POSItion.third.Final.place[2] = Servo3_PosD;
    
    /////////////////////////////////////////////  
    POSItion.fourth.open = HandOpenpPos;
    POSItion.fourth.close = HandClosepPos;
}

//输入为0则保持上一动作，最后一个是延时(ms)
void Robot_Position(uint16 Position1, uint16 Position2, uint16 Position3, uint16 Position4, uint16 Delay_Time )
{
  Command[0] = 0xAA;
  Command[1] = 0x00;
  Command[14] = 0x00;
  Command[15] = 0x0D;  
  if (Position1 != 0)
  {
    Command[2] = Position1>>8;
    Command[3] = Position1;
    POSItion.first.Current = Position1;
  }
  else 
  {
    Command[2] = POSItion.first.Current>>8;
    Command[3] = POSItion.first.Current;
  }
  if (Position2 != 0)
  {
    Command[4] = Position2>>8;
    Command[5] = Position2;
    POSItion.second.Current = Position2;
  }
  else 
  {
    Command[4] = POSItion.second.Current>>8;
    Command[5] = POSItion.second.Current;
  }
    if (Position3 != 0)
  {
    Command[6] = Position3>>8;
    Command[7] = Position3;
    POSItion.third.Current = Position3;
  }
  else 
  {
    Command[6] = POSItion.third.Current>>8;
    Command[7] = POSItion.third.Current;
  }
  if (Position4 != 0)
  {
    Command[8] = Position4>>8;
    Command[9] = Position4;
    POSItion.fourth.Current = Position4;
  }
  else 
  {
    Command[8] = POSItion.fourth.Current>>8;
    Command[9] = POSItion.fourth.Current;
  }
  for(int i=0;i<5;i++)
  {
  uart_putbuff(ServoMotor_COF_UART,&Command[0],sizeof(Command)); 
  }
  
  systick_delay_ms(Delay_Time);
}




void ServoMotor_uart_interrupt(void)
{

   // uart_query(ServoMotor_COF_UART,&getQRCode.Barcode_rec_data[getQRCode.Barcode_rec_num]);
    

}

//串口0中断函数，需要主函数打开中断，此函数复制到isr.c也可以实用
void FLEXCOMM1_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART1_FIFO_FLAG;   
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
        ServoMotor_uart_interrupt();//uart_query(USART_2,&ddf[fg]);读取数据
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//发送FIFO达到设定水平（库默认设定水平 当发送FIFO为空的时候触发中断）
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        USART1->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART1->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
    }
}


/*stm32程序协议部分，供参考
//数据格式 0xAA 0X00帧头，高 低 X 6数据  0x xx 方式选择，0x0D帧尾
     if(Receive[0] != 0xAA) //帧头
     {   	i = 0;  }
     else if(i == 1 && Receive[1]!= 0x00) //第二帧  00独立位置命令，01是群组控制命令
     {   	i = 0;  } 
     else if(i == 15&& Receive[15]== 0x0D) //帧尾 0D 
     {  
			 switch(Receive[14])
       {
						 case 0x00:          //按主单片机位置控制
				           Target1=Receive[3]|Receive[2]<<8;   //高位前，低位后
			             Target2=Receive[5]|Receive[4]<<8;   //高位前，低位后
			             Target3=Receive[7]|Receive[6]<<8;   //高位前，低位后
			             Target4=Receive[9]|Receive[8]<<8;    //高位前，低位后			 
                   Target5=Receive[11]|Receive[10]<<8;   //高位前，低位后	
                   Target5=Receive[13]|Receive[12]<<8;   //高位前，低位后							 						 
						       break;
						 case 0x01:          
							     Target1=760;
						       Target2=700;
						       Target3=800;
						       Target4=585;
						       Target5=250;
						       Target6=250;						 
						       break;
//Target1=760,Target2=700,Target3=800,竖直    //Target4=585,  松开  T4增加是加紧 						 
						 case 0x02:          
							     Target1=300;
						       Target2=775;
						       Target3=800;
						       Target4=585;
						       Target5=250;
						       Target6=250;						 
//float Target1=300,Target2=775,Target3=800,Target4=585,    //倒下抓取状态，手抓开						 
						       break;
						 case 0x03:  
							     Target1=300;
						       Target2=775;
						       Target3=800;
						       Target4=713;
						       Target5=250;
						       Target6=250;						 
						       break;							 
//float Target1=300,Target2=775,Target3=800,Target4=713,    //倒下抓取状态，手抓合						 
  					 case 0x04:  
							     Target1=450;
						       Target2=775;
						       Target3=800;
						       Target4=713;
						       Target5=250;
						       Target6=250;						 
						       break;	
//float Target1=450,Target2=775,Target3=800,Target4=713,    //倒下抬起状态						 
						 case 0x05:  
							     Target1=270;
						       Target2=900;
						       Target3=600;
						       Target4=713;
						       Target5=250;
						       Target6=250;						 
						       break;	
//float Target1=270,Target2=900,Target3=600,Target4=713,    //放下准备放料状态						 
						 case 0x06: 
							     Target1=270;
						       Target2=900;
						       Target3=600;
						       Target4=585;
						       Target5=250;
						       Target6=250;						 
						       break;	
//float Target1=270,Target2=900,Target3=600,Target4=585,    //放下放料						 
						 case 0x07: 
							     Target1=760;
						       Target2=700;
						       Target3=800;
						       Target4=250;
						       Target5=250;
						       Target6=250;						 
						       break;	
             case 0x08:  		
							     Target1=760;
						       Target2=700;
						       Target3=800;
						       Target4=250;
						       Target5=250;
						       Target6=250;						 
						       break;	
            default:
							     Target1=760;
						       Target2=700;
						       Target3=800;
						       Target4=250;
						       Target5=250;
						       Target6=250;						
						       break;	
			 
			 }
			 i = 0; 
		      while((USART3->SR&0X40)==0){ ; } 
     		      USART3->DR = 0x55; 
*/
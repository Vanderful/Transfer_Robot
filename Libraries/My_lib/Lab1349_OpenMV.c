/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,上海工程技术大学 工程实训中心 1349实验室
 * All rights reserved.
 * 技术讨论QQ群：320746302  实训智能车队报名群
 *
 * 以下所有内容版权均属 上海工程技术大学 实训智能车队 所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留 上海工程技术大学 实训智能车队 的版权声明。
 *
 * @file       		TFmini Plus
 * @company	   		上海工程技术大学 工程实训中心 1349实验室
 * @author     		实训智能车(QQ320746302)
 * @version    		
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100                      
 * @Taobao   		https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w5001-14519673283.4.3bae5f22zPC7Gn&id=586827631220&scene=taobao_shop
                        星瞳科技
 * @date       		2019-04-09
 * @note		
					接线定义：
					------------------------------------ 
		      模块引脚		  单片机引脚

                   P4   TX                UART7_RX_B29
                   P5   RX                UART7_TX_B30 
                      (GND)	             GND               

					------------------------------------ 
教程参考网址：https://singtown.com/openmv/
              http://book.openmv.cc/
              http://makermare.com:60010//example/hardware/uart.html
 ********************************************************************************************************************/


//#include "common.h"
//#include "LPC546XX_iocon.h"
//#include "LPC546XX_flexcomm.h" 
//#include "LPC546XX_uart.h"
#include "Lab1349_OpenMV.h"
//#include "My_Math.h"


OpenMV  myOpenMV = {0};
Openmv  MYOPENMV = {0};

static unsigned char Command[3];
void  OpenMV_uart_interrupt(void);	
void  Filter(uint8 filter_buf1[],uint8 filter_buf2[],uint8 filter_buf3[],uint8 FILTER_N); //  中位值平均滤波法（又称防脉冲干扰平均滤波法）

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OpenMV_uart_init串口初始化函数 8，N，1，19200
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:            串口USART_2，接收中断使能uart_init(USART_0,115200,UART0_TX_A25,UART0_RX_A24); 
//-------------------------------------------------------------------------------------------------------------------
void OpenMV_uart_init(void)
{
    uart_init(OpenMV_COF_UART,19200,OpenMV_COF_TX,OpenMV_COF_RX);
    uart_rx_irq(OpenMV_COF_UART,1);                               // 打开串口0接收中断
  
   memset(&myOpenMV,0,sizeof(myOpenMV));  // 清空数组
  
  //memset(&myOpenMV,0,sizeof(myOpenMV));//memset(ZEROARRAY, 0, 1024);memset(Receive, 0, sizeof(u8)*50);
}

void  OpenMV_uart_disable(void)//串口中断禁止
{
   uart_rx_irq(OpenMV_COF_UART,0);
}

void OpenMV_Step1_Command(void)
{
  Command[0] = 0x41;//A
  Command[1] = 0x31;//1
  Command[2] = 0x41;//A
  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
}  

void OpenMV_Step3_Command(void)
{
  Command[0] = 0x43;//C
  Command[1] = 0x33;//3
  Command[2] = 0x43;//C
  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
} 

void OpenMV_Step4_Command(void)
{
  Command[0] = 0x44;//D
  Command[1] = 0x34;//4
  Command[2] = 0x44;//D
  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
} 
  
void OpenMV_Step2_Left_Command(void)
{  
  Command[0] = 0x42;//B
  Command[1] = 0x32;//2
  Command[2] = 0x42;//B
//  myOpenMV.Step2Left_flag=1;
//  myOpenMV.Step2Middle_flag=0;  
//  myOpenMV.Step2Right_flag=0;
  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
}

//void OpenMV_Step2_Middle_Command(void)
//{  
//  Command[0] = 0x42;//B
//  Command[1] = 0x32;//2
//  Command[2] = 0x42;//B
//  myOpenMV.Step2Left_flag=0;
//  myOpenMV.Step2Middle_flag=1;  
//  myOpenMV.Step2Right_flag=0;
//  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
//}
//
//void OpenMV_Step2_Right_Command(void)
//{  
//  Command[0] = 0x42;//B
//  Command[1] = 0x32;//2
//  Command[2] = 0x42;//B
//  myOpenMV.Step2Left_flag=0;
//  myOpenMV.Step2Middle_flag=0;  
//  myOpenMV.Step2Right_flag=1;
//  uart_putbuff(OpenMV_COF_UART,&Command[0],sizeof(Command)); 
//}

//串口2中断函数，需要主函数打开中断，此函数复制到isr.c也可以实用
void FLEXCOMM3_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART3_FIFO_FLAG; 
    DisableInterrupts;
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
        OpenMV_uart_interrupt();//uart_query(USART_2,&ddf[fg]);读取数据
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//发送FIFO达到设定水平（库默认设定水平 当发送FIFO为空的时候触发中断）
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        USART3->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART3->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
    }
    EnableInterrupts;
}


// protocol processing function:
void OpenMV_uart_interrupt(void)
{
  uart_query(OpenMV_COF_UART,&myOpenMV.OpenMV_rec[myOpenMV.OpenMV_recnum]);
  
  if(myOpenMV.OpenMV_rec[0] != 0x41) //字符A
   { 	myOpenMV.OpenMV_recnum = 0;  }
  else if(myOpenMV.OpenMV_recnum == 5  && myOpenMV.OpenMV_rec[5]== 0x44) //字符D
   {
     myOpenMV.OpenMV_recnum = 0; 
     if(myOpenMV.OpenMV_rec[1]== 0x42) //字符B
     {
  
       if((myOpenMV.OpenMV_rec[2]!=myOpenMV.OpenMV_rec[3])&&
          (myOpenMV.OpenMV_rec[2]!=myOpenMV.OpenMV_rec[4])&&
          (myOpenMV.OpenMV_rec[3]!=myOpenMV.OpenMV_rec[4]))
       {     
         if( myOpenMV.usefulcount<5)
         {
            myOpenMV.Left[myOpenMV.usefulcount]  =myOpenMV.OpenMV_rec[2]-0x30;
            myOpenMV.Middle[myOpenMV.usefulcount]=myOpenMV.OpenMV_rec[3]-0x30;
            myOpenMV.Right[myOpenMV.usefulcount] =myOpenMV.OpenMV_rec[4]-0x30;
            myOpenMV.usefulcount++;
         }
         else if(myOpenMV.usefulcount==5)
         {
          Filter(myOpenMV.Left,myOpenMV.Middle,myOpenMV.Right,6);    //三位一起排序，以第一维为准
          myOpenMV.Left_N=myOpenMV.Left[3];           //取中间值 
          myOpenMV.Middle_N=myOpenMV.Middle[3];       //取中间值   
          myOpenMV.Right_N=myOpenMV.Right[3];         //取中间值 
          myOpenMV.receiveComplete=1; 
          myOpenMV.usefulcount=0;
         }
       }
     }
     else if(myOpenMV.OpenMV_rec[1]== 0x43) //字符C
     {
                   myOpenMV.Step2Left  =myOpenMV.OpenMV_rec[3]-0x30;
                   myOpenMV.receiveComplete=1;
     }
   }
  else if(myOpenMV.OpenMV_recnum == 8 && myOpenMV.OpenMV_rec[8]== 0x49) //字符I
  {
    myOpenMV.OpenMV_recnum = 0; 
    if(myOpenMV.OpenMV_rec[1]== 0x45)//字符E
    {
      if( MYOPENMV.count<5)
      {
        MYOPENMV.X[MYOPENMV.count] = (myOpenMV.OpenMV_rec[2]-0x30) * 100 + (myOpenMV.OpenMV_rec[3]-0x30) * 10 + (myOpenMV.OpenMV_rec[4]-0x30);
        MYOPENMV.Y[MYOPENMV.count] = (myOpenMV.OpenMV_rec[5]-0x30) * 100 + (myOpenMV.OpenMV_rec[6]-0x30) * 10 + (myOpenMV.OpenMV_rec[7]-0x30);
        MYOPENMV.count++;
      }
      else if( MYOPENMV.count==5)
      {
        bubble_sort(MYOPENMV.X,sizeof(MYOPENMV.X));
        bubble_sort(MYOPENMV.Y,sizeof(MYOPENMV.Y));
        for(int a = 1;a<4;a++)
        {
          MYOPENMV.Avg_X += MYOPENMV.X[a];
          MYOPENMV.Avg_Y += MYOPENMV.Y[a];
        }
        MYOPENMV.Avg_X = MYOPENMV.Avg_X/3;
        MYOPENMV.Avg_Y = MYOPENMV.Avg_Y/3;
        MYOPENMV.count = 0;
        myOpenMV.receiveComplete=1;
      }
    }
        if(myOpenMV.OpenMV_rec[1]== 0x46)//字符F
    {
      if( MYOPENMV.count<5)
      {
        MYOPENMV.X[MYOPENMV.count] = (myOpenMV.OpenMV_rec[2]-0x30) * 100 + (myOpenMV.OpenMV_rec[3]-0x30) * 10 + (myOpenMV.OpenMV_rec[4]-0x30);
        MYOPENMV.Y[MYOPENMV.count] = (myOpenMV.OpenMV_rec[5]-0x30) * 10 + (myOpenMV.OpenMV_rec[6]-0x30);
        MYOPENMV.count++;
      }
      else if( MYOPENMV.count==5)
      {
        bubble_sort(MYOPENMV.X,sizeof(MYOPENMV.X));
        bubble_sort(MYOPENMV.Y,sizeof(MYOPENMV.Y));
        for(int a = 1;a<4;a++)
        {
          MYOPENMV.Avg_X += MYOPENMV.X[a];
          MYOPENMV.Avg_Y += MYOPENMV.Y[a];
        }
        MYOPENMV.Avg_X = MYOPENMV.Avg_X/3;
        MYOPENMV.Avg_Y = MYOPENMV.Avg_Y/3;
        MYOPENMV.count = 0;
        myOpenMV.receiveComplete=1;
      }
    }
            if(myOpenMV.OpenMV_rec[1]== 0x47)//字符G
    {
      if( MYOPENMV.count<5)
      {
        MYOPENMV.X[MYOPENMV.count] = (myOpenMV.OpenMV_rec[2]-0x30) * 10 + (myOpenMV.OpenMV_rec[3]-0x30);
        MYOPENMV.Y[MYOPENMV.count] = (myOpenMV.OpenMV_rec[4]-0x30) * 100 + (myOpenMV.OpenMV_rec[5]-0x30) * 10 + (myOpenMV.OpenMV_rec[6]-0x30);
        MYOPENMV.count++;
      }
      else if( MYOPENMV.count==5)
      {
        bubble_sort(MYOPENMV.X,sizeof(MYOPENMV.X));
        bubble_sort(MYOPENMV.Y,sizeof(MYOPENMV.Y));
        for(int a = 1;a<4;a++)
        {
          MYOPENMV.Avg_X += MYOPENMV.X[a];
          MYOPENMV.Avg_Y += MYOPENMV.Y[a];
        }
        MYOPENMV.Avg_X = MYOPENMV.Avg_X/3;
        MYOPENMV.Avg_Y = MYOPENMV.Avg_Y/3;
        MYOPENMV.count = 0;
        myOpenMV.receiveComplete=1;
      }
    }
                if(myOpenMV.OpenMV_rec[1]== 0x48)//字符H
    {
      if( MYOPENMV.count<5)
      {
        MYOPENMV.X[MYOPENMV.count] = (myOpenMV.OpenMV_rec[2]-0x30) * 10 + (myOpenMV.OpenMV_rec[3]-0x30);
        MYOPENMV.Y[MYOPENMV.count] = (myOpenMV.OpenMV_rec[4]-0x30) * 10 + (myOpenMV.OpenMV_rec[5]-0x30);
        MYOPENMV.count++;
      }
      else if( MYOPENMV.count==5)
      {
        bubble_sort(MYOPENMV.X,sizeof(MYOPENMV.X));
        bubble_sort(MYOPENMV.Y,sizeof(MYOPENMV.Y));
        for(int a = 1;a<4;a++)
        {
          MYOPENMV.Avg_X += MYOPENMV.X[a];
          MYOPENMV.Avg_Y += MYOPENMV.Y[a];
        }
        MYOPENMV.Avg_X = MYOPENMV.Avg_X/3;
        MYOPENMV.Avg_Y = MYOPENMV.Avg_Y/3;
        MYOPENMV.count = 0;
        myOpenMV.receiveComplete=1;
      }
    }
  }
  else if(myOpenMV.OpenMV_recnum > 11)
  {
    myOpenMV.OpenMV_recnum = 0;
  }
   else 
   {  myOpenMV.OpenMV_recnum++;    }


   


}

void Filter(uint8 filter_buf1[],uint8 filter_buf2[],uint8 filter_buf3[],uint8 FILTER_N) //  中位值平均滤波法（又称防脉冲干扰平均滤波法）
{
  int i, j;
  uint8 filter_temp=0;
                             
  for(j=0;j<FILTER_N-1;j++)                      //采样值从小到大排列（冒泡法）
  {
    for(i=0;i<FILTER_N-1-j;i++)
    {
      if(filter_buf1[i]>filter_buf1[i+1])
      {
        filter_temp = filter_buf1[i];         //第一维调换
        filter_buf1[i] = filter_buf1[i+1];
        filter_buf1[i+1] = filter_temp;
        
        filter_temp = filter_buf2[i];
        filter_buf2[i] = filter_buf2[i+1];
        filter_buf2[i+1] = filter_temp;        
        
        filter_temp = filter_buf3[i];
        filter_buf3[i] = filter_buf3[i+1];
        filter_buf3[i+1] = filter_temp;          
        
      }
    }
  }  
}


int getIndexOfSigns(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if(ch >= 'A' && ch <='F') 
    {
        return ch - 'A' + 10;
    }
    if(ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    return -1;
}


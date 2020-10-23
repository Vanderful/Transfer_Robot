/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,上海工程技术大学 工程实训中心 1349实验室
 * All rights reserved.
 * 技术讨论QQ群：320746302  实训智能车队报名群
 *
 * 以下所有内容版权均属 上海工程技术大学 实训智能车队  所有，未经允许不得用于商业用途，
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



#ifndef _Lab1349_OpenMV_h
#define _Lab1349_OpenMV_h

#include "headfile.h"
//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
//#define OpenMV_COF_UART        USART_3         //配置摄像头所使用到的串口     
//#define OpenMV_COF_TX          UART3_TX_A2    //定义TFmini_Plus_RX引脚  可任意更改为其他IO
//#define OpenMV_COF_RX          UART3_RX_A3    //定义STFmini_Plus_TX引脚  可任意更改为其他IO

typedef struct {
   uint8 X[5];
   uint8 Y[5];
   float Avg_X;
   float Avg_Y;
   int count;
   int complete;
}Openmv;
   
   
// 定义OpenMV测量变量
typedef struct {
   uint8  Left_N;
   uint8  Middle_N;
   uint8  Right_N;    
   uint8  Left[6];
   uint8  Middle[6];
   uint8  Right[6];  
   uint8  receiveComplete;
   uint8  OpenMV_rec[10];
   uint8  OpenMV_recnum;
   uint8  usefulcount; 
   
   uint8  Step2Left;
//   uint8  Step2Middle;
//   uint8  Step2Right;    
//   uint8  Step2Left_flag;
//   uint8  Step2Middle_flag;
//   uint8  Step2Right_flag; 
}OpenMV;


/*********************************************
主函数初始化
程序调用直接初始化  
           OpenMV_uart_init(）;//初始化1次就够
/////////////////////////////////////////////////////// 
           myOpenMV.receiveComplete=0;
           do{ OpenMV_Step1_Command();systick_delay_ms(20);}
           while(!myOpenMV.receiveComplete);//注意程序采集5次取中间一次后就结束。

           myOpenMV.Left_N
           myOpenMV.Middle_N
           myOpenMV.Right_N
/////////////////////上面是第一步物料颜色识别////////////////////
//////////////////////下面是十字靶心识别，分别是机械手动作后识别3次///////////////////
           myOpenMV.receiveComplete=0;
           do{ OpenMV_Step2_Left_Command();systick_delay_ms(20);}
           while(!myOpenMV.receiveComplete);//

           myOpenMV.receiveComplete=0;
           do{ OpenMV_Step2_Middle_Command();systick_delay_ms(20);}
           while(!myOpenMV.receiveComplete);//

           myOpenMV.receiveComplete=0;
           do{ OpenMV_Step2_Right_Command();systick_delay_ms(20);}
           while(!myOpenMV.receiveComplete);//

           myOpenMV.Step2Left
           myOpenMV.Step2Middle
           myOpenMV.Step2Right

     采集完毕，使用OpenMV_uart_disable，关闭串口中断接收功能。

**********************************************/

extern OpenMV myOpenMV;
extern Openmv  MYOPENMV;

void  OpenMV_uart_init(void);	

void  OpenMV_uart_disable(void);

void  OpenMV_Step1_Command(void);
void OpenMV_Step3_Command(void);
void OpenMV_Step4_Command(void);

void  OpenMV_Step2_Left_Command(void);
void  OpenMV_Step2_Middle_Command(void);
void  OpenMV_Step2_Right_Command(void);

int getIndexOfSigns(char ch);


#endif

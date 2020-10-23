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
 * @Taobao   		https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-15726392041.12.7f4110a9uPJ8Ye&id=555742998021
                         
 * @date       		2019-04-11
 * @note		
					接线定义：
					------------------------------------ 
	         STM32模块引脚		            单片机引脚
                 PIN-1 
                 PIN-2 TXD B10                       UART0_RX_A24
                 PIN-3 RXD B11                       UART0_TX_A25 
                 PIN-4 GND            	          GND               

					------------------------------------ 
注意：两种，一种采用平衡车之家stm32控制板，一种采用telesky淘宝网舵机控制器
 ********************************************************************************************************************/

#ifndef _Lab1349_ServoMotor_h
#define _Lab1349_ServoMotor_h

#include "headfile.h"

//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
//#define ServoMotor_COF_UART        USART_1         //配置摄像头所使用到的串口     
//#define ServoMotor_COF_TX          UART1_TX_A10    //定义TFmini_Plus_RX引脚  可任意更改为其他IO
//#define ServoMotor_COF_RX          UART1_RX_B10    //定义STFmini_Plus_TX引脚  可任意更改为其他IO

//////从下往上数
//第四个舵机（手爪） 只有 打开 和 关闭 两种状态
typedef struct {
   uint16 Current;  //当前状态
   uint16 open;     //打开
   uint16 close;    //关闭
} Servo4_Mode;

//第一个舵机（底盘） 至少有四个方向的状态，已预留斜45°状态位置
typedef struct {
   uint16 Current;  //当前状态
   uint16 Material; //物料区
   uint16 Process;  //加工区
   uint16 Final;    //成品区
   uint16 Start;    //发车初始姿态
   uint16 Process_Color[2];   //（预留）加工区颜色识别
   uint16 Final_Color[2];     //（预留）成品区颜色识别
} Servo1_Mode;

//第二、三舵机在 抓取 和 放置 的动作组
typedef struct {
   uint16 Grasp[3];
   uint16 place[3];
} area_step;

//第二、三个舵机，有不同的动作组
typedef struct {
   uint16 Current;  //当前状态
   uint16 START;    //发车初始姿态
   uint16 Color_Recognition[3];  //物料区颜色识别
   area_step Material;   //物料区动作组
   area_step Process;    //加工区动作组
   area_step Final;      //成品区动作组
} Servo_Mode;

//四个舵机合并（结构体套娃，多此一举，但是我懒得改了）
typedef struct {
   Servo1_Mode first;
   Servo_Mode second;
   Servo_Mode third;
   Servo4_Mode fourth;
} ROBOT_Position;

extern ROBOT_Position POSItion;

void ServoMotor_uart_init(void);

void Robot_Position(uint16 Position1, uint16 Position2, uint16 Position3, uint16 Position4, uint16 Delay_Time );



#endif

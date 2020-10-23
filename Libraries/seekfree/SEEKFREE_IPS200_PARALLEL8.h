/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		IPS 2.0寸液晶
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.26
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-09-17
 * @note		
					接线定义：
					------------------------------------ 
						模块管脚            单片机管脚
						D0                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D0_PIN  宏定义
						D1                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D1_PIN  宏定义
						D2                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D2_PIN  宏定义
						D3                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D3_PIN  宏定义
						D4                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D4_PIN  宏定义
						D5                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D5_PIN  宏定义
						D6                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D6_PIN  宏定义
						D7                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D7_PIN  宏定义
                                                              _                           
						BL                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_BL_PIN  宏定义
						CS                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_CS_PIN  宏定义
						RD                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RD_PIN  宏定义
						WR                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_WR_PIN  宏定义
						RS                 查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RS_PIN  宏定义
						RST                查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RST_PIN 宏定义

						电源引脚
						VCC 3.3V电源
						GND 电源地
						最大分辨率240*320
					------------------------------------ 
						A13 A14为硬件IIC，不能作为IP2.0寸屏幕的数据引脚和命令引脚使用。 
 ********************************************************************************************************************/



#ifndef _SEEKFREE_IPS20_PARALLEL8_H
#define _SEEKFREE_IPS20_PARALLEL8_H

#include "common.h"
#include "SEEKFREE_FONT.h"

//--------------引脚定义--------------
//A13 A14为硬件IIC，不能作为屏幕数据引脚和命令引脚使用。 

//8个数据引脚必须连续 例如B0-B7,B6-B13等等。
#define IPS200_D0_PIN           B8
#define IPS200_D1_PIN           B9
#define IPS200_D2_PIN           B10
#define IPS200_D3_PIN           B11
#define IPS200_D4_PIN           B12
#define IPS200_D5_PIN           B13
#define IPS200_D6_PIN           B14
#define IPS200_D7_PIN           B15

//命令引脚
#define IPS200_RD_PIN           B5
#define IPS200_WR_PIN           B6
#define IPS200_RS_PIN           B20
#define IPS200_RST_PIN          A10
#define IPS200_CS_PIN           A16
#define IPS200_BL_PIN           B0

//寄存器操作引脚，具体请查看LPC546XX_gpio.h文件
#define IPS200_BL(x)            P(IPS200_BL_PIN  >> 5,IPS200_BL_PIN  & 0x1f) = x
#define IPS200_CS(x)            P(IPS200_CS_PIN  >> 5,IPS200_CS_PIN  & 0x1f) = x
#define IPS200_RD(x)            P(IPS200_RD_PIN  >> 5,IPS200_RD_PIN  & 0x1f) = x
#define IPS200_WR(x)            P(IPS200_WR_PIN  >> 5,IPS200_WR_PIN  & 0x1f) = x
#define IPS200_RS(x)            P(IPS200_RS_PIN  >> 5,IPS200_RS_PIN  & 0x1f) = x
#define IPS200_RST(x)           P(IPS200_RST_PIN >> 5,IPS200_RST_PIN & 0x1f) = x



//--------------定义数据端口--------------
#define IPS200_DATAPORT     	GPIO->MPIN[IPS200_D0_PIN >> 5]   //0：A端口  1：B端口
#define DATA_START_NUM			(IPS200_D0_PIN&0x1f)  			//宏定义数据引脚的起始编号




//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	0xF800	//红色
//#define BLUE         	0x001F  //蓝色
//#define YELLOW       	0xFFE0	//黄色
//#define GREEN        	0x07E0	//绿色
//#define WHITE        	0xFFFF	//白色
//#define BLACK        	0x0000	//黑色 
//#define GRAY  		0X8430 	//灰色
//#define BROWN 		0XBC40 	//棕色
//#define PURPLE    	0XF81F	//紫色
//#define PINK    		0XFE19	//粉色


//定义写字笔的颜色
#define IPS200_PENCOLOR         RED

//定义背景颜色
#define IPS200_BGCOLOR          WHITE


#define IPS200_W                240	    	
#define IPS200_H                320	   		


//--------------定义显示方向--------------
//0 竖屏模式
//1 竖屏模式  旋转180°
//2 横屏模式
//3 横屏模式  旋转180°
#define IPS200_DISPLAY_DIR 		3

#if (0==IPS200_DISPLAY_DIR || 1==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX			IPS200_W	//液晶X方宽度
#define IPS200_Y_MAX			IPS200_H   //液晶Y方宽度
     
#elif (2==IPS200_DISPLAY_DIR || 3==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX			IPS200_H	//液晶X方宽度
#define IPS200_Y_MAX			IPS200_W   //液晶Y方宽度
     
#else
#error "IPS200_DISPLAY_DIR 定义错误"
     
#endif


void ips200_init(void); 
void ips200_w_data(uint8 dat);
void ips200_wr_reg(uint16 com);
void ips200_wr_data(uint8 dat);
void ips200_wr_data16(uint16 dat);
void ips200_w_reg(uint8 com,uint8 dat);
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void ips200_clear(uint16 Color);
void ips200_drawpoint(uint16 x,uint16 y,uint16 color);
void ips200_showchar(uint16 x,uint16 y,uint8 dat);
void ips200_showstr(uint16 x,uint16 y,uint8 dat[]);

void ips200_showint8(uint16 x,uint16 y,int8 dat);
void ips200_showuint8(uint16 x,uint16 y,uint8 dat);
void ips200_showint16(uint16 x,uint16 y,int16 dat);
void ips200_showuint16(uint16 x,uint16 y,uint16 dat);
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num);
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum);
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p);
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

void ips200_displayimage032(uint8 *p, uint16 width, uint16 height);
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);

#endif


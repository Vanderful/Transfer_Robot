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

#ifndef _Lab1349_Barcode_Scanner_h
#define _Lab1349_Barcode_Scanner_h

#include "headfile.h"
//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
//#define Barcode_Scanner_COF_UART       USART_2         //配置二维码模块所使用到的串口     
//#define Barcode_Scanner_COF_TX         UART2_TX_B25    //定义Barcode_Scanner_COF_TX引脚
//#define Barcode_Scanner_COF_RX         UART2_RX_B24    //定义Barcode_Scanner_COF_RX引脚

//--------------------------------------------------------------------------------------------------
//命令字定义
//--------------------------------------------------------------------------------------------------
#define Command_Head 0x7E      //帧头
#define Command_Read 0x07     //读命令
#define Command_Write 0x08     //写命令
#define Command_SaveEEPROM 0x09     //保存到 EEPROM 指令

#define Addr_Functions 0x0000  //功能地址
/*---------------------------------------------------
标志位 0x0000
数据位 功能
Bit 7   1：开启解码成功 LED 提示 0：关闭解码成功 LED 提示
Bit 6   1：关闭静音 0：启动静音
Bit 5-4 00：无瞄准 01：普通 10/11：常亮
Bit 3-2 00：无照明 01：普通 10/11：常亮
Bit 1-0 00：手动模式 01：命令触发模式 10：连续模式 11：感应模式
-----------------------------------------------------*/
#define LED_Indicator_En  (0x1 << 7)
#define LED_Indicator_Dis (0x0 << 7)

#define Buz_Indicator_En  (0x1 << 6)
#define Buz_Indicator_Dis (0x0 << 6)

#define Focus_Dis         (0x0 << 4)
#define Focus_Com         (0x1 << 4)
#define Focus_Keep        (0x2 << 4)

#define Light_Dis         (0x0 << 2)
#define Light_Com         (0x1 << 2)
#define Light_Keep        (0x2 << 2)

#define Manual_Mode        0x00
#define Command_Mode       0x01
#define Continous_Mode     0x02
#define Sensor_Mode        0x03

#define Addr_TimeHoldImage 0x0004
/*---------------------------------------------------
标志位 0x0004
数据位 功能
Bit 7-0 稳像时长
//Max:25.5s, FA=25s., 64=10s
稳像时长指在感应识读模式下，侦测到场景变化的识读模块在读码之前需要等待图像稳定
的时间。稳像时长设置范围为 0~25.5 秒，步长为 0.1 秒。默认稳像时长为 0.4 秒。
-----------------------------------------------------*/

#define Addr_IntervalSetting 0x0005
/*---------------------------------------------------
标志位 0x0005
数据位 功能
Bit 7-0 识读间隔时长
//Max:25.5s, FA=25s., 64=10s
在识读成功输出信息或单次读码超时后，识读模块需间隔一段时间（可设置）才重新
进入监测状态。识读间隔时长的设置范围为 0~25.5 秒，步长为 0.1 秒。默认间隔时长
为 1.0 秒。
-----------------------------------------------------*/

#define Addr_SingleReadTime 0x0006
/*---------------------------------------------------
标志位 0x0006
数据位 功能
Bit 7-0 单次读码时长
在感应识读模式下，该参数指在识读成功前允许识读模块持续进行采集识别的最大时长。
识读成功或单次读码超时后，识读模块将进入不采集识读的间隔期。单次读码时长设置范围为
0.1~25.5 秒，步长为0.1 秒。当设置为 0 时，表示读码时间无限长。默认时长为 5.0 秒。
-----------------------------------------------------*/

#define Addr_OutputMode 0x000D
/*---------------------------------------------------
标志位 0x000D
数据位 功能
Bit 7-4 保留
Bit 3-2 数据编码格式
00：GBK 01：UNICODE 10：BIG5 11：保留
Bit1-0 00：串口输出 01：USB PC 键盘 10：保留 11：USB 虚拟串口（保留）
-----------------------------------------------------*/
#define UART_Output 0x00
#define USB_Output 0x01

/*---------------------------------------------------
标志位 0x002B，0x2A
数据位 功能
Bit 15-13 保留
Bit 12-0 0x09C4：串口波特率为1200 bps
-----------------------------------------------------*/


/******************************************************************************
Barcode_Scanner
写标志位操作
对于设备标志位的写操作最多可一次写入 256 个字节的标志位。
命令格式：
输入：{Head1} {Types} {Lens} {Address} {Data} {CRC}
其中
Head1 ：0x7E 0x00（2 bytes）
Types ：0x08（1 byte）
Lens ：0x00~0xFF（1 byte），表示该命令中 Data 字段的字节数，同时也表示要
进行连续写操作的次数，而 0x00 表示有 256 个字节
Address ：0x0000~0xFFFF（2 bytes），表示要写入的标志位的起始地址
Data ：0x00~0xFF（1~256 bytes），表示写入标志位的数据
CRC ：CRC_CCITT 校验值（2 bytes）。计算的范围：Types、Lens、Address、Data
计算的方法为 CRC_CCITT，特征多项式：X16+X12+X5+1，即多项式系数为 0x1021，
初始值为全 0，对于单个字节来说最高位先计算，不需要取反直接输出。
*****************************************************************************/


/******************************************************************************
Barcode_Scanner
读标志位操作
对于设备标志位的读操作，最多可一次读取 256 个字节的标志位。
命令格式：
输入：{Head1} {Types} {Lens} {Address} {Data} {CRC}
其中 
Head1 ：0x7E 0x00（2 bytes）
Types ：0x07（1 byte）
Lens ：0x01（1 byte）
Address ：0x0000~0x00FF（2 bytes），表示要读取的标志位的起始地址。
Data ：0x00~0xFF（1 byte），表示要连续读取的标志位的字节数，0x00 表示 256
个字节。
CRC ：CRC_CCITT 校验值（2 bytes）。计算的范围：Types、Lens、Address、Data
计算的方法为 CRC_CCITT，特征多项式：X16+X12+X5+1，即多项式系数为 0x1021，
初始值为全 0，对于单个字节来说最高位先计算，不需要取反直接输出。

1） 读成功并返回读数据
其中Head2 ：0x02 0x00
Types ：0x00（读成功）
Lens ：表示上传的Data 的字节个数，0x00 表示256 个
Data ：0x00~0xFF，表示读上来的数据
CRC ：CRC_CCITT 校验值。计算的范围：Types、Lens、Data
*****************************************************************************/

// 定义TFmini_Plus测量变量
typedef struct {
   uint8 first[2];
   uint8 second[2];
   uint8 third[2];
   char  receiveComplete;
   uint8 Barcode_rec_data[15];
   uint8 Barcode_rec_num;
} BarcodeQRCode;

extern BarcodeQRCode getQRCode;

/************************************************************
 主函数初始化：
        void Barcode_uart_init(void);
 程序循环中调用：
        void Barcode_Scan_Command(void);//初始化getQRCode
        数据存储getQRCode.first  second  third
************************************************************/

void Barcode_uart_init(void);

//--------首次设置扫码模块功能，调用1次即可，也可以扫码设置------------
//基本功能设置（写），寄存器地址0x0000,参考功能#define Addr_Functions 0x0000 
void Barcode_Common_Setting(void);
//基本功能设置（写），寄存器地址0x000D，Bit1-0 00：串口输出 01：USB PC 键盘 10：保留 11：USB 虚拟串口（保留）
void Barcode_Set_Interface(void);
//基本功能设置（写），保存设置
void Barcode_SaveEEPROM(void);
//基本功能设置（读），寄存器地址0x002A 0x002B，查询波特率
void Barcode_Read_Baud(void);

/*注：在命令触发模式下，触发扫描的串口指令为：7E 00 08 01 00 02 01 AB CD；识读模
块收到触发指令后，会先输出七个字节的回应信息并同步启动扫描（回应信息内容：02 00 00 01 00 33 31）*/
void Barcode_Scan_Command(void);



#endif

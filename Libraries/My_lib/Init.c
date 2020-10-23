#include "headfile.h"

uint8 Init_Finish = 0;

uint8 CAR_Init()
{
  DisableInterrupts;
  get_clk();
  Moto_Init();          //电机初始化
  Screen_Init();        //屏幕初始化
  Sensor_Init();        //传感器初始化
  Parament_Init();      //参数初始化
  Task_Init();          //任务初始化  
  Get_S_Info_Init();    //从单片机数据串口初始化
  pit_init_ms(5);       //中断初始化
  set_irq_priority(FLEXCOMM0_IRQn,0);
  //总中断最后开启
  EnableInterrupts;
  //机械臂恢复初始姿态
  Robot_Position(POSItion.first.Start,POSItion.second.START,POSItion.third.START,POSItion.fourth.open,0);
  //等待OPS初始化完成（A8亮起）
  while(!Ops9.receiveComplete);
  //按键发车
  Task.STOP = 1;
  while(gpio_get(A13));
  Task.STOP = 0;
  return 1;
}

void Screen_Init()
{
#if  0 == SCREEN_Type
  oled_init();//OLED初始化
#else 
  lcd_init();//TFT初始化
#endif
}

void Sensor_Init()
{
  //按键初始化
  gpio_init(A13,GPI,1,NOPULL);
  //指示灯（OPS初始化完成后会亮起）
  gpio_init(A8,GPO,1,NOPULL);
  WS2812_init();
  //二维码扫描初始化
  Barcode_uart_init();
  //全平面定位系统初始化
  Ops9_uart_init();
  //OpenMv初始化
  OpenMV_uart_init();
  //机械臂初始化
  ServoMotor_uart_init();
  
//  //ESP8266主程序初始化程序初始化串口和
//  ESP8266_uart_init(); 
//  flag_ipconfig=0;  //若重新设置本地ip地址的话，设置flag_ipconfig=1；
//  do{
//    UDPLinkErr=ESP8266_wifista_UDP();   
//    UDPLinkNum++;
//  }while((UDPLinkErr)&&(UDPLinkNum<=2)); 
//  oled_p6x8str(10,5,"Esp_Ok");
}
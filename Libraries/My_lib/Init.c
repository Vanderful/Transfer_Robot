#include "headfile.h"

uint8 Init_Finish = 0;

uint8 CAR_Init()
{
  DisableInterrupts;
  get_clk();
  Moto_Init();          //�����ʼ��
  Screen_Init();        //��Ļ��ʼ��
  Sensor_Init();        //��������ʼ��
  Parament_Init();      //������ʼ��
  Task_Init();          //�����ʼ��  
  Get_S_Info_Init();    //�ӵ�Ƭ�����ݴ��ڳ�ʼ��
  pit_init_ms(5);       //�жϳ�ʼ��
  set_irq_priority(FLEXCOMM0_IRQn,0);
  //���ж������
  EnableInterrupts;
  //��е�ۻָ���ʼ��̬
  Robot_Position(POSItion.first.Start,POSItion.second.START,POSItion.third.START,POSItion.fourth.open,0);
  //�ȴ�OPS��ʼ����ɣ�A8����
  while(!Ops9.receiveComplete);
  //��������
  Task.STOP = 1;
  while(gpio_get(A13));
  Task.STOP = 0;
  return 1;
}

void Screen_Init()
{
#if  0 == SCREEN_Type
  oled_init();//OLED��ʼ��
#else 
  lcd_init();//TFT��ʼ��
#endif
}

void Sensor_Init()
{
  //������ʼ��
  gpio_init(A13,GPI,1,NOPULL);
  //ָʾ�ƣ�OPS��ʼ����ɺ������
  gpio_init(A8,GPO,1,NOPULL);
  WS2812_init();
  //��ά��ɨ���ʼ��
  Barcode_uart_init();
  //ȫƽ�涨λϵͳ��ʼ��
  Ops9_uart_init();
  //OpenMv��ʼ��
  OpenMV_uart_init();
  //��е�۳�ʼ��
  ServoMotor_uart_init();
  
//  //ESP8266�������ʼ�������ʼ�����ں�
//  ESP8266_uart_init(); 
//  flag_ipconfig=0;  //���������ñ���ip��ַ�Ļ�������flag_ipconfig=1��
//  do{
//    UDPLinkErr=ESP8266_wifista_UDP();   
//    UDPLinkNum++;
//  }while((UDPLinkErr)&&(UDPLinkNum<=2)); 
//  oled_p6x8str(10,5,"Esp_Ok");
}
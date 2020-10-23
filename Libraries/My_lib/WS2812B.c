#include "WS2812B.h"
/*
WS2812灯带的驱动方式有很多种，可以用GPIO,PWM,SPI
这里用的是GPIO,其他驱动方法请自行查阅
*/
LED_struct LED1;


void WS2812_init()
{
  LED1.pin = WS2812B_LED1;
  gpio_init(LED1.pin,GPO,0,NOPULL);
}

void ws2812_write_byte(uint8 dat, PIN_enum pin)
{
  uint8 i = 8;
  while(i --)
  {
    gpio_set(pin ,1);
    LOW_delay(0);
    if((dat & 0x80) == 0x80)
    {
      LOW_delay(10);
      gpio_set(pin ,0);
//      LOW_delay(0);
    }
    else
    {
      gpio_set(pin ,0);
      LOW_delay(10);
    }
    dat = dat << 1;
  }
}

//RT1064输入6就延时大约400纳秒
//LPC54606输入0就延时大约400纳秒
void LOW_delay(uint8 time)
{
  while(time--);
}

void LED_change_color(LED_struct led)
{
  uint8 i;
  for(i = 0; i < LED_num; i ++)
  {
    ws2812_write_byte(led.LED[i].G, led.pin);
    ws2812_write_byte(led.LED[i].R, led.pin);
    ws2812_write_byte(led.LED[i].B, led.pin);
  }
}

void Led_set(PIN_enum led, uint8 num, uint8 R, uint8 G, uint8 B)
{
  switch(led)
  {
  case WS2812B_LED1:
    LED1.LED[num - 1].R = R;
    LED1.LED[num - 1].G = G;
    LED1.LED[num - 1].B = B;
    break;
//  case WS2812B_LED2:
//    LED2.LED[num - 1].R = R;
//    LED2.LED[num - 1].G = G;
//    LED2.LED[num - 1].B = B;
//    break;
  }
}

//void LED_flow(LED_struct lednum,uint8 num, uint8 R, uint8 G, uint8 B)
//{
////  uint8 i;
////  for(i = LED_num; i > 0; i --)
////  {
////    lednum.LED[i].G = lednum.LED[i - 1].G;
////    lednum.LED[i].R = lednum.LED[i - 1].R;
////    lednum.LED[i].B = lednum.LED[i - 1].B;
////  }
//  lednum.LED[num].R = R;
//  lednum.LED[num].G = G;
//  lednum.LED[num].B = B;
//  
////  LED_change_color(lednum);
//}
#ifndef _WS2812B_
#define _WS2812B_

#include "headfile.h"

#define LED_num 3

typedef struct{
  uint8 R;
  uint8 G;
  uint8 B;
}Color_struct;

typedef struct{
  PIN_enum pin;
  Color_struct LED[LED_num];
}LED_struct;


extern LED_struct LED1, LED2;








void WS2812_init();
void ws2812_write_byte(uint8 dat, PIN_enum pin);
void LED_change_color(LED_struct LED);
void LOW_delay(uint8 time);
void LED_flow(LED_struct lednum,uint8 num, uint8 R, uint8 G, uint8 B);
void Led_set(PIN_enum led, uint8 num, uint8 R, uint8 G, uint8 B);





#endif
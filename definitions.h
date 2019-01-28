#pragma once
#include <stdint.h>

#define RED        (uint32_t)0xFF0000
#define GREEN      (uint32_t)0x00FF00
#define BLUE       (uint32_t)0x0000FF
#define MAGENTA    (uint32_t)0xFF00FF
#define PURPLE     (uint32_t)0x400080
#define ORANGE     (uint32_t)0xFF3000

enum Strip_Type { ESMD_STRIP, EWS28_STRIP };// Use E* prefix for enum
Strip_Type strip_type = EWS28_STRIP;

#define SMD_STRIP   0                       // 5050 SMD RGB DC 12V 
#define WS28_STRIP  1                       // WS2811/WS2812/WS2812b RGB DC 5V 
#define BUILTIN_LED 2                       // Build-in LED PIN on ESP8266
#define LED_PIN     14
#define LED_COUNT   30

enum StateMode { SET_COLOR, OFF, ON, BLINK };
StateMode s_mode = OFF;

enum SwitchMode { FADE, FLASH };
SwitchMode sw_mode = FADE;

enum TransitionPhase { SETCOLOR, TRANSITION };
TransitionPhase tr_phase = SETCOLOR;


struct rgb             
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
typedef struct rgb RGB;  

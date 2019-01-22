#pragma once
#include <stdint.h>


#define PIN 14
#define NUMLEDS 300

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

#pragma once
#include <stdint.h>

enum StateMode { SET_COLOR, OFF, ON, BLINK };
StateMode s_mode = OFF;

struct rgb             
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

typedef struct rgb RGB;  

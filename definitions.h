#pragma once
#include <stdint.h>

static enum { OFF, BLINK_OFF, BLINK_ON, ON } mode;

struct rgb             
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

typedef struct rgb RGB;
//RGB pin_color = { 0, 0, 0 };   

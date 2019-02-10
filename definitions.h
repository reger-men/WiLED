#pragma once
#include <stdint.h>

enum Strip_Type { ESMD_STRIP, EWS28_STRIP };// Use E* prefix for enum
Strip_Type strip_type = EWS28_STRIP;

#define SMD_STRIP   0                       // 5050 SMD RGB DC 12V. Set to 1 if you use SMD strip.
#define WS28_STRIP  1                       // WS2811/WS2812/WS2812b RGB DC 5V 
#define USE_ALEXA   1                       // Set to 1 if you want to use smart home  
#define ESPALEXA_MAXDEVICES 15
#define BUILTIN_LED 2                       // Build-in LED PIN on ESP8266

enum StateMode { OFF, ON, STATIC, DYNAMIC, BLINK, SET_MODE };
StateMode s_mode = OFF;

enum SwitchMode { FLASH, FADE };
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

RGB BLUE    = {0, 0, 255};
RGB PURPLE  = {185, 0, 255};
RGB RED     = {255, 0, 0};
RGB ORANGE  = {255, 112, 0};
RGB GOLD    = {255, 200, 0};


//////////////////////////////////////////////////////////////INCLUDE////////////////////////////////////////////////////////////////////////////////
#include <Espalexa.h>
Espalexa espalexa;

#include "model.h"
#include "model_factory.h"
#include "controller.h"
#include "webServer.h"
#include "uploadOTA.h"


//////////////////////////////////////////////////////////Globale Section/////////////////////////////////////////////////////////////////////////
Controller controller;
WebServer *wserver;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "alexa.h"

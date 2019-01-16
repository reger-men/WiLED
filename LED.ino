/*
  ESP8266 LED
*/
#include "definitions.h"
#include "model.h"
#include "controller.h"
#include "webServer.h"
#include "uploadOTA.h"
#include <WS2812FX.h>
WS2812FX strip = WS2812FX(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

//////////////////////////////////////////////////////////Globale Section/////////////////////////////////////////////////////////////////////////
Model model;
Controller controller; 
WebServer *wserver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //////////////////////////////////////////////////////////OTA and Server/////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("Booting");
  UploadOTA uploadOTA;

  model = Model();
  controller = Controller(model); 
  wserver = new WebServer(controller);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  Serial.println("LED initialization...");
  pinMode(2, OUTPUT);
  
  Serial.println("insert RGB values...");
  //controller.setDelay(5000);
  /*RGB pin_color = { 255, 0, 0 };
  controller.insertRGB(pin_color);*/

  uint16_t i;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 255);
  }
  strip.show();
  
  printf(".............\n");
}


// The loop function runs over and over again forever
void loop() {
  wserver->serverListener();                                // Start the listener  
  wserver->webSocketListener();                             // Constantly check for websocket events
  ArduinoOTA.handle();                                      // Listen for OTA events
  
  if (s_mode == SET_COLOR) {
    controller.runQueue();
  }

}

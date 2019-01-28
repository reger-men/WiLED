/*
  ESP8266 LED
*/
#include "definitions.h"
#include "model.h"
#include "model_factory.h"
#include "controller.h"
#include "webServer.h"
#include "uploadOTA.h"


//////////////////////////////////////////////////////////Globale Section/////////////////////////////////////////////////////////////////////////
Controller controller; 
WebServer *wserver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //////////////////////////////////////////////////////////OTA and Server/////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("Booting");
  UploadOTA uploadOTA;

  //////////////////////////////////////////////////////////MVC & Factory /////////////////////////////////////////////////////////////////////////
  Model_Factory model_factory;
  Model *model  = model_factory.create(strip_type);
  
  controller    = Controller(model); 
  wserver       = new WebServer(controller);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  Serial.println("LED initialization...");
  pinMode(2, OUTPUT);
    
  //Serial.println("insert RGB values...");
  //controller.setDelay(5000);
  /*RGB pin_color = { 255, 0, 0 };
  controller.insertRGB(pin_color);*/
  printf(".............\n");
}


// The loop function runs over and over again forever
void loop() {
  wserver->serverListener();                                // Start the listener  
  wserver->webSocketListener();                             // Constantly check for websocket events
  ArduinoOTA.handle();                                      // Listen for OTA events

  if(strip_type == EWS28_STRIP){                            // Continually run the animation service for WS28xx strip
    controller.runModelService();
  }
  
  if (s_mode == SET_COLOR) {
    controller.runQueue();
  }
}

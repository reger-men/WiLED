/*
  ESP8266 LED
*/
#include "uploadOTA.h"
#include "controller.h"
#include "webServer.h"


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

  
  model = Model("MyName1");
  controller = Controller(model); 
  wserver = new WebServer(controller);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  Serial.println("LED initialization...");
  pinMode(2, OUTPUT);
  
  Serial.println("insert RGB values...");
  RGB pin_color = { 125, 25, 48 };
  controller.insertRGB(pin_color);
}


// the loop function runs over and over again forever
void loop() {
  wserver->serverListener();                                // Start the listener  
  wserver->webSocketListener();                             // Constantly check for websocket events
  ArduinoOTA.handle();                                      // Listen for OTA events
  
}

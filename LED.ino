/*
  ESP8266 LED
*/
#include "uploadOTA.h"
#include "controller.h"
#include "webServer.h"


//////////////////////////////////////////////////////////XXX/////////////////////////////////////////////////////////////////////////
/*Model model("MyName1");
Controller controller(model); 
WebServer *wserver;*/

Model model;
Controller controller;
WebServer *wserver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //////////////////////////////////////////////////////////OTA and Server/////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("Booting");
  UploadOTA uploadOTA;

  printf("Model name1: %s\n", model._name.c_str());
  printf("Model adress1: %p\n", &model);
  model = Model("MyName1");
  printf("Model name1: %s\n", model._name.c_str());
  printf("Model adress1: %p\n", &model);

  printf("Controller adress1: %p\n", &controller);
  controller = Controller(model); 
  printf("Controller adress1: %p\n", &controller);

  printf("WebServer adress1: %p\n", &wserver);
  printf("server adress1: %p\n", &wserver->server);
  wserver = new WebServer(controller);
  printf("WebServer adress1: %p\n", &wserver->server);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  Serial.println("LED initialization...");
  pinMode(2, OUTPUT);
  
  Serial.println("insert RGB values...");
  RGB pin_color = { 125, 25, 48 };
  controller.insertRGB(pin_color);
}


// the loop function runs over and over again forever
void loop() {
  wserver->listener(); // run the server  
  wserver->webSocket.loop();                           // constantly check for websocket events
  ArduinoOTA.handle();                        // listen for OTA events
  
  /*for(int i=0; i<=10; i++){
    controller.runQueue();
    delay(2000);
  }*/
}

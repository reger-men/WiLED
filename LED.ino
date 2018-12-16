/*
  ESP8266 LED
*/

#include "definitions.h"
#include "controller.h"
#include "uploadOTA.h"
#include "webServer.h"


//////////////////////////////////////////////////////////Server/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Model model;
Controller controller(model);  

void setup() {
  //////////////////////////////////////////////////////////OTA and Server/////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("Booting");
  UploadOTA uploadOTA;
  WebServer server();
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  Serial.println("LED initialization...");
  pinMode(2, OUTPUT);
  
  Serial.println("insert RGB values...");
  controller.insertRGB(std::make_tuple (243, 320,852));
  controller.insertRGB(std::make_tuple (1043, 20,252));
  controller.insertRGB(std::make_tuple (43, 1020,952));
  controller.insertRGB(std::make_tuple (546, 920,252));
  controller.insertRGB(std::make_tuple (742, 823,41));
  controller.insertRGB(std::make_tuple (178, 23,777));
}


// the loop function runs over and over again forever
void loop() {
  webSocket.loop();                           // constantly check for websocket events
  server.handleClient();                      // run the server
  ArduinoOTA.handle();                        // listen for OTA events

  
  
  /*for(int i=0; i<=10; i++){
    controller.runQueue();
    delay(2000);
  }*/
}

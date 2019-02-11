/*
  ESP8266 LED
*/
#include "src/definitions.h"

void setup() {
  ////////////////////////////////////////////////////////// OTA and Server////////////////////////////////////////////////////////////////////////
  Serial.begin(115200);
  Serial.println("Booting...");
  UploadOTA uploadOTA;

  ////////////////////////////////////////////////////////// MVC & Factory ////////////////////////////////////////////////////////////////////////
  Model_Factory model_factory;
  Model *model  = model_factory.create(strip_type);

  controller    = Controller(model);
  wserver       = new WebServer(controller);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Serial.println("LED initialization...");
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  ////////////////////////////////////////////////////////// ALEXA ////////////////////////////////////////////////////////////////////////////////
#ifdef USE_ALEXA
  // Add your alexa virtual devices giving them a name and associated callback
  adddevices();
  espalexa.begin(&wserver->server); // Give alexa a pointer to server object so it can use server instead of creating its own
#endif
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  printf(".............\n");
}


// The loop function runs over and over again forever
void loop() {
  
#ifdef USE_ALEXA
  espalexa.loop();                                          // Start server
#else
  wserver->serverListener();                                // Omit this if USE_ALEXA 1
#endif

  wserver->webSocketListener();                             // Constantly check for websocket events
  ArduinoOTA.handle();                                      // Listen for OTA events

  if (strip_type == EWS28_STRIP) {                          // Continually run the animation service for WS28xx strip
    controller.runModelService();
  }

  controller.run();
}

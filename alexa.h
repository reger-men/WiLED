#pragma once

void onCallback(uint8_t brightness) {
    if (brightness == 255) {
      controller.on();
    }
    else if (brightness == 0) {
      controller.off();
    }
    else {
      controller.setBrightness(brightness);
    }
}

void offCallback(uint8_t brightness) {
    controller.off();
}

void checkOff(uint8_t brightness)
{
  if (brightness == 0) {
      controller.off();
    }
}

void ownFadeCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(-2);
  checkOff(brightness);
}

void blinkCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(1);
  checkOff(brightness);
}

void colorWipeRandomCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(7);
  checkOff(brightness);
}

void multiDynamicCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(10);
  checkOff(brightness);
}

void RainbowCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(11);
  checkOff(brightness);
}

void rainbowCycleCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(12);
  checkOff(brightness);
}

void dualScanCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(14);
  checkOff(brightness);
}

void twinkleRandomCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(20);
  checkOff(brightness);
}

void chaseWhiteCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(30);
  checkOff(brightness);
}

void chaseRainbowCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(33);
  checkOff(brightness);
}

void chaseBlackoutRainbowCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(37);
  checkOff(brightness);
}

void larsonScannerCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(42);
  checkOff(brightness);
}

void fireworksRandomCallback(uint8_t brightness) {
  controller.setBrightness(brightness);
  controller.updateMode(45);
  checkOff(brightness);
}


void adddevices()
{
  espalexa.addDevice("Light An", onCallback);
  espalexa.addDevice("Light Aus", offCallback);
  espalexa.addDevice("Light Fade", ownFadeCallback);
  espalexa.addDevice("Light Blink", blinkCallback);
  espalexa.addDevice("Light Wipe", colorWipeRandomCallback);
  espalexa.addDevice("Light Multi", multiDynamicCallback);
  espalexa.addDevice("Light Rainbow", RainbowCallback);
  espalexa.addDevice("Light Rainbow Cycle", rainbowCycleCallback);
  espalexa.addDevice("Light Dual Scan", dualScanCallback);
  espalexa.addDevice("Light Twinkle", twinkleRandomCallback);
  espalexa.addDevice("Light Chase White", chaseWhiteCallback);
  espalexa.addDevice("Light Chase Rainbow", chaseRainbowCallback);
  espalexa.addDevice("Light Chase Blackout", chaseBlackoutRainbowCallback);
  espalexa.addDevice("Light Larson", larsonScannerCallback);
  espalexa.addDevice("Light Firework", fireworksRandomCallback);
}

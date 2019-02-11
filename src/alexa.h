#pragma once

bool checkIsOff(uint8_t brightness)
{
  if (brightness == 0) {
      return true;
  }
  return false;
}

void onCallback(uint8_t brightness) {
    if (!checkIsOff(brightness)) {
      controller.setBrightness(brightness);
      controller.on();
    }
    else {
      controller.off();
    }
}

void ownFadeCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(-2);
  }else{
    controller.off();
  }
}

void blinkCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(1);
  }else{
    controller.off();
  }
}

void colorWipeRandomCallback(uint8_t brightness) {
  if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(7);
  }else{
    controller.off();
  }
}

void multiDynamicCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(10);
  }else{
    controller.off();
  }
}

void RainbowCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(11);
  }else{
    controller.off();
  }
}

void rainbowCycleCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(12);
  }else{
    controller.off();
  }
}

void dualScanCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(14);
  }else{
    controller.off();
  }
}

void twinkleRandomCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(20);
  }else{
    controller.off();
  }
}

void chaseWhiteCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(30);
  }else{
    controller.off();
  }
}

void chaseRainbowCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(33);
  }else{
    controller.off();
  }
}

void chaseBlackoutRainbowCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(37);
  }else{
    controller.off();
  }
}

void runningRandomCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(42);
  }else{
    controller.off();
  }
}

void larsonScannerCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(43);
  }else{
    controller.off();
  }
}

void fireworksRandomCallback(uint8_t brightness) {
if (!checkIsOff(brightness)) {
    controller.on();
    controller.setBrightness(brightness);
    controller.updateMode(45);
  }else{
    controller.off();
  }
}


void adddevices()
{
  espalexa.addDevice("Light",     onCallback);
  espalexa.addDevice("Light 1",   ownFadeCallback);
  espalexa.addDevice("Light 2",   blinkCallback);
  espalexa.addDevice("Light 3",   colorWipeRandomCallback);
  espalexa.addDevice("Light 4",   multiDynamicCallback);
  espalexa.addDevice("Light 5",   RainbowCallback);
  espalexa.addDevice("Light 6",   rainbowCycleCallback);
  espalexa.addDevice("Light 7",   dualScanCallback);
  espalexa.addDevice("Light 8",   twinkleRandomCallback);
  espalexa.addDevice("Light 9",   chaseWhiteCallback);
  espalexa.addDevice("Light 10",  chaseRainbowCallback);
  espalexa.addDevice("Light 11",  chaseBlackoutRainbowCallback);
  espalexa.addDevice("Light 13",  runningRandomCallback);
  espalexa.addDevice("Light 14",  larsonScannerCallback);
  espalexa.addDevice("Light 15",  fireworksRandomCallback);
}

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

void ownFadeCallback(uint8_t brightness) {
  onCallback(brightness);
  controller.setBrightness(brightness);
  controller.updateMode(-2);
}

void ownFlashCallback(uint8_t brightness) {
  onCallback(brightness);
  controller.setBrightness(brightness);
  controller.updateMode(-1);
}

void staticCallback(uint8_t brightness) {
  onCallback(brightness);
  controller.setBrightness(brightness);
  controller.updateMode(0);
}

void blinkCallback(uint8_t brightness) {
  onCallback(brightness);
  controller.setBrightness(brightness);
  controller.updateMode(1);
}

void breathCallback(uint8_t brightness) {
  onCallback(brightness);
  controller.setBrightness(brightness);
  controller.updateMode(2);
}

void colorWipeCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(3);
}

void colorWipeInverseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(4);
}

void colorWipeReverseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(5);
}

void colorWipeReverseInverseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(6);
}

void colorWipeRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(7);
}

void randomColorCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(8);
}

void singleDynamicCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(9);
}

void multiDynamicCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(10);
}

void RainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(11);
}


void rainbowCycleCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(12);
}

void ScanCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(13);
}

void dualScanCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(14);
}

void fadeCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(15);
}

void theaterChaseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(16);
}

void theaterChaseRainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(17);
}

void runningLightsCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(18);
}

void twinkleCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(19);
}

void twinkleRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(20);
}

void twinkleFadeCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(21);
}

void twinkleFadeRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(22);
}

void SparkleCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(23);
}

void flashSparkleCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(24);
}

void hyperSparkleCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(25);
}

void strobeCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(26);
}

void strobeRainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(27);
}

void multiStrobeCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(28);
}

void blinkRainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(29);
}

void chaseWhiteCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(30);
}


void chaseColorCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(31);
}

void chaseRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(32);
}

void chaseRainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(33);
}

void chaseFlashCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(34);
}

void chaseFlashRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(35);
}

void chaseRainbowWhiteCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(30);
}

void chaseBlackoutCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(36);
}

void chaseBlackoutRainbowCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(37);
}

void colorSweepRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(38);
}

void runningColorCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(39);
}

void runningRedBlueCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(40);
}

void runningRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(41);
}

void larsonScannerCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(42);
}

void cometCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(43);
}

void fireworksCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(44);
}

void fireworksRandomCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(45);
}

void merryChristmasCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(46);
}

void fireFlickerCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(47);
}

void fireFlickerSoftCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(48);
}

void fireFlickerIntenseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(49);
}

void circusCombustusCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(50);
}

void halloweenCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(51);
}

void bicolorChaseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(52);
}

void tricolorChaseCallback(uint8_t brightness) {
  controller.on();
  controller.setBrightness(brightness);
  controller.updateMode(53);
}



void adddevices()
{
  espalexa.addDevice("LED ON", onCallback);
  
  espalexa.addDevice("mode 0", ownFadeCallback);
  espalexa.addDevice("mode 1", ownFlashCallback);
  espalexa.addDevice("mode 2", staticCallback);
  /*espalexa.addDevice("mode 3", blinkCallback);
  espalexa.addDevice("mode 4", breathCallback);
  espalexa.addDevice("mode 5", colorWipeCallback);
  espalexa.addDevice("mode 6", colorWipeInverseCallback);
  espalexa.addDevice("mode 7", colorWipeReverseCallback);
  espalexa.addDevice("mode 8", colorWipeReverseInverseCallback);
  espalexa.addDevice("mode 9", colorWipeRandomCallback);
  espalexa.addDevice("mode 10", randomColorCallback);
  espalexa.addDevice("mode 11", singleDynamicCallback);
  espalexa.addDevice("mode 12", multiDynamicCallback);
  espalexa.addDevice("mode 13", RainbowCallback);
  espalexa.addDevice("mode 14", rainbowCycleCallback);
  espalexa.addDevice("mode 15", ScanCallback);
  espalexa.addDevice("mode 16", dualScanCallback);
  espalexa.addDevice("mode 17", fadeCallback);
  espalexa.addDevice("mode 18", theaterChaseCallback);
  espalexa.addDevice("mode 19", theaterChaseRainbowCallback);
  espalexa.addDevice("mode 20", runningLightsCallback);
  espalexa.addDevice("mode 21", twinkleCallback);
  espalexa.addDevice("mode 22", twinkleRandomCallback);
  espalexa.addDevice("mode 23", twinkleFadeCallback);
  espalexa.addDevice("mode 24", twinkleFadeRandomCallback);
  espalexa.addDevice("mode 25", SparkleCallback);
  espalexa.addDevice("mode 26", flashSparkleCallback);
  espalexa.addDevice("mode 27", hyperSparkleCallback);
  espalexa.addDevice("mode 28", strobeCallback);
  espalexa.addDevice("mode 29", strobeRainbowCallback);
  espalexa.addDevice("mode 30", multiStrobeCallback);
  espalexa.addDevice("mode 31", blinkRainbowCallback);
  espalexa.addDevice("mode 32", chaseWhiteCallback);
  espalexa.addDevice("mode 33", chaseColorCallback);
  espalexa.addDevice("mode 34", chaseRandomCallback);
  espalexa.addDevice("mode 35", chaseRainbowCallback);
  espalexa.addDevice("mode 36", chaseFlashCallback);
  espalexa.addDevice("mode 37", chaseFlashRandomCallback);
  espalexa.addDevice("mode 38", chaseRainbowWhiteCallback);
  espalexa.addDevice("mode 39", chaseBlackoutCallback);
  espalexa.addDevice("mode 40", chaseBlackoutRainbowCallback);
  espalexa.addDevice("mode 41", colorSweepRandomCallback);
  espalexa.addDevice("mode 42", runningColorCallback);
  espalexa.addDevice("mode 43", runningRedBlueCallback);
  espalexa.addDevice("mode 44", runningRandomCallback);
  espalexa.addDevice("mode 45", larsonScannerCallback);
  espalexa.addDevice("mode 46", cometCallback);
  espalexa.addDevice("mode 47", fireworksCallback);
  espalexa.addDevice("mode 48", fireworksRandomCallback);
  espalexa.addDevice("mode 49", merryChristmasCallback);
  espalexa.addDevice("mode 50", fireFlickerCallback);
  espalexa.addDevice("mode 51", fireFlickerSoftCallback);
  espalexa.addDevice("mode 52", fireFlickerIntenseCallback);
  espalexa.addDevice("mode 53", circusCombustusCallback);
  espalexa.addDevice("mode 54", halloweenCallback);
  espalexa.addDevice("mode 55", bicolorChaseCallback);
  espalexa.addDevice("mode 56", tricolorChaseCallback);*/
}

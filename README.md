# ![WiLED Logo](https://raw.githubusercontent.com/reger-men/WiLED/master/web_src/logo.png) 
WiLED is an Open Source project to control various types of LED strips with ESP8266. 5050 SMD and WS28xx LED strips are supported.

## How to install ##
**IMPORTANT:** Download the latest release version (ZIP file) from [HERE](https://github.com/reger-men/WiLED/releases) and upload the binary file or compile the source code.

[![WiLED on youtube](https://raw.githubusercontent.com/reger-men/WiLED/master/web_src/view.PNG)](https://www.youtube.com/watch?v=cLCZFH-E9To)

Click on the image above to watch the video.

## Building from Source ## 
* Install Arduino IDE
 * Install driver for ESP8266 [https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)
 * Install plugin for ESP8266 Sketch Data Upload [https://github.com/esp8266/arduino-esp8266fs-plugin](https://github.com/esp8266/arduino-esp8266fs-plugin)
 * Install [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel), [Espalexa](https://github.com/Aircoookie/Espalexa), [WebSockets](https://github.com/Links2004/arduinoWebSockets), [WifiManager](https://github.com/tzapu/WiFiManager) and [WS2812FX](https://github.com/kitesurfer1404/WS2812FX) Libraries
  
## Upload the pre-compiled  binary ##
Download the latest release version [**WiLED.ino.nodemcu.bin**](https://github.com/reger-men/WiLED/releases) and use [ESPTool](https://github.com/espressif/esptool) or [ESPFlashDownloadTool](https://www.espressif.com/en/support/download/other-tools) to upload the binary to ESP8266.


## Features ##
User ...
* ... doesn't need to install any app to controlle the LED strip
* ... can controlle the LED strip via Webinterface or via Alexa
* ... Alexa can detect this skill as multiple devices, you may include the number of devices by increase this line ```#define ESPALEXA_MAXDEVICES 15``` in ```definitions.h```
* ... to invoke custom Skills, use:
  * ``` Alexa turn light on```
  * ``` Alexa turn light 1 on```
  * ``` Alexa turn light off```
* ... can upload new file from within a Web browser without having to connect to the ESP8266 over USB
  *  ``` http://esp8266.local/update``` 
* ... may load the firmware to ESP module using Wi-Fi connection **OTA (Over the Air)**
  
  
## Adaption ##
To controle SMD or WS28xx LED strips you need to set ``` #define SMD_STRIP   1 ``` or ``` #define WS28_STRIP  1 ``` in ```definitions.h```
Make sure that you set only one to ``` 1``` and the other one to ``` 0``` 

If you don't want to use Alexa set ``` #define USE_ALEXA   0 ```

## Wiring ## 
![Wiring](https://raw.githubusercontent.com/reger-men/WiLED/master/web_src/wiring.png) 

## Things you need (Shopping Cart) ## 
[ESP82666](https://www.amazon.com/AZDelivery-Nodemcu-Module-ESP8266-Development/dp/B07F8759RC/ref=sr_1_2?keywords=esp8266&qid=1549978307&s=gateway&sr=8-2)

[5050 SMD](https://www.amazon.com/SUPERNIGHT-Changing-Non-waterproof-Flexible-Decoration/dp/B00E0EVHYA/ref=sr_1_3_sspa?keywords=rgb+led+strip&qid=1549978486&s=gateway&sr=8-3-spons&psc=1&smid=AXEJGN8WLZD9M) or [WS28xx](https://www.amazon.com/BTF-LIGHTING-Flexible-Individually-Addressable-Non-waterproof/dp/B01CDTEJBG/ref=sr_1_1_sspa?keywords=ws2812b&qid=1549978517&s=gateway&sr=8-1-spons&psc=1)

(Optional) [Alexa echo or any other version](https://www.amazon.de/dp/B01DFKBG5E/ref=asc_df_B01DFKBG5E58466726/?tag=googshopde-21&creative=22398&creativeASIN=B01DFKBG5E&linkCode=df0&hvadid=204288091658&hvpos=1o3&hvnetw=g&hvrand=8361400114568144756&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9044401&hvtargid=pla-329799024896&th=1&psc=1)

#pragma once
#include <Arduino.h>
#include <queue>
#include <WS2812FX.h>

// Only the Model has the access to the LED strip
class WS28_Model : public Model{
    public:     
        WS28_Model()
        {
			    printf("WS28: Initialize the pins as an output...\n");
          this->stripModel = EWS28_STRIP;
          
			    this->strip = new WS2812FX(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
          this->strip->init();
          this->strip->setBrightness(brightness_);
          this->strip->setSpeed(delay_);
          this->strip->setColor(0x007BFF);
          this->strip->setMode(FX_MODE_STATIC);
          this->strip->start();

    			// Initialize the pins values  
    			this->off();  
        }

        void runService()
        {
          this->strip->service();
        }
        
        void setRGB(RGB rgb)
        { 
    			//Set the new RGB Values
    			printf("Set RGB in EWS28_STRIP\n");
    			strip->setColor(rgb.r, rgb.g, rgb.b);
          strip->trigger();
                  
    			this->prev_color_ = rgb;
    			printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
        }
        
        void on() 
        { 
			    strip->setColor(255, 255, 255);
        }
        
        void off() 
        { 
			    if(strip->isRunning()) strip->stop();
        }

        void applyQueue(SwitchMode sw_mode = FADE)
        {
          printf("WS28: Set RGB");
          RGB tmp = {0,0,0}; RGB rgb = {0,0,0};
          tmp = this->pullFromQueue();                          //Get the first item from the queue
          this->setRGB(tmp);                                    //Set the RGB Value 
          this->shiftQueue();                                   //Shift the queue to update the items order
          delay(delay_);
        }

      
    private:
		  RGB prev_color_                   = {0,0,0};                  // Store the preview color
		  unsigned long delay_              = 1000;                     // Steps the delay value for one color
		  uint8_t brightness_               = 30;                       // Store the brightness value
      WS2812FX *strip = nullptr;
};

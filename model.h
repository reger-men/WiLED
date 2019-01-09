#pragma once
#include "definitions.h"
#include <Arduino.h>
#include <tuple>
#include <queue>

// Only the Model has the access to the LED
class Model {
    public:
        
        Model();  // default constructor
        void setRGB(RGB rgb);
        void pushInQueue(RGB rgb);
        RGB pullFromQueue();
        
        void shiftQueue();
        void applyQueue();
        
        void On();
        void Off();

    private:
      //LED Pins
      static const int kRedPin   = 12;
      static const int kGreenPin = 13;
      static const int kBluePin  = 14;
      std::queue<RGB> RGBQueue;
      
};

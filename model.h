#pragma once
#include <Arduino.h>
#include <tuple>
#include <queue>

// Only the Model has the access to the LED
class Model {
    public:
        
        Model();  // default constructor
        void setRGB(std::tuple <int, int, int> RGB);
        void pushInQueue(std::tuple <int, int, int> RGB);
        std::tuple <int, int, int> pullFromQueue();
        
        void shiftQueue();
        void applyQueue();
        
        void On();
        void Off();

    private:
      //LED Pins
      static const int kRedPin   = 12;
      static const int kGreenPin = 13;
      static const int kBluePin  = 14;
      std::tuple <int, int, int> RGB {0,0,0}; 
      std::queue<std::tuple <int, int, int>> RGBQueue;
      
};

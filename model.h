#pragma once

#include <Arduino.h>
#include <queue>

// Only the Model has the access to the LED strip
class Model {
    public:
        // default constructor
        Model()
        {
          printf("Initialize the pins as an output...\n");
          pinMode(kRedPin,    OUTPUT);     
          pinMode(kGreenPin,  OUTPUT);
          pinMode(kBluePin,   OUTPUT);
        
          // Initialize the pins values  
          this->Off();                          
        }

        void setRGB(RGB rgb) 
        { 
          digitalWrite(kRedPin,   ((rgb.r)/100));                 
          digitalWrite(kGreenPin, ((rgb.g)/100));                            
          digitalWrite(kBluePin,  ((rgb.b)/100));
        }
        
        void On() 
        { 
          digitalWrite(kRedPin,   1);                             
          digitalWrite(kGreenPin, 1);                             
          digitalWrite(kBluePin,  1);
        }
        
        void Off() 
        { 
          digitalWrite(kRedPin,   0);                             
          digitalWrite(kGreenPin, 0);                             
          digitalWrite(kBluePin,  0);
        }
        
        void pushInQueue(RGB rgb)
        {
          RGBQueue.push(rgb);
          printf("Size: %i\n", RGBQueue.size());
        }
        
        RGB pullFromQueue()
        {
          return RGBQueue.front(); //Get next element
        }
        
        void shiftQueue()
        {
          RGB front = this->pullFromQueue();
          RGBQueue.pop(); //Remove next element
          this->pushInQueue(front);
        }
        
        void setDelay(int sec)
        {
          this->delay_ = sec;
        }
        
        void applyQueue()
        {
          printf("Huu from model...\n");
          RGB tmp = this->pullFromQueue();
          this->setRGB(tmp);
          this->shiftQueue();
          delay(this->delay_);
        }
        
    private:
      //LED Pins
      static const int kRedPin   = 12;
      static const int kGreenPin = 13;
      static const int kBluePin  = 14;
      std::queue<RGB> RGBQueue;
      int delay_ = 1000;
      
};

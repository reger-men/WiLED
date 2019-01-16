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
          //Set the new RGB Values
          analogWrite(kRedPin,   rgb.r);                 
          analogWrite(kGreenPin, rgb.g);                            
          analogWrite(kBluePin,  rgb.b);
          
          
          this->prev_color = rgb;
          printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
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

        void clearQueue() 
        {
          std::queue<RGB> empty;
          std::swap( this->RGBQueue, empty );                     // Clear the RGB queue
        }
        
        void pushInQueue(RGB rgb)
        {
          this->RGBQueue.push(rgb);
        }
        
        RGB pullFromQueue()
        {
          return RGBQueue.front();                                //Get next element
        }
        
        void shiftQueue()
        {
          RGB front = this->pullFromQueue();
          RGBQueue.pop(); //Remove next element
          this->pushInQueue(front);
        }
        
        void setDelay(int sec)
        {
          //Compute the transition period
          this->switchColorDelay = (sec * TRANSITION_PART);
          this->transitionSteps = (int)((this->switchColorDelay*2)/this->TRANSITION_DELAY);
          this->delay_ = sec - this->switchColorDelay;
        }

        int getNextColor(int prev_queue, int prev, int next){
          float ret = 0;
          
          if(prev > next){
            ret = floor(prev - ((float)(prev_queue-next)/(float)this->transitionSteps));
          }else{
            ret = ceil(prev + ((float)(next-prev_queue)/(float)this->transitionSteps));
          }
          int min_value = min(prev_queue, next);
          int max_value = max(prev_queue, next);
          
          ret = (ret < min_value)? min_value: ret;
          ret = (ret > max_value)? max_value: ret;
          
          return (int)ret;
        }

        // Update Transistion Phase
        void updateTransistionPhase()
        {
          unsigned long currentMillis = millis(); 
          unsigned long period = currentMillis - previousMillis; 
          
          if ((period >= this->delay_) and (period <= this->delay_ + (this->switchColorDelay*2))){ // Transition period
            tr_phase = TRANSITION;
          }
          if(period > this->delay_ + (this->switchColorDelay*2)){ //End transition
            previousMillis = currentMillis;                       //Rest timer
            tr_phase = SETCOLOR;
          }
        }

        
        void applyQueue(SwitchMode sw_mode = FADE)
        {        
          RGB tmp = {0,0,0}; RGB rgb = {0,0,0};
          updateTransistionPhase();                               // Update Transistion Phase
          
          
          switch (tr_phase) {
            case SETCOLOR:
              tmp = this->pullFromQueue();                        //Get the first item from the queue
              this->setRGB(tmp);                                  //Set the RGB Value 
              this->shiftQueue();                                 //Shift the queue to update the items order
              
              prev_queue_color = tmp;                             //Set the Current Color to prev
              this->current_step = 0;
              delay(this->delay_);
              break;
            case TRANSITION:
              
              rgb = this->pullFromQueue();
              tmp.r = getNextColor(prev_queue_color.r, prev_color.r, rgb.r); 
              tmp.g = getNextColor(prev_queue_color.g, prev_color.g, rgb.g); 
              tmp.b = getNextColor(prev_queue_color.b, prev_color.b, rgb.b);
                            
              this->setRGB(tmp);                                //Set the RGB Value 
              
              this->current_step = min(this->current_step+1, this->transitionSteps);      

              delay(this->TRANSITION_DELAY);
              break;
            default:
            
              break;
          }
        }

      
    private:
      //LED Pins
      static const int kRedPin   = 12;
      static const int kGreenPin = 13;
      static const int kBluePin  = 14;
      std::queue<RGB> RGBQueue;
      
      
      RGB prev_color             = {0,0,0};                     // Store the preview color
      RGB prev_queue_color       = {0,0,0};                     // Store the preview color from queue
      int current_step = 0;
      
      unsigned long switchColorDelay  = 0;
      unsigned long previousMillis    = 0;
      
      float TRANSITION_PART     = 0.4f;                         //Set the transition part as 20 percent
      uint8_t TRANSITION_DELAY  = 20;                           //Set the transition time (ms)
      int transitionSteps       = 0;                            //Steps number for one transition
      unsigned long delay_      = 1000;
};

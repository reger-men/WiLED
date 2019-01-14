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
          digitalWrite(kRedPin,   ((rgb.r)/100));                 
          digitalWrite(kGreenPin, ((rgb.g)/100));                            
          digitalWrite(kBluePin,  ((rgb.b)/100));
          
          //Set the Current Color to prev
          prev_color = rgb;

          printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
          printf("delay_: %i\n", this->delay_);
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
          //Compute the transition period
          this->switchColorDelay = (sec * TRANSITION_PART);
          this->transitionSteps = (int)((this->switchColorDelay*2)/this->SWITCH_DELAY);
          this->delay_ = sec - this->switchColorDelay;
        }
        
        void applyQueue(SwitchMode sw_mode = FADE)
        {
          
          

          unsigned long currentMillis = millis(); 
         // How much time has passed, accounting for rollover with subtraction!
         if ((unsigned long)(currentMillis - previousMillis) >= 2400) {
            // It's time to do something!
            printf("transitionTimer: %i\n", currentMillis);
       
            // Use the snapshot to set track time until next event
            previousMillis = currentMillis;
         }
   
          /*if ((transitionTimer >= this->delay_) and (transitionTimer < this->delay_ + (this->switchColorDelay*2))){ // Transition period
            tr_phase = TRANSITION;
            printf("transitionTimer1: %i\n", transitionTimer);
          }
          if(transitionTimer > this->delay_ + (this->switchColorDelay*2)){ //End transition
            transitionTimer = this->switchColorDelay; //Rest timer
            tr_phase = SETCOLOR;
            printf("transitionTimer2: %i\n", transitionTimer);
          }
          
          
          RGB tmp;
          switch (tr_phase) {
            case SETCOLOR:
              tmp = this->pullFromQueue();    //Get the first item from the queue
              this->setRGB(tmp);                  //Set the RGB Value 
              this->shiftQueue();                 //Shift the queue to update the items order
              delay(this->delay_);
              break;
            case TRANSITION:
              tmp = {0,0,0};
              this->setRGB(tmp);                  //Set the RGB Value 
              delay(this->SWITCH_DELAY);
              break;
            default:
              int z = 98;
              break;
          }*/

          
          
          
          /*switch (sw_mode) {
              case FADE:
                printf("prev_color.g Value: %i\n", prev_color.g);
                
                tmp = rgb;
                //tmp.r = (prev_color.r > rgb.r)? rgb.r + (prev_color.r - rgb.r)/this->transitionSteps : rgb.r - (rgb.r - prev_color.r)/this->transitionSteps;
                //tmp.g = (prev_color.g > rgb.g)? rgb.g + (prev_color.g - rgb.g)/this->transitionSteps : rgb.g - (rgb.g - prev_color.g)/this->transitionSteps;
                //tmp.b = (prev_color.b > rgb.b)? rgb.b + (prev_color.b - rgb.b)/this->transitionSteps : rgb.b - (rgb.b - prev_color.b)/this->transitionSteps;

                
                
                printf("rgb.g Value: %i\n", rgb.g);
                printf("tmp.g Value: %i\n", tmp.g);
                
                rgb = tmp;
                break;
              case FLASH:
                // statements
                break;
              default:
                if(RGB tmp = this->pullFromQueue(); //Get the first item from the queue
                this->setRGB(tmp);                  //Set the RGB Value 
                this->shiftQueue();                 //Shift the queue to update the items order
                break;
          }
          delay(this->SWITCH_DELAY);*/
          /*RGB tmp = this->pullFromQueue(); //Get the first item from the queue
          this->setRGB(tmp);                  //Set the RGB Value 
          this->shiftQueue();                 //Shift the queue to update the items order
          delay(50);*/
        }

        int getStep(int srcRGB, int dstRGB) {
          int step = dstRGB - srcRGB; 
          if (step) {                      
            step = 1020/step;              
          } 
          return step;
        }

        int getNewValue(int stp, int value, int i) {
          if ((stp) && i % stp == 0) { // If step is non-zero and its time to change a value,
            if (stp > 0) {              //   increment the value if step is positive...
              value += (255/80);           
            } 
            else if (stp < 0) {         //   ...or decrement it if step is negative
              value -= (255/80);
            } 
          }
          // Defensive driving: make sure val stays in the range 0-255
          if (value > 255) {
            value = 255;
          } 
          else if (value < 0) {
            value = 0;
          }
          return value;
        }


    private:
      //LED Pins
      static const int kRedPin   = 12;
      static const int kGreenPin = 13;
      static const int kBluePin  = 14;
      std::queue<RGB> RGBQueue;
      
      
      RGB prev_color = {0,0,0};                     // Store the preview color*/
      unsigned long switchColorDelay = 0;
      unsigned long transitionTimer = 0;
      unsigned long previousMillis = 0;
      
      float TRANSITION_PART = 0.2f;                 //Set the transition part as 20 percent
      uint8_t SWITCH_DELAY = 50;                     //Set the transition time (ms)
      int transitionSteps = 0;                      //Steps number for one transition
      unsigned long delay_ = 1000;
    
      int currentStep = 0;
};

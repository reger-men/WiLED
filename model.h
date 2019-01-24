#pragma once
#include <Arduino.h>
#include <queue>

#include <WS2812FX.h>
WS2812FX strip = WS2812FX(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


// Only the Model has the access to the LED strip
class Model {
    public:
        // default constructor
        Model()
        {
          printf("Init Model with default constructor.\n");
        }
        
        Model(Strip_Type type)
        {
          printf("Initialize the pins as an output...\n");
          this->strip_type_ = type;
          
          switch (strip_type_) {
            case ESMD_STRIP: 
              pinMode(kRedPin,    OUTPUT);     
              pinMode(kGreenPin,  OUTPUT);
              pinMode(kBluePin,   OUTPUT);
              break;
              
            case EWS28_STRIP: 
              strip.init();
              strip.setBrightness(brightness_);
              strip.setSpeed(delay_);
              strip.setColor(0, 0, 0);
              strip.start();
              break;
              
            default: // compilation error
              break;
          }

          // Initialize the pins values  
          this->Off();  
        }

        void setRGB(RGB rgb)
        { 
          //Set the new RGB Values
          switch (strip_type_) {
            case ESMD_STRIP: 
              analogWrite(kRedPin,   rgb.r);                 
              analogWrite(kGreenPin, rgb.g);                            
              analogWrite(kBluePin,  rgb.b);
              break;
              
            case EWS28_STRIP: 
              printf("Set RGB in EWS28_STRIP\n");
              strip.setColor(rgb.r, rgb.g, rgb.b);
              break;
              
            default: // compilation error
              break;
          }
          
          this->prev_color_ = rgb;
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
        
        void pushInQueue(RGB rgb)
        {
          this->RGBQueue_.push(rgb);
        }
        
        RGB pullFromQueue()
        {
          return RGBQueue_.front();                                //Get next element
        }
        
        void shiftQueue()
        {
          RGB front = this->pullFromQueue();
          this->RGBQueue_.pop(); //Remove next element
          this->pushInQueue(front);
        }

        void clearQueue() 
        {
          std::queue<RGB> empty;
          std::swap( this->RGBQueue_, empty );                     // Clear the RGB queue
        }
        
        void setDelay(int sec)
        {
          //Compute the transition period
          this->switchColorDelay_ = (sec * TRANSITION_PART);
          this->transitionSteps_ = (int)((this->switchColorDelay_*2)/this->TRANSITION_DELAY);
          this->delay_ = sec - this->switchColorDelay_;
        }

        int getNextColor(int prev_queue, int prev, int next){
          float ret = 0;
          
          if(prev > next){
            ret = floor(prev - ((float)(prev_queue-next)/(float)this->transitionSteps_));
          }else{
            ret = ceil(prev + ((float)(next-prev_queue)/(float)this->transitionSteps_));
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
          unsigned long period = currentMillis - previousMillis_; 
          
          if ((period >= this->delay_) and (period <= this->delay_ + (this->switchColorDelay_*2))){ // Transition period
            tr_phase = TRANSITION;
          }
          if(period > this->delay_ + (this->switchColorDelay_*2)){ //End transition
            previousMillis_ = currentMillis;                       //Rest timer
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
              
              prev_queue_color_ = tmp;                             //Set the Current Color to prev
              this->current_step_ = 0;
              delay(this->delay_);
              break;
            case TRANSITION:
              
              rgb = this->pullFromQueue();
              tmp.r = getNextColor(prev_queue_color_.r, prev_color_.r, rgb.r); 
              tmp.g = getNextColor(prev_queue_color_.g, prev_color_.g, rgb.g); 
              tmp.b = getNextColor(prev_queue_color_.b, prev_color_.b, rgb.b);
                            
              this->setRGB(tmp);                                //Set the RGB Value 
              
              this->current_step_ = min(this->current_step_+1, this->transitionSteps_);      

              delay(this->TRANSITION_DELAY);
              break;
            default:
            
              break;
          }
        }

      
    private:
      Strip_Type strip_type_;
      
      static const uint8_t kRedPin      = 12;                       // Used for SMD strip as output
      static const uint8_t kGreenPin    = 13;                       // ...
      static const uint8_t kBluePin     = 14;                       // ...
      std::queue<RGB> RGBQueue_;
      
      
      RGB prev_color_                   = {0,0,0};                  // Store the preview color
      RGB prev_queue_color_             = {0,0,0};                  // Store the preview color from queue
      int current_step_                 = 0;
      
      unsigned long switchColorDelay_   = 0;
      unsigned long previousMillis_     = 0;
      
      float TRANSITION_PART             = 0.4f;                     // Set the transition part as 20 percent
      uint8_t TRANSITION_DELAY          = 20;                       // Set the transition time (ms)
      int transitionSteps_              = 0;                        // Steps number for one transition
      
      unsigned long delay_              = 1000;                     // Steps the delay value for one color
      uint8_t brightness_               = 0;                        // Store the brightness value
};

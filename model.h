#pragma once
#include <Arduino.h>
#include <queue>

// Only the Model has the access to the LED strip
class Model {
    public:
      // Default constructor
      Model()
      {
        printf("Init Model with default constructor.\n");
      }

		  // Abstract methods which has to be implemeted by its subclasses
      virtual void setRGB(RGB rgb)  = 0;
      virtual void on()             = 0;
      virtual void off()            = 0;
      virtual void runService(){}; // Do nothing: this method will be overwritten if needed.
      
      void pushInQueue(RGB rgb)
      {
        this->RGBQueue_.push(rgb);
      }
        
      RGB pullFromQueue()
      {
        return RGBQueue_.front();                                	//Get next element
      }
        
      void shiftQueue()
      {
        RGB front = this->pullFromQueue();
        this->RGBQueue_.pop(); 									//Remove next element
        this->pushInQueue(front);
      }
       
      void clearQueue() 
      {
        std::queue<RGB> empty;
        std::swap( this->RGBQueue_, empty );                     	// Clear the RGB queue
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
      TransitionPhase getTransistionPhase()
      {
        unsigned long currentMillis = millis(); 
        unsigned long period = currentMillis - previousMillis_; 
          
        if ((period >= this->delay_) and (period <= this->delay_ + (this->switchColorDelay_*2))){ // Transition period
          return TRANSITION;
        }
        if(period > this->delay_ + (this->switchColorDelay_*2)){   //End transition
          previousMillis_ = currentMillis;                        //Rest timer
          return SETCOLOR;
        }
      }

      void applyQueue(SwitchMode sw_mode = FADE)
      {        
        RGB tmp = {0,0,0}; RGB rgb = {0,0,0};
        TransitionPhase tr = getTransistionPhase();                                 // Update Transistion Phase
 
        switch (tr) {
          case SETCOLOR:
            tmp = this->pullFromQueue();                          //Get the first item from the queue
            this->setRGB(tmp);                                    //Set the RGB Value 
            this->shiftQueue();                                   //Shift the queue to update the items order
              
            prev_queue_color_ = tmp;                              //Set the Current Color to prev
            this->current_step_ = 0;
            delay(this->delay_);
            break;
          case TRANSITION:
              
            rgb = this->pullFromQueue();
            tmp.r = getNextColor(prev_queue_color_.r, prev_color_.r, rgb.r); 
            tmp.g = getNextColor(prev_queue_color_.g, prev_color_.g, rgb.g); 
            tmp.b = getNextColor(prev_queue_color_.b, prev_color_.b, rgb.b);
                            
            this->setRGB(tmp);                                  //Set the RGB Value 
              
            this->current_step_ = min(this->current_step_+1, this->transitionSteps_);      
            delay(this->TRANSITION_DELAY);
            break;
          default:
            
            break;
        }
      }
    protected:
      std::queue<RGB> RGBQueue_;									                // Queue that contains all the RGB values
      Strip_Type stripModel;                                      // Store the strip model
      
      unsigned long switchColorDelay_   = 0;						          // Set transition duration
      float TRANSITION_PART             = 0.4f;                   // Set the transition part as 20 percent
      uint8_t TRANSITION_DELAY          = 20;                     // Set the transition time (ms)
      int transitionSteps_              = 0;                      // Steps number for one transition
      unsigned long delay_              = 3000;                   // Steps the delay value for one color

      RGB prev_color_                   = {0,0,0};                // Store the preview color
      RGB prev_queue_color_             = {0,0,0};                // Store the preview color from queue
      int current_step_                 = 0;
      unsigned long previousMillis_     = 0;
};

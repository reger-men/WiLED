#pragma once
#include <Arduino.h>
#include <queue>

// Only the Model has the access to the LED strip
class SMD_Model : public Model{
    public:
        SMD_Model()
        {
    			printf("Initialize the pins as an output...\n");
    
    			pinMode(kRedPin,    OUTPUT);     
    			pinMode(kGreenPin,  OUTPUT);
    			pinMode(kBluePin,   OUTPUT);

  			  // Initialize the pins values  
  			  this->off();  
        }

        void setRGB(RGB rgb)
        { 
          analogWrite(kRedPin,   rgb.r);                 
          analogWrite(kGreenPin, rgb.g);                            
          analogWrite(kBluePin,  rgb.b);
              
    			this->prev_color_ = rgb;
    			printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
        }
        
        void on() 
        { 
          digitalWrite(kRedPin,   1);                             
          digitalWrite(kGreenPin, 1);                             
          digitalWrite(kBluePin,  1);
        }
        
        void off() 
        { 
          digitalWrite(kRedPin,   0);                             
          digitalWrite(kGreenPin, 0);                             
          digitalWrite(kBluePin,  0);
        }
        
        // Update Transistion Phase
        void updateTransistionPhase()
        {
          unsigned long currentMillis = millis(); 
          unsigned long period = currentMillis - previousMillis_; 
          
          if ((period >= this->delay_) and (period <= this->delay_ + (this->switchColorDelay_*2))){ // Transition period
            tr_phase = TRANSITION;
          }
          if(period > this->delay_ + (this->switchColorDelay_*2)){ 	//End transition
            previousMillis_ = currentMillis;                       	//Rest timer
            tr_phase = SETCOLOR;
          }
        }

        void applyQueue(SwitchMode sw_mode = FADE)
        {        
          RGB tmp = {0,0,0}; RGB rgb = {0,0,0};
          updateTransistionPhase();                               	// Update Transistion Phase
          
          
          switch (tr_phase) {
            case SETCOLOR:
              tmp = this->pullFromQueue();                        	//Get the first item from the queue
              this->setRGB(tmp);                                  	//Set the RGB Value 
              this->shiftQueue();                                 	//Shift the queue to update the items order
              
              prev_queue_color_ = tmp;                             	//Set the Current Color to prev
              this->current_step_ = 0;
              delay(this->delay_);
              break;
            case TRANSITION:
              
              rgb = this->pullFromQueue();
              tmp.r = getNextColor(prev_queue_color_.r, prev_color_.r, rgb.r); 
              tmp.g = getNextColor(prev_queue_color_.g, prev_color_.g, rgb.g); 
              tmp.b = getNextColor(prev_queue_color_.b, prev_color_.b, rgb.b);
                            
              this->setRGB(tmp);                                	//Set the RGB Value 
              
              this->current_step_ = min(this->current_step_+1, this->transitionSteps_);      

              delay(this->TRANSITION_DELAY);
              break;
            default:
            
              break;
          }
        }

      
    private:      
		static const uint8_t kRedPin      = 12;                    // Used for SMD strip as output
		static const uint8_t kGreenPin    = 13;                    // ...
		static const uint8_t kBluePin     = 14;                    // ...
      
		RGB prev_color_                   = {0,0,0};               // Store the preview color
		RGB prev_queue_color_             = {0,0,0};               // Store the preview color from queue
		int current_step_                 = 0;
		unsigned long previousMillis_     = 0;
};

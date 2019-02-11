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
      this->pushInQueue(BLUE);
      this->pushInQueue(PURPLE);
      this->pushInQueue(RED);
      this->pushInQueue(ORANGE);
      this->pushInQueue(GOLD);
    }

    // Abstract methods which has to be implemeted by its subclasses
    virtual void setRGB(RGB rgb)  = 0;
    virtual void on()             = 0;
    virtual void off()            = 0;
    virtual void runService() {};                               // Do nothing: this method will be overwritten if needed.
    virtual void updateMode(uint8_t m) {};                      // ...
    virtual void setBrightness(uint8_t brt) {};                 // ...
    virtual void updateSpeed(int s = -1)
    {
      s = s != -1 ? s : this->delay_;
      this->setSpeed(s);
    }


    void pushInQueue(RGB rgb)
    {
      this->RGBQueue_.push(rgb);
    }

    RGB pullFromQueue()
    {
      return RGBQueue_.front();                                 //Get next element
    }

    void shiftQueue()
    {
      RGB front = this->pullFromQueue();
      this->RGBQueue_.pop(); 									                  //Remove next element
      this->pushInQueue(front);
    }

    void clearQueue()
    {
      std::queue<RGB> empty;
      std::swap( this->RGBQueue_, empty );                      // Clear the RGB queue
    }

    void setNextRGB()
    {
      RGB tmp = {0, 0, 0};
      tmp = this->pullFromQueue();                              //Get the first item from the queue
      this->prev_queue_color_ = tmp;                            // Set the Current Color to prev
      this->setRGB(tmp);                                        //Set the RGB Value
      this->shiftQueue();                                       //Shift the queue to update the items order
    }

    void setSpeed(int sec)
    {
      this->delay_ = sec;
      if (s_mode == DYNAMIC && sw_mode == FADE) {
        //Compute the transition period
        this->switchColorDelay_ = (sec * TRANSITION_PART);
        this->transitionSteps_ = (int)((this->switchColorDelay_ * 2) / (this->TRANSITION_DELAY + 10)); // 10 is the estimated processing time of the fade procedure
        this->speed_ = sec - this->switchColorDelay_;
      } else {
        this->speed_ = sec;
      }
    }

    int getSpeed()
    {
      return this->delay_;
    }

    int getNextColor(int prev_queue, int prev, int next) {
      float ret = 0;

      if (prev > next) {
        ret = floor(prev - ((float)(prev_queue - next) / (float)this->transitionSteps_));
      } else {
        ret = ceil(prev + ((float)(next - prev_queue) / (float)this->transitionSteps_));
      }
      int min_value = min(prev_queue, next);
      int max_value = max(prev_queue, next);

      ret = (ret < min_value) ? min_value : ret;
      ret = (ret > max_value) ? max_value : ret;

      return (int)ret;
    }

    // Update Transistion Phase
    TransitionPhase getTransistionPhase()
    {
      unsigned long currentMillis = millis();
      unsigned long period = currentMillis - previousMillis_;

      if ((period >= this->speed_) and (period <= this->speed_ + (this->switchColorDelay_ * 2))) { // Transition period
        return TRANSITION;
      }
      if (period > this->speed_ + (this->switchColorDelay_ * 2)) { //End transition
        previousMillis_ = currentMillis;                        //Rest timer
        return SETCOLOR;
      }
    }

    void fade()
    {
      RGB tmp = {0, 0, 0}; RGB rgb = {0, 0, 0};
      TransitionPhase tr = getTransistionPhase();               // Update Transistion Phase

      switch (tr) {
        case SETCOLOR:
          this->setNextRGB();                                   // Set the next color from the queue

          this->current_step_ = 0;
          delay(this->speed_);
          break;
        case TRANSITION:

          rgb = this->pullFromQueue();
          tmp.r = getNextColor(this->prev_queue_color_.r, this->prev_color_.r, rgb.r);
          tmp.g = getNextColor(this->prev_queue_color_.g, this->prev_color_.g, rgb.g);
          tmp.b = getNextColor(this->prev_queue_color_.b, this->prev_color_.b, rgb.b);

          this->setRGB(tmp);                                    // Set the RGB Value

          this->current_step_ = min(this->current_step_ + 1, this->transitionSteps_);
          delay(this->TRANSITION_DELAY);
          break;
        default:

          break;
      }
    }

    void flash()
    {
      this->setNextRGB();                                       // Set the next color from the queue
      delay(this->speed_);
    }

    // Check if two RGB colors are the same
    bool isSameColor(RGB c1, RGB c2)
    {
      if ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b)) {
        return true;
      } else {
        return false;
      }
    }

    virtual void applyQueue(StateMode stm, SwitchMode swm)
    {
      RGB tmp = {0, 0, 0};
      switch (stm) {
        case OFF:
          this->off();
          break;

        case ON:
          this->on();
          break;

        case STATIC:
          tmp = this->pullFromQueue();
          if (!this->isSameColor(this->prev_color_, tmp)) {
            this->setRGB(tmp);
          }
          break;

        case DYNAMIC:
          if (swm == FLASH) {
            this->flash();
          } else if (swm == FADE) {
            this->fade();
          }
          break;

        default:
          printf("applyQueue error. State Mode is not defined.\n");
          break;
      }
    }
  protected:
    std::queue<RGB> RGBQueue_;									                // Queue that contains all the RGB values
    Strip_Type stripModel;                                      // Store the strip model

    unsigned long switchColorDelay_   = 0;						          // Set transition duration
    float TRANSITION_PART             = 0.5f;                   // Set the transition part as 20 percent
    uint8_t TRANSITION_DELAY          = 20;                     // Set the transition time (ms)
    int transitionSteps_              = 0;                      // Steps number for one transition
    int speed_                        = 0;                      // Steps the speed value for one color
    int delay_                        = 1000;                   // Steps the delay value

    RGB prev_color_                   = {0, 0, 0};              // Store the preview color
    RGB prev_queue_color_             = {0, 0, 0};              // Store the preview color from queue
    int current_step_                 = 0;
    unsigned long previousMillis_     = 0;
};

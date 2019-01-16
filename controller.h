#pragma once
#include "model.h"
#include <tuple>

// Controller combines Model and View
class Controller {
    public:
        // default constructor
        Controller()
        {
          printf("Init Controller with default constructor.\n");
        }
        
        Controller(const Model &m) : model(m){}
                
        void setRGB(RGB rgb) 
        {
          this->model.setRGB(rgb);
        }
        
        void setDelay(int sec)
        {
          this->model.setDelay(sec);
        }
        
        void insertRGB(RGB rgb)
        {
          this->model.pushInQueue(rgb);
        }
        
        void insertRGBArray(uint8_t rgbs[], uint8_t len)
        {
          for (int i = 0; i < len/3; i++){
            pin_color.r = rgbs[(i*3) + 0];
            pin_color.g = rgbs[(i*3) + 1];
            pin_color.b = rgbs[(i*3) + 2];
        
            printf("r: %d , g: %d, b: %d\n", rgbs[(i*3) + 0], rgbs[(i*3) + 1], rgbs[(i*3) + 2]);
            this->insertRGB(pin_color);
          }
        }
        
        void runQueue()
        {
          this->model.applyQueue();
        }
        
        void On() 
        { 
          this->model.On();
        }
        
        void Off() 
        { 
          this->model.Off();
        }   

        void clearQueue()
        {
          this->model.clearQueue();
        }
    private:
        Model model;
        RGB pin_color = { 0, 0, 0 };
};

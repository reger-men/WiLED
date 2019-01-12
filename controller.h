#pragma once
#include "model.h"
#include <tuple>


// Controller combines Model and View
class Controller {
    public:
        Controller(); // default constructor
        Controller(const Model &model);
        void setRGB(RGB rgb);
        void insertRGB(RGB rgb);
        void insertRGBArray(uint8_t rgbs[], uint8_t len);
        void runQueue();


        void On();
        void Off();  
        Model model;   //delete me   
    private:
        //Model &model;
        RGB pin_color = { 0, 0, 0 };
};

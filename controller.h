#pragma once
#include "model.h"
#include <tuple>


// Controller combines Model and View
class Controller {
    public:
        Controller(); // default constructor
        Controller(Model model);
        void setRGB(RGB rgb);
        void insertRGB(RGB rgb);
        void insertRGBArray(int rgbs[], int len);
        void runQueue();


        void On();
        void Off();        
    private:
        Model model;
};

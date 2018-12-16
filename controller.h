#pragma once
#include "model.h"
#include <tuple>
 
// Controller combines Model and View
class Controller {
    public:
        Controller(Model model);
        void setRGB(std::tuple <int, int, int> RGB);
        void insertRGB(std::tuple <int, int, int> RGB);
        void runQueue();


        void On();
        void Off();
    private:
        Model model;
};

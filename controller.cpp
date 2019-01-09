#include "controller.h"

// default constructor
Controller::Controller() 
{
  
}

Controller::Controller(Model model) 
{ 
  this->model = model;
}
        
void Controller::setRGB(RGB rgb) 
{
  this->model.setRGB(rgb);
}

void Controller::insertRGB(RGB rgb)
{
  this->model.pushInQueue(rgb);
}

void Controller::insertRGBArray(int rgbs[], int len)
{
  int r = 0;
  int g = 0;
  int b = 0;
  for (int i = 0; i < len/3; i++){
    r = rgbs[(i*3) + 0];
    g = rgbs[(i*3) + 1];
    b = rgbs[(i*3) + 2];

    Serial.printf("r: %d , g: %d, b: %d\n", r, g, b);
    //insertRGB(std::make_tuple (243, 320,852));
  }
}

void Controller::runQueue()
{
  this->model.applyQueue();
}

void Controller::On() 
{ 
  this->model.On();
}

void Controller::Off() 
{ 
  this->model.Off();
}

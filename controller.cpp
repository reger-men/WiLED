#include "controller.h"

// default constructor
Controller::Controller()
{
  printf("Init Controller with default constructor.\n");
}

Controller::Controller(const Model &m) : model(m) 
{ 
  printf("Model name2: %s\n", this->model._name.c_str());
  printf("Model adress2: %p\n", &this->model);
}
        
void Controller::setRGB(RGB rgb) 
{
  this->model.setRGB(rgb);
}

void Controller::insertRGB(RGB rgb)
{
  printf("Model name3: %s\n", this->model._name.c_str());
  printf("Model adress3: %p\n", &this->model);
  this->model.pushInQueue(rgb);
}

void Controller::insertRGBArray(uint8_t rgbs[], uint8_t len)
{
  for (int i = 0; i < len/3; i++){
    pin_color.r = rgbs[(i*3) + 0];
    pin_color.g = rgbs[(i*3) + 1];
    pin_color.b = rgbs[(i*3) + 2];

    printf("r: %d , g: %d, b: %d\n", rgbs[(i*3) + 0], rgbs[(i*3) + 1], rgbs[(i*3) + 2]);
    this->insertRGB(pin_color);
  }
}

void Controller::runQueue()
{
  //this->model.applyQueue();
}

void Controller::On() 
{ 
  //this->model.On();
}

void Controller::Off() 
{ 
  //this->model.Off();
}

#include "controller.h"

Controller::Controller(Model model) 
{ 
  this->model = model;
}
        
void Controller::setRGB(std::tuple <int, int, int> RGB) 
{
  this->model.setRGB(RGB);
}

void Controller::insertRGB(std::tuple <int, int, int> RGB)
{
  this->model.pushInQueue(RGB);
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

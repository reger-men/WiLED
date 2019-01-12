#include "model.h"

// default constructor
Model::Model()
{
  printf("Init Model with default constructor.\n");
}
Model::Model(String Name): _name(Name)
{
  printf("Initialize the pins as an output");
  pinMode(kRedPin,    OUTPUT);     
  pinMode(kGreenPin,  OUTPUT);
  pinMode(kBluePin,   OUTPUT);

  // Initialize the pins values  
  this->Off();                          
}
 
void Model::setRGB(RGB rgb) 
{ 
  digitalWrite(kRedPin,   ((rgb.r)/100));                 
  digitalWrite(kGreenPin, ((rgb.g)/100));                            
  digitalWrite(kBluePin,  ((rgb.b)/100));
}

void Model::On() 
{ 
  digitalWrite(kRedPin,   1);                             
  digitalWrite(kGreenPin, 1);                             
  digitalWrite(kBluePin,  1);
}

void Model::Off() 
{ 
  digitalWrite(kRedPin,   0);                             
  digitalWrite(kGreenPin, 0);                             
  digitalWrite(kBluePin,  0);
}

void Model::pushInQueue(RGB rgb)
{
  RGBQueue.push(rgb);
  printf("Size: %i\n", RGBQueue.size());
}

RGB Model::pullFromQueue()
{
  return RGBQueue.front(); //Get next element
}

void Model::shiftQueue()
{
  RGB front = this->pullFromQueue();
  RGBQueue.pop(); //Remove next element
  this->pushInQueue(front);
}

void Model::applyQueue()
{
  RGB tmp = this->pullFromQueue();
  this->setRGB(tmp);
  this->shiftQueue();
}

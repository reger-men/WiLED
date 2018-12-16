#include "model.h"

// default constructor
Model::Model() 
{
  Serial.print("Initialize the pins as an output");
  pinMode(kRedPin,    OUTPUT);     
  pinMode(kGreenPin,  OUTPUT);
  pinMode(kBluePin,   OUTPUT);

  // Initialize the pins values  
  this->Off();                             
}
 
void Model::setRGB(std::tuple <int, int, int> RGB) 
{ 
  digitalWrite(kRedPin,   (std::get<0>(RGB)/100));                 
  digitalWrite(kGreenPin, (std::get<1>(RGB)/100));                            
  digitalWrite(kBluePin,  (std::get<2>(RGB)/100));
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

void Model::pushInQueue(std::tuple <int, int, int> RGB)
{
  RGBQueue.push(RGB);
}

std::tuple <int, int, int> Model::pullFromQueue()
{
  return RGBQueue.front(); //Get next element
}

void Model::shiftQueue()
{
  std::tuple <int, int, int> front = this->pullFromQueue();
  RGBQueue.pop(); //Remove next element
  this->pushInQueue(front);
}

void Model::applyQueue()
{
  std::tuple <int, int, int> tmp = this->pullFromQueue();
  this->setRGB(tmp);
  this->shiftQueue();
}

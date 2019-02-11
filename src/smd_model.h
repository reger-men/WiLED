#pragma once
#include <Arduino.h>
#include <queue>

// Only the Model has the access to the LED strip
class SMD_Model : public Model {
  public:
    SMD_Model()
    {
      printf("SMD: Initialize the pins as an output...\n");
      this->stripModel = ESMD_STRIP;

      pinMode(kRedPin,    OUTPUT);
      pinMode(kGreenPin,  OUTPUT);
      pinMode(kBluePin,   OUTPUT);

      // update delay
      this->updateSpeed(this->delay_);
      // Initialize the pins values
      this->off();
    }

    void setRGB(RGB rgb)
    {
      analogWrite(kRedPin,   rgb.r);
      analogWrite(kGreenPin, rgb.g);
      analogWrite(kBluePin,  rgb.b);

      this->prev_color_ = rgb;
      //printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
    }

    void on()
    {
      digitalWrite(kRedPin,   1);
      digitalWrite(kGreenPin, 1);
      digitalWrite(kBluePin,  1);
    }

    void off()
    {
      digitalWrite(kRedPin,   0);
      digitalWrite(kGreenPin, 0);
      digitalWrite(kBluePin,  0);
    }

  private:
    static const uint8_t kRedPin      = 12;                    // Used for SMD strip as output
    static const uint8_t kGreenPin    = 13;                    // ...
    static const uint8_t kBluePin     = 14;                    // ...
};

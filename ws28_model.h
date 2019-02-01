#pragma once
#include <Arduino.h>
#include <queue>
#include <WS2812FX.h>

// Only the Model has the access to the LED strip
class WS28_Model : public Model {
  public:
    WS28_Model()
    {
      printf("WS28: Initialize the pins as an output...\n");
      this->stripModel = EWS28_STRIP;

      this->strip = new WS2812FX(kLEDCount, kLEDPin, NEO_GRB + NEO_KHZ800);
      this->strip->init();
      this->strip->setBrightness(this->brightness_);
      this->strip->setSpeed(this->delay_);
      this->strip->setColor(0x007BFF);
      this->strip->setMode(FX_MODE_STATIC);
      this->strip->start();

      // update delay
      this->updateSpeed(this->delay_);
      // Initialize the pins values
      this->off();
    }

    void runService()
    {
      this->strip->service();
    }

    void setBrightness(uint8_t brt)
    {
      this->brightness_ = brt;
      this->strip->setBrightness(brt);
      this->strip->trigger();
    }

    void updateSpeed(int s = -1) {
      s = s != -1 ? s : this->delay_;
      this->setSpeed(s);
      this->strip->setSpeed(s);
      this->strip->trigger();
    }

    void setRGB(RGB rgb)
    {
      if(s_mode != OFF){
        //Set the new RGB Values
        this->strip->setColor(rgb.r, rgb.g, rgb.b);
        this->strip->trigger();
        this->prev_color_ = rgb;
        printf("Set RGB: %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
      }
    }

    void updateMode(uint8_t m)
    {
      this->mode_ = m;
      this->setMode(m);
    }

    void setMode(uint8_t m)
    {
      //Set the new Mode
      this->strip->setMode(m);
      this->strip->trigger();
      this->prev_mode_ = m;

      printf("Set mode to: %i\n", this->strip->getMode());

    }

    void on()
    {
      unsigned long hex = this->strip->getColor() == 0 ?  0x007BFF : this->strip->getColor();
      this->strip->setColor(hex);
      this->strip->setMode(FX_MODE_STATIC);
      if (!this->strip->isRunning()) this->strip->start();
    }

    void off()
    {
      this->strip->setColor(0x000000);
      if (this->strip->isRunning()) this->strip->stop();
    }

    void applyQueue(StateMode stm, SwitchMode swm) override
    {
      RGB tmp = {0, 0, 0};
      switch (stm) {
        case OFF:
          this->off();
          break;

        case ON:
          this->on();
          break;

        case STATIC:
          tmp = this->pullFromQueue();
          if (!this->isSameColor(this->prev_color_, tmp)) {
            this->setRGB(tmp);
          }
          break;

        case DYNAMIC:
          if (swm == FLASH) {
            this->flash();
          } else if (swm == FADE) {
            this->fade();
          }
          break;

        case SET_MODE:
          if (this->prev_mode_ != this->mode_) {
            this->setMode(mode_);
          }
          break;

        default:
          printf("applyQueue error. State Mode is not defined.\n");
          break;
      }
    }
  private:
    static const uint8_t kLEDPin      = 14;                     // Used for WS28 strip as output pin
    static const uint16_t kLEDCount   = 30;                     // Used for WS28 strip as LED Count
    uint8_t mode_                     = 0;
    uint8_t prev_mode_                = 255;                    // Store the previous mode

    uint8_t brightness_               = 90;                     // Store the brightness value
    WS2812FX *strip                   = nullptr;
};

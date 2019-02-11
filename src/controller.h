#pragma once
#include "model.h"
#include <tuple>

// Controller combines Model and View
class Controller {
  public:
    // default constructor
    Controller()
    {
      printf("Init Controller with default constructor.\n");
    }

    Controller(Model *m) : model(m) {}

    void runModelService()
    {
      this->model->runService();
    }

    void setRGB(RGB rgb)
    {
      this->model->setRGB(rgb);
    }

    void setSpeed(int sec)
    {
      this->model->updateSpeed(sec);
    }

    void setBrightness(uint8_t brt)
    {
      this->model->setBrightness(brt);
    }

    void insertRGB(RGB rgb)
    {
      this->model->pushInQueue(rgb);
    }

    void insertRGBArray(uint8_t rgbs[], uint8_t len)
    {
      for (int i = 0; i < (len / 3); i++) {
        pin_color.r = rgbs[(i * 3) + 0];
        pin_color.g = rgbs[(i * 3) + 1];
        pin_color.b = rgbs[(i * 3) + 2];

        //printf("r: %d , g: %d, b: %d\n", rgbs[(i * 3) + 0], rgbs[(i * 3) + 1], rgbs[(i * 3) + 2]);
        this->insertRGB(pin_color);
      }
    }

    void updateStateMode(StateMode sm)
    {
      s_mode = sm;
    }

    void updateSwitchMode(SwitchMode swm)
    {
      sw_mode = swm;
    }

    void updateColors(uint8_t rgbs[], uint8_t len)
    {
      this->clearQueue();
      this->insertRGBArray(rgbs, len);
      this->model->updateSpeed();
      this->model->setNextRGB();                 // Set the next color from the queue
    }

    void updateMode(int m)
    {
      if (m >= 0) {
        this->updateStateMode(SET_MODE);
        this->model->updateMode(m);
      } else {
        this->updateStateMode(DYNAMIC);
        this->model->updateMode(FX_MODE_STATIC); // Set mode back to static
        if (m == -2) {      // Fade
          this->updateSwitchMode(FADE);
        } else if (m == -1) { // Flash
          this->updateSwitchMode(FLASH);
        }
      }
      this->model->updateSpeed();
    }
    
    void run()
    {
      this->model->applyQueue(s_mode, sw_mode);
    }

    void on()
    {
      //printf(".....................................On....................................:\n");
      this->updateStateMode(ON);
      this->model->on();
    }

    void off()
    {
      //printf(".....................................OFF....................................:\n");
      this->updateStateMode(OFF);
      this->model->off();
    }

    void clearQueue()
    {
      this->model->clearQueue();
    }
  protected:
    Model *model;
  private:
    RGB pin_color = { 0, 0, 0 };
};

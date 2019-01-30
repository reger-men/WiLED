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
      this->model->setSpeed(sec);
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

        printf("r: %d , g: %d, b: %d\n", rgbs[(i * 3) + 0], rgbs[(i * 3) + 1], rgbs[(i * 3) + 2]);
        this->insertRGB(pin_color);
      }
    }

    void updateColors(uint8_t rgbs[], uint8_t len, StateMode sm)
    {
      s_mode = sm;
      this->clearQueue();
      this->insertRGBArray(rgbs, len);
      this->model->updateDelay();
    }

    void updateMode(uint8_t m)
    {
      s_mode = SET_MODE;
      this->model->updateMode(m);
    }

    void run()
    {
      this->model->applyQueue(s_mode, sw_mode);
    }

    void on()
    {
      this->model->on();
    }

    void off()
    {
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

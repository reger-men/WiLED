#pragma once
#include <Arduino.h>
#include <queue>
#include "smd_model.h"
#include "ws28_model.h"

// Model factory to create the concrete model by type
class Model_Factory {
  public:
    static Model* create(Strip_Type type)
    {
      switch (type) {
        case ESMD_STRIP:
          return new SMD_Model;
        case EWS28_STRIP:
          return new WS28_Model;
        default: // Compilation error
          printf("Init Model error. Model type is not defined.\n");
          return NULL;
      }
    }
};

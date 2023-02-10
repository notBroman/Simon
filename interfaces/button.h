#ifndef _BUTTON_H
#define _BUTTON_H

#include "out_interface.h"

class Button : IOutput{
  uint8_t pin;
  uint8_t value;

  bool updated = false;
  uint8_t last_read = 0;
  uint8_t delta = 100;
public:
  Button();

  bool read();
};

#endif

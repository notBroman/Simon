#ifndef _LED_H
#define _LED_H

#include "out_interface.h"

class Led : IOutput{
  uint8_t pin;
  uint8_t value = 0;
  bool digital;



public:
  Led(uint8_t pin, bool digital=true);

  bool write();
};

#endif

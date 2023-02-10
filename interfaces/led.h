#ifndef _LED_H
#define _LED_H

#include "out_interface.h"

class Led : IOutput{
  uint8_t pin;
  uint8_t value = 0;
  bool digital;

public:
  Led(uint8_t p, bool dig=true) : pin(p), digital(dig){
    // nothing to do
  }

  virtual bool write(uint8_t out){
    if(digital){
      digitalWrite(pin, out);
    } else if (!digital){
      analogWrite(pin, out);
    }
  }
};

#endif

#ifndef _LED_H
#define _LED_H

#include "out_interface.h"

class Led : public IOutput{
  uint8_t pin;
  uint8_t value = 0;
  bool digital = true;

public:
  Led(uint8_t p, bool dig) : pin(p), digital(dig){
    // nothing to do
  }

  virtual bool write(uint8_t out){
    if(digital){
      digitalWrite(pin, out);
      value = out;
      return true;
    }
    else if (!digital){
      analogWrite(pin, out);
      value = out;
      return true;
    }
    return false;
  }

  Led* operator* (){
    return this;
  }
};

#endif

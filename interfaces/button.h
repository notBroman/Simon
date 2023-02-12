#ifndef _BUTTON_H
#define _BUTTON_H

#include "in_interface.h"

class Button : public IInput{
  uint8_t pin;
  uint8_t value;

  bool updated;
  uint8_t last_read;
  uint8_t delta = 100;
public:
  Button(uint8_t p) : pin(p){
    value = 0;
    updated = false;
    last_read = 0;
  }

  virtual bool read(){
    if (millis() > (last_read + delta) && !updated){
      value = digitalRead(pin);
      last_read = millis();
      updated = true;

    }
    return false;
    
  }

  Button* operator* (){
    return this;
  }

  uint8_t get_value(){
    return value;
  }

  void set_updated(bool state){
    updated = state;
  }

};


#endif

#ifndef _BUTTON_H
#define _BUTTON_H

#include "in_interface.h"

class Button : public IInput{
  uint8_t pin;
  uint8_t value;
  uint8_t active_val;

  bool updated;
  long double last_read = 0;
  uint8_t delta = 180;
public:
  Button(uint8_t p) : pin(p){
    value = 1; // because active low
    active_val = 0;
    updated = false;
    last_read = 0;
  }

  virtual bool read(){
    if (millis() > (last_read + delta)){
      int tmp = digitalRead((int)pin);
      last_read = millis();
      value = (tmp == active_val) ? tmp : value;
      updated = (value == active_val) ? true : false;
      return updated;

    }
    return false;
    
  }

  Button* operator* (){
    return this;
  }

  uint8_t get_value(){
    uint8_t old = value;
    value = 1;
    return old;
  }

  int get_pin(){
    get_value();
    return (int)pin;
  }

  void set_updated(bool state){
    updated = state;
  }

};


#endif

#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "Array.h"
#include "interfaces/button.h"

class InputHandler{
  Array<IInput*, 10> m_ins; 
public:
  InputHandler(){
    // initialize the serial line for debugging
    Serial.begin(9600);
  }

  void test(){
    for(IInput* in : m_ins){ // does not work T_T, iterator broken ?
      bool next = false;
      while(!next){
        // do nothing
        // every button has to be pressed in order to check if connected correctly
        in->read();
        if(in->get_value() == 0){
          //Serial.println("read");
          next = true;
        }
        //Serial.println((in->get_value()));
        delay(250);
      }
    }
  }

  void setup(){
    // add two buttons as input devices
    Button b1((uint8_t)2);
    m_ins.push_back(*b1);

    Button b2((uint8_t)4);
    m_ins.push_back(*b2);

    test();
  }

  void read_all();
};

#endif

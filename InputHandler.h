#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "Array.h"
#include "interfaces/button.h"

class InputHandler{
  Array<IInput*, 10> m_ins; 

  int input_time;
public:
  InputHandler(){
    // initialize the serial line for debugging
    Serial.begin(9600);
    input_time = 30*1000;

    // register the input devices
    m_ins.push_back( new Button((uint8_t)2));
    m_ins.push_back( new Button((uint8_t)4));
    m_ins.push_back( new Button((uint8_t)7));
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
    test();
  }

  void read_sequence(int* read_seqi, int difficulty){
    long double timer = millis();
    int i = 0;
    bool read;

    Serial.println("entered");

    while(millis() <= timer + input_time && i < difficulty){
      // do the reading in the permitted window
      for(IInput* in : m_ins){
        read = in->read();
        if(read){
          in->get_value();
          i++;
          read = false;
          break;
        }
      }
      Serial.println(i);
    }
    // do nothing for now
  }
};

#endif

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
    input_time = 30*1000; // 30s time to respond to simon

  }

  void test(){
    int i = -1;
    for(IInput* in : m_ins){ // does not work T_T, iterator broken ?
      bool next = false;
      while(!next){
        // do nothing
        // every button has to be pressed in order to check if connected correctly
        in->read();
        if(in->get_value() == 0){
          Serial.print("Botton ");
          Serial.println(++i);
          next = true;
        }
        //Serial.println((in->get_value()));
      }
    }
  }

  void setup(){
    /* configure the input devices in order 0 to max */
    m_ins.push_back( new Button((uint8_t)2));
    m_ins.push_back( new Button((uint8_t)4));
    m_ins.push_back( new Button((uint8_t)7));

    // add two buttons as input devices
    test();
  }

  int read_que(int* read_seq, int que, long double time){
    bool read = false;
    if(time <= input_time){
      // do the reading in the permitted window
      int pos = 0;
      for(IInput* in : m_ins){
        read = in->read();
        if(read){
          in->reset();
          read_seq[que] = pos;
          read = false;
          return 0;
        }
        pos++;
      }
    }
    return -1;
  }

};

#endif

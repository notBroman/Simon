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
      }
    }
  }

  void setup(){
    // add two buttons as input devices
    test();
  }

  void read_sequence(int* read_seq, int difficulty){
    long double timer = millis();
    int que = 0;
    bool read;

    Serial.println("entered");

    while(millis() <= timer + input_time && que < difficulty){
      // do the reading in the permitted window
      int pos = 0;
      for(IInput* in : m_ins){
        read = in->read();
        if(read){
          in->get_value();
          read_seq[que] = pos;
          que++;
          read = false;
          break;
        }
        pos++;
      }
    }
    // do nothing for now
    for(int i = 0; i < difficulty; i++){
      Serial.print(read_seq[i] );
      Serial.print(", ");
    }
    Serial.println();
  }
};

#endif

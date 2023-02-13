#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "Array.h"
#include "interfaces/led.h"

class OutputHandler{
  Array<IOutput*, 10> m_outs;
public:
  OutputHandler(){
    // initialize the serial line for debugging
    Serial.begin(9600);
  }

  void test(){
    for(IOutput* out : m_outs){
    //for(int i = 0; i < m_outs.size(); i++){
    //IOutput* out = m_outs[i];      
    out->write(255);
    delay(500);
    out->write(0);
    }
  }

  void setup(){
        /* configure the outputs */
    Led l1((uint8_t)3, false);
    m_outs.push_back(*l1);

    Led l2((uint8_t)5, false);
    m_outs.push_back(*l2);

    Led l3((uint8_t)6, false);
    m_outs.push_back(*l3);

    /* test if the outputs are set correctly */
    test();
  }

  void read_all();
};

#endif

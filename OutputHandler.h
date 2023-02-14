#ifndef _OUTPUTHANDLER_H
#define _OUTPUTHANDLER_H

#include "Array.h"
#include "interfaces/led.h"

// template<size_t S>
class OutputHandler{
  //Array<int, 6> available_pins = {3, 5, 6, 9, 10, 11};
  //Array<IOutput*, S> m_outs;
  Array<IOutput*, 10> m_outs;
public:
  OutputHandler(){
    // initialize the serial line for debugging
    Serial.begin(9600);
  }

  void test(){
    for(IOutput* out : m_outs){
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

  void run_sequence(Array<int, 10> sequence){
    Serial.print("run seq, leds: ");
    Serial.println(m_outs.last());
    for(int entry : sequence){
      Serial.println(entry);
      m_outs[1]->write((uint8_t)255) ? Serial.println("t") : Serial.println("f");
      delay(250);
      m_outs[1]->write((uint8_t)0) ? Serial.println("t") : Serial.println("f");
      delay(250);
    }
  }

  int num_devices(){
    return m_outs.last();
  }
};

#endif

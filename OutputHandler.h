#ifndef _OUTPUTHANDLER_H
#define _OUTPUTHANDLER_H

#include "Array.h"
#include "interfaces/led.h"

// template<size_t S>
class OutputHandler{
  //int available_pins[6] = {3, 5, 6, 9, 10, 11};
  //Array<IOutput*, S> m_outs;
  //Array<IOutput*, 10> m_outs;
  IOutput* m_outs[10];
  int out_num = 3;
  

public:
  OutputHandler(){
    // initialize the serial line for debugging
    Serial.begin(9600);

  }

  void test(){
    for(int i = 0; i < num_devices(); ++i){
      IOutput* out = m_outs[i];
      out->write(255);
      delay(500);
      out->write(0);

    }
  }

  void setup(){
    /* configure the outputs */
    m_outs[0] = new Led((uint8_t)3, false);
    m_outs[1] = new Led((uint8_t)5, false);
    m_outs[2] = new Led((uint8_t)6, false);

    /* test if the outputs are set correctly */
    test();
  }

  void run_sequence(int* sequence, int difficulty){
    for(int i = 0; i < difficulty; ++i){
      IOutput* out = this->m_outs[(sequence[i])];
      out->write(255);
      delay(500);
      out->write(0);
      delay(500);
    }
  }

  void single_out(int idx, int val){
    IOutput* device = m_outs[idx];
    device->write(val);
    delay(125);
    device->write(0);
  }

  int num_devices(){
    //return m_outs.last();
    return out_num;
  }

  bool loss(){
    for(int i = 0; i < num_devices(); ++i){
      IOutput* out = m_outs[i];
      out->write(255);
    }
    return false;
  }

  bool win(){
    for(int i = 0; i < num_devices(); ++i){
      IOutput* out = m_outs[i];
      out->write(255);
      delay(500);
      out->write(0);

    }
    return true;
  }
};

#endif

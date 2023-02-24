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
  OutputHandler(int one, int two, int three){
    // initialize the serial line for debugging
    //Serial.begin(9600);

    /* configure the outputs */
    m_outs[0] = new Led((uint8_t)one, false);
    m_outs[1] = new Led((uint8_t)two, false);
    m_outs[2] = new Led((uint8_t)three, false);
  }

  OutputHandler(int* outs, int len){
    // initialize the serial line for debugging
    Serial.begin(9600);

    /* configure the outputs */
    for(int i = 0; i < len; i++){
      Serial.println(i);
      int pin = outs[i];
      m_outs[i] = new Led((uint8_t)pin, false);
    }
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


    /* test if the outputs are set correctly */
    test();
  }

  int run_sequence(int* sequence, int que, long int active_time){
    IOutput* out = this->m_outs[(sequence[que])];
    if(digitalRead(out->get_pin()) == LOW && active_time <= 250){
      out->write(255);
      return 0;
    }
    else if(digitalRead(out->get_pin()) == HIGH && active_time >= 250){
      out->write(0);
      return -1;
    }
    else if(active_time >= 500){
      return 1    ;  
    }
    return -1;
  }

  void single_out(int idx, int val){
    IOutput* device = m_outs[idx];
    device->write(val);
    delay(50);
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
    return true;
  }

  bool win(){
    IOutput* out = m_outs[0];
    out->write(255);
    return true;
  }
};

#endif

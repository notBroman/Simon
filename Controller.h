#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "interfaces/button.h"
#include "interfaces/led.h"

#include "Array.h"

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  Array<IInput*, 10> m_ins;
  Array<IOutput*, 10> m_outs;

public:
  Controller(){};

  void get_inputs();

  void control();

  void set_outputs(){
    for(IOutput* out : m_outs){
      out->write(1);
    }
  };

  void setup(){
    /*
    * Configure all the input and output devices
    * This needs to be done manually, unfortunately
    *
    * configure onboard led for testing:
    * Led l1((uint8_t)13, true);
    * m_outs.push_back(*l1);
    */
    Led l1((uint8_t)13, true);
    m_outs.push_back(*l1);
  };

  void play();

};

#endif

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "interfaces/button.h"
#include "interfaces/led.h"

#include "Array.h"
#include "interfaces/out_interface.h"

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  Array<IInput*, 3> m_ins;
  Array<IOutput*, 2> m_outs;

  uint8_t round;
  uint8_t score_player;
  uint8_t score_computer;

public:
  Controller(){
    Serial.begin(9600);
  };

  void get_inputs();

  void control();

  void set_outputs(){
  };

  void test_out(){
    for(IOutput* out : m_outs){
      out->write((uint8_t)255);
      delay(250);
      out->write((uint8_t)0);
    }

  }

  void test_in(){
    for(IInput* in : m_ins){ // does not work T_T, iterator broken ?
      /*
      while(true){
        // do nothing
        // every button has to be pressed in order to check if connected correctly
        ((Button*)in)->read();
        if(((Button*)in)->get_value() != 0);
      }
      */
    }
    
  }

  void setup(){
    /*
    * Configure all the input and output devices
    * This needs to be done manually, unfortunately
    *
    * configure onboard led for testing:
    * Led l1((uint8_t)13, true);
    * m_outs.push_back(*l1);
    */

    /* configure the outputs */
    Led l1((uint8_t)3, false);
    m_outs.push_back(*l1);

    Led l2((uint8_t)5, false);
    m_outs.push_back(*l2);

    Led l3((uint8_t)6, false);
    m_outs.push_back(*l3);
    /* test if the outputs are set correctly */
    test_out();

    /* configure the outputs */
    Button b1((uint8_t)2);
    m_ins.push_back(*b1);

    Button b2((uint8_t)4);
    m_ins.push_back(*b2);
/*    
    Button b3((uint8_t)7);
    m_ins.push_back(*b3);
*/
    /* test the inputs */
    test_in();
  };

  void play(){

    get_inputs();
    control();
    set_outputs();
  }

};

#endif

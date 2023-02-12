#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "interfaces/button.h"
#include "interfaces/led.h"

#include "Array.h"

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  Array<IInput*, 3> m_ins;
  Array<IOutput*, 10> m_outs;

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
    //for(int i = 0; i < m_outs.size(); i++){
      //IOutput* out = m_outs[i];      
      out->write(255);
      delay(500);
      out->write(0);
    }

  }

  void test_in(){
    //for(int i = 0; i < m_ins.last(); i++){
      //IInput* in = m_ins[i];
    for(IInput* in : m_ins){ // does not work T_T, iterator broken ?
      bool next = false;
      while(!next){
        // do nothing
        // every button has to be pressed in order to check if connected correctly
        in->read();
        if(((Button*)in)->get_value() == 0){
          Serial.println("read");
          next = true;
        }
        Serial.println((((Button*)in)->get_value()));
        delay(250);
      }
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
    Serial.println("why?");
    test_in();
  };

  void play(){

    get_inputs();
    control();
    set_outputs();
  }

};

#endif

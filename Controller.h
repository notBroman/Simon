#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "InputHandler.h"
#include "OutputHandler.h"

#include "Array.h"

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  InputHandler h_in;
  OutputHandler h_out;

  uint8_t round;
  uint8_t score_player;
  uint8_t score_computer;

  Array<int, 10> sequence;
  int difficulty = 5;

public:
  Controller(){
    Serial.begin(9600);
  };

  void control(){

    // check if the sequence read matched the generated sequence

    // generate the output sequence
    generate_seq();
  };

  void setup(){
    h_out.setup();
    h_in.setup();
  };

  void generate_seq(){
    sequence.clear();
    // fill with random numbers from 0 to num output devices
    // rand num % h_out.num_devices()
    for(int i = 0; i < difficulty; i++){
      long double rand = millis()*millis();
      rand = rand & h_out.num_device();
      sequence.push_back((int)rand);
    }
  }

  void play(){
    if(round != 0){
      h_in.read_sequence();
    }
    control();
    h_out.run_sequence(sequence);
  }

};

#endif

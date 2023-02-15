#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "InputHandler.h"
#include "OutputHandler.h"

#include "Array.h"
#include <avr/sleep.h>

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  InputHandler h_in;
  OutputHandler h_out;

  uint8_t round;
  uint8_t score_player;
  uint8_t score_computer;

  int sequence[10];
  int read_sequence[10];
  int m_difficulty = 5;

public:
  Controller(){
    Serial.begin(9600);
    round = 1;
    score_player = 0;
    score_computer = 0;
    generate_seq();
  };

  void control(){
    // read sequence
    h_in.read_sequence(read_sequence, m_difficulty);

    // check if the sequence read matched the generated sequence
    for(int i = 0; i < m_difficulty; i++){
      if(sequence[i] != read_sequence[i]){
        score_computer++;
        // decrease difficulty
        break;
      }
      if(i+1 == m_difficulty){
        score_player++; 
        //increase difficulty
      }
    }


    // generate the output sequence
    generate_seq();
  };

  void setup(){
    h_out.setup();
    h_in.setup();
  };

  void generate_seq(){
    // fill with random numbers from 0 to num output devices
    // rand num % h_out.num_devices()
    for(int i = 0; i < m_difficulty; i++){
      int rand = random(0, h_out.num_devices());
      sequence[i] = rand;
    }
  }

  void play(){
    if(score_player < 3 && score_computer <3){ 
      h_out.run_sequence(sequence, m_difficulty);  
      control();
      round++;
    } else{
      (score_player > 2) ? Serial.println("Player wins") : Serial.println("Computer wins");
      while(true){
        // do nothing
      }      
    }
  }

};

#endif

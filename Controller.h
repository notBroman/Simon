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

  enum { READ=0, CONTROL, WRITE, END };
  int current_state = WRITE;


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
    int que = 0;
    long double start_time = millis();
    int timeout = 0;
    while(que < m_difficulty && timeout == 0){
      timeout = h_in.read_que(read_sequence, que, start_time);
      if(timeout == -1){
        break;
      }
      h_out.single_out(read_sequence[que], 50);
      ++que;    
    }

    // check if the sequence read matched the generated sequence
    int max = m_difficulty;
    for(int i = 0; i < max; i++){
      if(sequence[i] != read_sequence[i]){
        score_computer++;
        Serial.println(score_computer);
        m_difficulty--;
        break;
      }
      if(i + 1 == m_difficulty){
        Serial.println(score_player);
        score_player++;
        m_difficulty++;
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
    randomSeed(analogRead(A0));
    for(int i = 0; i < m_difficulty; i++){
      int rand = random(0, h_out.num_devices());
      sequence[i] = rand;
    }
  }

  void play(){
    switch(current_state){
      case WRITE:
        h_out.run_sequence(sequence, m_difficulty);
        current_state = CONTROL;
        break;

      case CONTROL:
        control();
        round++;
        
        Serial.print("P:");
        Serial.println(score_player);
        Serial.print("Com:");
        Serial.println(score_computer);

        if(score_player >= 3 || score_computer >= 3){
          current_state = END;
          break;
        } 

        current_state = WRITE;
        break;

      case READ:
        break;
      
      case END:
        (score_player > 2) ? h_out.win() : h_out.loss();
        while(true){
          // do nothing
        }   
        break;


    }
    /*
    if(score_player < 3 && score_computer <3){

      h_out.run_sequence(sequence, m_difficulty);  
      control();
      round++;
      Serial.print("P:");
      Serial.println(score_player);
      Serial.print("Com:");
      Serial.println(score_computer);
    } else{
      (score_player > 2) ? h_out.win() : h_out.loss();
      //h_out.loss();
      //h_out.win();
      while(true){
        // do nothing
        
      }      
    }
    */
  }

};

#endif

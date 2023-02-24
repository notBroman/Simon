#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "InputHandler.h"
#include "OutputHandler.h"

#include "Array.h"

class Controller{
  // i wish i had std::shared_pointer<> T_T
  // references or pointers that is the question
  InputHandler* h_in;
  OutputHandler* h_out;

  uint8_t round;
  uint8_t score_player;
  uint8_t score_computer;

  int sequence[10];
  int read_sequence[10];
  int m_difficulty = 5;

  enum { READ=0, CONTROL, WRITE, END };
  int current_state = WRITE;
  int que;
  long int ellapsed_time;


public:
  Controller(int* ins, int l1, int* outs, int l2){
    Serial.begin(9600);
    round = 1;
    score_player = 0;
    score_computer = 0;
    que = 0;
    ellapsed_time = 0;
    generate_seq();
    
    h_in = new InputHandler(ins, l1);
    h_out = new OutputHandler(outs, l2);
  };

  void control(){

    // check if the sequence read matched the generated sequence
    int max = m_difficulty;
    for(int i = 0; i < max; i++){
      if(sequence[i] != read_sequence[i]){
        score_computer++;
        m_difficulty--;
        break;
      }
      if(i + 1 == m_difficulty){
        score_player++;
        m_difficulty++;
      }
    }

    // generate the output sequence
    generate_seq();
  };

  void read(){

    long double start_time = millis();
    int timeout = 0;
    timeout = h_in->read_que(read_sequence, que, ellapsed_time);
    if(timeout == 0){
      h_out->single_out(read_sequence[que], 50);
      ++que;
    } else if(timeout == -1){
      for(int i = 0; i < 10; i++){
        read_sequence[i] = 0;
      }
      que = m_difficulty;
    }
    ellapsed_time += (millis() - start_time);
  }

  void setup(){
    h_out->setup();
    h_in->setup();
  };

  void generate_seq(){
    // fill with random numbers from 0 to num output devices
    // rand num % h_out.num_devices()
    randomSeed(analogRead(A0));
    for(int i = 0; i < m_difficulty; i++){
      int rand = random(0, h_out->num_devices());
      sequence[i] = rand;
    }
  }

  void play(){
    switch(current_state){
      case WRITE:
        h_out->run_sequence(sequence, m_difficulty);
        current_state = READ;
        que = 0;
        ellapsed_time = 0;
        break;

      case CONTROL:
        control();
        round++;
        
        Serial.print("P:");
        Serial.print(score_player);
        Serial.print(" | Com:");
        Serial.println(score_computer);

        if(score_player >= 3 || score_computer >= 3){
          current_state = END;
          break;
        } 

        current_state = WRITE;
        break;

      case READ:
        // read sequence
        read();
        if (que == m_difficulty){ 
          current_state = CONTROL;
        }
        break;
      
      case END:
        (score_player > 2) ? h_out->win() : h_out->loss();
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

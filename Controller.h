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

  uint8_t m_round;
  uint8_t m_score_player;
  uint8_t m_score_computer;

  int m_sequence[10];
  int m_read_sequence[10];
  int m_difficulty = 5;

  enum { READ=0, CONTROL, WRITE, END };
  int m_current_state = WRITE;
  int m_que;
  long int m_ellapsed_time;
  long int m_active_time;


public:
  Controller(int* ins, int l1, int* outs, int l2){
    Serial.begin(9600);
    m_round = 1;
    m_score_player = 0;
    m_score_computer = 0;
    m_que = 0;
    m_ellapsed_time = 0;
    generate_seq();
    
    h_in = new InputHandler(ins, l1);
    h_out = new OutputHandler(outs, l2);
  };

  void control(){

    // check if the sequence read matched the generated sequence
    int max = m_difficulty;
    for(int i = 0; i < max; i++){
      if(m_sequence[i] != m_read_sequence[i]){
        m_score_computer++;
        m_difficulty--;
        break;
      }
      if(i + 1 == m_difficulty){
        m_score_player++;
        m_difficulty++;
      }
    }

    // generate the output sequence
    generate_seq();
  };

  void read(){

    long double start_time = millis();
    int timeout = 0;
    timeout = h_in->read_que(m_read_sequence, m_que, m_ellapsed_time);
    if(timeout == 0){
      h_out->single_out(m_read_sequence[m_que], 50);
      ++m_que;
    } else if(timeout == -1){
      for(int i = 0; i < 10; i++){
        m_read_sequence[i] = 0;
      }
      m_que = m_difficulty;
    }
    m_ellapsed_time += (millis() - start_time);
  }

  void write(){
    long int start = millis();
    //Serial.println(m_active_time);
    int done = h_out->run_sequence(m_sequence, m_que, m_active_time);
    Serial.println(done);

    if( done == 1 ){
      m_que++;
      m_active_time = 0;
      Serial.println(m_que == m_difficulty);
    }
    else{
      // the led did not change, because it has not be on long enough
      m_active_time += (millis() - start);
    }
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
      m_sequence[i] = rand;
    }
  }

  void play(){
    switch(m_current_state){
      case WRITE:
        write();
        
        if(m_que == m_difficulty){
          Serial.println("switch");
          m_que = 0;
          m_ellapsed_time = 0;
          m_current_state = READ;
        }
        break;

      case CONTROL:
        control();
        m_round++;
        
        Serial.print("P:");
        Serial.print(m_score_player);
        Serial.print(" | Com:");
        Serial.println(m_score_computer);

        if(m_score_player >= 3 || m_score_computer >= 3){
          m_current_state = END;
          break;
        } 

        m_current_state = WRITE;
        break;

      case READ:
        // read sequence
        Serial.println("R");
        read();
        if (m_que == m_difficulty){ 
          m_current_state = CONTROL;
          m_que = 0;
        }
        break;
      
      case END:
        (m_score_player > 2) ? h_out->win() : h_out->loss();
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

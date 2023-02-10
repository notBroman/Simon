#include "Simon.hpp"

#include <Beginner_LED.h>

Input in;
Output out;

void setup(){
    // do stuff
  in.add_input(2);
  out.add_output(13, false);
  Serial.begin(9600);
}

void loop(){
    // do stuff
  if((in.read_inputs() & 0x01) == 0){
    out.write_digital(0xFF);
  }
  else if ((in.read_inputs() & 0x01) == 1){
    out.write_digital(0x00);
  }

  Serial.println(in.read_inputs() & 0x01);

  delay(250);
}

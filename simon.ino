#include "Simon.hpp"

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
  out.write_digital(0xFF);
  delay(250);
  out.write_digital(0x00);
  delay(250);
  
  
}

#include "Simon.hpp"

#include <Beginner_LED.h>

#include "Interfaces/button.h"
#include "Interfaces/led.h"

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
  delay(500);
  out.write_digital(0x00);

  delay(250);
}

#include "Controller.h"

Controller c1;

void setup(){
    // do stuff
    Serial.begin(9600); // for debugging
    c1.setup();
}

void loop(){
  // do stuff
  c1.play();
}

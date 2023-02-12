#include <Beginner_LED.h>

#include "Controller.h"

Controller c1;

void setup(){
    // do stuff

    Serial.begin(9600);
    c1.setup();
}

void loop(){
  //Serial.println("1");
    // do stuff
    //c1.play();
}

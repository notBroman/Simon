#include "Controller.h"

int i1[3] = {2,4,7};
int i2[3] = {8,12,13};

int o1[3] = {3,5,6};
int o2[3] = {9,10,11};

Controller* c1;
Controller* c2;

void setup(){
    // do stuff
    //Serial.begin(9600); // for debugging
    while(!Serial){}

    //Serial.println("hello world");

    c1 = new Controller(i1, 3, o1, 3);
    c2 = new Controller(i2, 3, o2, 3);

    c1->setup();
    c2->setup();

}

void loop(){
  // do stuff
  c1->play();
  c2->play();
}

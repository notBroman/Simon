#ifndef _SIMON_HPP
#define _SIMON_HPP

#include "Arduino.h"

#include "Array.hpp"
#include <Basic_Input.h>

class Input{
    int pin_num;
    static Array<10> pins;

public:
    Input(){
      Serial.begin(9600);
    }

    bool add_input(int pin){
        if(pin > 1 && pin < 14){
	        pinMode(pin, INPUT);
	        pins.push_back(pin);
	        return true;
        }
        return false;
    }

    uint8_t read_inputs(){
        uint8_t read = 0;
        for(int i = 0; i < pins.size(); i++){
            read << 1;
	          read += digitalRead(pins[i]);
        }
        return read;
    }
};

class Output{
    int device_num;
    static Array<10> devices_digital;
    static Array<10> devices_analog;

public:
    Output(){
      Serial.begin(9600);
    };

    bool add_output(int pin, bool analog){
        if( analog == false && pin > 1 && pin < 14){
            pinMode(pin, OUTPUT);
            return devices_digital.push_back(pin);
        } else if (analog == true && (pin == 3 || pin == 5 || pin == 6 || (pin >= 9 && pin <= 11))){
            pinMode(pin, OUTPUT);
            return devices_analog.push_back(pin);
        }
        return false;
    }

    void write_digital(uint8_t pattern){
        int val = 0;
        for(int i = 0; i < devices_digital.last(); i++){
            val = pattern & 0x01;
            digitalWrite(devices_digital[i], val);
            pattern >> 1;
        }
    }

    void write_pwm(uint8_t brightness){
        for(int i = 0; i < devices_analog.size(); i++){
            analogWrite(devices_analog[i], constrain(brightness, 0, 255));
        }
    }
};

Array<10> Input::pins;
Array<10> Output::devices_digital;
Array<10> Output::devices_analog;

#endif
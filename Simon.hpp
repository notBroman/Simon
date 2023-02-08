#ifndef _SIMON_HPP
#define _SIMON_HPP

#include "Arduino.h"

#include "Array.hpp"

class Input{
    int pin_num;
    static Array<10> pins;

public:
    Input(){}

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
        for(int i; i < pins.size(); i++){
            read << 1;
	          read += digitalRead(pins[i]);
        }
        return read;
    }
};

class Output{
    int device_num;
    static Array<10> devices_digital;
    static Array<10> devices_pwm;

public:
    Output(){};

    bool add_output(int pin, bool pwm){
        if( pwm == false && pin > 1 && pin < 14){
            pinMode(pin, OUTPUT);
            return devices_digital.push_back(pin);
        } else if (pwm == true && (pin == 3 || pin == 5 || pin == 6 || (pin >= 9 && pin <= 11))){
            pinMode(pin, OUTPUT);
            return devices_pwm.push_back(pin);
        }
        return false;
    }

    void write_digital(uint8_t pattern){
        uint8_t val = 0x00;
        for(int i; i < devices_digital.size(); i++){
            val = (pattern | 0xFF);
            digitalWrite(devices_digital[i], val);
            pattern >> 1;
        }
    }

    void write_pwm(){
        for(int i; i < devices_pwm.size(); i++){
            analogWrite(devices_pwm[i], 128);
        }
    }
};

Array<10> Input::pins;
Array<10> Output::devices_digital;
Array<10> Output::devices_pwm;

#endif
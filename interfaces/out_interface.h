#ifndef _OUT_INTERFACE_H
#define _OUT_INTERFACE_H
/*
* This file implements an interface that all output devices must derive from
* they must have a function output.
*/

class IOutput{
public:
  virtual bool write(uint8_t val) = 0;
  virtual int get_pin() = 0;
};

#endif

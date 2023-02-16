#ifndef _IN_INTERFACE_H
#define _IN_INTERFACE_H

class IInput{
public:
  virtual bool read() = 0;
  virtual uint8_t get_value() = 0;
  virtual int get_pin() = 0;
};

#endif

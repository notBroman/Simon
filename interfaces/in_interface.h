#ifndef _IN_INTERFACE_H
#define _IN_INTERFACE_H

class IInput{
public:
  virtual bool read() = 0;
  virtual bool get_value() = 0;
};

#endif

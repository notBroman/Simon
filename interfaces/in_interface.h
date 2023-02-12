#ifndef _IN_INTERFACE_H
#define _IN_INTERFACE_H

class IInput{
public:
  virtual bool read() = 0;
  // virtual bool set_updated() = 0;
};

#endif

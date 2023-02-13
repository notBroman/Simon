#ifndef _HANDLER_H
#define _HANDLER_H

#include "Array.h"

template<typename T, size_t S>
class Handler{
  Array<T*, S> devicces;

public:

  void read_all();

  void write_all();
}


#endif

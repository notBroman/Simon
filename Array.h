#ifndef _ARRAY_H
#define _ARRAY_H

template<typedef T, uint8_t N=10>
class Array{
  T* data;
  int last_added = 0;
public:
  Array<T,N>(){
    data = new (T[N]);
  }

  int size(){
    return N;
  }

  bool push_back(int& num){
    if(last_added < this->size()){
      data[last_added] = num;
      last_added++;
      return true;
    }
    return false;
  }

  int last(){
    return last_added;
  }

  T& operator[] (uint8_t idx){
    return *(data + idx * sizeof(int));
  }

  
};

#endif

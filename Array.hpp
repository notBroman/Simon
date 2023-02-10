#ifndef _ARRAY_H
#define _ARRAY_H

template<uint8_t N=10>
class Array{
  int* data;
  int last_added = 0;
public:
  Array<N>(){
    data = new (int[N]);
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

  int operator[] (uint8_t idx){
    return *(data + idx * sizeof(int));
  }

  
};

#endif
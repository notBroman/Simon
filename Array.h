#ifndef _ARRAY_H
#define _ARRAY_H

/*
* This implementation is heavily inspired by the C++ STL
* I just really wanted range based for loops
*
* In Controller Class:
* This will be used for arrays of type IInput and IOutput
* from which all the input and ouput devices must inherit
* -> the interfaces mandate functions for the devices
*/

template<typename Array>
class ArrayIterator{
public:
  using ValueType = typename Array::ValueType;
  using PointerType = ValueType*;
  using ReferenceType = ValueType&;
public:
  ArrayIterator(PointerType ptr) : m_ptr(ptr){};

  ArrayIterator& operator++ (){
    m_ptr++;
    return *this;
  }

  ArrayIterator& operator++(int){
    ArrayIterator itr = *this;
    ++(*this);
    return itr;
  }

  ArrayIterator& operator-- (){
    m_ptr--;
    return *this;
  }

  ArrayIterator& operator--(int){
    ArrayIterator itr = *this;
    --(*this);
    return itr;
  }

  ArrayIterator& operator[] (const uint8_t idx){
    return *(m_ptr + idx);
  }

  PointerType operator-> (){
    return m_ptr;
  }

  ReferenceType operator* (){
    return *m_ptr;
  }

  bool operator== (const ArrayIterator& rhs) const {
    return m_ptr == rhs.m_ptr;
  }

  bool operator!= (const ArrayIterator& rhs) const {
    return !(m_ptr == rhs.m_ptr);
  }

private:
  PointerType m_ptr;

};

template<typename T, uint8_t N=10>
class Array{
  T* data;
  int last_added = 0;
public:
  using ValueType = T;
  using Iterator = ArrayIterator<Array<T,N>>;
public:
  Array<T,N>(){
    data = new (T[N]);
  }
  ~Array(){
    delete data;
  };


  int size(){
    return N;
  }

  bool push_back(T num){
    if(last_added + 1 < this->size()){
      data[last_added] = num;
      last_added++;
      return true;
    }
    return false;
  }

  int last(){
    return last_added;
  }

  T& operator[] (const uint8_t idx) const {
    return *(data + idx * sizeof(T));
  }
  
  bool operator== (const Array& rhs) const {
    return this->data == rhs->data;
  }

  bool operator!= (const Array& rhs) const {
    return !(this->data == rhs->data);
  }
  
  Iterator begin(){
    return Iterator(data);
  }

  Iterator end(){
    return Iterator(&(data[this->last()]));
  }

};

#endif

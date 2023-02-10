#ifndef _ARRAY_H
#define _ARRAY_H

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
    return !(*this == rhs);
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
  using Iterator = ArrayIterator<Array<T,N>>I;
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
    return data;
  }

  Iterator end(){
    return Iterator(data + this->size() * sizeof(T));
  }

};

#endif

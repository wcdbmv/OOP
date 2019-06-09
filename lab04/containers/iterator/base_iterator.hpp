#ifndef ITERATOR_BASE_HPP
#define ITERATOR_BASE_HPP

#include <cstddef>

template <typename T>
class BaseIterator {
 public:
  BaseIterator(const BaseIterator&);
  virtual ~BaseIterator();
  BaseIterator& operator=(const BaseIterator&);

  BaseIterator& operator++();
  BaseIterator operator++(int);
  BaseIterator& operator--();
  BaseIterator operator--(int);

  ptrdiff_t operator-(const BaseIterator&);

  bool operator==(const BaseIterator&);
  bool operator!=(const BaseIterator&);

 protected:
  BaseIterator(T*);

  T* pointer;
};

template <typename T>
BaseIterator<T>::BaseIterator(T* pointer) {
  this->pointer = pointer;
}

template <typename T>
BaseIterator<T>::BaseIterator(const BaseIterator& other) {
  this->pointer = other.pointer;
}

template <typename T>
BaseIterator<T>::~BaseIterator() {
  this->pointer = nullptr;
}

template <typename T>
BaseIterator<T>& BaseIterator<T>::operator=(const BaseIterator& rhs) {
  if (this != &rhs) {
    this->pointer = rhs.pointer;
  }

  return *this;
}

template <typename T>
BaseIterator<T>& BaseIterator<T>::operator++() {
  ++this->pointer;
  return *this;
}

template <typename T>
BaseIterator<T> BaseIterator<T>::operator++(int) {
  BaseIterator temp(*this);
  this->operator++();
  return temp;
}

template <typename T>
BaseIterator<T>& BaseIterator<T>::operator--() {
  --this->pointer;
  return *this;
}

template <typename T>
BaseIterator<T> BaseIterator<T>::operator--(int) {
  BaseIterator temp(*this);
  this->operator--();
  return temp;
}

template <typename T>
ptrdiff_t BaseIterator<T>::operator-(const BaseIterator<T>& rhs) {
  return this->pointer - rhs.pointer;
}

template <typename T>
bool BaseIterator<T>::operator==(const BaseIterator& rhs) {
  return this->pointer == rhs.pointer;
}

template <typename T>
bool BaseIterator<T>::operator!=(const BaseIterator& rhs) {
  return this->pointer != rhs.pointer;
}

#endif // ITERATOR_BASE_HPP

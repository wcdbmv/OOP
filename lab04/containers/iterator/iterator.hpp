#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T> class BaseVector;
template <typename T> class BaseMatrix;

#include "base_iterator.hpp"

template <typename T>
class Iterator : public BaseIterator<T> {
 public:
  Iterator(const Iterator&);

  T& operator*();
  T* operator->();

  friend class BaseVector<T>;
  friend class BaseMatrix<T>;

 private:
  Iterator(T*);
};

template <typename T>
Iterator<T>::Iterator(T* pointer) : BaseIterator<T>(pointer) {

}

template <typename T>
Iterator<T>::Iterator(const Iterator& other) : BaseIterator<T>(other.pointer) {

}

template <typename T>
T& Iterator<T>::operator*() {
  return *this->pointer;
}

template <typename T>
T* Iterator<T>::operator->() {
  return this->pointer;
}

#endif // ITERATOR_HPP

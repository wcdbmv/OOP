#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

template <typename T> class BaseVector;
template <typename T> class BaseMatrix;

#include "base_iterator.hpp"

template <typename T>
class ConstIterator : public BaseIterator<T> {
 public:
  ConstIterator(const ConstIterator&);

  const T& operator*();
  const T* operator->();

  friend class BaseVector<T>;
  friend class BaseMatrix<T>;

 private:
  ConstIterator(T*);
};

template <typename T>
ConstIterator<T>::ConstIterator(T* pointer) : BaseIterator<T>(pointer) {

}

template <typename T>
ConstIterator<T>::ConstIterator(const ConstIterator& other) : BaseIterator<T>(other.pointer) {

}

template <typename T>
const T& ConstIterator<T>::operator*() {
  return *this->pointer;
}

template <typename T>
const T* ConstIterator<T>::operator->() {
  return this->pointer;
}

#endif // CONST_ITERATOR_HPP

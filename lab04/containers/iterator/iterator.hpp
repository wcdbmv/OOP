#ifndef LAB04_CONTAINERS_ITERATOR_ITERATOR_HPP_
#define LAB04_CONTAINERS_ITERATOR_ITERATOR_HPP_

#include "base_iterator.hpp"

template <typename T>
class Iterator : public BaseIterator<T> {
 public:
  constexpr explicit Iterator(T*);
  constexpr Iterator(const BaseIterator<T>&);

  T& operator*();
  T* operator->();
};

#include "detail/iterator.hpp"

#endif  // LAB04_CONTAINERS_ITERATOR_ITERATOR_HPP_

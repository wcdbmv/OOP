#ifndef LAB04_CONTAINERS_ITERATOR_CONST_ITERATOR_HPP_
#define LAB04_CONTAINERS_ITERATOR_CONST_ITERATOR_HPP_

#include "base_iterator.hpp"

template <typename T>
class ConstIterator : public BaseIterator<T> {
 public:
  constexpr explicit ConstIterator(T*);
  constexpr ConstIterator(const BaseIterator<T>&);

  constexpr const T& operator*() const;
  constexpr const T* operator->() const;
};

#include "detail/const_iterator.hpp"

#endif  // LAB04_CONTAINERS_ITERATOR_CONST_ITERATOR_HPP_

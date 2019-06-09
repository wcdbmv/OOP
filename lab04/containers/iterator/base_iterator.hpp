#ifndef LAB04_CONTAINERS_ITERATOR_BASE_ITERATOR_HPP_
#define LAB04_CONTAINERS_ITERATOR_BASE_ITERATOR_HPP_

#include <cstddef>

template <typename T>
class BaseIterator : public std::iterator<std::random_access_iterator_tag, T> {
 public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;

 public:
  constexpr explicit BaseIterator(T*);

  constexpr BaseIterator& operator++();
  constexpr const BaseIterator operator++(int);
  constexpr BaseIterator& operator--();
  constexpr const BaseIterator operator--(int);

  constexpr BaseIterator& operator+=(difference_type value);
  constexpr BaseIterator& operator-=(difference_type value);
  constexpr BaseIterator operator[](difference_type index) const;

  template <typename U>
  friend constexpr const bool operator==(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);
  template <typename U>
  friend constexpr const bool operator!=(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);
  template <typename U>
  friend constexpr const bool operator<(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);
  template <typename U>
  friend constexpr bool operator>(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);
  template <typename U>
  friend constexpr bool operator<=(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);
  template <typename U>
  friend constexpr bool operator>=(const BaseIterator<U>& lhs, const BaseIterator<U>& rhs);

 protected:
  T* pointer_;
};

// TODO: fix [ no matching function for call to ‘copy(ConstIterator<double>&, const BaseIterator<double>, double*&)’ ]

#include "detail/base_iterator.hpp"

#endif  // LAB04_CONTAINERS_ITERATOR_BASE_ITERATOR_HPP_

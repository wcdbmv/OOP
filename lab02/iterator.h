#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <algorithm>
#include <iterator>

template <typename T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
 public:
  using base = std::iterator<std::bidirectional_iterator_tag, T>;
  using typename base::pointer;
  using typename base::reference;
  using typename base::difference_type;
  typedef const T* const_pointer;
  typedef const T& const_reference;


  Iterator() = default;
  explicit Iterator(T* ptr) : ptr_(ptr) {}
  Iterator(const Iterator<T>&) = default;
  Iterator<T>& operator=(const Iterator<T>&) = default;
  ~Iterator() = default;

  reference operator*() { return *ptr_; }
  const_reference operator*() const { return *ptr_; }

  pointer operator->() { return ptr_; }
  const_pointer operator->() const { return ptr_; }

  Iterator<T>& operator++() { ++ptr_; return *this; }
  const Iterator<T> operator++(int) { auto old = *this; ++(*this); return old; }

  Iterator<T>& operator--() { --ptr_; return *this; }
  const Iterator<T> operator--(int) { auto old = *this; --(*this); return old; }

  reference operator[](difference_type n) const { auto tmp = *this; tmp += n; return *tmp; }
  Iterator<T>& operator+=(difference_type n) { ptr_ += n; return *this; }
  Iterator<T>& operator-=(difference_type n) { return *this += -n; }

  template <typename U> friend difference_type operator-(const Iterator<U>& a, const Iterator<U>& b);
  template <typename U> friend bool operator==(const Iterator<U>& a, const Iterator<U>& b);
  template <typename U> friend void swap(Iterator<U>& a, Iterator<U>& b);
private:
  T* ptr_;
};

template <typename T>
Iterator<T> operator+(const Iterator<T>& a, typename Iterator<T>::difference_type b) {
  return Iterator<T>(a) += b;
}

template <typename T>
Iterator<T> operator+(typename Iterator<T>::difference_type a, const Iterator<T>& b) {
  return b + a;
}

template <typename T>
Iterator<T> operator-(const Iterator<T>& a, typename Iterator<T>::difference_type b) {
  return Iterator<T>(a) -= b;
}

template <typename T>
typename Iterator<T>::difference_type operator-(const Iterator<T>& a, const Iterator<T>& b) {
  return a.ptr_ - b.ptr_;
}

template <typename T>
void swap(Iterator<T>& a, Iterator<T>& b) { std::swap(a.ptr_, b.ptr_); }

template <typename T>
bool operator==(const Iterator<T>& a, const Iterator<T>& b) { return a.ptr_ == b.ptr_; }

template <typename T>
bool operator!=(const Iterator<T>& a, const Iterator<T>& b) { return !(a == b); }

template <typename T>
bool operator<(const Iterator<T>& a, const Iterator<T>& b) { return a.ptr_ < b.ptr_; }

template <typename T>
bool operator>(const Iterator<T>& a, const Iterator<T>& b) { return b < a; }

template <typename T>
bool operator<=(const Iterator<T>& a, const Iterator<T>& b) { return !(b > a); }

template <typename T>
bool operator>=(const Iterator<T>& a, const Iterator<T>& b) { return !(a < b); }


#endif  // ITERATOR_H

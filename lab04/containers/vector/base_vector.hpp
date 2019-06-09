#ifndef LAB04_CONTAINERS_VECTOR_BASE_VECTOR_HPP_
#define LAB04_CONTAINERS_VECTOR_BASE_VECTOR_HPP_

#include <istream>
#include <ostream>

#include "containers/iterator/iterator.hpp"
#include "containers/iterator/const_iterator.hpp"
#include "exceptions/container_exceptions.hpp"

template <typename T>
class BaseVector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  using iterator = value_type*;
  using const_iterator = const value_type*;
  using size_type = std::size_t;

 public:
  explicit BaseVector();
  explicit BaseVector(size_type);
  explicit BaseVector(size_type, const_reference);
  explicit BaseVector(const_iterator, const_iterator);
  BaseVector(std::initializer_list<T>);
  BaseVector(size_type, std::initializer_list<T>);
  BaseVector(const BaseVector&);
  BaseVector(BaseVector&&) noexcept;
  virtual ~BaseVector();
  BaseVector& operator=(const BaseVector&);
  BaseVector& operator=(BaseVector&&) noexcept;
  BaseVector& operator=(std::initializer_list<T>);

  T& at(size_type);
  const T& at(size_type) const;
  T& operator[](size_type);
  const T& operator[](size_type) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  std::size_t size() const;
  std::size_t capacity() const;
  void clear();

 protected:
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  T* data_;

  void Allocate();
  void Reallocate(size_type);
  void ThrowBadMemoryAllocationException() const;
  void CheckOutOfRangeException(size_type) const;

  static constexpr std::size_t DEFAULT_CAPACITY = 8;
};

template <typename T>
std::istream& operator>>(std::istream& is, BaseVector<T>& vector);
template <typename T>
std::ostream& operator<<(std::ostream& os, const BaseVector<T>& vector);

#include "detail/base_vector.hpp"

#endif  // LAB04_CONTAINERS_VECTOR_BASE_VECTOR_HPP_

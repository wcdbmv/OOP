#ifndef VECTOR_BASE_HPP
#define VECTOR_BASE_HPP

#include <cstddef>
#include <iostream>

#include "exceptions/container_exceptions.hpp"
#include "containers/iterator/iterator.hpp"
#include "containers/iterator/const_iterator.hpp"

template <typename T>
class BaseVector {
  const std::size_t BASE_SIZE = 7;

 public:
  typedef Iterator<T> iterator;
  typedef ConstIterator<T> const_iterator;

  explicit BaseVector();
  explicit BaseVector(std::size_t);
  explicit BaseVector(std::size_t, const T&);
  BaseVector(iterator, iterator);
  BaseVector(const_iterator, const_iterator);
  BaseVector(std::initializer_list<T>);
  BaseVector(const BaseVector&);
  BaseVector(BaseVector&&);
  virtual ~BaseVector();
  BaseVector& operator=(const BaseVector&);
  BaseVector& operator=(BaseVector&&);
  BaseVector& operator=(std::initializer_list<T>);

  T& at(std::size_t);
  const T& at(std::size_t) const;
  T& operator[](std::size_t);
  const T& operator[](std::size_t) const;

  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

  iterator rbegin();
  const_iterator rcbegin() const;
  iterator rend();
  const_iterator rcend() const;

  bool empty() const;
  std::size_t size() const;
  std::size_t capacity() const;
  void clear();
  void swap(BaseVector&);

  template <typename U>
  friend inline void swap(BaseVector<U>&, BaseVector<U>&);

  template <typename U>
  friend inline bool operator==(const BaseVector<U>&, const BaseVector<U>&);
  template <typename U>
  friend inline bool operator!=(const BaseVector<U>&, const BaseVector<U>&);
  template <typename U>
  friend inline bool operator<(const BaseVector<U>&, const BaseVector<U>&);
  template <typename U>
  friend inline bool operator<=(const BaseVector<U>&, const BaseVector<U>&);
  template <typename U>
  friend inline bool operator>(const BaseVector<U>&, const BaseVector<U>&);
  template <typename U>
  friend inline bool operator>=(const BaseVector<U>&, const BaseVector<U>&);

  template <typename U>
  friend inline std::ostream& operator<<(std::ostream&, const BaseVector<U>&);

 protected:
  std::size_t size_;
  std::size_t capacity_;
  T* data_;

  inline void reallocate();
};

template <typename T>
BaseVector<T>::BaseVector() : size_(0), capacity_(BASE_SIZE) {
  try {
    this->data_ = new T[this->capacity_];

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("vector_base::(bad memory allocation)!");
  }
}

template <typename T>
BaseVector<T>::BaseVector(std::size_t count) : size_(count), capacity_(count) {
  try {
    this->data_ = new T[this->capacity_];

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("vector_base::(bad memory allocation)!");
  }
}

template <typename T>
BaseVector<T>::BaseVector(std::size_t count, const T& value) : BaseVector(count) {
  for (std::size_t i = 0; i < this->size_; ++i) {
    (*this)[i] = value;
  }
}

template <typename T>
BaseVector<T>::BaseVector(iterator first, iterator last) : BaseVector(last - first) {
  for (std::size_t i = 0; i < this->size_; ++i, ++first) {
    (*this)[i] = *first;
  };
}

template <typename T>
BaseVector<T>::BaseVector(const_iterator first, const_iterator last) : BaseVector(last - first) {
  for (std::size_t i = 0; i < this->size_; ++i, ++first) {
    (*this)[i] = *first;
  };
}

template <typename T>
BaseVector<T>::BaseVector(std::initializer_list<T> lst) : BaseVector(lst.size()) {
  std::copy(lst.begin(), lst.end(), this->data_);
}

template <typename T>
BaseVector<T>::BaseVector(const BaseVector<T>& other) : BaseVector(other.size()) {
  std::copy(other.data_, other.data_ + other.size_, this->data_);
}

template <typename T>
BaseVector<T>::BaseVector(BaseVector<T>&& other)
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
BaseVector<T>::~BaseVector() {
  delete[] this->data_;

  this->capacity_ = 0;
  this->data_ = nullptr;
}

template <typename T>
BaseVector<T>& BaseVector<T>::operator=(const BaseVector<T>& rhs) {
  if (this != &rhs) {
    this->size_ = rhs.size_;
    this->capacity_ = rhs.capacity_;

    try {
      delete[] this->data_;
      this->data_ = new T[this->capacity_];

    } catch (std::bad_alloc& ex) {
      throw BadMemoryAllocationException("vector_base::(bad memory allocation)!");
    }

    std::copy(rhs.data_, rhs.data_ + rhs.size_, this->data_);
  }

  return *this;
}

template <typename T>
BaseVector<T>& BaseVector<T>::operator=(BaseVector<T>&& rhs) {
  if (this != &rhs) {
    this->size_ = rhs.size_;
    this->capacity_ = rhs.capacity_;

    delete[] this->data_;
    this->data_ = (std::move(rhs.data_));

    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.data_ = nullptr;
  }

  return *this;
}

template <typename T>
BaseVector<T>& BaseVector<T>::operator=(std::initializer_list<T> lst) {
  this->size_ = lst.size();
  this->capacity_ = lst.size();

  try {
    delete[] this->data_;
    this->data_ = new T[this->capacity_];

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("vector_base::(bad memory allocation)!");
  }

  std::copy(lst.begin(), lst.end(), this->data_);

  return *this;
}

template <typename T>
T& BaseVector<T>::at(std::size_t pos) {
  if (pos < this->size_) {
    return (*this)[pos];

  } else {
    throw OutOfRangeException("vector_base::(out of range index)!");
  }
}

template <typename T>
const T& BaseVector<T>::at(std::size_t pos) const {
  if (pos < this->size_) {
    return (*this)[pos];

  } else {
    throw OutOfRangeException("vector_base::(out of range index)!");
  }
}

template <typename T>
T& BaseVector<T>::operator[](std::size_t pos) {
  if (pos < this->size_) {
    return this->data_[pos];

  } else {
    throw OutOfRangeException("vector_base::(out of range index)!");
  }
}

template <typename T>
const T& BaseVector<T>::operator[](std::size_t pos) const {
  if (pos < this->size_) {
    return this->data_[pos];

  } else {
    throw OutOfRangeException("vector_base::(out of range index)!");
  }
}

template <typename T>
typename BaseVector<T>::iterator BaseVector<T>::begin() {
  return iterator(this->data_);
}

template <typename T>
typename BaseVector<T>::const_iterator BaseVector<T>::cbegin() const {
  return const_iterator(this->data_);
}

template <typename T>
typename BaseVector<T>::iterator BaseVector<T>::end() {
  return iterator(this->data_ + this->size_);
}

template <typename T>
typename BaseVector<T>::const_iterator BaseVector<T>::cend() const {
  return const_iterator(this->data_ + this->size_);
}

template <typename T>
typename BaseVector<T>::iterator BaseVector<T>::rbegin() {
  return iterator(this->data_ + this->size_ - 1);
}

template <typename T>
typename BaseVector<T>::const_iterator BaseVector<T>::rcbegin() const {
  return const_iterator(this->data_ + this->size_ - 1);
}

template <typename T>
typename BaseVector<T>::iterator BaseVector<T>::rend() {
  return iterator(this->data_ - 1);
}

template <typename T>
typename BaseVector<T>::const_iterator BaseVector<T>::rcend() const {
  return const_iterator(this->data_ - 1);
}

template <typename T>
bool BaseVector<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
std::size_t BaseVector<T>::size() const {
  return this->size_;
}

template <typename T>
std::size_t BaseVector<T>::capacity() const {
  return this->capacity_;
}

template <typename T>
void BaseVector<T>::clear() {
  for (std::size_t i = 0; i < this->size(); ++i) {
    (*this)[i].~T();
  }

  this->size_ = 0;
}

template <typename T>
inline void BaseVector<T>::reallocate() {
  try {
    T* temp_buffer = new T[this->capacity_];
    std::copy(this->data_, this->data_ + this->size_, temp_buffer);
    delete[] this->data_;
    this->data_ = temp_buffer;

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("vector_base::(bad memory allocation)!");
  }
}

template <typename T>
void BaseVector<T>::swap(BaseVector<T>& other) {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->data_, other.data_);
}

template <typename T>
void swap(BaseVector<T>& lhs, BaseVector<T>& rhs) {
  lhs.swap(rhs);
}

template <typename T>
bool operator==(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  bool are_equal = lhs.size() == rhs.size();

  if (are_equal) {

    for (std::size_t i = 0; i < lhs.size() && are_equal; ++i) {

      if (lhs[i] != rhs[i]) {
        are_equal = false;
      }
    }
  }

  return are_equal;
}

template <typename T>
bool operator!=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return !(rhs == lhs);
}

template <typename T>
bool operator<(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  bool is_less = lhs.size() < rhs.size();

  if (!is_less && lhs.size() == rhs.size()) {

    for (std::size_t i = 0; i < lhs.size() && !is_less; ++i) {

      if (lhs[i] < rhs[i]) {
        is_less = true;
      }
    }
  }

  return is_less;
}

template <typename T>
bool operator<=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator>(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return !(lhs < rhs) && !(lhs == rhs);
}

template <typename T>
bool operator>=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const BaseVector<T>& vec) {
  for (typename BaseVector<T>::const_iterator iter = vec.cbegin(); iter != vec.cend(); ++iter) {
    stream << *iter << " ";
  }

  return stream;
}

#endif // VECTOR_BASE_HPP

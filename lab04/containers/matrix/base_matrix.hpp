#ifndef MATRIX_BASE_HPP
#define MATRIX_BASE_HPP

#include <cstddef>
#include <iostream>

#include "exceptions/container_exceptions.hpp"
#include "containers/iterator/iterator.hpp"
#include "containers/iterator/const_iterator.hpp"

template <typename T>
class BaseMatrix {
  class proxy {
   public:
    proxy(std::size_t, T*);

    T& at(std::size_t);
    const T& at(std::size_t) const;
    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;

   private:
    std::size_t cols_;
    T* data_;
  };

 public:
  typedef Iterator<T> iterator;
  typedef ConstIterator<T> const_iterator;

  explicit BaseMatrix(std::size_t, std::size_t);
  explicit BaseMatrix(std::size_t, std::size_t, const T&);
  BaseMatrix(std::size_t, std::size_t, iterator, iterator);
  BaseMatrix(std::size_t, std::size_t, const_iterator, const_iterator);
  BaseMatrix(std::size_t, std::size_t, std::initializer_list<T>);
  BaseMatrix(const BaseMatrix&);
  BaseMatrix(BaseMatrix&&);
  virtual ~BaseMatrix();
  BaseMatrix& operator=(const BaseMatrix&);
  BaseMatrix& operator=(BaseMatrix&&);
  BaseMatrix& operator=(std::initializer_list<T>);

  proxy at(std::size_t);
  const proxy at(std::size_t) const;
  proxy operator[](std::size_t);
  const proxy operator[](std::size_t) const;

  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

  iterator rbegin();
  const_iterator rcbegin() const;
  iterator rend();
  const_iterator rcend() const;

  std::size_t rows() const;
  std::size_t columns() const;
  std::size_t capacity() const;
  void zero();
  void swap(BaseMatrix&);

  template <typename U>
  friend inline void swap(BaseMatrix<U>&, BaseMatrix<U>&);

  template <typename U>
  friend inline bool operator==(const BaseMatrix<U>&, const BaseMatrix<U>&);
  template <typename U>
  friend inline bool operator!=(const BaseMatrix<U>&, const BaseMatrix<U>&);
  template <typename U>
  friend inline bool operator<(const BaseMatrix<U>&, const BaseMatrix<U>&);
  template <typename U>
  friend inline bool operator<=(const BaseMatrix<U>&, const BaseMatrix<U>&);
  template <typename U>
  friend inline bool operator>(const BaseMatrix<U>&, const BaseMatrix<U>&);
  template <typename U>
  friend inline bool operator>=(const BaseMatrix<U>&, const BaseMatrix<U>&);

  template <typename U>
  friend inline std::ostream& operator<<(std::ostream&, const BaseMatrix<U>&);

 protected:
  std::size_t rows_;
  std::size_t cols_;
  std::size_t capacity_;
  T* data_;
};

template <typename T>
BaseMatrix<T>::proxy::proxy(std::size_t col_count, T* data) : cols_(col_count), data_(data) {

}

template <typename T>
T& BaseMatrix<T>::proxy::at(std::size_t index) {
  if (index < this->cols_) {
    return *(this->data_ + index);

  } else {
    throw OutOfRangeException("matrix_base::proxy::(out of range index)!");
  }
}

template <typename T>
const T& BaseMatrix<T>::proxy::at(std::size_t index) const {
  if (index < this->cols_) {
    return *(this->data_ + index);

  } else {
    throw OutOfRangeException("matrix_base::proxy::(out of range index)!");
  }
}

template <typename T>
T& BaseMatrix<T>::proxy::operator[](std::size_t index) {
  if (index < this->cols_) {
    return *(this->data_ + index);

  } else {
    throw OutOfRangeException("matrix_base::proxy::(out of range index)!");
  }
}

template <typename T>
const T& BaseMatrix<T>::proxy::operator[](std::size_t index) const {
  if (index < this->cols_) {
    return *(this->data_ + index);

  } else {
    throw OutOfRangeException("matrix_base::proxy::(out of range index)!");
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count)
    : rows_(row_count), cols_(col_count), capacity_(row_count * col_count) {
  try {
    this->data_ = new T[this->capacity_];

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("matrix_base::(bad memory allocation)!");
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count, const T& value)
    : BaseMatrix(row_count, col_count) {
  for (std::size_t i = 0; i < this->capacity_; ++i) {
    this->data_[i] = value;
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count, iterator first, iterator last)
    : BaseMatrix(row_count, col_count) {
  std::size_t size = this->capacity_ <= static_cast<std::size_t>(last - first) ?
                this->capacity_ : static_cast<std::size_t>(last - first);

  for (std::size_t i = 0; i < size; ++i, ++first) {
    this->data_[i] = *first;
  }

  for (std::size_t i = size; i < this->capacity_; ++i) {
    this->data_[i] = 0;
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count, const_iterator first, const_iterator last)
    : BaseMatrix(row_count, col_count) {
  std::size_t size = this->capacity_ <= static_cast<std::size_t>(last - first) ?
                this->capacity_ : static_cast<std::size_t>(last - first);

  for (std::size_t i = 0; i < size; ++i, ++first) {
    this->data_[i] = *first;
  }

  for (std::size_t i = size; i < this->capacity_; ++i) {
    this->data_[i] = 0;
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count, std::initializer_list<T> lst)
    : BaseMatrix(row_count, col_count) {
  std::size_t size = this->capacity_ <= lst.size() ? this->capacity_ : lst.size();
  typename std::initializer_list<T>::iterator iter = lst.begin();

  for (std::size_t i = 0; i < size; ++i, ++iter) {
    this->data_[i] = *iter;
  }

  for (std::size_t i = size; i < this->capacity_; ++i) {
    this->data_[i] = 0;
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix& other)
    : BaseMatrix(other.rows_, other.cols_) {
  std::copy(other.data_, other.data_ + other.capacity_, this->data_);
}

template <typename T>
BaseMatrix<T>::BaseMatrix(BaseMatrix&& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
BaseMatrix<T>::~BaseMatrix() {
  delete[] data_;
  this->rows_ = 0;
  this->cols_ = 0;
  this->capacity_ = 0;
  this->data_ = nullptr;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(const BaseMatrix<T>& other) {
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->capacity_ = other.capacity_;

    try {
      delete[] this->data_;
      this->data_ = new T[this->capacity_];

    } catch (std::bad_alloc& ex) {
      throw BadMemoryAllocationException("matrix_base::(bad memory allocation)!");
    }

    std::copy(other.data_, other.data_ + other.capacity_, this->data_);
  }

  return *this;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(BaseMatrix&& other) {
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->capacity_ = other.capacity_;

    delete[] this->data_;
    this->data_ = other.data_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }

  return *this;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(std::initializer_list<T> lst) {
  std::size_t size = this->capacity_ <= lst.size() ? this->capacity_ : lst.size();
  typename std::initializer_list<T>::const_iterator iter = lst.begin();

  for (std::size_t i = 0; i < size; ++i, ++iter) {
    this->data_[i] = *iter;
  }

  for (std::size_t i = size; i < this->capacity_; ++i) {
    this->data_[i] = 0;
  }

  return *this;
}

template <typename T>
typename BaseMatrix<T>::proxy BaseMatrix<T>::at(std::size_t index) {
  if (index < this->rows_) {
    return proxy(this->cols_, this->data_ + this->cols_ * index);

  } else {
    throw OutOfRangeException("matrix_base::(out of range index)!");
  }
}

template <typename T>
const typename BaseMatrix<T>::proxy BaseMatrix<T>::at(std::size_t index) const {
  if (index < this->rows_) {
    return proxy(this->cols_, this->data_ + this->cols_ * index);

  } else {
    throw OutOfRangeException("matrix_base::(out of range index)!");
  }
}

template <typename T>
typename BaseMatrix<T>::proxy BaseMatrix<T>::operator[](std::size_t index) {
  if (index < this->rows_) {
    return proxy(this->cols_, this->data_ + this->cols_ * index);

  } else {
    throw OutOfRangeException("matrix_base::(out of range index)!");
  }
}

template <typename T>
const typename BaseMatrix<T>::proxy BaseMatrix<T>::operator[](std::size_t index) const {
  if (index < this->rows_) {
    return proxy(this->cols_, this->data_ + this->cols_ * index);

  } else {
    throw OutOfRangeException("matrix_base::(out of range index)!");
  }
}

template <typename T>
typename BaseMatrix<T>::iterator BaseMatrix<T>::begin() {
  return iterator(this->data_);
}

template <typename T>
typename BaseMatrix<T>::const_iterator BaseMatrix<T>::cbegin() const {
  return const_iterator(this->data_);
}

template <typename T>
typename BaseMatrix<T>::iterator BaseMatrix<T>::end() {
  return iterator(this->data_ + this->capacity_);
}

template <typename T>
typename BaseMatrix<T>::const_iterator BaseMatrix<T>::cend() const {
  return const_iterator(this->data_ + this->capacity_);
}

template <typename T>
typename BaseMatrix<T>::iterator BaseMatrix<T>::rbegin() {
  return iterator(this->data_ + this->capacity_ - 1);
}

template <typename T>
typename BaseMatrix<T>::const_iterator BaseMatrix<T>::rcbegin() const {
  return const_iterator(this->data_ + this->capacity_ - 1);
}

template <typename T>
typename BaseMatrix<T>::iterator BaseMatrix<T>::rend() {
  return iterator(this->data_ - 1);
}

template <typename T>
typename BaseMatrix<T>::const_iterator BaseMatrix<T>::rcend() const {
  return const_iterator(this->data_ - 1);
}

template <typename T>
std::size_t BaseMatrix<T>::rows() const {
  return this->rows_;
}

template <typename T>
std::size_t BaseMatrix<T>::columns() const {
  return this->cols_;
}

template <typename T>
std::size_t BaseMatrix<T>::capacity() const {
  return this->capacity_;
}

template <typename T>
void BaseMatrix<T>::zero() {
  for (std::size_t i = 0; i < this->capacity_; ++i) {
    this->data_[i] = T();
  }
}

template <typename T>
void BaseMatrix<T>::swap(BaseMatrix<T>& other) {
  std::swap(this->rows_, other.rows_);
  std::swap(this->cols_, other.cols_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->data_, other.data_);
}

template <typename T>
void swap(BaseMatrix<T>& lhs, BaseMatrix<T>& rhs) {
  lhs.swap(rhs);
}

template <typename T>
bool operator==(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
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
bool operator!=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  return !(rhs == lhs);
}

template <typename T>
bool operator<(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
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
bool operator<=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator>(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  return !(lhs < rhs) && !(lhs == rhs);
}

template <typename T>
bool operator>=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const BaseMatrix<T>& mtx) {
  for (std::size_t i = 0; i < mtx.rows(); ++i) {

    for (std::size_t j = 0; j < mtx.columns(); ++j) {
      stream << mtx[i][j] << " ";
    }

    stream << std::endl;
  }

  return stream;
}

#endif // MATRIX_BASE_HPP

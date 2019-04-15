#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdexcept>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include "base_vector.h"
#include "iterator.h"
#include "exception.h"

template <typename T>
class Vector : public BaseVector {
 public:
  explicit Vector(size_t size = 1);
  Vector(const Vector<T>& other);
  Vector(Vector<T>&& other) noexcept;
  Vector(const std::initializer_list<T>& other);
  ~Vector() override;

  Vector<T>& operator=(const Vector<T>& other);
  Vector<T>& operator=(Vector&& other) noexcept;
  Vector<T>& operator=(const std::initializer_list<T>& other);

  T& operator[](size_t i);
  const T& operator[](size_t i) const;

  Vector<T>& Negate();
  Vector<T>& Add(const Vector<T>& other);
  Vector<T>& Add(const T& addend);
  Vector<T>& Subtract(const Vector<T>& other);
  Vector<T>& Multiply(const T& factor);
  Vector<T>& Divide(const T& factor);
  static T DotProduct(const Vector<T>& a, const Vector<T>& b);

  Vector<T>& operator+=(const Vector<T>& other);
  Vector<T>& operator-=(const Vector<T>& other);
  Vector<T>& operator*=(const T& factor);
  Vector<T>& operator/=(const T& factor);

//  template <typename U> friend Vector<U> operator-(const Vector<U>& a);
//  template <typename U> friend Vector<U> operator+(const Vector<U>& a, const Vector<U>& b);
//  template <typename U> friend Vector<U> operator-(const Vector<U>& a, const Vector<U>& b);
//  template <typename U> friend Vector<U> operator*(const Vector<U>& a, const U& factor);
//  template <typename U> friend Vector<U> operator*(const U& factor, const Vector<U>& a);
//  template <typename U> friend Vector<U> operator/(const Vector<U>& vector, const U& factor);
//  template <typename U> friend U operator*(const Vector<U>& a, const Vector<U>& b);

  Iterator<T> begin();
  Iterator<const T> begin() const;
  Iterator<T> end();
  Iterator<const T> end() const;

 private:
  T* data_ = nullptr;

  Vector<T>& Add(const Vector<T>& other, void (*f)(T&, const T&));
  Vector<T>& Multiply(const T& factor, void (*f)(T&, const T&));

  void CheckInvalidSizeException(const Vector<T>& other) const;
};

template<typename T>
Vector<T>::Vector(size_t size) : BaseVector(size), data_(new T[size]) {}

template<typename T>
Vector<T>::Vector(const Vector& other) : BaseVector(other.size_), data_(new T[other.size_]) {
  std::copy(other.begin(), other.end(), begin());
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : BaseVector(other.size_), data_(other.data_) {
  other.data_ = nullptr;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& other) {
  *this = other;
}

template<typename T>
Vector<T>::~Vector() { delete[] data_; }

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if (*this != other) {
    delete[] data_;
    data_ = new T[size_ = other.size];
    std::copy(other.begin(), other.end(), begin());
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  delete[] data_;
  size_ = other.size_;
  data_ = other.data_;
  other.data_ = nullptr;
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& other) {
  delete[] data_;
  data_ = new T[size_ = other.size()];
  std::copy(other.begin(), other.end(), begin());
  return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t i) {
  if (i >= size_)
    throw IndexOutOfRangeException();
  return data_[i];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const {
  if (i >= size_)
    throw IndexOutOfRangeException();
  return data_[i];
}

template <typename T>
void Vector<T>::CheckInvalidSizeException(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw InvalidSizeException();
}

template <typename T>
Vector<T>& Vector<T>::Negate() {
  for (auto& v: *this)
    v = -v;
  return *this;
}

template<typename T>
Vector<T>& Vector<T>::Add(const Vector<T>& other, void (*f)(T&, const T&)) {
    CheckInvalidSizeException(other);
    for (size_t i = 0; i != size_; ++i)
      f(data_[i], other.data_[i]);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::Add(const Vector<T>& other) {
  return Add(other, [](T& a, const T& b) { a += b; });
}

template <typename T>
Vector<T>& Vector<T>::Add(const T& addend) {
  CheckInvalidSizeException();
  for (auto& v: *this)
    v += addend;
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::Subtract(const Vector<T>& other) {
  return Add(other, [](T& a, const T& b) { a -= b; });
}

template <typename T>
Vector<T>& Vector<T>::Multiply(const T& factor, void (*f)(T&, const T&)) {
  for (auto& v: *this)
    f(v, factor);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::Multiply(const T& factor) {
  return Multiply(factor, [](T& v, const T& factor) { v *= factor; });
}

template <typename T>
Vector<T>& Vector<T>::Divide(const T& factor) {
  if (!factor)
    throw DivisionByZeroException();
  return Multiply(factor, [](T& v, const T& factor) { v /= factor; });
}

template <typename T>
T Vector<T>::DotProduct(const Vector<T>& a, const Vector<T>& b) {
  a.CheckInvalidSizeException(b);
  T result = 0;
  for (size_t i = 0; i != a.size_; ++i)
    result += a.data_[i] * b.data_[i];
  return result;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
  return Add(other);
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
  return Subtract(other);
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const T& factor) {
  return Multiply(factor);
}

template <typename T>
Vector<T>& Vector<T>::operator/=(const T& factor) {
  return Divide(factor);
}

template <typename T>
Vector<T> operator-(const Vector<T>& vector) {
  return Vector<T>(vector).Negate();
}

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
  return Vector<T>(a) += b;
}

template <typename T>
Vector<T> operator-(const Vector<T>& a, const Vector<T>& b) {
  return Vector<T>(a) -= b;
}

template <typename T>
Vector<T> operator*(const Vector<T>& vector, const T& factor) {
  return Vector<T>(vector) *= factor;
}

template <typename T>
Vector<T> operator*(const T& factor, const Vector<T>& vector) {
  return Vector<T>(vector) *= factor;
}

template <typename T>
Vector<T> operator/(const Vector<T>& vector, const T& factor) {
  return Vector<T>(vector) /= factor;
}

template <typename T>
T operator*(const Vector<T>& a, const Vector<T>& b) {
  return Vector<T>::DotProduct(a, b);
}

template <typename T>
Iterator<T> Vector<T>::begin() {
  return Iterator<T>(data_);
}

template <typename T>
Iterator<const T> Vector<T>::begin() const {
  return Iterator<const T>(data_);
}

template <typename T>
Iterator<T> Vector<T>::end() {
  return Iterator<T>(data_ + size_);
}

template <typename T>
Iterator<const T> Vector<T>::end() const {
  return Iterator<const T>(data_ + size_);
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vector) {
  for (auto& v: vector)
    is >> v;
  return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
  if (vector.size()) {
    os << '(';
    for (size_t i = 0; i + 1 < vector.size(); ++i)
      os << vector[i] << ", ";
    os << vector[vector.size() - 1] << ")";
  }
  return os;
}

#endif  // VECTOR_H_

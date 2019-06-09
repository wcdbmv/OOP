#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>

#include "base_vector.hpp"

template <typename T>
class Vector : public BaseVector<T> {
  const std::size_t GROW_COEF = 2;

 public:
  typedef typename BaseVector<T>::iterator iterator;
  typedef typename BaseVector<T>::const_iterator const_iterator;

  explicit Vector();
  explicit Vector(std::size_t);
  explicit Vector(std::size_t, const T&);
  Vector(iterator, iterator);
  Vector(const_iterator, const_iterator);
  Vector(std::initializer_list<T>);
  Vector(const Vector&);
  Vector(Vector&&);
  virtual ~Vector() = default;
  virtual Vector& operator=(const Vector&);
  Vector& operator=(Vector&&);
  void assign(std::size_t, const T&);
  void assign(iterator, iterator);
  void assign(const_iterator, const_iterator);

  std::size_t max_size() const;
  void reserve(std::size_t);
  void shrink_to_fit();

  void insert(std::size_t, const T&);
  void insert(std::size_t, T&&);
  void erase(std::size_t);
  void push_back(const T&);
  void push_back(T&&);
  void pop_back();
  void resize(std::size_t);
  void resize(std::size_t, const T&);
};

template <typename T>
Vector<T>::Vector() : BaseVector<T>() {

}

template <typename T>
Vector<T>::Vector(std::size_t count) : BaseVector<T>(count) {

}

template <typename T>
Vector<T>::Vector(std::size_t count, const T& value) : BaseVector<T>(count, value) {

}

template <typename T>
Vector<T>::Vector(iterator first, iterator last) : BaseVector<T>(first, last) {

}

template <typename T>
Vector<T>::Vector(const_iterator first, const_iterator last) : BaseVector<T>(first, last) {

}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst) : BaseVector<T>(lst) {

}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : BaseVector<T>(other) {

}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) : BaseVector<T>(std::move(other)) {

}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
  BaseVector<T>::operator=(rhs);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) {
  BaseVector<T>::operator=(std::move(rhs));
  return *this;
}

template <typename T>
void Vector<T>::assign(std::size_t count, const T& value) {
  if (count > this->capacity()) {
    this->capacity_ = count << GROW_COEF;
    this->reallocate();
  }

  for (std::size_t i = 0; i < count; ++i) {
    (*this)[i] = value;
  }

  this->size_ = count;
}

template <typename T>
void Vector<T>::assign(iterator first, iterator last) {
  std::size_t count = last - first;

  if (count > this->capacity()) {
    this->capacity_ = count << GROW_COEF;
    this->reallocate();
  }

  for (std::size_t i = 0; i < count; ++i, ++first) {
    (*this)[i] = *first;
  }

  this->size_ = count;
}

template <typename T>
void Vector<T>::assign(const_iterator first, const_iterator last) {
  std::size_t count = last - first;

  if (count > this->capacity()) {
    this->capacity_ = count << GROW_COEF;
    this->reallocate();
  }

  for (std::size_t i = 0; i < count; ++i, ++first) {
    (*this)[i] = *first;
  }

  this->size_ = count;
}

template <typename T>
std::size_t Vector<T>::max_size() const {
  return this->capacity();
}

template <typename T>
void Vector<T>::reserve(std::size_t size) {
  if (size > this->capacity_) {
    this->capacity_ = size;
    this->reallocate();
  }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  this->capacity_ = this->size();
  this->reallocate();
}

template <typename T>
void Vector<T>::insert(std::size_t pos, const T& value) {
  if (this->size() == this->capacity()) {
    this->capacity_ <<= GROW_COEF;
    this->reallocate();
  }

  T* mem_flag = this->data_ + pos;
  std::memmove(mem_flag + 1, mem_flag, (this->size() - (mem_flag - this->data_)) * sizeof(T));
  ++this->size_;
  (*this)[pos] = value;
}

template <typename T>
void Vector<T>::insert(std::size_t pos, T&& value) {
  if (this->size() == this->capacity()) {
    this->capacity_ <<= GROW_COEF;
    this->reallocate();
  }

  T* mem_flag = this->data_ + pos;
  std::memmove(mem_flag + 1, mem_flag, (this->size() - (mem_flag - this->data_)) * sizeof(T));
  ++this->size_;
  (*this)[pos] = std::move(value);
}

template <typename T>
void Vector<T>::erase(std::size_t pos) {
  T* mem_flag = this->data_ + pos;
  std::memmove(mem_flag, mem_flag + 1, (this->size() - (mem_flag - this->data_) - 1) * sizeof(T));
  --this->size_;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (this->size() == this->capacity()) {
    this->capacity_ <<= GROW_COEF;
    this->reallocate();
  }

  (*this)[this->size_++] = value;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
  if (this->size() == this->capacity()) {
    this->capacity_ <<= GROW_COEF;
    this->reallocate();
  }

  (*this)[this->size_++] = std::move(value);
}

template <typename T>
void Vector<T>::pop_back() {
  --this->size_;
}

template <typename T>
void Vector<T>::resize(std::size_t size) {
  if (size > this->size()) {

    if (size > this->capacity_) {
      this->capacity_ = size;
      this->reallocate();
    }

  } else {

    for (std::size_t i = this->size(); i < size; ++i) {
      (*this)[i].~T();
    }
  }

  this->size_ = size;
}

template <typename T>
void Vector<T>::resize(std::size_t size, const T& value) {
  if (size > this->size()) {

    if (size > this->capacity()) {
      this->capacity_ = size;
      this->reallocate();
    }

    for (std::size_t i = this->size(); i < size; ++i) {
      (*this)[i] = value;
    }

  } else {

    for (std::size_t i = this->size(); i < size; ++i) {
      (*this)[i].~T();
    }
  }

  this->size_ = size;
}

#endif // VECTOR_HPP

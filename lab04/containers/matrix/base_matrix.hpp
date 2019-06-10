#ifndef LAB04_CONTAINERS_MATRIX_BASE_MATRIX_HPP_
#define LAB04_CONTAINERS_MATRIX_BASE_MATRIX_HPP_

#include <ostream>

#include "exceptions/container_exceptions.hpp"
#include "containers/iterator/iterator.hpp"
#include "containers/iterator/const_iterator.hpp"

template <typename T>
class BaseMatrix {
  // TODO: refactor

  class Proxy {
   public:
    Proxy(std::size_t, T*);

    T& at(std::size_t);
    const T& at(std::size_t) const;
    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;

   private:
    std::size_t cols_;
    T* data_;
  };

 public:
  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;

  explicit BaseMatrix(std::size_t, std::size_t);
  explicit BaseMatrix(std::size_t, std::size_t, const T&);
  BaseMatrix(std::size_t, std::size_t, const_iterator, const_iterator);
  BaseMatrix(std::size_t, std::size_t, std::initializer_list<T>);
  BaseMatrix(const BaseMatrix&);
  BaseMatrix(BaseMatrix&&) noexcept;
  virtual ~BaseMatrix();
  BaseMatrix& operator=(const BaseMatrix&);
  BaseMatrix& operator=(BaseMatrix&&) noexcept;
  virtual BaseMatrix& operator=(std::initializer_list<T>);

  Proxy at(std::size_t);
  const Proxy at(std::size_t) const;
  Proxy operator[](std::size_t);
  const Proxy operator[](std::size_t) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  std::size_t rows() const;
  std::size_t columns() const;
  std::size_t capacity() const;

  void zero();

 protected:
  std::size_t rows_;
  std::size_t cols_;
  std::size_t capacity_;
  T* data_;
};

template <typename T>
inline bool operator==(const BaseMatrix<T>&, const BaseMatrix<T>&);
template <typename T>
inline bool operator!=(const BaseMatrix<T>&, const BaseMatrix<T>&);
template <typename T>
inline std::ostream& operator<<(std::ostream&, const BaseMatrix<T>&);

#include "detail/base_matrix.hpp"

#endif  // LAB04_CONTAINERS_MATRIX_BASE_MATRIX_HPP_

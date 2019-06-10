#ifndef LAB04_CONTAINERS_MATRIX_MATRIX_HPP_
#define LAB04_CONTAINERS_MATRIX_MATRIX_HPP_

#include "base_matrix.hpp"

template <typename T>
class Matrix : public BaseMatrix<T> {
 public:
  using Base = BaseMatrix<T>;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base ::const_iterator;

 public:
  explicit Matrix(std::size_t, std::size_t);
  explicit Matrix(std::size_t, std::size_t, const T&);
  Matrix(std::size_t, std::size_t, const_iterator, const_iterator);
  Matrix(std::size_t, std::size_t, std::initializer_list<T>);
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  virtual ~Matrix() = default;
  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&) noexcept;
  virtual Matrix& operator=(std::initializer_list<T>);

  Matrix& operator+=(const Matrix&);
  Matrix& operator+=(const T&);
  Matrix& operator-=(const Matrix&);
  Matrix& operator-=(const T&);
  Matrix& operator*=(const Matrix&);
  Matrix& operator*=(const T&);
  Matrix& operator/=(const T&);
};

template <typename T>
Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);
template <typename T>
Matrix<T> operator+(const Matrix<T>&, const T&);
template <typename T>
Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);
template <typename T>
Matrix<T> operator-(const Matrix<T>&, const T&);
template <typename T>
Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);
template <typename T>
Matrix<T> operator*(const Matrix<T>&, const T&);
template <typename T>
Matrix<T> operator/(const Matrix<T>&, const T&);

#include "detail/matrix4x4.hpp"

#endif  // LAB04_CONTAINERS_MATRIX_MATRIX_HPP_

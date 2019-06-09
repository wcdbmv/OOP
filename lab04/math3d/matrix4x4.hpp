#ifndef LAB04_MATH3D_MATRIX4X4_HPP_
#define LAB04_MATH3D_MATRIX4X4_HPP_

#include "containers/matrix/matrix.hpp"
#include "vector4d.hpp"
#include "point3d.hpp"

template <typename T>
class Matrix4x4 : public Matrix<T> {
  static_assert(std::is_arithmetic<T>::value, "Type nust be arithmetic!");

 public:
  Matrix4x4();
  Matrix4x4(std::initializer_list<T>);
  Matrix4x4(const Matrix4x4&);
  Matrix4x4(Matrix4x4&&) noexcept;
  ~Matrix4x4() = default;

  Matrix4x4& operator=(const Matrix4x4&);
  Matrix4x4& operator=(Matrix4x4&&) noexcept;
  Matrix4x4& operator=(std::initializer_list<T>);

  Vector4D<T> operator*(const Vector4D<T>&) const;
  Matrix4x4 operator*(const T&) const;
  Point3D<T> operator*(const Point3D<T>&) const;

  template <typename U>
  friend Vector4D<U> operator*(const Vector4D<U>&, const Matrix4x4<U>&);
};

template <typename T>
Matrix4x4<T>::Matrix4x4()
    : Matrix<T>(4, 4) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(std::initializer_list<T> lst)
    : Matrix<T>(4, 4, lst) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& other)
    : Matrix<T>(other) {}

template <typename T>
Matrix4x4<T>::Matrix4x4(Matrix4x4<T>&& other) noexcept
    : Matrix<T>(std::move(other)) {}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4& rhs) {
  Matrix<T>::operator=(rhs);
  return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(Matrix4x4&& rhs) noexcept {
  Matrix<T>::operator=(std::move(rhs));
  return *this;
}

template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(std::initializer_list<T> lst) {
  Matrix<T>::operator=(lst);
  return *this;
}

template <typename T>
Vector4D<T> Matrix4x4<T>::operator*(const Vector4D<T>& vector) const {
  Vector4D<T> result = {0, 0, 0, 0};

  for (std::size_t i = 0; i < 4; ++i)
    for (std::size_t j = 0; j < 4; ++j)
      result[i] += (*this)[i][j] * vector[j];

  return result;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const T& value) const {
  Matrix4x4<T> result = *this;

  for (std::size_t i = 0; i < Matrix<T>::capacity(); ++i)
    result.data_[i] *= value;

  return result;
}

template <typename T>
Point3D<T> Matrix4x4<T>::operator*(const Point3D<T>& point) const {
  Vector<T> vector = point.ToVector4D();
  Vector<T> result = {0, 0, 0, 0};

  for (std::size_t i = 0; i < 4; ++i)
    for (std::size_t j = 0; j < 4; ++j)
      result[i] += (*this)[i][j] * vector[j];

  return Point3D<T>(result[0], result[1], result[2]);
}

template <typename T>
Vector4D<T> operator*(const Vector4D<T>& vector, const Matrix4x4<T>& matrix) {
  Vector4D<T> result = {0, 0, 0, 0};

  for (std::size_t i = 0; i < 4; ++i)
    for (std::size_t j = 0; j < 4; ++j)
      result[i] += matrix[i][j] * vector[j];

  return result;
}

#endif  // LAB04_MATH3D_MATRIX4X4_HPP_

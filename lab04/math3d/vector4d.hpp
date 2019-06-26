#ifndef LAB04_MATH3D_VECTOR4D_HPP_
#define LAB04_MATH3D_VECTOR4D_HPP_

#include <cmath>

#include "containers/vector/vector.hpp"

template <typename T>
class Vector4D : public Vector<4, T> {
  static_assert(std::is_arithmetic<T>::value, "Type must be arithmetic");

 public:
  Vector4D();
  Vector4D(const T&, const T&, const T&);
  Vector4D(std::initializer_list<T>);
  Vector4D(const Vector4D&);
  Vector4D(Vector4D&&) noexcept;

  Vector4D& operator=(const Vector<4, T>&);
  Vector4D& operator=(Vector4D&&) noexcept;

  T Length();
  void Normalize();

  static T Dot(const Vector4D&, const Vector4D&);
  static Vector4D Cross(const Vector4D&, const Vector4D&);
};

#include "detail/vector4d.hpp"

#endif  // LAB04_MATH3D_VECTOR4D_HPP_

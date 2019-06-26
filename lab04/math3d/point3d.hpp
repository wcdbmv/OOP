#ifndef LAB04_MATH3D_POINT3D_HPP
#define LAB04_MATH3D_POINT3D_HPP

#include <istream>
#include <ostream>

#include "containers/vector/vector.hpp"

template <typename T>
class Point3D {
  static_assert(std::is_arithmetic<T>::value, "Type must be arithmetic");

 public:
  constexpr explicit Point3D();
  constexpr explicit Point3D(const T&, const T&, const T&);
  constexpr Point3D(const Point3D&);
  constexpr Point3D& operator=(const Point3D&);

  constexpr T& x();
  constexpr const T& x() const;
  constexpr T& y();
  constexpr const T& y() const;
  constexpr T& z();
  constexpr const T& z() const;

  Vector<4, T> ToVector4D() const;

  constexpr Point3D& operator+=(const Point3D&);
  constexpr Point3D& operator+=(const T&);
  constexpr Point3D& operator-=(const Point3D&);
  constexpr Point3D& operator-=(const T&);
  constexpr Point3D& operator*=(const Point3D&);
  constexpr Point3D& operator*=(const T&);
  constexpr Point3D& operator/=(const Point3D&);
  constexpr Point3D& operator/=(const T&);

 private:
  T x_, y_, z_;
};

template <typename T>
constexpr bool operator==(const Point3D<T>& lhs, const Point3D<T>& rhs);
template <typename T>
constexpr bool operator!=(const Point3D<T>& lhs, const Point3D<T>& rhs);

template <typename T>
constexpr Point3D<T> operator+(const Point3D<T>& lhs, const Point3D<T>& rhs);
template <typename T>
constexpr Point3D<T> operator+(const Point3D<T>& point, const T& value);
template <typename T>
constexpr Point3D<T> operator-(const Point3D<T>& lhs, const Point3D<T>& rhs);
template <typename T>
constexpr Point3D<T> operator-(const Point3D<T>& point, const T& value);
template <typename T>
constexpr Point3D<T> operator*(const Point3D<T>& lhs, const Point3D<T>& rhs);
template <typename T>
constexpr Point3D<T> operator*(const Point3D<T>& point, const T& value);
template <typename T>
constexpr Point3D<T> operator/(const Point3D<T>& lhs, const Point3D<T>& rhs);
template <typename T>
constexpr Point3D<T> operator/(const Point3D<T>& point, const T& value);

template <typename T>
std::istream& operator>>(std::istream& is, Point3D<T>& point);
template <typename T>
std::ostream& operator<<(std::ostream& os, const Point3D<T>& point);

#include "detail/point3d.hpp"

#endif  // LAB04_MATH3D_POINT3D_HPP

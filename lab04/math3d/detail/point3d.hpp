template <typename T>
constexpr Point3D<T>::Point3D()
    : x_(0), y_(0), z_(0) {}

template <typename T>
constexpr Point3D<T>::Point3D(const T& x, const T& y, const T& z)
    : x_(x), y_(y), z_(z) {}

template <typename T>
constexpr Point3D<T>::Point3D(const Point3D<T>& other)
    : Point3D(other.x_, other.y_, other.z_) {}


template <typename T>
constexpr Point3D<T>& Point3D<T>::operator=(const Point3D<T>& rhs) {
  x_ = rhs.x_;
  y_ = rhs.y_;
  z_ = rhs.z_;

  return *this;
}

template <typename T>
constexpr T& Point3D<T>::x() {
  return x_;
}

template <typename T>
constexpr const T& Point3D<T>::x() const {
  return x_;
}

template <typename T>
constexpr T& Point3D<T>::y() {
  return y_;
}

template <typename T>
constexpr const T& Point3D<T>::y() const {
  return y_;
}

template <typename T>
constexpr T& Point3D<T>::z() {
  return z_;
}

template <typename T>
constexpr const T& Point3D<T>::z() const {
  return z_;
}

template <typename T>
Vector<T> Point3D<T>::ToVector4D() const {
  return Vector<T>({x_, y_, z_, 1});
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator+=(const Point3D<T>& pnt) {
  x_ += pnt.x_;
  y_ += pnt.y_;
  z_ += pnt.z_;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator+=(const T& value) {
  x_ += value;
  y_ += value;
  z_ += value;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator-=(const Point3D<T>& rhs) {
  x_ -= rhs.x_;
  y_ -= rhs.y_;
  z_ -= rhs.z_;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator-=(const T& value) {
  x_ -= value;
  y_ -= value;
  z_ -= value;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator*=(const Point3D<T>& rhs) {
  x_ *= rhs.x_;
  y_ *= rhs.y_;
  z_ *= rhs.z_;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator*=(const T& value) {
  x_ *= value;
  y_ *= value;
  z_ *= value;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator/=(const Point3D<T>& rhs) {
  x_ /= rhs.x_;
  y_ /= rhs.y_;
  z_ /= rhs.z_;

  return *this;
}

template <typename T>
constexpr Point3D<T>& Point3D<T>::operator/=(const T& value) {
  x_ /= value;
  y_ /= value;
  z_ /= value;

  return *this;
}

template <typename T>
constexpr bool operator==(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
}

template <typename T>
constexpr bool operator!=(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
constexpr Point3D<T> operator+(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return Point3D<T>(lhs) += rhs;
}

template <typename T>
constexpr Point3D<T> operator+(const Point3D<T>& point, const T& value) {
  return Point3D<T>(point) += value;
}

template <typename T>
constexpr Point3D<T> operator-(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return Point3D<T>(lhs) -= rhs;
}

template <typename T>
constexpr Point3D<T> operator-(const Point3D<T>& point, const T& value) {
  return Point3D<T>(point) -= value;
}

template <typename T>
constexpr Point3D<T> operator*(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return Point3D<T>(lhs) *= rhs;
}

template <typename T>
constexpr Point3D<T> operator*(const Point3D<T>& point, const T& value) {
  return Point3D<T>(point) *= value;
}

template <typename T>
constexpr Point3D<T> operator/(const Point3D<T>& lhs, const Point3D<T>& rhs) {
  return Point3D<T>(lhs) += rhs;
}

template <typename T>
constexpr Point3D<T> operator/(const Point3D<T>& point, const T& value) {
  return Point3D<T>(point) += value;
}

template <typename T>
std::istream& operator>>(std::istream& is, Point3D<T>& point) {
  return is >> point.x() >> point.y() >> point.z();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point3D<T>& point) {
  return os << point.x() << ' ' << point.y() << ' ' << point.z();
}

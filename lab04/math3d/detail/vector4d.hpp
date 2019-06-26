template <typename T>
Vector4D<T>::Vector4D()
    : Vector<4, T>{0, 0, 0, 1} {}

template <typename T>
Vector4D<T>::Vector4D(const T& x, const T& y, const T& z)
    : Vector<4, T>{x, y, z, 1} {}

template <typename T>
Vector4D<T>::Vector4D(std::initializer_list<T> lst)
    : Vector<4, T>(lst) {}

template <typename T>
Vector4D<T>::Vector4D(const Vector4D<T>& other)
    : Vector<4, T>(other) {}

template <typename T>
Vector4D<T>::Vector4D(Vector4D<T>&& other) noexcept
    : Vector<4, T>(std::move(other)) {}

template <typename T>
T Vector4D<T>::Length() {
  const auto x = (*this)[0];
  const auto y = (*this)[1];
  const auto z = (*this)[2];

  return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
void Vector4D<T>::Normalize() {
  const T norm = 1 / Length();

  for (std::size_t i = 0; i < Vector<4, T>::size() - 1; ++i)
    (*this)[i] *= norm;
}

template <typename T>
T Vector4D<T>::Dot(const Vector4D<T>& v1, const Vector4D<T>& v2) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <typename T>
Vector4D<T> Vector4D<T>::Cross(const Vector4D<T>& v1, const Vector4D<T>& v2) {
  Vector4D<T> result;

  result[0] = v1[2] * v2[1] - v1[1] * v2[2];
  result[1] = v1[0] * v2[2] - v1[2] * v2[0];
  result[2] = v1[1] * v2[0] - v1[0] * v2[1];
  result[3] = 1;

  return result;
}

template <typename T>
Vector4D<T>& Vector4D<T>::operator=(const Vector<4, T>& other) {
  Vector<4, T>::operator=(other);
  return *this;
}

template <typename T>
Vector4D<T>& Vector4D<T>::operator=(Vector4D<T>&& other) noexcept {
  Vector<4, T>::operator=(std::move(other));
  return *this;
}

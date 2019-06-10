template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols)
    : Base(rows, cols) {}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const T& value)
    : Base(rows, cols, value) {}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const_iterator first, const_iterator last)
    : Base(rows, cols, first, last) {}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, std::initializer_list<T> list)
    : Base(rows, cols, list) {}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : Base(other) {}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : Base(std::move(other)) {}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
  Base::operator=(rhs);

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept {
  Base::operator=(std::move(rhs));

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<T> lst) {
  Base::operator=(lst);

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
  const std::size_t rows = Base::rows() < rhs.rows() ? Base::rows() : rhs.rows();
  const std::size_t cols = Base::columns() < rhs.columns() ? Base::columns() : rhs.columns();

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      (*this)[i][j] += rhs[i][j];

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& value) {
  for (std::size_t i = 0; i < Base::capacity(); ++i)
    Base::data_[i] += value;

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
  const std::size_t rows = Base::rows() < rhs.rows() ? Base::rows() : rhs.rows();
  const std::size_t cols = Base::columns() < rhs.columns() ? Base::columns() : rhs.columns();

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      (*this)[i][j] -= rhs[i][j];

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& value) {
  for (std::size_t i = 0; i < Base::capacity(); ++i)
    Base::data_[i] -= value;

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  if (Base::columns() == rhs.rows()) {
    for (std::size_t i = 0; i < Base::rows(); ++i)
      for (std::size_t j = 0; j < rhs.columns(); ++j)
        for (std::size_t k = 0; k < Base::columns(); ++k)
          (*this)[i][j] = (*this)[i][k] * rhs[k][j];

    return *this;

  } else {
    throw OutOfRangeException("Matrix::(Multiplication error)");
  }
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
  for (std::size_t i = 0; i < Base::capacity(); ++i)
    Base::data_[i] *= value;

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
  for (std::size_t i = 0; i < Base::capacity(); ++i)
    Base::data_[i] /= value;

  return *this;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  return Matrix<T>(lhs) += rhs;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& matrix, const T& value) {
  return Matrix<T>(matrix) += value;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  return Matrix<T>(lhs) -= rhs;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& matrix, const T& value) {
  return Matrix<T>(matrix) -= value;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  return Matrix<T>(lhs) *= rhs;
}

template <typename T>
Matrix<T>& operator*(const Matrix<T>& matrix, const T& value) {
  return Matrix<T>(matrix) *= value;
}

template <typename T>
Matrix<T>& operator/(const Matrix<T>& matrix, const T& value) {
  return Matrix<T>(matrix) *= value;
}

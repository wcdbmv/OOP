#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "base_matrix.hpp"

template <typename T>
class Matrix : public BaseMatrix<T> {
 public:
  typedef typename BaseMatrix<T>::iterator iterator;
  typedef typename BaseMatrix<T>::const_iterator const_iterator;

  explicit Matrix(size_t, size_t);
  explicit Matrix(size_t, size_t, const T&);
  Matrix(size_t, size_t, iterator, iterator);
  Matrix(size_t, size_t, const_iterator, const_iterator);
  Matrix(size_t, size_t, std::initializer_list<T>);
  Matrix(const Matrix&);
  Matrix(Matrix&&);
  virtual ~Matrix() = default;
  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&);
  virtual Matrix& operator=(std::initializer_list<T>);

  template <typename U>
  friend Matrix<U> operator+(const Matrix<U>&, const Matrix<U>&);
  template <typename U>
  friend Matrix<U> operator+(const Matrix<U>&, const U&);
  Matrix& operator+=(const Matrix&);
  Matrix& operator+=(const T&);
  template <typename U>
  friend Matrix<U> operator-(const Matrix<U>&, const Matrix<U>&);
  template <typename U>
  friend Matrix<U> operator-(const Matrix<U>&, const U&);
  Matrix& operator-=(const Matrix&);
  Matrix& operator-=(const T&);
  template <typename U>
  friend Matrix<U> operator*(const Matrix<U>&, const Matrix<U>&);
  template <typename U>
  friend Matrix<U> operator*(const Matrix<U>&, const U&);
  Matrix& operator*=(const Matrix&);
  Matrix& operator*=(const T&);
  template <typename U>
  friend Matrix<U> operator/(const Matrix<U>&, const U&);
  Matrix& operator/=(const T&);
};

template <typename T>
Matrix<T>::Matrix(size_t row_count, size_t col_count)
    : BaseMatrix<T>(row_count, col_count) {

}

template <typename T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, const T& value)
    : BaseMatrix<T>(row_count, col_count, value) {

}

template <typename T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, iterator first, iterator last)
    : BaseMatrix<T>(row_count, col_count, first, last) {

}

template <typename T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, const_iterator first, const_iterator last)
    : BaseMatrix<T>(row_count, col_count, first, last) {

}

template <typename T>
Matrix<T>::Matrix(size_t row_count, size_t col_count, std::initializer_list<T> lst)
    : BaseMatrix<T>(row_count, col_count, lst) {

}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : BaseMatrix<T>(other) {

}

template <typename T>
Matrix<T>::Matrix(Matrix&& other)
    : BaseMatrix<T>(std::move(other)) {

}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
  BaseMatrix<T>::operator=(rhs);

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) {
  BaseMatrix<T>::operator=(std::move(rhs));

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<T> lst) {
  BaseMatrix<T>::operator=(lst);

  return *this;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  Matrix<T> result = lhs;
  size_t rows_count = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows();
  size_t cols_count = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();

  for (size_t i = 0; i < rows_count; ++i) {

    for (size_t j = 0; j < cols_count; ++j) {
      result[i][j] += rhs[i][j];
    }
  }

  return result;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& mtx, const T& value) {
  Matrix<T> result = mtx;

  for (size_t i = 0; i < mtx.capacity(); ++i) {
    result.data_[i] += value;
  }

  return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
  size_t rows_count = this->rows() < rhs.rows() ? this->rows() : rhs.rows();
  size_t cols_count = this->columns() < rhs.columns() ? this->columns() : rhs.columns();

  for (size_t i = 0; i < rows_count; ++i) {

    for (size_t j = 0; j < cols_count; ++j) {
      (*this)[i][j] += rhs[i][j];
    }
  }

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& value) {
  for (size_t i = 0; i < this->capacity(); ++i) {
    this->data_[i] += value;
  }

  return *this;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  Matrix<T> result = lhs;
  size_t rows_count = lhs.rows() < rhs.rows() ? lhs.rows() : rhs.rows();
  size_t cols_count = lhs.columns() < rhs.columns() ? lhs.columns() : rhs.columns();

  for (size_t i = 0; i < rows_count; ++i) {

    for (size_t j = 0; j < cols_count; ++j) {
      result[i][j] -= rhs[i][j];
    }
  }

  return result;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& mtx, const T& value) {
  Matrix<T> result = mtx;

  for (size_t i = 0; i < mtx.capacity(); ++i) {
    result.data_[i] -= value;
  }

  return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
  size_t rows_count = this->rows() < rhs.rows() ? this->rows() : rhs.rows();
  size_t cols_count = this->columns() < rhs.columns() ? this->columns() : rhs.columns();

  for (size_t i = 0; i < rows_count; ++i) {

    for (size_t j = 0; j < cols_count; ++j) {
      (*this)[i][j] -= rhs[i][j];
    }
  }

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& value) {
  for (size_t i = 0; i < this->capacity(); ++i) {
    this->data_[i] -= value;
  }

  return *this;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  if (lhs.columns() == rhs.rows()) {
    Matrix<T> result = lhs;

    for (size_t i = 0; i < lhs.rows(); ++i) {

      for (size_t j = 0; j < rhs.columns(); ++j) {

        for (size_t k = 0; k < lhs.columns(); ++k) {
          result[i][j] += lhs[i][k] * rhs[k][j];
        }
      }
    }

    return result;

  } else {
    throw OutOfRangeException("matrix::(error multiplicating matrixes)!");
  }
}

template <typename T>
Matrix<T>& operator*(const Matrix<T>& mtx, const T& value) {
  Matrix<T> result = mtx;

  for (size_t i = 0; i < mtx.capacity(); ++i) {
    result.data_[i] *= value;
  }

  return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  if (this->columns() == rhs.rows()) {

    for (size_t i = 0; i < this->rows(); ++i) {

      for (size_t j = 0; j < rhs.columns(); ++j) {

        for (size_t k = 0; k < this->columns(); ++k) {
          (*this)[i][j] = (*this)[i][k] * rhs[k][j];
        }
      }
    }

    return *this;

  } else {
    throw OutOfRangeException("matrix::(error multiplicating matrixes)!");
  }
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
  for (size_t i = 0; i < this->capacity(); ++i) {
    this->data_[i] *= value;
  }

  return *this;
}

template <typename T>
Matrix<T>& operator/(const Matrix<T>& mtx, const T& value) {
  Matrix<T> result = mtx;

  for (size_t i = 0; i < mtx.capacity(); ++i) {
    result.data_[i] /= value;
  }

  return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
  for (size_t i = 0; i < this->capacity(); ++i) {
    this->data_[i] /= value;
  }

  return *this;
}

#endif // MATRIX_HPP

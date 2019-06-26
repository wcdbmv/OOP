#ifndef LAB04_CONTAINERS_MATRIX_RECTANGULAR_MATRIX_HPP_
#define LAB04_CONTAINERS_MATRIX_RECTANGULAR_MATRIX_HPP_

#include "containers/vector/vector.hpp"

template <std::size_t rows, std::size_t cols, typename T>
class RectangularMatrix {
 public:
  using value_type = Vector<cols, T>;
  using reference = Vector<cols, T> &;
  using const_reference = const Vector<cols, T> &;

  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

 public:
  constexpr RectangularMatrix() = default;
  constexpr explicit RectangularMatrix(T value) noexcept;
  constexpr RectangularMatrix(std::initializer_list<Vector <cols, T>> list) noexcept;

  constexpr iterator begin();
  constexpr const_iterator begin() const;
  constexpr iterator end();
  constexpr const_iterator end() const;

  constexpr reference operator[](size_type index);
  constexpr const_reference operator[](size_type index) const;
  reference at(size_type index);
  const_reference at(size_type index) const;

 protected:
  Vector<rows, Vector<cols, T>> data_;
};

template <std::size_t rows, std::size_t cols, typename T>
std::istream& operator<<(std::istream& is, RectangularMatrix<rows, cols, T>& matrix);
template <std::size_t rows, std::size_t cols, typename T>
std::ostream& operator<<(std::ostream& os, const RectangularMatrix<rows, cols, T>& matrix);

template <std::size_t L, std::size_t M, std::size_t N, typename T>
const RectangularMatrix<L, N, T> operator*(const RectangularMatrix<L, M, T>& m1, const RectangularMatrix<M, N, T>& m2);

#include "detail/rectangular_matrix.hpp"

#endif  // LAB04_CONTAINERS_MATRIX_RECTANGULAR_MATRIX_HPP_

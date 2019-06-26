#ifndef LAB04_CONTAINERS_MATRIX_MATRIX_HPP_
#define LAB04_CONTAINERS_MATRIX_MATRIX_HPP_

#include "rectangular_matrix.hpp"

template <std::size_t size, typename T>
class Matrix : public RectangularMatrix<size, size, T> {
 public:
  using Base = RectangularMatrix<size, size, T>;
  using value_type = typename Base::value_type;
  using reference = typename Base::reference;
  using const_reference = typename Base::const_reference;

  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using size_type = typename Base::size_type;

 public:
  constexpr static Matrix Identity();

  constexpr Matrix() noexcept = default;
  constexpr explicit Matrix(T value) noexcept;
  constexpr Matrix(std::initializer_list<Vector<size, T>> list) noexcept;
};

#include "detail/matrix.hpp"

#endif  // LAB04_CONTAINERS_MATRIX_MATRIX_HPP_

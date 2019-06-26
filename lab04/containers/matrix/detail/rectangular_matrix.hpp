template <std::size_t rows, std::size_t cols, typename T>
constexpr RectangularMatrix<rows, cols, T>::RectangularMatrix(T value) noexcept
    : data_(Vector<cols, T>(value)) {}

template <std::size_t rows, std::size_t cols, typename T>
constexpr RectangularMatrix<rows, cols, T>::RectangularMatrix(std::initializer_list<Vector < cols, T>> list) noexcept
    : data_ {} {
  auto i = begin();
  for (auto j = list.begin(); i != end() && j != list.end(); ++i, ++j)
    *i = *j;
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::begin() -> iterator {
  return data_.begin();
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::begin() const -> const_iterator {
  return data_.begin();
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::end() -> iterator {
  return data_.end();
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::end() const -> const_iterator {
  return data_.end();
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::operator[](RectangularMatrix::size_type index) -> reference {
  return data_[index];
}

template <std::size_t rows, std::size_t cols, typename T>
constexpr auto RectangularMatrix<rows, cols, T>::operator[](RectangularMatrix::size_type index) const -> const_reference {
  return data_[index];
}

template <std::size_t rows, std::size_t cols, typename T>
auto RectangularMatrix<rows, cols, T>::at(RectangularMatrix::size_type index) -> reference {
  if (index >= rows)
    throw std::out_of_range("RectangularMatrix::at");
  return data_.at(index);
}

template <std::size_t rows, std::size_t cols, typename T>
auto RectangularMatrix<rows, cols, T>::at(RectangularMatrix::size_type index) const -> const_reference {
  if (index >= rows)
    throw std::out_of_range("RectangularMatrix::at");
  return data_.at(index);
}

template <std::size_t L, std::size_t M, std::size_t N, typename T>
const RectangularMatrix<L, N, T> operator*(const RectangularMatrix<L, M, T>& m1, const RectangularMatrix<M, N, T>& m2) {
  RectangularMatrix<L, N, T> result;

  for (std::size_t i = 0; i != L; ++i)
    for (std::size_t j = 0; j != N; ++j)
      for (std::size_t k = 0; k != M; ++k)
        result[i][j] += m1[i][k] * m2[k][j];

  return result;
}

template <std::size_t rows, std::size_t cols, typename T>
std::istream& operator<<(std::istream& is, RectangularMatrix<rows, cols, T>& matrix) {
  for (auto& row: matrix)
    is >> row;
  return is;
}

template <std::size_t rows, std::size_t cols, typename T>
std::ostream& operator<<(std::ostream& os, const RectangularMatrix<rows, cols, T>& matrix) {
  std::copy(matrix.begin(), matrix.end(), std::experimental::make_ostream_joiner(os, "\n"));
  return os;
}

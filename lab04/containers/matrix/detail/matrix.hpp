template <std::size_t size, typename T>
constexpr auto Matrix<size, T>::Identity() -> Matrix {
  return Matrix(1);
}

template <std::size_t size, typename T>
constexpr Matrix<size, T>::Matrix(T value) noexcept : Base{} {
  for (std::size_t i = 0; i != size; ++i)
    Base::data_[i][i] = value;
}

template <std::size_t size, typename T>
constexpr Matrix<size, T>::Matrix(std::initializer_list<Vector < size, T>> list) noexcept
    : Base(list) {}


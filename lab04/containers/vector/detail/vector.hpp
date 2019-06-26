#include <experimental/iterator>

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector() noexcept : data_{} {}

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector(const value_type& value) noexcept : data_{} {
  fill(value);
}

template <std::size_t Size, typename T>
constexpr Vector<Size, T>::Vector(std::initializer_list<value_type> list) noexcept : data_{} {
  // std::copy_n(list.begin(), min(size(), list.size()), begin()); — non-constexpr
  auto i = begin();
  for (auto j = list.begin(); i != end() && j != list.end(); ++i, ++j)
    *i = *j;
}

template <std::size_t Size, typename T> template <std::size_t OtherSize, typename U>
constexpr Vector<Size, T>::Vector(const Vector<OtherSize, U>& other) noexcept : data_{} {
  // std::copy_n(other.begin(), min(size(), other.size()), begin()); — non-constexpr
  for (std::size_t i = 0; i != min(size(), other.size()); ++i)
    data_[i] = other[i];
}

template <std::size_t Size, typename T>
constexpr void Vector<Size, T>::fill(const value_type& value) {
  // std::fill_n(begin(), size(), value); — non-constexpr
  for (std::size_t i = 0; i != size(); ++i)
    data_[i] = value;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::begin() -> iterator {
  return iterator(std::addressof(data_[0]));
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::begin() const -> const_iterator {
  return const_iterator(std::addressof(data_[0]));
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::end() -> iterator {
  return iterator(std::addressof(data_[Size]));
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::end() const -> const_iterator {
  return const_iterator(std::addressof(data_[Size]));
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::size() const -> size_type {
  return Size;
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator[](size_type index) -> reference {
  return data_[index];
}

template <std::size_t Size, typename T>
constexpr auto Vector<Size, T>::operator[](size_type index) const -> const_reference {
  return data_[index];
}

template <std::size_t Size, typename T>
auto Vector<Size, T>::at(size_type index) -> reference {
  if (index >= size())
    throw std::out_of_range("Vector::at");
  return data_[index];
}

template <std::size_t Size, typename T>
auto Vector<Size, T>::at(size_type index) const -> const_reference {
  if (index >= size())
    throw std::out_of_range("Vector::at");
  return data_[index];
}

template <std::size_t Size, typename T>
std::istream& operator>>(std::istream& is, Vector<Size, T>& vector) {
  for (auto& it: vector)
    is >> it;
  return is;
}

template <std::size_t Size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<Size, T>& vector) {
  std::copy(vector.begin(), vector.end(), std::experimental::make_ostream_joiner(os, " "));
  return os;
}

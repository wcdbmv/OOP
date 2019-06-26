#ifndef LAB04_CONTAINERS_VECTOR_VECTOR_HPP_
#define LAB04_CONTAINERS_VECTOR_VECTOR_HPP_

#include <initializer_list>
#include <istream>
#include <ostream>

template <std::size_t Size, typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  using iterator = value_type*;
  using const_iterator = const value_type*;
  using size_type = std::size_t;

 public:
  constexpr Vector() noexcept;
  constexpr explicit Vector(const value_type& value) noexcept;
  constexpr Vector(std::initializer_list<value_type> list) noexcept;
  template <std::size_t OtherSize, typename U>
  constexpr explicit Vector(const Vector<OtherSize, U>& other) noexcept;

  constexpr void fill(const value_type& value);

  constexpr iterator begin();
  constexpr const_iterator begin() const;
  constexpr iterator end();
  constexpr const_iterator end() const;

  constexpr size_type size() const;

  constexpr reference operator[](size_type index);
  constexpr const_reference operator[](size_type index) const;
  reference at(size_type index);
  const_reference at(size_type index) const;

 protected:
  T data_[Size ? Size : 1];
};

template <std::size_t Size, typename T>
std::istream& operator>>(std::istream& is, Vector<Size, T>& vector);
template <std::size_t Size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<Size, T>& vector);

#include "detail/vector.hpp"

#endif  // LAB04_CONTAINERS_VECTOR_VECTOR_HPP_

#ifndef LAB04_CONTAINERS_VECTOR_VECTOR_HPP_
#define LAB04_CONTAINERS_VECTOR_VECTOR_HPP_

#include <cstring>

#include "base_vector.hpp"

template <typename T>
class Vector : public BaseVector<T> {
 public:
  using Base = BaseVector<T>;
  using value_type = typename Base::value_type;
  using reference = typename Base::reference;
  using const_reference = typename Base::const_reference;

  using iterator = typename Base::iterator;
  using const_iterator = typename Base::const_iterator;
  using size_type = typename Base::size_type;

 public:
  explicit Vector();
  explicit Vector(size_type);
  explicit Vector(size_type, const_reference);
  explicit Vector(const_iterator, const_iterator);
  Vector(std::initializer_list<T>);
  Vector(size_type, std::initializer_list<T>);
  Vector(const Vector&);
  Vector(Vector&&) noexcept;
  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&) noexcept;

  std::size_t max_size() const;
  void reserve(std::size_t);
  void shrink_to_fit();

  void erase(std::size_t);
  void push_back(const T&);
  void push_back(T&&);
  void pop_back();

 private:
  static constexpr std::size_t GROW_COEF = 2;

  void GrowIfNeed();
};

#include "detail/vector.hpp"

#endif  // LAB04_CONTAINERS_VECTOR_VECTOR_HPP_

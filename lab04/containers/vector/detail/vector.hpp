template <typename T>
Vector<T>::Vector()
    : Base() {}

template <typename T>
Vector<T>::Vector(size_type size)
    : Base(size) {}

template <typename T>
Vector<T>::Vector(size_type size, const_reference value)
    : Base(size, value) {}

template <typename T>
Vector<T>::Vector(const_iterator first, const_iterator last)
    : Base(first, last) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
    : Base(list) {}

template <typename T>
Vector<T>::Vector(size_type size, std::initializer_list<T> list)
    : Base(size, list) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : Base(other) {}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
    : Base(other) {}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
  Base::operator=(rhs);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) noexcept {
  Base::operator=(rhs);
  return *this;
}

template <typename T>
std::size_t Vector<T>::max_size() const {
  return Base::capacity();
}

template <typename T>
void Vector<T>::reserve(std::size_t size) {
  if (size > Base::capacity())
    Base::Reallocate(size);
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (Base::size() != Base::capacity())
    Base::Reallocate(Base::size());
}

template <typename T>
void Vector<T>::erase(std::size_t index)  {
  T* mem_flag = Base::data_ + index;
  std::memmove(mem_flag, mem_flag + 1, (Base::size() - (mem_flag - Base::data_) - 1) * sizeof(T));
  --Base::size_;
}

template <typename T>
void Vector<T>::GrowIfNeed() {
  if (Base::size() == Base::capacity())
    Base::Reallocate(Base::capacity() * GROW_COEF);
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  GrowIfNeed();

  (*this)[Base::size_++] = value;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
  GrowIfNeed();

  (*this)[Base::size_++] = std::move(value);
}

template <typename T>
void Vector<T>::pop_back() {
  --Base::size_;
}

template <typename T>
constexpr BaseIterator<T>::BaseIterator(T* pointer)
    : pointer_(pointer) {}

template <typename T>
constexpr BaseIterator<T>& BaseIterator<T>::operator++() {
  ++pointer_;
  return *this;
}

template <typename T>
constexpr const BaseIterator<T> BaseIterator<T>::operator++(int) {
  BaseIterator temp(*this);
  operator++();
  return temp;
}

template <typename T>
constexpr BaseIterator<T>& BaseIterator<T>::operator--() {
  --pointer_;
  return *this;
}

template <typename T>
constexpr const BaseIterator<T> BaseIterator<T>::operator--(int) {
  BaseIterator temp(*this);
  operator--();
  return temp;
}

template <typename T>
constexpr BaseIterator<T>& BaseIterator<T>::operator+=(difference_type value) {
  pointer_ += value;
  return *this;
}

template <typename T>
constexpr BaseIterator<T>& BaseIterator<T>::operator-=(difference_type value) {
  pointer_ -= value;
  return *this;
}

template <typename T>
constexpr BaseIterator<T> BaseIterator<T>::operator[](difference_type index) const {
  return BaseIterator<T>(*this) += index;
}

template <typename T>
constexpr const bool operator==(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ == rhs.pointer_;
}

template <typename T>
constexpr const bool operator!=(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ != rhs.pointer_;
}

template <typename T>
constexpr const bool operator<(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ < rhs.pointer_;
}

template <typename T>
constexpr const bool operator>(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ > rhs.pointer_;
}

template <typename T>
constexpr const bool operator<=(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ <= rhs.pointer_;
}

template <typename T>
constexpr const bool operator>=(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ >= rhs.pointer_;
}

template <typename T>
constexpr const BaseIterator<T> operator+(const BaseIterator<T>& iterator, typename BaseIterator<T>::difference_type value) {
  return BaseIterator<T>(iterator) += value;
}

template <typename T>
constexpr const BaseIterator<T> operator+(typename BaseIterator<T>::difference_type value, const BaseIterator<T>& iterator) {
  return BaseIterator<T>(iterator) += value;
}

template <typename T>
constexpr const BaseIterator<T> operator-(const BaseIterator<T>& iterator, typename BaseIterator<T>::difference_type value) {
  iterator -= value;
}

template <typename T>
constexpr const typename BaseIterator<T>::difference_type operator-(const BaseIterator<T>& lhs, const BaseIterator<T>& rhs) {
  return lhs.pointer_ - rhs.pointer_;
}

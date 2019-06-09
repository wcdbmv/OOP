#include <algorithm>
#include <experimental/iterator>

template <typename T>
BaseVector<T>::BaseVector() : size_(0), capacity_(DEFAULT_CAPACITY) {
  Allocate();
}

template <typename T>
BaseVector<T>::BaseVector(size_type size) : size_(size), capacity_(size ? size_ : 1) {
  Allocate();
}

template <typename T>
BaseVector<T>::BaseVector(size_type size, const_reference value) : BaseVector(size) {
  for (auto& it: *this)
    it = value;
}

template <typename T>
BaseVector<T>::BaseVector(const_iterator first, const_iterator last) : BaseVector(last - first) {
  for (iterator __begin = begin(), __end = end(); __begin != __end; ++__begin, ++first)
    *__begin = *first;
}

template <typename T>
BaseVector<T>::BaseVector(std::initializer_list<T> list)
    : BaseVector(list.size(), list) {}

template <typename T>
BaseVector<T>::BaseVector(size_type size, std::initializer_list<T> list) : BaseVector(size) {
  std::copy_n(list.begin(), size_, data_);
}

template <typename T>
BaseVector<T>::BaseVector(const BaseVector<T>& other) : BaseVector(other.size()) {
  std::copy_n(other.begin(), size_, data_);
}

template <typename T>
BaseVector<T>::BaseVector(BaseVector<T>&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
BaseVector<T>::~BaseVector() {
  delete[] data_;
}

template <typename T>
auto BaseVector<T>::operator=(const BaseVector<T>& other) -> BaseVector& {
  if (this != &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete[] data_;

    Allocate();

    std::copy_n(other.begin(), size_, data_);
  }

  return *this;
}

template <typename T>
auto BaseVector<T>::operator=(BaseVector<T>&& other) noexcept -> BaseVector& {
  if (this != &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    delete[] data_;
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }

  return *this;
}

template <typename T>
auto BaseVector<T>::operator=(std::initializer_list<T> list) -> BaseVector& {
  size_ = capacity_ = list.size();

  delete[] data_;
  Allocate();

  std::copy_n(list.begin(), capacity_, data_);

  return *this;
}

template <typename T>
auto BaseVector<T>::at(std::size_t index) -> reference {
  CheckOutOfRangeException(index);

  return operator[](index);
}

template <typename T>
auto BaseVector<T>::at(std::size_t index) const -> const_reference {
  CheckOutOfRangeException(index);

  return data_[index];
}

template <typename T>
auto BaseVector<T>::operator[](std::size_t index) -> reference {
  CheckOutOfRangeException(index);

  return data_[index];
}

template <typename T>
auto BaseVector<T>::operator[](std::size_t index) const -> const_reference {
  CheckOutOfRangeException(index);

  return data_[index];
}

template <typename T>
auto BaseVector<T>::begin() -> iterator {
  return iterator(std::addressof(data_[0]));
}

template <typename T>
auto BaseVector<T>::begin() const -> const_iterator {
  return const_iterator(std::addressof(data_[0]));
}

template <typename T>
auto BaseVector<T>::end() -> iterator {
  return iterator(std::addressof(data_[size_]));
}

template <typename T>
auto BaseVector<T>::end() const -> const_iterator {
  return const_iterator(std::addressof(data_[size_]));
}

template <typename T>
bool BaseVector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
std::size_t BaseVector<T>::size() const {
  return size_;
}

template <typename T>
std::size_t BaseVector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void BaseVector<T>::clear() {
  for (auto& it: *this)
    it.~T();

  size_ = 0;
}

template <typename T>
void BaseVector<T>::Allocate() {
  try {
    data_ = new T[capacity_];
  } catch (std::bad_alloc&) {
    ThrowBadMemoryAllocationException();
  }
}

template <typename T>
void BaseVector<T>::Reallocate(size_type size) {
  try {
    capacity_ = size ? size : 1;
    auto data = new T[capacity_];

    if (size_)
      std::copy_n(data_, std::min(size_, size), data);

    delete[] data_;
    data_ = data;
  } catch (std::bad_alloc&) {
    ThrowBadMemoryAllocationException();
  }
}

template <typename T>
void BaseVector<T>::ThrowBadMemoryAllocationException() const {
  throw BadMemoryAllocationException("BaseVector::(Bad memory allocation)");
}

template <typename T>
void BaseVector<T>::CheckOutOfRangeException(size_type index) const {
  if (index >= size_)
    throw OutOfRangeException("BaseVector::(Out of range)");
}

template <typename T>
bool operator==(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return !(rhs == lhs);
}

template <typename T>
bool operator<(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator>(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return !(lhs < rhs) && !(lhs == rhs);
}

template <typename T>
bool operator>=(const BaseVector<T>& lhs, const BaseVector<T>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <typename T>
std::istream& operator>>(std::istream& is, BaseVector<T>& vector) {
  for (auto& it: vector)
    is >> it;
  return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BaseVector<T>& vector) {
  std::copy(vector.begin(), vector.end(), std::experimental::make_ostream_joiner(os, " "));
  return os;
}

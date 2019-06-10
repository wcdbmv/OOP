template <typename T>
BaseMatrix<T>::Proxy::Proxy(std::size_t cols, T* data)
    : cols_(cols), data_(data) {}

template <typename T>
T& BaseMatrix<T>::Proxy::at(std::size_t index) {
  if (index >= cols_)
    throw OutOfRangeException("BaseMatrix::Proxy::(Out of range)");

  return data_[index];
}

template <typename T>
const T& BaseMatrix<T>::Proxy::at(std::size_t index) const {
  if (index >= cols_)
    throw OutOfRangeException("BaseMatrix::Proxy::(Out of range)");

  return data_[index];
}

template <typename T>
T& BaseMatrix<T>::Proxy::operator[](std::size_t index) {
  return data_[index];
}

template <typename T>
const T& BaseMatrix<T>::Proxy::operator[](std::size_t index) const {
  return data_[index];
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), capacity_(rows * cols) {
  try {
    data_ = new T[capacity_];

  } catch (std::bad_alloc& ex) {
    throw BadMemoryAllocationException("BaseMatrix::(Bad memory allocation)");
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t rows, std::size_t cols, const T& value)
    : BaseMatrix(rows, cols) {
  for (std::size_t i = 0; i < capacity_; ++i) {
    data_[i] = value;
  }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t rows, std::size_t cols, const_iterator first, const_iterator last)
    : BaseMatrix(rows, cols) {
  const std::size_t size = capacity_ <= static_cast<std::size_t>(last - first) ?
                           capacity_ : static_cast<std::size_t>(last - first);

  for (std::size_t i = 0; i < size; ++i, ++first)
    data_[i] = *first;

  for (std::size_t i = size; i < capacity_; ++i)
    data_[i] = 0;
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::size_t row_count, std::size_t col_count, std::initializer_list<T> lst)
    : BaseMatrix(row_count, col_count) {
  std::size_t size = capacity_ <= lst.size() ? capacity_ : lst.size();
  typename std::initializer_list<T>::iterator iter = lst.begin();

  for (std::size_t i = 0; i < size; ++i, ++iter)
    data_[i] = *iter;

  for (std::size_t i = size; i < capacity_; ++i)
    data_[i] = 0;
}

template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix& other)
    : BaseMatrix(other.rows_, other.cols_) {
  std::copy(other.data_, other.data_ + other.capacity_, data_);
}

template <typename T>
BaseMatrix<T>::BaseMatrix(BaseMatrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T>
BaseMatrix<T>::~BaseMatrix() {
  delete[] data_;
  rows_ = 0;
  cols_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(const BaseMatrix<T>& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    capacity_ = other.capacity_;

    try {
      delete[] data_;
      data_ = new T[capacity_];

    } catch (std::bad_alloc& ex) {
      throw BadMemoryAllocationException("BaseMatrix::(Bad memory allocation)");
    }

    std::copy(other.data_, other.data_ + other.capacity_, data_);
  }

  return *this;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(BaseMatrix&& other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    capacity_ = other.capacity_;

    delete[] data_;
    data_ = other.data_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }

  return *this;
}

template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(std::initializer_list<T> lst) {
  std::size_t size = capacity_ <= lst.size() ? capacity_ : lst.size();
  typename std::initializer_list<T>::const_iterator iter = lst.begin();

  for (std::size_t i = 0; i < size; ++i, ++iter)
    data_[i] = *iter;

  for (std::size_t i = size; i < capacity_; ++i)
    data_[i] = 0;

  return *this;
}

template <typename T>
typename BaseMatrix<T>::Proxy BaseMatrix<T>::at(std::size_t index) {
  if (index >= rows_)
    throw OutOfRangeException("MatrixBase::(Out of range)");

  return Proxy(cols_, data_ + cols_ * index);
}

template <typename T>
auto BaseMatrix<T>::at(std::size_t index) const -> const Proxy {
  if (index >= rows_)
    throw OutOfRangeException("MatrixBase::(Out of range)");

  return Proxy(cols_, data_ + cols_ * index);
}

template <typename T>
auto BaseMatrix<T>::operator[](std::size_t index) -> Proxy {
  return Proxy(cols_, data_ + cols_ * index);
}

template <typename T>
auto BaseMatrix<T>::operator[](std::size_t index) const -> const Proxy {
  return Proxy(cols_, data_ + cols_ * index);
}

template <typename T>
auto BaseMatrix<T>::begin() -> iterator {
  return iterator(data_);
}

template <typename T>
auto BaseMatrix<T>::begin() const -> const_iterator {
  return const_iterator(data_);
}

template <typename T>
auto BaseMatrix<T>::end() -> iterator {
  return iterator(data_ + capacity_);
}

template <typename T>
auto BaseMatrix<T>::end() const -> const_iterator {
  return const_iterator(data_ + capacity_);
}

template <typename T>
std::size_t BaseMatrix<T>::rows() const {
  return rows_;
}

template <typename T>
std::size_t BaseMatrix<T>::columns() const {
  return cols_;
}

template <typename T>
std::size_t BaseMatrix<T>::capacity() const {
  return capacity_;
}

template <typename T>
void BaseMatrix<T>::zero() {
  for (std::size_t i = 0; i < capacity_; ++i)
    data_[i] = T();
}

template <typename T>
bool operator==(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  bool are_equal = lhs.size() == rhs.size();

  if (are_equal)
    for (std::size_t i = 0; i < lhs.size() && are_equal; ++i)
      if (lhs[i] != rhs[i])
        are_equal = false;

  return are_equal;
}

template <typename T>
bool operator!=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs) {
  return !(rhs == lhs);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, BaseMatrix<T>& matrix) {
  for (std::size_t i = 0; i != matrix.rows(); ++i) {
    for (std::size_t j = 0; j != matrix.columns(); ++j)
      os << matrix[i][j] << ' ';
    os << std::endl;
  }

  return os;
}

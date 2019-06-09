template <typename T>
constexpr ConstIterator<T>::ConstIterator(T* pointer)
    : BaseIterator<T>(pointer) {}

template <typename T>
constexpr ConstIterator<T>::ConstIterator(const BaseIterator<T>& other)
    : BaseIterator<T>(other.pointer_) {}

template <typename T>
constexpr const T& ConstIterator<T>::operator*() const {
  return *BaseIterator<T>::pointer_;
}

template <typename T>
constexpr const T* ConstIterator<T>::operator->() const {
  return BaseIterator<T>::pointer_;
}

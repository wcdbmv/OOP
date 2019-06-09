template <typename T>
constexpr Iterator<T>::Iterator(T* pointer) : BaseIterator<T>(pointer) {}

template <typename T>
constexpr Iterator<T>::Iterator(const BaseIterator<T>& other) : BaseIterator<T>(other.pointer_) {}

template <typename T>
T& Iterator<T>::operator*() {
  return *BaseIterator<T>::pointer_;
}

template <typename T>
T* Iterator<T>::operator->() {
  return BaseIterator<T>::pointer_;
}

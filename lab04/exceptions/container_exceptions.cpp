#include "container_exceptions.hpp"

BaseContainerException::BaseContainerException(const char* message)
    : BaseException(message) {}

const char* BaseContainerException::what() const noexcept {
  return message_.empty() ? "Container::(Base exception)" : message_.c_str();
}

BadMemoryAllocationException::BadMemoryAllocationException(const char* message)
    : BaseContainerException(message) {}

const char* BadMemoryAllocationException::what() const noexcept {
  return message_.empty() ? "Container::(Bad memory allocation)" : message_.c_str();
}

OutOfRangeException::OutOfRangeException(const char* message)
    : BaseContainerException(message) {}

const char* OutOfRangeException::what() const noexcept {
  return message_.empty() ? "Container::(Out of range)!" : message_.c_str();
}

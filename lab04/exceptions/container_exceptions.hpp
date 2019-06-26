#ifndef LAB04_EXCEPTIONS_CONTAINER_EXCEPTIONS_HPP_
#define LAB04_EXCEPTIONS_CONTAINER_EXCEPTIONS_HPP_

#include "base_exception.hpp"

class BaseContainerException : public BaseException {
 public:
  explicit BaseContainerException() = default;
  explicit BaseContainerException(const char* message);

  const char* what() const noexcept override;
};

class BadMemoryAllocationException : public BaseContainerException {
 public:
  explicit BadMemoryAllocationException() = default;
  explicit BadMemoryAllocationException(const char* message);

  const char* what() const noexcept override;
};

class OutOfRangeException : public BaseContainerException {
 public:
  explicit OutOfRangeException() = default;
  explicit OutOfRangeException(const char* message);

  const char* what() const noexcept override;
};

#endif  // LAB04_EXCEPTIONS_CONTAINER_EXCEPTIONS_HPP_

#ifndef BASE_VECTOR_H_
#define BASE_VECTOR_H_

#include <cstddef>

class BaseVector {
 public:
  explicit BaseVector(size_t size = 1) noexcept;
  BaseVector(const BaseVector&) = default;
  virtual ~BaseVector() = default;

  constexpr size_t size() const;
 protected:
  size_t size_;
};

BaseVector::BaseVector(size_t size) noexcept : size_(size) {}

constexpr size_t BaseVector::size() const { return size_; }

#endif  // BASE_VECTOR_H_

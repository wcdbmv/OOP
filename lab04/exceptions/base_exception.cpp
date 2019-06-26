#include "base_exception.hpp"

BaseException::BaseException(const char* message)
    : message_(message) {}

const char* BaseException::what() const noexcept {
  return "BaseException";
}

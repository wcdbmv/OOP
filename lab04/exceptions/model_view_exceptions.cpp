#include "model_view_exceptions.hpp"

BaseModelViewException::BaseModelViewException(const char* message)
    : BaseException(message) {}

const char* BaseModelViewException::what() const noexcept {
  return message_.empty() ? "ModelView::(Base exception)" : message_.c_str();
}

ModelViewOutOfRangeException::ModelViewOutOfRangeException(const char* message)
    : BaseModelViewException(message) {}

const char* ModelViewOutOfRangeException::what() const noexcept {
  return message_.empty() ? "ModelView::(Out of range)" : message_.c_str();
}

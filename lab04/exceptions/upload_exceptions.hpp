#ifndef LAB04_EXCEPTIONS_UPLOAD_EXCEPTIONS_HPP_
#define LAB04_EXCEPTIONS_UPLOAD_EXCEPTIONS_HPP_

#include "base_exception.hpp"

class BaseStreamException : public BaseException {
 public:
  explicit BaseStreamException() = default;
  explicit BaseStreamException(const char* message);

  const char* what() const noexcept override;
};

class OpenStreamException : public BaseStreamException {
 public:
  explicit OpenStreamException() = default;
  explicit OpenStreamException(const char* message);

  const char* what() const noexcept override;
};

class ReadStreamException : public BaseStreamException {
 public:
  explicit ReadStreamException() = default;
  explicit ReadStreamException(const char* message);

  const char* what() const noexcept override;
};

class FileFormatException : public BaseStreamException {
 public:
  explicit FileFormatException() = default;
  explicit FileFormatException(const char* message);

  const char* what() const noexcept override;
};

#endif  // LAB04_EXCEPTIONS_UPLOAD_EXCEPTIONS_HPP_

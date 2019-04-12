#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class InvalidSizeException : public std::exception {
 public:
  const char* what() const noexcept override { return "invalid size"; }
};

class DivisionByZeroException : public std::exception {
 public:
  const char* what() const noexcept override { return "division by zero"; }
};

class IndexOutOfRangeException : public std::exception {
 public:
  const char* what() const noexcept override { return "index out of range"; }
};

#endif  // ECXEPTION_H

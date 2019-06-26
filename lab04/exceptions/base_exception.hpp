#ifndef LAB04_EXCEPTIONS_BASE_EXCEPTION_HPP_
#define LAB04_EXCEPTIONS_BASE_EXCEPTION_HPP_

#include <exception>
#include <string>

class BaseException : public std::exception {
 public:
  explicit BaseException() = default;
  explicit BaseException(const char* message);

  const char* what() const noexcept override;

 protected:
  std::string message_;
};

#endif  // LAB04_EXCEPTIONS_BASE_EXCEPTION_HPP_

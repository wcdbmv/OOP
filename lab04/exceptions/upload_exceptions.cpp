#include "upload_exceptions.hpp"

BaseStreamException::BaseStreamException(const char* message)
    : BaseException(message) {}

const char* BaseStreamException::what() const noexcept {
  return message_.empty() ? "Uploader::(Base stream exception)" : message_.c_str();
}

OpenStreamException::OpenStreamException(const char* message)
    : BaseStreamException(message) {}

const char* OpenStreamException::what() const noexcept {
  return message_.empty() ? "Uploader::(Open stream exception)" : message_.c_str();
}

ReadStreamException::ReadStreamException(const char* message)
    : BaseStreamException(message) {}

const char* ReadStreamException::what() const noexcept {
  return message_.empty() ? "Uploader::(Read stream exception)" : message_.c_str();
}

FileFormatException::FileFormatException(const char* message)
    : BaseStreamException(message) {}

const char* FileFormatException::what() const noexcept {
  return message_.empty() ? "Uploader::(Parsing file error)" : message_.c_str();
}

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

CloseStreamException::CloseStreamException(const char* message)
    : BaseStreamException(message) {}

const char* CloseStreamException::what() const noexcept {
  return message_.empty() ? "Uploader::(Close stream exception)" : message_.c_str();
}

JsonException::JsonException(const char* message)
    : BaseStreamException(message) {}

const char* JsonException::what() const noexcept {
  return message_.empty() ? "Uploader::jsmn::(Parsing json error)" : message_.c_str();
}

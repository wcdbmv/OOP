#ifndef LAB04_UPLOAD_BASE_UPLOADER_HPP_
#define LAB04_UPLOAD_BASE_UPLOADER_HPP_

#include "objects/model.hpp"

class BaseUploader {
 public:
  BaseUploader() = default;
  BaseUploader(const BaseUploader&) = delete;
  virtual ~BaseUploader() = default;

  virtual void open() = 0;
  virtual Model get_model() = 0;
  virtual void close() = 0;
};

#endif  // LAB04_UPLOAD_BASE_UPLOADER_HPP_

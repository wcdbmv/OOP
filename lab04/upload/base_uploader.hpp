#ifndef LAB04_UPLOAD_BASE_UPLOADER_HPP_
#define LAB04_UPLOAD_BASE_UPLOADER_HPP_

#include "objects/model.hpp"

class BaseUploader {
 public:
  virtual ~BaseUploader() noexcept = default;

  virtual void open() = 0;
  virtual bool is_open() const = 0;
  virtual void close() = 0;

  virtual const Model get_model() = 0;
};

#endif  // LAB04_UPLOAD_BASE_UPLOADER_HPP_

#ifndef LAB04_MANAGERS_UPLOAD_MANAGER_HPP_
#define LAB04_MANAGERS_UPLOAD_MANAGER_HPP_

#include "upload/uploader.hpp"

class UploadManager {
 public:
  static Model UploadModel(BaseUploader& uploader);

 private:
  UploadManager() = default;
};

#endif  // LAB04_MANAGERS_UPLOAD_MANAGER_HPP_

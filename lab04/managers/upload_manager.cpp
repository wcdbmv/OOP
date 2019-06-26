#include "upload_manager.hpp"

Model UploadManager::UploadModel(BaseUploader& uploader) {
  uploader.open();
  auto model = uploader.get_model();
  uploader.close();

  return model;
}

#ifndef LAB04_UPLOAD_UPLOADER_HPP_
#define LAB04_UPLOAD_UPLOADER_HPP_

#include <fstream>

#include "base_uploader.hpp"

class Uploader : public BaseUploader {
 public:
  explicit Uploader(std::string filename);
  ~Uploader() override;

  void open() override;
  bool is_open() const override;
  void close() override;
  const Model get_model() override;

 private:
  std::string filename_;
  std::ifstream file_;
};

#endif  // LAB04_UPLOAD_UPLOADER_HPP_

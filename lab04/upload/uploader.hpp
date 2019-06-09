#ifndef LAB04_UPLOAD_UPLOADER_HPP_
#define LAB04_UPLOAD_UPLOADER_HPP_

#include <fstream>
#include <cstring>
#include <functional>

#include "exceptions/upload_exceptions.hpp"
#include "containers/vector/vector.hpp"
#include "containers/pair/pair.hpp"
#include "objects/model.hpp"
#include "3dparty/jsmn.h"
#include "base_uploader.hpp"

class Uploader : public BaseUploader {
 public:
  explicit Uploader(std::string);
  ~Uploader() override = default;

  void open() override;
  Model get_model() override;
  void close() override;

 protected:
  void serialize_json();
  Model deserialize_json();

  static int json_equal(const char*, jsmntok_t*, const char*);

  Pair<int, Point3D<double>> get_point(int, jsmntok_t*, int);
  Pair<int, Vector<int>> get_link(int, jsmntok_t*, int);

  template <typename T>
  void import_data(Vector<T>&, int, jsmntok_t*, std::function<T(int, jsmntok_t*, int)>&, const char*, const char*);

  void retrieve_lines(Vector<Pair<Point3D<double>, Point3D<double>>>&,
                      Vector<Pair<int, Point3D<double>>>&,
                      Vector<Pair<int, Vector<int>>>&);

  void normalize_points(Vector<Pair<int, Point3D<double>>>&,
                        Vector<Point3D<double>>&);

 private:
  std::string file_name;
  std::ifstream input_stream;
  std::string json_string;
  jsmn_parser json_parser;
};

template<typename T>
void Uploader::import_data(Vector<T>& data, int i, jsmntok_t* buffer,
                           std::function<T (int, jsmntok_t*, int)>& func, const char* str1, const char* str2) {
  if (json_equal(this->json_string.c_str(), &buffer[i], str1) == 0 &&
      json_equal(this->json_string.c_str(), &buffer[i + 2], str2) == 0) {
    data.push_back(func(i, buffer, 0));

  } else if (json_equal(this->json_string.c_str(), &buffer[i], str2) == 0 &&
      json_equal(this->json_string.c_str(), &buffer[i + 2], str1) == 0) {
    data.push_back(func(i, buffer, 2));

  } else {
    throw JsonException("uploader::jsmn(corrupted data)!");
  }
}

#endif  // LAB04_UPLOAD_UPLOADER_HPP_

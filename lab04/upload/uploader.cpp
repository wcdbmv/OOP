#include "uploader.hpp"

Uploader::Uploader(std::string file_name) : BaseUploader(), file_name(file_name) {
  input_stream.exceptions(std::ifstream::badbit);
}

int Uploader::json_equal(const char* json_str, jsmntok_t* token, const char* str) {
  if (token->type == JSMN_STRING && static_cast<int>(strlen(str)) == token->end - token->start &&
      strncmp(json_str + token->start, str, token->end - token->start) == 0) {
    return 0;
  }

  return -1;
}

Pair<int, Point3D<double>> Uploader::get_point(int i, jsmntok_t* buffer, int offset) {
  int id = std::stoi(std::string(this->json_string.c_str() + buffer[i + 1 + offset].start,
                                 this->json_string.c_str() + buffer[i + 1 + offset].end));

  if (buffer[i + 3 - offset].type != JSMN_ARRAY) {
    throw JsonException("uploader::jsmn(object is not of type ARRAY)!");
  }

  Vector<double> vec;

  for (int j = 0; j < buffer[i + 3 - offset].size; ++j) {
    jsmntok_t* element = &buffer[i + j + 4 - offset];
    vec.push_back(std::stod(std::string(this->json_string.c_str() + element->start,
                                        this->json_string.c_str() + element->end)));
  }

  return Pair<int, Point3D<double>>(id, Point3D<double>(vec[0], vec[1], vec[2]));
}

Pair<int, Vector<int>> Uploader::get_link(int i, jsmntok_t* buffer, int offset) {
  int id = std::stoi(std::string(this->json_string.c_str() + buffer[i + 1 + offset].start,
                                 this->json_string.c_str() + buffer[i + 1 + offset].end));

  if (buffer[i + 3 - offset].type != JSMN_ARRAY) {
    throw JsonException("uploader::jsmn(object is not of type ARRAY)!");
  }

  Vector<int> vec;

  for (int j = 0; j < buffer[i + 3 - offset].size; ++j) {
    jsmntok_t* element = &buffer[i + j + 4 - offset];
    vec.push_back(std::stoi(std::string(this->json_string.c_str() + element->start,
                                        this->json_string.c_str() + element->end)));
  }

  return Pair<int, Vector<int>>(id, vec);
}

void Uploader::serialize_json() {
  if (this->input_stream.is_open()) {

    try {
      std::string buffer;

      while (this->input_stream >> buffer) {
        this->json_string += buffer;
      }

    } catch (std::ifstream::failure& e) {
      input_stream.close();
      throw ReadStreamException();
    }
  }
}

Model Uploader::deserialize_json() {
  jsmntok_t buffer[this->json_string.size()];
  jsmn_init(&this->json_parser);
  const int root_keys_count = jsmn_parse(&this->json_parser, this->json_string.c_str(),
                                         this->json_string.size(), buffer, sizeof(buffer) / sizeof(*buffer));
  std::string model_name;
  Vector<Pair<int, Point3D<double>>> points;
  Vector<Pair<int, Vector<int>>> links;

  if (root_keys_count < 0) {
    throw JsonException("uploader::jsmn(empty document)!");
  }

  if (root_keys_count < 1 || (*buffer).type != JSMN_OBJECT) {
    throw JsonException("uploader::jsmn(object is not of type OBJECT)!");
  }

  for (int i = 1; i < root_keys_count; ++i) {

    if (json_equal(this->json_string.c_str(), &buffer[i], "object_name") == 0) {
      model_name = std::string(this->json_string.c_str() + buffer[i + 1].start,
                               this->json_string.c_str() + buffer[i + 1].end);
      ++i;

    } else if (json_equal(this->json_string.c_str(), &buffer[i], "point") == 0) {
      i += 2;
      std::function<Pair<int, Point3D<double>>(int, jsmntok_t*, int)> func =
          std::bind(&Uploader::get_point, this, std::placeholders::_1,
                    std::placeholders::_2, std::placeholders::_3);
      this->import_data<Pair<int, Point3D<double>>>(points, i, buffer, func, "id", "coordinates");

    } else if (json_equal(this->json_string.c_str(), &buffer[i], "link") == 0) {
      i += 2;
      std::function<Pair<int, Vector<int>>(int, jsmntok_t*, int)> func =
          std::bind(&Uploader::get_link, this, std::placeholders::_1,
                    std::placeholders::_2, std::placeholders::_3);
      this->import_data<Pair<int, Vector<int>>>(links, i, buffer, func, "id", "connections");
    }
  }

  Vector<Pair<Point3D<double>, Point3D<double>>> lines;
  Vector<Point3D<double>> normalized_points;

  retrieve_lines(lines, points, links);

  return Model(model_name, lines);
}

void Uploader::retrieve_lines(Vector<Pair<Point3D<double>, Point3D<double>>>& lines,
                              Vector<Pair<int, Point3D<double>>>& points,
                              Vector<Pair<int, Vector<int>>>& links) {
  for (size_t i = 0; i < links.size(); ++i) {

    for (size_t k = 0; k < points.size(); ++k) {

      if (links.at(i).get_first() == points.at(k).get_first()) {

        for (size_t j = 0; j < links.at(i).get_second().size(); ++j) {

          for (size_t w = 0; w < points.size(); ++w) {

            if (links.at(i).get_second()[j] == points.at(w).get_first()) {
              Point3D<double> p1 = points.at(k).get_second();
              Point3D<double> p2 = points.at(w).get_second();
              lines.push_back(Pair<Point3D<double>, Point3D<double>>(p1, p2));
            }
          }
        }
      }
    }
  }
}

void Uploader::normalize_points(Vector<Pair<int, Point3D<double>>>& pair_points, Vector<Point3D<double>>& points) {
  for (size_t i = 0; i < pair_points.size(); ++i) {
    points.push_back(pair_points.at(i).get_second());
  }
}

void Uploader::open() {
  try {
    this->input_stream.open(this->file_name);

  } catch (std::ifstream::failure& e) {
    throw OpenStreamException();
  }
}

Model Uploader::get_model() {
  this->serialize_json();
  return this->deserialize_json();
}

void Uploader::close() {
  try {
    this->input_stream.close();

  } catch (std::ifstream::failure& e) {
    throw CloseStreamException();
  }
}

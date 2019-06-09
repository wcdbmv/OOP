#include "uploader.hpp"

#include "exceptions/upload_exceptions.hpp"

Uploader::Uploader(std::string filename)
    : filename_(std::move(filename)) {}

Uploader::~Uploader() {
  close();
}

void Uploader::open() {
  if (is_open())
    close();

  file_.open(filename_);
  if (!file_)
    throw OpenStreamException();
}

bool Uploader::is_open() const {
  return file_.is_open();
}

void Uploader::close() {
  if (!is_open())
    file_.close();
}

const Model Uploader::get_model() {
  if (!is_open())
    throw ReadStreamException();

  std::size_t n_vertices, n_edges;
  file_ >> n_vertices >> n_edges;

  Vector<Point3D<double>> vertices(n_vertices);
  for (auto& vertex: vertices)
    file_ >> vertex;

  Vector<Edge> edges(n_edges);
  for (auto& edge: edges)
    file_ >> edge;

  return Model(filename_, vertices, edges);
}

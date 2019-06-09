#include "model.hpp"

Model::Model(std::string name, Vector<Point3D<double>> vertices, Vector<Edge> edges)
    : name_(std::move(name)), vertices_(std::move(vertices)), edges_(std::move(edges)) {}

Model::Model(const Model& other)
    : VisibleObject(), name_(other.name_), vertices_(other.vertices_), edges_(other.edges_) {}

Model::Model(Model&& other) noexcept
    : name_(std::move(other.name_)), vertices_(std::move(other.vertices_)), edges_(std::move(other.edges_)) {}

Model& Model::operator=(const Model& other) {
  if (this != &other) {
    name_ = other.name_;
    vertices_ = other.vertices_;
    edges_ = other.edges_;
  }

  return *this;
}

Model& Model::operator=(Model&& other) noexcept {
  if (this != &other) {
    name_ = std::move(other.name_);
    vertices_ = std::move(other.vertices_);
    edges_ = std::move(other.edges_);
    other.~Model();
  }

  return *this;
}

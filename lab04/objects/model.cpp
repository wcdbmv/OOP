#include "model.hpp"

Model::Model(std::string name, Vector<Pair<Point3D<double>, Point3D<double>>> edges)
    : name_(std::move(name)), edges_(std::move(edges)) {}

Model::Model(const Model& other)
    : VisibleObject(), name_(other.name_), edges_(other.edges_) {}

Model& Model::operator=(const Model& other) {
  if (this != &other) {
    name_ = other.name_;
    edges_ = other.edges_;
  }

  return *this;
}

Model& Model::operator=(Model&& other) noexcept {
  if (this != &other) {
    name_ = std::move(other.name_);
    edges_ = std::move(other.edges_);
    other.~Model();
  }

  return *this;
}

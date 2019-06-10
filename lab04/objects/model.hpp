#ifndef LAB04_OBJECTS_MODEL_HPP_
#define LAB04_OBJECTS_MODEL_HPP_

#include <string>

#include "visible_object.hpp"
#include "containers/vector/vector.hpp"
#include "math3d/point3d.hpp"
#include "math3d/edge.hpp"

class Model : public VisibleObject {
 public:
  explicit Model() = default;
  explicit Model(std::string, Vector<Point3D<double>>, Vector<Edge>);
  Model(const Model&);
  Model(Model&&) noexcept;

  Model& operator=(const Model&);
  Model& operator=(Model&&) noexcept;

  friend class Transformation;
  friend class DrawManager;

 private:
  std::string name_;
  Vector<Point3D<double>> vertices_;
  Vector<Edge> edges_;
};

#endif  // LAB04_OBJECTS_MODEL_HPP_

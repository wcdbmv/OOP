#ifndef LAB04_OBJECTS_MODEL_HPP_
#define LAB04_OBJECTS_MODEL_HPP_

#include <string>

#include "visible_object.hpp"
#include "containers/vector/vector.hpp"
#include "containers/pair/pair.hpp"
#include "math3d/point3d.hpp"

class Model : public VisibleObject {
 public:
  explicit Model() = default;
  explicit Model(std::string , Vector<Pair<Point3D<double>, Point3D<double>>> );
  Model(const Model&);
  ~Model() override = default;

  Model& operator=(const Model&);
  Model& operator=(Model&&) noexcept ;

  friend class ModelTransformation;
  friend class DrawManager;

 private:
  std::string name_;
  Vector<Pair<Point3D<double>, Point3D<double>>> edges_;
};

#endif  // LAB04_OBJECTS_MODEL_HPP_

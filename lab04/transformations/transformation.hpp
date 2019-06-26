#ifndef LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_
#define LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_

#include "base_transformation.hpp"
#include "transformation_interface.hpp"
#include "objects/model.hpp"

class Transformation : public BaseTransformation {
 public:
  explicit Transformation(ITransformation& interface);
  ~Transformation() override = default;

  void Transform(SceneObject*& object) override;

 private:
  Matrix4x4<double> matrix_ = Matrix4x4<double>();
};

#endif  // LAB04_TRANSFORMATIONS_TRANSFORMATION_HPP_

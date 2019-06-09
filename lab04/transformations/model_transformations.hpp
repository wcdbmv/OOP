#ifndef LAB04_TRANSFORMATIONS_MODEL_TRANSFORMATIONS_HPP_
#define LAB04_TRANSFORMATIONS_MODEL_TRANSFORMATIONS_HPP_

#include "base_transformations.hpp"
#include "objects/model.hpp"

class ModelTransformation : public BaseTransformation {
 public:
  explicit ModelTransformation(ITransformation& interface);
  ~ModelTransformation() override = default;

  void Transform(SceneObject*& object) override;

 private:
  Matrix4x4<double> matrix_ = Matrix4x4<double>();
};

#endif  // LAB04_TRANSFORMATIONS_MODEL_TRANSFORMATIONS_HPP_

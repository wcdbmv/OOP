#ifndef LAB04_TRANSFORMATIONS_TRANSFORMATIONS_HPP_
#define LAB04_TRANSFORMATIONS_TRANSFORMATIONS_HPP_

#include "objects/scene_object.hpp"
#include "transformation_interface.hpp"
#include "containers/vector/vector.hpp"
#include "math3d/point3d.hpp"

class BaseTransformation {
 public:
  BaseTransformation() = default;
  BaseTransformation(BaseTransformation&) = delete;
  BaseTransformation(const BaseTransformation&) = delete;
  virtual ~BaseTransformation() = default;

  virtual void Transform(SceneObject*&) = 0;
};

#endif  // LAB04_TRANSFORMATIONS_TRANSFORMATIONS_HPP_

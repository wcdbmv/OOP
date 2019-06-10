#ifndef LAB04_TRANSFORMATIONS_BASE_TRANSFORMATION_HPP_
#define LAB04_TRANSFORMATIONS_BASE_TRANSFORMATION_HPP_

#include "objects/scene_object.hpp"

class BaseTransformation {
 public:
  BaseTransformation() = default;
  BaseTransformation(const BaseTransformation&) = delete;
  virtual ~BaseTransformation() = default;

  virtual void Transform(SceneObject*&) = 0;
};

#endif  // LAB04_TRANSFORMATIONS_BASE_TRANSFORMATION_HPP_

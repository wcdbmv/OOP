#ifndef LAB04_MANAGERS_MODEL_MANAGER_HPP_
#define LAB04_MANAGERS_MODEL_MANAGER_HPP_

#include "scene/scene.hpp"
#include "transformations/base_transformations.hpp"

class ModelManager {
 public:
  static void Transform(Scene& scene, BaseTransformation& transformation, ssize_t index);

 private:
  ModelManager() = default;
};

#endif  // LAB04_MANAGERS_MODEL_MANAGER_HPP_

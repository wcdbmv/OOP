#include "model_manager.hpp"

void ModelManager::Transform(Scene& scene, BaseTransformation& transformation, ssize_t index) {
  if (index == -1) {
    scene.Transform(transformation);
  } else {
    transformation.Transform(scene.get_model(index));
  }
}

#ifndef LAB04_SCENE_SCENE_HPP_
#define LAB04_SCENE_SCENE_HPP_

#include "objects/composite_object.hpp"

class Scene {
 public:
  Scene() = default;
  ~Scene() = default;

  void Transform(BaseTransformation& transformation);

  void AddModel(SceneObject* object);
  void RemoveModel(std::size_t index);

  void AddCamera(SceneObject* object);
  void RemoveCamera(std::size_t index);

  SceneObject*& get_model(std::size_t);
  SceneObject*& get_camera(std::size_t);

  friend class ModelManager;
  friend class DrawManager;
  friend class CameraManager;

 private:
  CompositeObject object_;
};

#endif  // LAB04_SCENE_SCENE_HPP_

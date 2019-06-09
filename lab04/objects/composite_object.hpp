#ifndef LAB04_OBJECTS_COMPOSITE_OBJECT_HPP_
#define LAB04_OBJECTS_COMPOSITE_OBJECT_HPP_

#include "transformations/base_transformations.hpp"
#include "exceptions/scene_exceptions.hpp"
#include "containers/vector/vector.hpp"
#include "objects/model.hpp"
#include "objects/camera.hpp"

class CompositeObject : public SceneObject {
 public:
  CompositeObject();
  ~CompositeObject() override = default;

  void Transform(BaseTransformation& transformation);
  bool Visible() const override;

  void AddModel(SceneObject* object);
  void RemoveModel(std::size_t index);

  void AddCamera(SceneObject* object);
  void RemoveCamera(std::size_t index);

  SceneObject*& get_model(std::size_t);
  SceneObject*& get_camera(std::size_t);

  friend class DrawManager;

 private:
  std::size_t n_cameras_;
  std::size_t n_models_;
  Vector<SceneObject*> scene_objects_;
};

#endif  // LAB04_OBJECTS_COMPOSITE_OBJECT_HPP_

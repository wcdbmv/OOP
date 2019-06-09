#ifndef LAB04_OBJECTS_SCENE_OBJECT_HPP_
#define LAB04_OBJECTS_SCENE_OBJECT_HPP_

class SceneObject {
 public:
  explicit SceneObject() = default;
  SceneObject(SceneObject&) = delete;
  SceneObject(const SceneObject&) = delete;
  virtual ~SceneObject() = default;

  virtual bool Visible() const = 0;
};

#endif  // LAB04_OBJECTS_SCENE_OBJECT_HPP_

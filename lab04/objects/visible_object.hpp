#ifndef LAB04_OBJECTS_VISIBLE_OBJECT_HPP_
#define LAB04_OBJECTS_VISIBLE_OBJECT_HPP_

#include "scene_object.hpp"

class VisibleObject : public SceneObject {
 public:
  explicit VisibleObject() = default;
  VisibleObject(const VisibleObject&) = delete;
  ~VisibleObject() override = default;

  bool Visible() const final;
};

#endif  // LAB04_OBJECTS_VISIBLE_OBJECT_HPP_

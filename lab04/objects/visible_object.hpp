#ifndef LAB04_OBJECTS_VISIBLE_OBJECT_HPP_
#define LAB04_OBJECTS_VISIBLE_OBJECT_HPP_

#include "scene_object.hpp"

class VisibleObject : public SceneObject {
 public:
  explicit VisibleObject() = default;
  VisibleObject(VisibleObject&) = delete;
  VisibleObject(const VisibleObject&) = delete;
  ~VisibleObject() override = default;

  bool Visible() const override;
};

#endif  // LAB04_OBJECTS_VISIBLE_OBJECT_HPP_

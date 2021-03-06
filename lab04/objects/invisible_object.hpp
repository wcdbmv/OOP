#ifndef LAB04_OBJECTS_INVISIBLE_OBJECT_HPP_
#define LAB04_OBJECTS_INVISIBLE_OBJECT_HPP_

#include "scene_object.hpp"

class InvisibleObject : public SceneObject {
 public:
  explicit InvisibleObject() = default;
  InvisibleObject(const InvisibleObject&) = delete;
  ~InvisibleObject() override = default;

  bool Visible() const final;
};

#endif  // LAB04_OBJECTS_INVISIBLE_OBJECT_HPP_

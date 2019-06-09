#include "composite_object.hpp"

CompositeObject::CompositeObject() {
  AddCamera(new Camera());
}

void CompositeObject::Transform(BaseTransformation &transformation) {
  for (auto& scene_object : scene_objects_)
    transformation.Transform(scene_object);
}

bool CompositeObject::Visible() const {
  return true;
}

void CompositeObject::AddModel(SceneObject *object) {
  scene_objects_.push_back(reinterpret_cast<Model*>(object));
  ++n_models_;
}

void CompositeObject::RemoveModel(std::size_t index) {
  if (index < n_models_) {
    std::size_t count = 0;
    std::size_t i = 0;

    for (; i < scene_objects_.size(); ++i) {
      if (scene_objects_[i]->Visible()) {
        ++count;

        if (count - 1 == index)
          break;
      }
    }

    scene_objects_.erase(i);
    --n_models_;

  } else {
    throw SceneOutOfRangeException("Scene::(Model out of range)");
  }
}

void CompositeObject::AddCamera(SceneObject *object) {
  scene_objects_.push_back(reinterpret_cast<Camera*>(object));
  ++n_cameras_;
}

void CompositeObject::RemoveCamera(std::size_t index) {
  if (index < n_cameras_) {
    std::size_t count = 0;
    std::size_t i = 0;

    for (; i < scene_objects_.size(); ++i) {
      if (!scene_objects_[i]->Visible()) {
        ++count;

        if (count - 1 == index)
          break;
      }
    }

    scene_objects_.erase(i);
    --n_cameras_;

  } else {
    throw SceneOutOfRangeException("Scene::(Camera out of range)");
  }
}

SceneObject*& CompositeObject::get_model(std::size_t index) {
  if (index < n_models_) {
    std::size_t count = 0;
    std::size_t i = 0;

    for (; i < scene_objects_.size(); ++i) {
      if (scene_objects_[i]->Visible()) {
        ++count;

        if (count - 1 == index)
          break;
      }
    }

    return scene_objects_[i];

  } else {
    throw SceneOutOfRangeException("Scene::(Model out of range)");
  }
}

SceneObject*& CompositeObject::get_camera(std::size_t index) {
  if (index < n_cameras_) {
    std::size_t count = 0;
    std::size_t i = 0;

    for (; i < scene_objects_.size(); ++i) {
      if (!scene_objects_[i]->Visible()) {
        ++count;

        if (count - 1 == index)
          break;
      }
    }

    return scene_objects_[i];

  } else {
    throw SceneOutOfRangeException("Scene::(Camera out of range)");
  }
}

#include "scene.hpp"

void Scene::Transform(BaseTransformation& transformation) {
  object_.Transform(transformation);
}

void Scene::AddModel(SceneObject* object) {
  object_.AddModel(object);
}

void Scene::RemoveModel(std::size_t index) {
  object_.RemoveModel(index);
}

void Scene::AddCamera(SceneObject* object) {
  object_.AddCamera(object);
}

void Scene::RemoveCamera(std::size_t index) {
  object_.RemoveCamera(index);
}

SceneObject*& Scene::get_model(std::size_t index) {
  return object_.get_model(index);
}

SceneObject*& Scene::get_camera(std::size_t index) {
  return object_.get_camera(index);
}

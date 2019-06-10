#include "transformation.hpp"

Transformation::Transformation(ITransformation& interface)
    : matrix_(interface) {}

void Transformation::Transform(SceneObject*& object) {
  if (object->Visible()) {
    Model* p_model = reinterpret_cast<Model*>(object);

    for (auto& vertex: p_model->vertices_)
      vertex = matrix_ * vertex;
  }
}

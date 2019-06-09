#include "model_transformations.hpp"

ModelTransformation::ModelTransformation(ITransformation& interface)
    : matrix_(interface) {}

void ModelTransformation::Transform(SceneObject*& object) {
  if (object->Visible()) {
    Model* p_model = reinterpret_cast<Model*>(object);

    for (auto& vertex: p_model->vertices_)
      vertex = matrix_ * vertex;
  }
}

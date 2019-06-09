#include "model_transformations.hpp"

ModelTransformation::ModelTransformation(ITransformation& interface)
    : matrix_(interface) {}

void ModelTransformation::Transform(SceneObject*& object) {
  if (object->Visible()) {
    Model* p_model = reinterpret_cast<Model*>(object);

    for (size_t i = 0; i < p_model->edges_.size(); ++i) {
      p_model->edges_.at(i).set_first(matrix_ * p_model->edges_.at(i).get_first());
      p_model->edges_.at(i).set_second(matrix_ * p_model->edges_.at(i).get_second());
    }
  }
}

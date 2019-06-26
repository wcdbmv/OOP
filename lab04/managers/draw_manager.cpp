#include "draw_manager.hpp"

void DrawManager::Draw(Scene& scene, BaseDrawer& drawer, Camera* camera) {
  for (auto & scene_object: scene.object_.scene_objects_) {
    if (scene_object->Visible()) {
      Model* p_model = reinterpret_cast<Model*>(scene_object);
      Matrix4x4<double> matrix = camera->get_view_matrix();

      for (const auto& edge: p_model->edges_) {
        auto p1 = matrix * p_model->vertices_.at(edge.p1());
        auto p2 = matrix * p_model->vertices_.at(edge.p2());
        drawer(p1, p2);
      }
    }
  }
}

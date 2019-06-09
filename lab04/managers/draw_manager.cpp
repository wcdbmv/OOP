#include "draw_manager.hpp"

void DrawManager::Draw(Scene& scene, BaseDrawer& drawer, Camera* camera) {
  for (Vector<SceneObject*>::iterator iter = scene.object_.scene_objects_.begin();
       iter != scene.object_.scene_objects_.end(); ++iter) {

    if ((*iter)->Visible()) {
      Model* p_model = reinterpret_cast<Model*>(*iter);
      Matrix4x4<double> matrix = camera->get_view_matrix();

      for (const auto& edge: p_model->edges_) {
        Point3D<double> p1 = matrix * p_model->vertices_.at(edge.p1());
        Point3D<double> p2 = matrix * p_model->vertices_.at(edge.p2());
        drawer(p1, p2);
      }
    }
  }
}

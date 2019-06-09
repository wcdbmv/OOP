#include "draw_manager.hpp"

void DrawManager::Draw(Scene& scene, BaseDrawer& drawer, Camera* camera) {
  for (Vector<SceneObject*>::iterator iter = scene.object_.scene_objects_.begin();
       iter != scene.object_.scene_objects_.end(); ++iter) {

    if ((*iter)->Visible()) {
      Model* m = reinterpret_cast<Model*>(*iter);
      Matrix4x4<double> mtx = camera->get_view_matrix();

      for (size_t i = 0; i < m->edges_.size(); ++i) {
        Point3D<double> p1 = mtx * m->edges_.at(i).get_first();
        Point3D<double> p2 = mtx * m->edges_.at(i).get_second();
        drawer(p1, p2);
      }
    }
  }
}

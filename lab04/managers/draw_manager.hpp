#ifndef LAB04_MANAGERS_DRAW_MANAGER_HPP_
#define LAB04_MANAGERS_DRAW_MANAGER_HPP_

#include <QGraphicsScene>

#include "scene/scene.hpp"
#include "math3d/matrix4x4.hpp"
#include "gui/drawer.hpp"

class DrawManager {
 public:
  static void Draw(Scene& scene, BaseDrawer& drawer, Camera* camera);

 private:
  DrawManager() = default;
};

#endif  // LAB04_MANAGERS_DRAW_MANAGER_HPP_

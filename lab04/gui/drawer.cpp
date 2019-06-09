#include "drawer.hpp"

Drawer::Drawer(QGraphicsScene*& graphics_scene)
    : BaseDrawer(), graphics_scene_(graphics_scene) {}

Drawer::Drawer(const Drawer& other)
    : BaseDrawer(), graphics_scene_(other.graphics_scene_) {}

Drawer::~Drawer() {
  graphics_scene_ = nullptr;
}

void Drawer::operator()(const Point3D<double>& p1, const Point3D<double>& p2) {
  graphics_scene_->addLine(p1.x(), p1.y(), p2.x(), p2.y());
}

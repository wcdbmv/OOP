#ifndef LAB04_GUI_DRAWER_HPP_
#define LAB04_GUI_DRAWER_HPP_

#include <QGraphicsScene>

#include "math3d/point3d.hpp"

class BaseDrawer {
 public:
  BaseDrawer() = default;
  BaseDrawer(BaseDrawer&) = delete;
  BaseDrawer(const BaseDrawer&) = delete;
  virtual ~BaseDrawer() = default;

  virtual void operator()(const Point3D<double>&, const Point3D<double>&) = 0;
};

class Drawer : public BaseDrawer {
 public:
  explicit Drawer(QGraphicsScene*& graphics_scene);
  Drawer(const Drawer& other);
  ~Drawer() override;

  void operator()(const Point3D<double>& p1, const Point3D<double>& p2) override;

 private:
  QGraphicsScene* graphics_scene_;
};

#endif  // LAB04_GUI_DRAWER_HPP_

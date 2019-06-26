#ifndef LAB04_OBJECTS_CAMERA_HPP_
#define LAB04_OBJECTS_CAMERA_HPP_

#include "invisible_object.hpp"
#include "math3d/point3d.hpp"
#include "math3d/matrix4x4.hpp"

class Camera : public InvisibleObject {
 public:
  Camera();
  Camera(const Point3D<double>&, const Point3D<double>&, double, double, double);

  void set_position(const Point3D<double>&);
  void set_target(const Point3D<double>&);

  Matrix4x4<double> get_view_matrix();

  void RotateUpDownSphere(double);
  void RotateLeftRightSphere(double);

  void Yaw(double);
  void Pitch(double);
  void Roll(double);

 private:
  Vector4D<double> look_;
  Vector4D<double> up_;
  Vector4D<double> right_;

  Vector4D<double> position_;
  Vector4D<double> target_;
};

#endif  // LAB04_OBJECTS_CAMERA_HPP_

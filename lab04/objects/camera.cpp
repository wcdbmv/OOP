#include "camera.hpp"
#include "transformations/dimensional_transformations.hpp"

Camera::Camera() {
  right_[0] = right_[3] = 1;
  up_[1] = up_[3] = 1;
  look_[2] = look_[3] = 1;
}

Camera::Camera(const Point3D<double>& pos, const Point3D<double>& target, double yaw, double pitch, double roll) {
  position_ = pos.ToVector4D();
  target_ = target.ToVector4D();
  Pitch(pitch);
  Yaw(yaw);
  Roll(roll);
}

void Camera::set_position(const Point3D<double>& pos) {
  position_ = pos.ToVector4D();
}

void Camera::set_target(const Point3D<double>& target) {
  target_ = target.ToVector4D();
}

void Camera::RotateUpDownSphere(double angle) {
  Point3D<double> point(up_[0], up_[1], up_[2]);
  const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
  right_ = transform * right_;
  look_ = transform * look_;
  point = Point3D<double>(target_[0], target_[1], target_[2]);
  const Matrix4x4<double> move = DimensionalTransformations::Move(point);
  position_ = position_ * (move * -1.0) * transform * move;
}

void Camera::RotateLeftRightSphere(double angle) {
  Point3D<double> point(right_[0], right_[1], right_[2]);
  const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
  up_ = transform * up_;
  look_ = transform * look_;
  point = Point3D<double>(target_[0], target_[1], target_[2]);
  const Matrix4x4<double> move = DimensionalTransformations::Move(point);
  position_ = position_ * (move * -1.0) * transform * move;
}

void Camera::Yaw(double angle) {
  Point3D<double> point(up_[0], up_[1], up_[2]);
  const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
  right_ = transform * right_;
  look_ = transform * look_;
}

void Camera::Pitch(double angle) {
  Point3D<double> point(right_[0], right_[1], right_[2]);
  const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
  up_ = transform * up_;
  look_ = transform * look_;
}

void Camera::Roll(double angle) {
  Point3D<double> point(look_[0], look_[1], look_[2]);
  const Matrix4x4<double> transform = DimensionalTransformations::Rotation(point, angle);
  right_ = transform * right_;
  up_ = transform * up_;
}

Matrix4x4<double> Camera::get_view_matrix() {
  look_.Normalize();

  up_ = Vector4D<double>::Cross(look_, right_);
  up_.Normalize();

  right_ = Vector4D<double>::Cross(up_, look_);
  right_.Normalize();

  const double x = -Vector4D<double>::Dot(right_, position_);
  const double y = -Vector4D<double>::Dot(up_, position_);
  const double z = -Vector4D<double>::Dot(look_, position_);

  Matrix4x4<double> tmp = {
    right_[0], up_[0], look_[0], 0,
    right_[1], up_[1], look_[1], 0,
    right_[2], up_[2], look_[2], 0,
    x, y, z, 1
  };

  return tmp;
}

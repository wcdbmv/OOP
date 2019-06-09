#include "dimensional_transformations.hpp"

DimensionalTransformations::RotationOX::RotationOX(double x_angle)
    : ITransformation() {
  this->reset_matrix();
  (*this)[1][1] = cos(x_angle);
  (*this)[1][2] = sin(x_angle);
  (*this)[2][1] = -sin(x_angle);
  (*this)[2][2] = cos(x_angle);
}

DimensionalTransformations::RotationOY::RotationOY(double y_angle)
    : ITransformation() {
  this->reset_matrix();
  (*this)[0][0] = cos(y_angle);
  (*this)[0][2] = -sin(y_angle);
  (*this)[2][0] = sin(y_angle);
  (*this)[2][2] = cos(y_angle);
}

DimensionalTransformations::RotationOZ::RotationOZ(double y_angle)
    : ITransformation() {
  this->reset_matrix();
  (*this)[0][0] = cos(y_angle);
  (*this)[0][1] = sin(y_angle);
  (*this)[1][0] = -sin(y_angle);
  (*this)[1][1] = cos(y_angle);
}

DimensionalTransformations::Rotation::Rotation(const Point3D<double>& offset, double angle)
    : ITransformation() {
  this->reset_matrix();
  (*this)[0][0] = cos(angle) + (1 - cos(angle)) * offset.x() * offset.x();
  (*this)[1][0] = (1 - cos(angle)) * offset.x() * offset.y() - sin(angle) * offset.z();
  (*this)[2][0] = (1 - cos(angle)) * offset.x() * offset.z() + sin(angle) * offset.y();
  (*this)[0][1] = (1 - cos(angle)) * offset.y() * offset.x() + sin(angle) * offset.z();
  (*this)[1][1] = cos(angle) + (1 - cos(angle)) * offset.y() * offset.y();
  (*this)[2][1] = (1 - cos(angle)) * offset.y() * offset.z() - sin(angle) * offset.x();
  (*this)[0][2] = (1 - cos(angle)) * offset.z() * offset.x() - sin(angle) * offset.y();
  (*this)[1][2] = (1 - cos(angle)) * offset.z() * offset.y() + sin(angle) * offset.x();
  (*this)[2][2] = cos(angle) + (1 - cos(angle)) * offset.z() * offset.z();
}

DimensionalTransformations::Move::Move(const Point3D<double>& offset)
    : ITransformation() {
  this->reset_matrix();
  (*this)[0][3] = offset.x();
  (*this)[1][3] = offset.y();
  (*this)[2][3] = offset.z();
}

DimensionalTransformations::Scale::Scale(double scale_factor) {
  this->reset_matrix();
  (*this)[0][0] = scale_factor;
  (*this)[1][1] = scale_factor;
  (*this)[2][2] = scale_factor;
}

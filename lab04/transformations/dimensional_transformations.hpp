#ifndef LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_
#define LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_

#include <cmath>

#include "transformation_interface.hpp"
#include "math3d/point3d.hpp"

namespace DimensionalTransformations {

class RotationOX : public ITransformation {
 public:
  explicit RotationOX(double);
  RotationOX(const RotationOX&) = delete;
};

class RotationOY : public ITransformation {
 public:
  explicit RotationOY(double);
  RotationOY(const RotationOY&) = delete;
};

class RotationOZ : public ITransformation {
 public:
  explicit RotationOZ(double);
  RotationOZ(const RotationOZ&) = delete;
};

class Rotation : public ITransformation {
 public:
  explicit Rotation(const Point3D<double>&, double);
  Rotation(const Rotation&) = delete;
};

class Move : public ITransformation {
 public:
  explicit Move(const Point3D<double>&);
  Move(const Move&) = delete;
};

class Scale : public ITransformation {
 public:
  explicit Scale(double);
  Scale(const Scale&) = delete;
};

}  // namespace DimensionalTransformations

#endif  // LAB04_TRANSFORMATIONS_DIMENSIONAL_TRANSFORMATIONS_HPP_

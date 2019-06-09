#include "transformation_interface.hpp"

ITransformation::ITransformation()
    : Matrix4x4<double>() {
  this->reset_matrix();
}

void ITransformation::reset_matrix() {
  *(reinterpret_cast<Matrix4x4<double>*>(this)) = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
}

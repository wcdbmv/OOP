#include "commands.hpp"

namespace Commands {

UploadView::UploadView(std::string filename)
    : filename_(std::move(filename)) {}

void UploadView::Execute(Controller*&controller) {
  Uploader uploader(filename_);
  controller->UploadView(uploader);
}

DeleteView::DeleteView(size_t view_index)
    : view_index_(view_index) {}

void DeleteView::Execute(Controller*& controller) {
  controller->RemoveView(view_index_);
}

AddModel::AddModel(size_t view_index)
    : view_index_(view_index) {}

void AddModel::Execute(Controller*& controller) {
  controller->AddModel(view_index_);
}

RemoveModel::RemoveModel(size_t model_index)
    : model_index_(model_index) {}

void RemoveModel::Execute(Controller*& controller) {
  controller->RemoveModel(model_index_);
}

void AddCamera::Execute(Controller*& controller) {
  controller->AddCamera();
}

RemoveCamera::RemoveCamera(size_t camera_index)
    : camera_index_(camera_index) {}

void RemoveCamera::Execute(Controller*& controller) {
  controller->RemoveCamera(camera_index_);
}

Move::Move(Point3D<double> point, ssize_t model_index)
    : point_(std::move(point)), model_index_(model_index) {}

void Move::Execute(Controller*& controller) {
  DimensionalTransformations::Move move(point_);
  ModelTransformation transformation(move);
  controller->TransformModel(transformation, model_index_);
}

RotateModelOX::RotateModelOX(double angle, ssize_t model_index)
    : angle_(angle), model_index_(model_index) {}

void RotateModelOX::Execute(Controller*& controller) {
  DimensionalTransformations::RotationOX rotation(angle_);
  ModelTransformation transformation(rotation);
  controller->TransformModel(transformation, model_index_);
}

RotateModelOY::RotateModelOY(double angle, ssize_t model_index)
    : angle_(angle), model_index_(model_index) {}

void RotateModelOY::Execute(Controller*& controller) {
  DimensionalTransformations::RotationOY rotation(angle_);
  ModelTransformation transformation(rotation);
  controller->TransformModel(transformation, model_index_);
}

RotateModelOZ::RotateModelOZ(double angle, ssize_t model_index)
    : angle_(angle), model_index_(model_index) {}

void RotateModelOZ::Execute(Controller*& controller) {
  DimensionalTransformations::RotationOZ rotation(angle_);
  ModelTransformation transformation(rotation);
  controller->TransformModel(transformation, model_index_);
}

Scale::Scale(double scale_factor, ssize_t model_index)
    : scale_factor_(scale_factor), model_index_(model_index) {}

void Scale::Execute(Controller*& controller) {
  DimensionalTransformations::Scale scale(scale_factor_);
  ModelTransformation transformation(scale);
  controller->TransformModel(transformation, model_index_);
}

Draw::Draw(Drawer& drawer, ssize_t camera_index)
    : drawer_(drawer), camera_index_(camera_index) {}

void Draw::Execute(Controller*& controller) {
  controller->DrawScene(drawer_, camera_index_);
}

Yaw::Yaw(double angle, size_t index)
    : angle_(angle), camera_index_(index) {}

void Yaw::Execute(Controller*& controller) {
  CameraDimensionalTransformations::Yaw yaw(angle_);
  controller->TransformCamera(yaw, camera_index_);
}

Pitch::Pitch(double angle, size_t index)
    : angle_(angle), camera_index_(index) {}

void Pitch::Execute(Controller*& controller) {
  CameraDimensionalTransformations::Pitch pitch(angle_);
  controller->TransformCamera(pitch, camera_index_);
}

Roll::Roll(double angle, size_t index)
    : angle_(angle), camera_index_(index) {}

void Roll::Execute(Controller*& controller) {
  CameraDimensionalTransformations::Roll roll(angle_);
  controller->TransformCamera(roll, camera_index_);
}

}  // namespace Commands

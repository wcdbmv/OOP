#include "controller.hpp"

Controller* Controller::Instance() {
  return new Controller();
}

void Controller::UploadView(BaseUploader& uploader) {
  model_view_.AddView(UploadManager::UploadModel(uploader));
}

void Controller::RemoveView(std::size_t index) {
  model_view_.RemoveView(index);
}

void Controller::AddModel(std::size_t index) {
  scene_.AddModel(new Model(model_view_[index]));
}

void Controller::RemoveModel(std::size_t index) {
  scene_.RemoveModel(index);
}

void Controller::AddCamera() {
  scene_.AddCamera(new Camera());
}

void Controller::RemoveCamera(std::size_t index) {
  scene_.RemoveCamera(index);
}

void Controller::TransformModel(BaseTransformation& transformation, ssize_t index) {
  ModelManager::Transform(scene_, transformation, index);
}

void Controller::TransformCamera(ICommand& command, std::size_t index) {
  CameraManager::Transform(scene_, command, index);
}

void Controller::DrawScene(BaseDrawer& drawer, ssize_t camera_index) {
  DrawManager::Draw(scene_, drawer, reinterpret_cast<Camera*>(scene_.get_camera(camera_index)));
}

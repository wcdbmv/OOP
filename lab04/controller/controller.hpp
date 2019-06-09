#ifndef LAB04_CONTROLLER_CONTROLLER_HPP_
#define LAB04_CONTROLLER_CONTROLLER_HPP_

#include <QGraphicsScene>

#include "scene/scene.hpp"
#include "model_view/model_view.hpp"
#include "managers/camera_manager.hpp"
#include "managers/model_manager.hpp"
#include "managers/draw_manager.hpp"
#include "managers/upload_manager.hpp"
#include "gui/drawer.hpp"

class Controller {
 public:
  static Controller* Instance();

  Controller(Controller&) = delete;
  Controller(const Controller&) = delete;
  ~Controller() = default;

  void UploadView(BaseUploader& uploader);
  void RemoveView(size_t index);

  void AddModel(size_t index);
  void RemoveModel(size_t index);

  void AddCamera();
  void RemoveCamera(size_t index);

  void TransformModel(BaseTransformation& transformation, ssize_t index);
  void TransformCamera(ICommand& command, size_t index);

  void DrawScene(BaseDrawer& drawer, ssize_t camera_index);

 protected:
  Controller() = default;

 private:
  Scene scene_;
  ModelView model_view_;
};

#endif // LAB04_CONTROLLER_CONTROLLER_HPP_

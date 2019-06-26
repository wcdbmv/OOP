#ifndef LAB04_MANAGERS_CAMERA_MANAGER_HPP_
#define LAB04_MANAGERS_CAMERA_MANAGER_HPP_

#include "scene/scene.hpp"
#include "transformations/command_interface.hpp"

class CameraManager {
 public:
  static void Transform(Scene& scene, ICommand& command, std::size_t index);

 private:
  CameraManager() = default;
};

#endif  // LAB04_MANAGERS_CAMERA_MANAGER_HPP_

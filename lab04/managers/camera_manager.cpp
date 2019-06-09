#include "camera_manager.hpp"

void CameraManager::Transform(Scene& scene, ICommand& command, std::size_t index) {
  Camera* camera = reinterpret_cast<Camera*>(scene.get_camera(index));
  command.Execute(camera);
}

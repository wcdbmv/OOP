#include "command_interface.hpp"

namespace CameraCommands {

Yaw::Yaw(double angle)
    : angle_(angle) {}

void Yaw::Execute(Camera*& camera) {
  camera->Yaw(angle_);
}

Pitch::Pitch(double angle)
    : angle_(angle) {}

void Pitch::Execute(Camera*& camera) {
  camera->Pitch(angle_);
}

Roll::Roll(double angle)
    : angle_(angle) {}

void Roll::Execute(Camera*& camera) {
  camera->Roll(angle_);
}

}  // namespace CameraDimensionalTransformations

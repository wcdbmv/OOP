#ifndef LAB04_TRANSFORMATIONS_COMMAND_INTERFACE_HPP_
#define LAB04_TRANSFORMATIONS_COMMAND_INTERFACE_HPP_

#include "objects/camera.hpp"

class ICommand {
 public:
  ICommand() = default;
  ICommand(const ICommand&) = delete;

  virtual void Execute(Camera*&) = 0;
};

namespace CameraCommands {

class Yaw : public ICommand {
 public:
  explicit Yaw(double angle);
  Yaw(const Yaw&) = delete;

  void Execute(Camera*& camera) override;

 private:
  double angle_;
};

class Pitch : public ICommand {
 public:
  explicit Pitch(double angle);
  Pitch(const Pitch&) = delete;

  void Execute(Camera*& camera) override;

 private:
  double angle_;
};

class Roll : public ICommand {
 public:
  explicit Roll(double angle);
  Roll(const Roll&) = delete;

  void Execute(Camera*& camera) override;

 private:
  double angle_;
};

}  // namespace CameraCommands

#endif  // LAB04_TRANSFORMATIONS_COMMAND_INTERFACE_HPP_

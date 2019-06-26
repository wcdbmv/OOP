#ifndef LAB04_COMMANDS_COMMANDS_HPP_
#define LAB04_COMMANDS_COMMANDS_HPP_

#include "controller/controller.hpp"
#include "transformations/dimensional_transformations.hpp"
#include "transformations/transformation.hpp"
#include "gui/drawer.hpp"

class Command {
public:
 Command() = default;
 Command(const Command&) = delete;
 ~Command() = default;

 virtual void Execute(Controller*& controller) = 0;
};

namespace Commands {

class UploadView : public Command {
 public:
  explicit UploadView(std::string filename);
  UploadView(const UploadView&) = delete;
  ~UploadView() = default;

  void Execute(Controller*& controller) override;

 private:
  std::string filename_;
};

class DeleteView : public Command {
 public:
  explicit DeleteView(std::size_t view_index);
  DeleteView(const DeleteView&) = delete;
  ~DeleteView() = default;

  void Execute(Controller*& controller) override;

 private:
  std::size_t view_index_;
};

class AddModel : public Command {
 public:
  explicit AddModel(std::size_t view_index);
  AddModel(const AddModel&) = delete;
  ~AddModel() = default;

  void Execute(Controller*& controller) override;

 private:
  std::size_t view_index_;
};

class RemoveModel : public Command {
 public:
  explicit RemoveModel(std::size_t model_index);
  RemoveModel(RemoveModel&) = delete;
  RemoveModel(const RemoveModel&) = delete;
  ~RemoveModel() = default;

  void Execute(Controller*& controller) override;

 private:
  std::size_t model_index_;
};

class AddCamera : public Command {
 public:
  AddCamera() = default;
  AddCamera(const AddCamera&) = delete;
  ~AddCamera() = default;

  void Execute(Controller*& controller) override;
};

class RemoveCamera : public Command {
 public:
  explicit RemoveCamera(std::size_t camera_index);
  RemoveCamera(const RemoveCamera&) = delete;
  ~RemoveCamera() = default;

  void Execute(Controller*& controller) override;

 private:
  std::size_t camera_index_;
};

class TranslateModel : public Command {
 public:
  TranslateModel(const Point3D<double>& point, ssize_t model_index);
  TranslateModel(TranslateModel&) = delete;
  TranslateModel(const TranslateModel&) = delete;
  ~TranslateModel() = default;

  void Execute(Controller*& controller) override;

 private:
  Point3D<double> point_;
  ssize_t model_index_;
};

class RotateModelOX : public Command {
 public:
  RotateModelOX(double angle, ssize_t model_index);
  RotateModelOX(const RotateModelOX&) = delete;
  ~RotateModelOX() = default;

  void Execute(Controller*& controller) override;

private:
  double angle_;
  ssize_t model_index_;
};

class RotateModelOY : public Command {
 public:
  RotateModelOY(double angle, ssize_t model_index);
  RotateModelOY(const RotateModelOY&) = delete;
  ~RotateModelOY() = default;

  void Execute(Controller*& controller) override;

 private:
  double angle_;
  ssize_t model_index_;
};

class RotateModelOZ : public Command {
 public:
  RotateModelOZ(double angle, ssize_t model_index);
  RotateModelOZ(const RotateModelOZ&) = delete;
  ~RotateModelOZ() = default;

  void Execute(Controller*& controller) override;

 private:
  double angle_;
  ssize_t model_index_;
};

class ScaleModel : public Command {
 public:
  ScaleModel(double scale_factor, ssize_t model_index);
  ScaleModel(const ScaleModel&) = delete;
  ~ScaleModel() = default;

  void Execute(Controller*& controller) override;

 private:
  double scale_factor_;
  ssize_t model_index_;
};

class Draw : public Command {
 public:
  Draw(Drawer& drawer, ssize_t camera_index);
  Draw(const Draw&) = delete;
  ~Draw() = default;

  void Execute(Controller*& controller) override;

 private:
  Drawer drawer_;
  ssize_t camera_index_;
};

class YawCamera : public Command {
 public:
  YawCamera(double angle, std::size_t index);
  YawCamera(const YawCamera&) = delete;
  ~YawCamera() = default;

  void Execute(Controller*& controller) override;

 private:
  double angle_;
  std::size_t camera_index_;
};

class PitchCamera : public Command {
 public:
  PitchCamera(double angle, std::size_t index);
  PitchCamera(const PitchCamera&) = delete;
  ~PitchCamera() = default;

  void Execute(Controller*& controller) override;

 private:
  double angle_;
  std::size_t camera_index_;
};

class RollCamera : public Command {
 public:
  RollCamera(double angle, std::size_t index);
  RollCamera(const RollCamera&) = delete;
  ~RollCamera() = default;

  void Execute(Controller*& controller) override;

 private:
  double angle_;
  std::size_t camera_index_;
};

}  // namespace Commands

#endif  // LAB04_COMMANDS_COMMANDS_HPP_

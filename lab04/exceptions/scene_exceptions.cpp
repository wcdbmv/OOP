#include "scene_exceptions.hpp"

BaseSceneException::BaseSceneException(const char* message)
    : BaseException(message) {}

const char* BaseSceneException::what() const noexcept {
  return message_.empty() ? "Scene::(Base exception)" : message_.c_str();
}

SceneOutOfRangeException::SceneOutOfRangeException(const char* message)
    : BaseSceneException(message) {}

const char* SceneOutOfRangeException::what() const noexcept {
  return message_.empty() ? "Scene::(Out of range)" : message_.c_str();
}

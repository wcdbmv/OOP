#ifndef LAB04_EXCEPTIONS_SCENE_EXCEPTIONS_HPP_
#define LAB04_EXCEPTIONS_SCENE_EXCEPTIONS_HPP_

#include "base_exception.hpp"

class BaseSceneException : public BaseException {
 public:
  explicit BaseSceneException() = default;
  explicit BaseSceneException(const char* message);

  const char* what() const noexcept override;
};

class SceneOutOfRangeException : public BaseSceneException {
 public:
  explicit SceneOutOfRangeException() = default;
  explicit SceneOutOfRangeException(const char* message);

  const char* what() const noexcept override;
};

#endif  // LAB04_EXCEPTIONS_SCENE_EXCEPTIONS_HPP_

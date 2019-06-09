#ifndef LAB04_FACADE_FACADE_HPP_
#define LAB04_FACADE_FACADE_HPP_

#include <string>

#include "controller/controller.hpp"
#include "commands/commands.hpp"
#include "exceptions/base_exception.hpp"

class Facade {
 public:
  Facade();
  Facade(Facade&) = delete;
  Facade(const Facade&) = delete;
  ~Facade();

  void ExecuteCommand(Command& command);

 private:
  Controller* controller_;
};

#endif  // LAB04_FACADE_FACADE_HPP_

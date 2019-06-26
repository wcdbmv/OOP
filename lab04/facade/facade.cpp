#include "facade.hpp"

Facade::Facade()
    : controller_(Controller::Instance()) {}

Facade::~Facade() {
  delete controller_;
}

void Facade::ExecuteCommand(Command& command) {
  command.Execute(controller_);
}

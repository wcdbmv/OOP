#include "elevator.h"

Elevator::Elevator(int floors, QObject *parent, Logger *logger)
	: QObject(parent)
	, floors(floors)
	, control(floors, parent, logger)
	, cab(parent, logger)
	, logger(logger)
{
	connect(this, &Elevator::called, &control, &ControlPanel::call);
	connect(&control, &ControlPanel::called, &cab, &ElevatorCab::call);
	connect(&cab, &ElevatorCab::passed_floor, &control, &ControlPanel::pass_floor);
	connect(&cab, &ElevatorCab::stopped, &control, &ControlPanel::reach_target_floor);
	connect(&cab, &ElevatorCab::stopped, this, &Elevator::stopped);
	connect(&control, &ControlPanel::stopped, &cab, &ElevatorCab::reset_direction);
	connect(&control, &ControlPanel::on_floor, this, &Elevator::on_floor);
}

void Elevator::set_logger(Logger *logger)
{
	this->logger = logger;
	control.set_logger(logger);
	cab.set_logger(logger);
}

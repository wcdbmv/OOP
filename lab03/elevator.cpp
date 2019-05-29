#include "elevator.h"

Elevator::Elevator(int floors, QObject *parent, Logger *logger)
	: QObject(parent)
	, control(floors, parent, logger)
	, cab(parent, logger)
	, logger(logger)
{
	connect(this, &Elevator::called, &control, &ControlPanel::call);
	connect(&control, &ControlPanel::called, &cab, &ElevatorCab::call);
	connect(&control, &ControlPanel::move_up, &cab, &ElevatorCab::move_up);
	connect(&control, &ControlPanel::move_down, &cab, &ElevatorCab::move_down);
	connect(&control, &ControlPanel::stop, &cab, &ElevatorCab::stop);
	connect(&cab, &ElevatorCab::passed_floor, &control, &ControlPanel::pass_floor);
	connect(&cab, &ElevatorCab::ready, &control, &ControlPanel::look_around);
	connect(&control, &ControlPanel::passed_floor, this, &Elevator::passed_floor);
	connect(&control, &ControlPanel::stopped, this, &Elevator::stopped);
}

void Elevator::set_logger(Logger *logger)
{
	this->logger = logger;
	control.set_logger(logger);
	cab.set_logger(logger);
}

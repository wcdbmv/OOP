#include "elevatorcab.h"

#include <algorithm>

ElevatorCab::ElevatorCab(QObject *parent, Logger *logger)
	: QObject(parent)
	, floor(1)
	, target(1)
	, state(State::standing)
	, direction(Direction::stay)
	, doors(parent, logger)
	, logger(logger)
{
	pass_floor_timer.setInterval(TIME_TO_PASS_FLOOR);
	pass_floor_timer.setSingleShot(true);

	connect(this, &ElevatorCab::called, &doors, &ElevatorCabDoors::start_closing);
	connect(&doors, &ElevatorCabDoors::closed, this, &ElevatorCab::move);
	connect(&pass_floor_timer, &QTimer::timeout, this, &ElevatorCab::move);
	connect(this, &ElevatorCab::reached_target_floor, this, &ElevatorCab::stop);
	connect(this, &ElevatorCab::stopped, &doors, &ElevatorCabDoors::start_opening);
}

void ElevatorCab::set_logger(Logger *logger)
{
	this->logger = logger;
	doors.set_logger(logger);
}

void ElevatorCab::move()
{
	if (state == State::calling) {
		if (floor == target) {
			emit reached_target_floor(floor);
		}
		else {
			state = State::moving;
			emit passed_floor(floor, direction);
			pass_floor_timer.start();
		}
	}
	else if (state == State::moving) {
		floor += direction == Direction::up ? 1 : -1;
		if (floor == target) {
			emit reached_target_floor(floor);
		}
		else {
			pass_floor_timer.start();
			emit passed_floor(floor, direction);
		}

	}
}

void ElevatorCab::stop()
{
	if (direction != Direction::stay)
		log(logger, "Лифт остановился на " + QString::number(floor) + " этаже");
	state = State::standing;
	pass_floor_timer.stop();
	emit stopped(floor);
}

void ElevatorCab::call(int floor)
{
	state = State::calling;
	target = floor;
	if (this->floor == target) {
		emit reached_target_floor(floor);
	}
	else {
		direction = this->floor < target ? Direction::up : Direction::down;
		emit called();
	}
}

void ElevatorCab::reset_direction()
{
	direction = Direction::stay;
}

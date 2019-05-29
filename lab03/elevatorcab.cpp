#include "elevatorcab.h"

#include <algorithm>

ElevatorCab::ElevatorCab(QObject *parent, Logger *logger)
	: QObject(parent)
	, state(State::standing)
	, doors(parent, logger)
	, direction(Direction::stay)
	, logger(logger)
{
	up_floor_timer.setInterval(TIME_TO_PASS_FLOOR);
	up_floor_timer.setSingleShot(true);

	down_floor_timer.setInterval(TIME_TO_PASS_FLOOR);
	down_floor_timer.setSingleShot(true);

	connect(this, &ElevatorCab::called, &doors, &ElevatorCabDoors::start_closing);
	connect(&doors, &ElevatorCabDoors::closed, this, &ElevatorCab::start_moving);
	connect(&up_floor_timer, &QTimer::timeout, this, &ElevatorCab::passed_floor);
	connect(&down_floor_timer, &QTimer::timeout, this, &ElevatorCab::passed_floor);
	connect(this, &ElevatorCab::stopped, &doors, &ElevatorCabDoors::start_opening);
}

void ElevatorCab::set_logger(Logger *logger)
{
	this->logger = logger;
	doors.set_logger(logger);
}

void ElevatorCab::move_up()
{
	if (state == State::ready || state == State::moving_up) {
		state = State::moving_up;

		log(logger, "Лифт поднимается");
		up_floor_timer.start();
	}
}

void ElevatorCab::move_down()
{
	if (state == State::ready || state == State::moving_down) {
		state = State::moving_down;

		log(logger, "Лифт опускается");
		down_floor_timer.start();
	}
}

void ElevatorCab::start_moving()
{
	if (state == State::calling) {
		state = State::ready;

		if (direction == Direction::up) {
			log(logger, "Лифт поднимается");
			up_floor_timer.start();
		}
		else if (direction == Direction::down) {
			log(logger, "Лифт опускается");
			down_floor_timer.start();
		}
	}
	else if (state == State::standing) {
		emit ready();
	}
}

void ElevatorCab::stop()
{
	up_floor_timer.stop();
	down_floor_timer.stop();

	if (state != State::standing) {
		state = State::standing;
		emit stopped();
	}
}

void ElevatorCab::call(Direction direction)
{
	if (state == State::standing) {
		this->direction = direction;
		state = State::calling;
		emit called();
	}
}

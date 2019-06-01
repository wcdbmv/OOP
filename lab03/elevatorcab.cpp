#include "elevatorcab.h"

ElevatorCab::ElevatorCab(QObject *parent, Logger *logger)
	: QObject(parent)
	, state(State::standing)
	, doors(parent, logger)
	, direction(Direction::stay)
	, logger(logger)
{
	pass_floor_timer.setInterval(TIME_TO_PASS_FLOOR);
	pass_floor_timer.setSingleShot(true);

	connect(this, &ElevatorCab::called, &doors, &ElevatorCabDoors::start_closing);
	connect(&doors, &ElevatorCabDoors::closed, this, &ElevatorCab::move);
	connect(&pass_floor_timer, &QTimer::timeout, this, &ElevatorCab::passed_floor);
	connect(this, &ElevatorCab::stopped, &doors, &ElevatorCabDoors::start_opening);
}

void ElevatorCab::set_logger(Logger *logger)
{
	this->logger = logger;
	doors.set_logger(logger);
}

void ElevatorCab::_move()
{
	log(logger, "Лифт " + QString(direction == Direction::up ? "поднимается" : "опускается"));
	pass_floor_timer.start();
}

void ElevatorCab::move()
{
	if (state == State::calling || state == State::moving) {
		state = State::moving;
		_move();
	}
	else if (state == State::standing)
		emit ready();
}

void ElevatorCab::stop()
{
	pass_floor_timer.stop();

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

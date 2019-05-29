#include "controlpanel.h"

#include <QtDebug>

ControlPanel::ControlPanel(int floors, QObject *parent, Logger *logger)
	: QObject(parent)
	, state(State::idle)
	, floors(floors)
	, floor(0)
	, is_target(floors, false)
	, direction(Direction::stay)
	, logger(logger) {}

void ControlPanel::set_logger(Logger *logger)
{
	this->logger = logger;
}

void ControlPanel::call(int floor)
{
	log(logger, "Лифт вызван на " + QString::number(floor + 1) + " этаж");

	is_target[floor] = true;

	if (state == State::idle) {
		if (this->floor == floor) {
			emit stop();
			emit stopped(floor);
		}
		else {
			const int target = floor;
			Q_ASSERT(0 <= target && target < floors);

			state = State::busy;
			direction = dir(target, this->floor);
			emit called(direction);
		}
	}
	else {

	}
}

void ControlPanel::pass_floor()
{
	floor += direction;
	emit passed_floor(floor);

	{
	const QString action = direction == Direction::up ? "поднялся" : "опустился";
	log(logger, "Лифт " + action + " с " + QString::number(floor - direction + 1) + " на " + QString::number(floor + 1));
	}

	if (is_target[floor]) {
		log(logger, "Лифт остановился на " + QString::number(floor + 1) + " этаже");

		state = State::waiting;
		is_target[floor] = false;
		emit stop();
		emit stopped(floor);
	}
	else {
		if (direction == Direction::up)
			emit move_up();
		else if (direction == Direction::down)
			emit move_down();
	}
}

int ControlPanel::next_target() const
{
	for (int target = this->floor + direction; 0 <= target && target < floors; target += direction) {
		if (is_target[target])
			return target;
	}

	for (int target = this->floor - direction; 0 <= target && target < floors; target -= direction) {
		if (is_target[target])
			return target;
	}

	return 0;
}

void ControlPanel::look_around()
{
	if (state == State::waiting) {
		const int target = next_target();
		if (!target) {
			state = State::idle;
		}
		else {
			state = State::busy;
			direction = dir(target, floor);
			emit called(direction);
		}
	}
}

#include "controlpanel.h"

#include <QtDebug>

ControlPanel::ControlPanel(int floors, QObject *parent, Logger *logger)
	: QObject(parent)
	, floors(floors)
	, floor(1)
	, is_target(floors, false)
	, state(State::idle)
	, direction(Direction::stay)
	, logger(logger) {}

void ControlPanel::set_logger(Logger *logger)
{
	this->logger = logger;
}

void ControlPanel::call(int floor)
{
	is_target[floor - 1] = true;
	update_target(floor);
	state = State::busy;
	emit called(floor);
}

void ControlPanel::reach_target_floor(int floor)
{
	if (state == State::busy) {
		emit on_floor(floor);
		this->floor = floor;
		is_target[floor - 1] = false;
		if (update_target(floor))
			emit called(floor);
		else {
			state = State::idle;
			direction = Direction::stay;
			emit stopped();
		}
	}
}

void ControlPanel::pass_floor(int floor, Direction direction)
{
	if (this->floor != floor || !is_target[floor - 1]) {
		this->floor = floor;
		this->direction = direction;
		const bool up = direction == Direction::up;
		const QString action = up ? "поднимается" : "опускается";
		const int to = floor + (up ? 1 : -1);
		log(logger, "Лифт " + action + " с " + QString::number(floor) + " на " + QString::number(to));
		emit on_floor(floor);
	}
}

bool ControlPanel::update_target(int &floor)
{
	const int direction = this->direction == Direction::up ? 1 : -1;
	if (search_target(floor, direction))
		return true;
	return search_target(floor, -direction);
}

bool ControlPanel::search_target(int &floor, int direction)
{
	for (int i = this->floor; 0 < i && i <= floors; i += direction)
		if (is_target[i - 1]) {
			floor = i;
			return true;
		}
	return false;
}

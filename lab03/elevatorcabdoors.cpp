#include "elevatorcabdoors.h"

ElevatorCabDoors::ElevatorCabDoors(QObject *parent, Logger *logger)
	: QObject(parent)
	, state(State::opened)
	, logger(logger)
{
	open_timer.setInterval(TIME_TO_SWITCH);
	open_timer.setSingleShot(true);

	close_timer.setInterval(TIME_TO_SWITCH);
	close_timer.setSingleShot(true);

	hold_timer.setInterval(TIME_TO_HOLD);
	hold_timer.setSingleShot(true);

	connect(&open_timer, &QTimer::timeout, this, &ElevatorCabDoors::open);
	connect(&close_timer, &QTimer::timeout, this, &ElevatorCabDoors::close);
	connect(&hold_timer, &QTimer::timeout, this, &ElevatorCabDoors::start_closing);
	connect(this, &ElevatorCabDoors::opened, &hold_timer, static_cast<void (QTimer::*)()>(&QTimer::start));
}

void ElevatorCabDoors::set_logger(Logger *logger)
{
	this->logger = logger;
}

void ElevatorCabDoors::start_opening()
{
	if (state == State::closed || state == State::closing) {
		log(logger, "Двери открываются");
		state = State::opening;
		int time_to_start = TIME_TO_SWITCH;
		if (state == State::closing) {
			time_to_start -= close_timer.remainingTime();
			close_timer.stop();
		}
		open_timer.start(time_to_start);
	}
}

void ElevatorCabDoors::start_closing()
{
	if (state == State::opened) {
		log(logger, "Двери закрываются");
		state = State::closing;
		close_timer.start();
	}
	else if (state == State::closed) {
		emit closed();
	}
}

void ElevatorCabDoors::open()
{
	if (state == State::opening) {
		log(logger, "Двери открыты");
		state = State::opened;
		emit opened();
	}
}

void ElevatorCabDoors::close()
{
	if (state == State::closing) {
		log(logger, "Двери закрыты");
		state = State::closed;
		emit closed();
	}
}

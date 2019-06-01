#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include "controlpanel.h"
#include "elevatorcab.h"

class Elevator : public QObject
{
	Q_OBJECT

public:
	explicit Elevator(int floors, QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals: // in
	void called(int floor);

signals: // out
	void stopped(int floor);
	void passed_floor(int floor);

private:
	ControlPanel control;
	ElevatorCab cab;

private:
	Logger *logger;
};

#endif // ELEVATOR_H

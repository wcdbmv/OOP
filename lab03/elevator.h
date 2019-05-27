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

signals:
	void called(int floor);
	void stopped(int floor);
	void on_floor(int floor);

private:
	const int floors;
	ControlPanel control;
	ElevatorCab cab;
	Logger *logger;
};

#endif // ELEVATOR_H

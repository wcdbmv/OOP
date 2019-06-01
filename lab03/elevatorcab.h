#ifndef ELEVATORCAB_H
#define ELEVATORCAB_H

#include <QObject>
#include "direction.h"
#include "elevatorcabdoors.h"

class ElevatorCab : public QObject
{
	Q_OBJECT

	enum class State {
		standing,
		calling,
		moving
	};

public:
	explicit ElevatorCab(QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals: // in
	void called();
	void stopped();

signals: // out
	void passed_floor();
	void ready();

public slots:
	void move();
	void stop();
	void call(Direction direction);

private:
	State state;
	ElevatorCabDoors doors;
	Direction direction;
	QTimer pass_floor_timer;

	void _move();

private:
	Logger *logger;

private:
	constexpr static int TIME_TO_PASS_FLOOR = 1000;
};

#endif // ELEVATORCAB_H

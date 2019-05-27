#ifndef ELEVATORCAB_H
#define ELEVATORCAB_H

#include <QObject>
#include "direction.h"
#include "elevatorcabdoors.h"

class ElevatorCab : public QObject
{
	Q_OBJECT

	enum class State {
		moving,
		calling,
		standing
	};

public:
	explicit ElevatorCab(QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals:
	void called();
	void passed_floor(int floor, Direction direction);
	void reached_target_floor(int floor);
	void stopped(int floor);

public slots:
	void move();
	void stop();
	void call(int floor);
	void reset_direction();

private:
	int floor;
	int target;
	State state;
	Direction direction;
	ElevatorCabDoors doors;
	Logger *logger;

	QTimer pass_floor_timer;

private:
	constexpr static int TIME_TO_PASS_FLOOR = 1000;
};

#endif // ELEVATORCAB_H

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include <QVector>
#include "direction.h"
#include "logger.h"

class ControlPanel : public QObject
{
	Q_OBJECT

	enum class State {
		idle,
		busy,
		waiting
	};

public:
	explicit ControlPanel(int floors, QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals: // in
	void move_up();
	void move_down();
	void stop();
	void called(Direction direction);

signals: // out
	void passed_floor(int floor);
	void stopped(int floor);

public slots:
	void call(int floor);
	void pass_floor();
	void look_around();

private:
	State state;

	const int floors;
	int floor;

	QVector<bool> is_target;
	Direction direction;

private:
	Logger *logger;

private:
	int next_target() const;
};

#endif // CONTROLPANEL_H

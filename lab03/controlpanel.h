#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include <QVector>
#include "direction.h"
#include "logger.h"

class ControlPanel : public QObject
{
	Q_OBJECT

public:
	enum class State {
		idle,
		busy
	};

public:
	explicit ControlPanel(int floors, QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals:
	void called(int floor);
	void stopped();
	void on_floor(int floor);

public slots:
	void call(int floor);
	void reach_target_floor(int floor);
	void pass_floor(int floor, Direction direction);

private:
	const int floors;
	int floor;
	QVector<bool> is_target;
	State state;
	Direction direction;
	Logger *logger;

private:
	bool update_target(int &floor);
	bool search_target(int &floor, int direction);
};

#endif // CONTROLPANEL_H

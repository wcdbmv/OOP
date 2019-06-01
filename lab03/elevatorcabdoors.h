#ifndef ELEVATORCABDOORS_H
#define ELEVATORCABDOORS_H

#include <QObject>
#include <QTimer>
#include "logger.h"

class ElevatorCabDoors : public QObject
{
	Q_OBJECT

	enum class State {
		opened,
		closed,
		opening,
		closing
	};

public:
	explicit ElevatorCabDoors(QObject *parent = nullptr, Logger *logger = nullptr);

	void set_logger(Logger *logger);

signals: // out
	void closed();
	void opened();

public slots:
	void start_opening();
	void start_closing();

private slots:
	void open();
	void close();

private:
	State state;
	QTimer open_timer;
	QTimer hold_timer;
	QTimer close_timer;

private:
	Logger *logger;

private:
	constexpr static int TIME_TO_SWITCH = 500;
	constexpr static int TIME_TO_HOLD = 500;
};

#endif // ELEVATORCABDOORS_H

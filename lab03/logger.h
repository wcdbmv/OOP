#ifndef LOGGER_H
#define LOGGER_H

#include <QPlainTextEdit>

class Logger : public QPlainTextEdit
{
public:
	Logger(QWidget *parent = nullptr);

	void log(const QString& message);
};

void log(Logger *logger, const QString &message);

#endif // LOGGER_H

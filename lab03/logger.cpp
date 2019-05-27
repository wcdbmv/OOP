#include "logger.h"
#include <QTime>

Logger::Logger(QWidget *parent) : QPlainTextEdit(parent) { }

void Logger::log(const QString &message)
{
	QPlainTextEdit::appendPlainText(QTime::currentTime().toString("[hh:mm:ss] ") + message);
}

void log(Logger *logger, const QString &message)
{
	if (logger)
		logger->log(message);
}

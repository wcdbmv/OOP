#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QVector>
#include "elevator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:
	void called(int floor);

private slots:
	void floorButtonClicked(int i);
	void cabButtonClicked(int i);

	void stop(int floor);
	void update_floor(int floor);

private:
	constexpr static int floors = 16;

	Ui::MainWindow *ui;

	QVector<QCheckBox *> floor_buttons;
	QVector<QCheckBox *> cab_buttons;

	Elevator elevator;

private:
	void createFloorButtons();
	void createCabButtons();
	void createButtons(QVector<QCheckBox *>& buttons, QLayout *layout, void(MainWindow::*slot)(int));
};

#endif // MAINWINDOW_H

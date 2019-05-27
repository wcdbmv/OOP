#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <functional>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	floor_buttons(floors),
	cab_buttons(floors),
	elevator(floors, parent)
{
	ui->setupUi(this);

	ui->logger->setReadOnly(true);
	elevator.set_logger(ui->logger);

	createFloorButtons();
	createCabButtons();

	connect(this, &MainWindow::called, &elevator, &Elevator::called);
	connect(&elevator, &Elevator::stopped, this, &MainWindow::stop);
	connect(&elevator, &Elevator::on_floor, this, &MainWindow::update_floor);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createButtons(QVector<QCheckBox *>& buttons, QLayout *layout, void(MainWindow::*slot)(int))
{
	for (int i = floors - 1; i >= 0; --i) {
		buttons[i] = new QCheckBox(QString::number(i + 1));
		layout->addWidget(buttons[i]);
		connect(buttons[i], &QCheckBox::clicked, std::bind(slot, this, i));
	}
}

void MainWindow::createFloorButtons()
{
	createButtons(floor_buttons, ui->floorsGroupBox->layout(), &MainWindow::floorButtonClicked);
}

void MainWindow::createCabButtons()
{
	createButtons(cab_buttons, ui->cabGroupBox->layout(), &MainWindow::cabButtonClicked);
}

void MainWindow::floorButtonClicked(int i)
{
	log(ui->logger, "Лифт вызван на " + QString::number(i + 1) + " этаж");
	floor_buttons[i]->setEnabled(false);
	emit called(i + 1);
}

void MainWindow::cabButtonClicked(int i)
{
	log(ui->logger, "В лифте нажата кнопка " + QString::number(i + 1) + " этажа");
	cab_buttons[i]->setEnabled(false);
	emit called(i + 1);
}

void uncheck(QCheckBox *checkbox)
{
	checkbox->setChecked(false);
	checkbox->setEnabled(true);
}

void MainWindow::stop(int floor)
{
	uncheck(floor_buttons[floor - 1]);
	uncheck(cab_buttons[floor - 1]);
}

void MainWindow::update_floor(int floor)
{
	ui->lcdNumber->display(floor);
}

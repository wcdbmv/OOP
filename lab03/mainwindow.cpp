#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <functional>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	floor_buttons(floors),
	cabine_buttons(floors)
{
	ui->setupUi(this);

	ui->plainTextEdit->setReadOnly(true);

	createFloorButtons();
	createCabineButtons();
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

void MainWindow::createCabineButtons()
{
	createButtons(cabine_buttons, ui->cabineGroupBox->layout(), &MainWindow::cabineButtonClicked);
}

void MainWindow::log(const QString &string)
{
	ui->plainTextEdit->appendPlainText(QTime::currentTime().toString("[hh:mm:ss] ") + string);
}

void MainWindow::floorButtonClicked(int i)
{
	log("Вызван лифт на " + QString::number(i + 1) + " этаже");

	floor_buttons[i]->setEnabled(false);
}

void MainWindow::cabineButtonClicked(int i)
{
	log("В кабине лифта нажали на " + QString::number(i + 1) + " этаж");

	cabine_buttons[i]->setEnabled(false);
}

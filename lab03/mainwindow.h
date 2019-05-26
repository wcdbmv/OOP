#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void floorButtonClicked(int i);
	void cabineButtonClicked(int i);

private:
	constexpr static int floors = 16;

	Ui::MainWindow *ui;

	QVector<QCheckBox *> floor_buttons;
	QVector<QCheckBox *> cabine_buttons;

private:
	void createFloorButtons();
	void createCabineButtons();
	void createButtons(QVector<QCheckBox *>& buttons, QLayout *layout, void(MainWindow::*slot)(int));

private:
	void log(const QString &string);
};

#endif // MAINWINDOW_H

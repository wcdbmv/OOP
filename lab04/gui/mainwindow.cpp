#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "commands/commands.hpp"
#include "drawer.hpp"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->frame->setFixedWidth(250);
  this->set_up_scene_view();
  ui->cameraChoiceButton->addItem(QString::number(0) + " : camera");
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
  ssize_t model_current_index = ui->modelChoiceButton->currentIndex() - 1;
  std::size_t camera_current_index = ui->cameraChoiceButton->currentIndex();

  try {

    if (e->key() == Qt::Key_W) {
      Commands::RotateModelOX comm(ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_A) {
      Commands::RotateModelOY comm(ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_S) {
      Commands::RotateModelOX comm(-ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_D) {
      Commands::RotateModelOY comm(-ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_Z) {
      Commands::RotateModelOZ comm(-ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_X) {
      Commands::RotateModelOZ comm(ANGLE, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_I) {
      Point3D<double> point(0, OFFSET, 0);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_J) {
      Point3D<double> point(-OFFSET, 0, 0);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_K) {
      Point3D<double> point(0, -OFFSET, 0);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_L) {
      Point3D<double> point(OFFSET, 0, 0);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_M) {
      Point3D<double> point(0, 0, OFFSET);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    }  else if (e->key() == Qt::Key_N) {
      Point3D<double> point(0, 0, -OFFSET);
      Commands::Move comm(point, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    }  else if (e->key() == Qt::Key_Plus) {
      Commands::Scale comm(SCALE_FACTOR, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_Minus) {
      Commands::Scale comm(1 / SCALE_FACTOR, model_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_H) {
      Commands::Yaw comm(ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_F) {
      Commands::Yaw comm(-ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_T) {
      Commands::Pitch comm(-ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_G) {
      Commands::Pitch comm(ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_B) {
      Commands::Roll comm(-ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);

    } else if (e->key() == Qt::Key_V) {
      Commands::Roll comm(ANGLE, camera_current_index);
      this->command_controller.ExecuteCommand(comm);
    }

    this->update_scene_view(camera_current_index);

  } catch (BaseException& ex) {
    QMessageBox::warning(this, "Error message", QString(ex.what()));
  }
}

void MainWindow::set_up_scene_view() {
  this->scene_view_scene = new QGraphicsScene(ui->sceneView);
  ui->sceneView->setMinimumSize(600, 600);
  ui->sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->sceneView->installEventFilter(this);
}

void MainWindow::update_scene_view(ssize_t camera_index) {
  this->scene_view_scene->clear();
  Drawer dr(this->scene_view_scene);
  Commands::Draw comm(dr, camera_index);
  this->command_controller.ExecuteCommand(comm);
  ui->sceneView->setScene(this->scene_view_scene);
}

void MainWindow::on_actionupload_model_triggered() {
  try {
    QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Specify file with model"), QDir::currentPath(), QObject::tr("Any file (*)"));
    if (filename.isEmpty())
      return;
    Commands::UploadView comm(filename.toStdString());
    this->command_controller.ExecuteCommand(comm);
    ui->listWidget->addItem(filename.section("/", -1, -1).section(".", 0, 0));

  } catch (BaseException& ex) {
    QMessageBox::warning(this, "Error message", QString(ex.what()));
  }
}

void MainWindow::on_addSceneObjectButton_clicked() {
  try {

    if (ui->modelButton->isChecked() && ui->listWidget->count() > 0) {
      Commands::AddModel comm(ui->listWidget->currentIndex().row());
      this->command_controller.ExecuteCommand(comm);
      ui->modelChoiceButton->addItem(QString::number(ui->modelChoiceButton->count() - 1) + " : model");

    } else if (ui->cameraButton->isChecked()) {
      Commands::AddCamera comm;
      this->command_controller.ExecuteCommand(comm);
      ui->cameraChoiceButton->addItem(QString::number(ui->cameraChoiceButton->count()) + " : camera");
    }

    this->update_scene_view(ui->cameraChoiceButton->currentIndex());

  } catch (BaseException& ex) {
    QMessageBox::warning(this, "Error message", QString(ex.what()));
  }
}

void MainWindow::on_removeSceneObjectButton_clicked() {
  try {

    if (ui->modelButton->isChecked() && ui->modelChoiceButton->currentIndex() > 0) {
      Commands::RemoveModel comm(ui->modelChoiceButton->currentIndex() - 1);
      this->command_controller.ExecuteCommand(comm);
      std::size_t i = static_cast<std::size_t>(ui->modelChoiceButton->currentIndex());
      ui->modelChoiceButton->removeItem(ui->modelChoiceButton->currentIndex());

      for (; i < static_cast<std::size_t>(ui->modelChoiceButton->count()); ++i) {
        ui->modelChoiceButton->setItemText(i, QString::number(i - 1) + " : model");
      }

    } else if (ui->cameraButton->isChecked() && ui->cameraChoiceButton->currentIndex() > 0) {
      Commands::RemoveCamera comm(ui->cameraChoiceButton->currentIndex());
      this->command_controller.ExecuteCommand(comm);
      std::size_t i = static_cast<std::size_t>(ui->cameraChoiceButton->currentIndex());
      ui->cameraChoiceButton->removeItem(ui->cameraChoiceButton->currentIndex());

      for (; i < static_cast<std::size_t>(ui->cameraChoiceButton->count()); ++i) {
        ui->cameraChoiceButton->setItemText(i, QString::number(i) + " : camera");
      }
    }

    this->update_scene_view(ui->cameraChoiceButton->currentIndex());

  } catch (BaseException& ex) {
    QMessageBox::warning(this, "Error message", QString(ex.what()));
  }
}

void MainWindow::on_deleteViewButton_clicked() {
  try {
    Commands::DeleteView comm(ui->listWidget->currentIndex().row());
    this->command_controller.ExecuteCommand(comm);

  } catch (BaseException& ex) {
    QMessageBox::warning(this, "Error message", QString(ex.what()));
  }

  delete ui->listWidget->item(ui->listWidget->currentIndex().row());
}

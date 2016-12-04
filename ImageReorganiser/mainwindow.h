#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "imagelogicreorganizerThread.h"

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
  void on_pushButtonDirectory_clicked();
  void on_pushButtonExec_clicked();
  void on_executeFinished();

private:
  Ui::MainWindow *ui;
  ImageLogicReorganizerThread* imageLogicThread;
  void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H

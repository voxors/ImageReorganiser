#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "imagelogicreorganizer.h"

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
  const QString ParamsFilePath = QString("./Params.txt");
  Ui::MainWindow *ui;
  QPointer<ImageLogicReorganizerThread> imageLogicThread;
  void closeEvent(QCloseEvent * event);
  void SaveParams();
  void LoadParams();
};

#endif // MAINWINDOW_H

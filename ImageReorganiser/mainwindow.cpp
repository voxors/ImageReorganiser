#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include "imagelogicreorganizer.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButtonDirectory_clicked()
{
  QFileDialog fileDialog;
  fileDialog.setFileMode(QFileDialog::Directory);
  fileDialog.setOption(QFileDialog::ShowDirsOnly);
  fileDialog.setDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));\

  QString Directory = fileDialog.getExistingDirectory(this);

  if (!(Directory.isNull() && Directory.isEmpty()))
  {
    ui->lineEditDirectory->setText(Directory);
  }
}

void MainWindow::on_pushButton_clicked()
{
  QDir ImageFolder(ui->lineEditDirectory->text());
  if (ImageFolder.exists())
  {
    ImageLogicReorganizer imageLogicReorganizer(ui->lineEditDirectory->text());
    imageLogicReorganizer.Reorganise();
  }
}

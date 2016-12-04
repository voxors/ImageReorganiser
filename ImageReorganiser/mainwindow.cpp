#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setMaximumHeight(this->height());
  this->setMinimumHeight(this->height());
  imageLogicThread = nullptr;
  LoadParams();
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

void MainWindow::on_pushButtonExec_clicked()
{
  QDir ImageFolder(ui->lineEditDirectory->text());
  if (ImageFolder.exists())
  {
    ui->progressBarMain->reset();
    ui->pushButtonExec->setEnabled(false);
    ui->progressBarMain->setTextVisible(true);
    imageLogicThread = new ImageLogicReorganizerThread(ui->lineEditDirectory->text());
    ui->progressBarMain->setMaximum(imageLogicThread->GetNumberOfFile());
    connect(imageLogicThread, SIGNAL(ProgressSignal(int)), ui->progressBarMain, SLOT(setValue(int)));
    connect(imageLogicThread, SIGNAL(finished()), imageLogicThread, SLOT(deleteLater()));
    connect(imageLogicThread, SIGNAL(finished()), this, SLOT(on_executeFinished()));
    imageLogicThread->start();
  }
}

void MainWindow::on_executeFinished()
{
  ui->pushButtonExec->setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  if (!imageLogicThread.isNull())
  {
    if (!imageLogicThread->isFinished())
    {
      QMessageBox MessageBox;
      MessageBox.setText(tr("Êtes-vous sure de vouloir quiter alors que L'exécution est encore en cours"));
      MessageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
      MessageBox.setDefaultButton(QMessageBox::Cancel);
      MessageBox.exec();
      QMessageBox::StandardButton result = static_cast<QMessageBox::StandardButton>(MessageBox.result());
      if (result == QMessageBox::Cancel)
      {
        event->ignore();
      }
    }
  }
  SaveParams();
}

void MainWindow::SaveParams()
{
  QFile ParamsFile(ParamsFilePath);

  if (ParamsFile.open(QFile::WriteOnly|QFile::Truncate))
  {
    QTextStream out(&ParamsFile);
    out << "Directory=" << ui->lineEditDirectory->text() << endl;
  }
}

void MainWindow::LoadParams()
{
  QFile ParamsFile(ParamsFilePath);

  if (ParamsFile.open(QFile::ReadOnly))
  {
    QTextStream in(&ParamsFile);
    while (!in.atEnd())
    {
      QString line = in.readLine();
      int splitPosition = line.indexOf("=");
      QString Variable = line.left(splitPosition);
      QString Value = line.right(line.length() - splitPosition - 1);
      if (Variable == "Directory")
      {
        ui->lineEditDirectory->setText(Value);
      }
      else
      {
        qWarning() << Variable + " is not a defined save parameters";
      }
    }
  }
}

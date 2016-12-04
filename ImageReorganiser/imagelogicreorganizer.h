#ifndef IMAGELOGICREORGANIZER_H
#define IMAGELOGICREORGANIZER_H

#include <QtCore>
#include <QImageReader>

class ImageLogicReorganizerThread : public QThread
{
  Q_OBJECT

private:
  QDir Directory;
  QList<QFileInfo> ImageListPath;

  void FindAllFile();
signals:
  //send number of file completed
  void ProgressSignal(int Progress);
public:
  ImageLogicReorganizerThread(QString Directory);
  unsigned int GetNumberOfFile();
  void run();
};

#endif // IMAGELOGICREORGANIZER_H

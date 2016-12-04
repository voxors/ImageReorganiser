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
public:
  ImageLogicReorganizerThread(QString Directory);
  void run();
};

#endif // IMAGELOGICREORGANIZER_H

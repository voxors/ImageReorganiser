#ifndef IMAGELOGICREORGANIZER_H
#define IMAGELOGICREORGANIZER_H

#include <QtCore>
#include <QImageReader>

class ImageLogicReorganizer
{
private:
  QDir Directory;
  QList<QFileInfo> ImageListPath;

  void FindAllFile();
public:
  ImageLogicReorganizer(QString Directory);
  void Reorganise();
};

#endif // IMAGELOGICREORGANIZER_H

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
  QString Format;
  QHash<QString,QString> ConvertFormat;

  void FindAllFile();
  QString CreateDestPath(QFileInfo fileInfo);
  unsigned int gcd(unsigned int n1, unsigned int n2);
  void CopyFileImage(QFileInfo fileInfo);
signals:
  //send number of file completed
  void ProgressSignal(int Progress);
public:
  ImageLogicReorganizerThread(QString Directory,QString Format,QHash<QString,QString> HashTable);
  unsigned int GetNumberOfFile();
  void run();
};

#endif // IMAGELOGICREORGANIZER_H

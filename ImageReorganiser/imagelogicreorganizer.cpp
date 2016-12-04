#include "imagelogicreorganizer.h"

void ImageLogicReorganizerThread::FindAllFile()
{
  QList<QByteArray> FormatListByte = QImageReader::supportedImageFormats();

  QStringList FormatStringList;
  foreach (QByteArray FormatByte, FormatListByte)
  {
    FormatStringList.append("*."+FormatByte);
  }
  Directory.setNameFilters(FormatStringList);
  QDirIterator it(Directory, QDirIterator::Subdirectories);
  while (it.hasNext())
  {
    it.next();
    ImageListPath.append(it.filePath());
  }
}

ImageLogicReorganizerThread::ImageLogicReorganizerThread(QString Directory)
{
  this->Directory.setPath(Directory);
  this->Directory.setFilter(QDir::Files);
  FindAllFile();
}

unsigned int ImageLogicReorganizerThread::GetNumberOfFile()
{
  return ImageListPath.count();
}

void ImageLogicReorganizerThread::run()
{
  int count = 0;
  foreach (QFileInfo fileInfo, ImageListPath)
  {
    QImage image = QImage(fileInfo.absoluteFilePath());

    QFileInfo Destination = QFileInfo(Directory.absolutePath()
                            +"/"+QString::number(image.width()) + "x" + QString::number(image.height())
                            +"/"+fileInfo.fileName());
    Directory.mkdir(Destination.absolutePath());
    QFile::rename(fileInfo.filePath(),Destination.absoluteFilePath());
    ++count;
    emit ProgressSignal(count);
  }
}


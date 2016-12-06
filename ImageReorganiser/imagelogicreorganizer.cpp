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

ImageLogicReorganizerThread::ImageLogicReorganizerThread(QString Directory,
                                                         QString Format,
                                                         QHash<QString, QString> HashTable)
{
  this->Directory.setPath(Directory);
  this->Directory.setFilter(QDir::Files);
  this->Format = Format;
  this->ConvertFormat = HashTable;
  FindAllFile();
}

unsigned int ImageLogicReorganizerThread::GetNumberOfFile()
{
  return ImageListPath.count();
}

void ImageLogicReorganizerThread::run()
{
  //TODO Multi-Threading
  int count = 0;
  foreach (QFileInfo fileInfo, ImageListPath)
  {
    QFileInfo Destination = CreateDestPath(fileInfo);
    Directory.mkdir(Destination.absolutePath());
    QFile::rename(fileInfo.filePath(),Destination.absoluteFilePath());
    ++count;
    emit ProgressSignal(count);
  }
}

QString ImageLogicReorganizerThread::CreateDestPath(QFileInfo fileInfo)
{
  QImage image = QImage(fileInfo.absoluteFilePath());

  QString ConvertedFormat = Format;
  QHashIterator<QString,QString> i(ConvertFormat);
  while (i.hasNext())
  {
    i.next();
    if (i.key() == "%w")
    {
      ConvertedFormat = ConvertedFormat.replace("%w",QString::number(image.width()));
    }
    else if (i.key() == "%h")
    {
      ConvertedFormat = ConvertedFormat.replace("%h",QString::number(image.height()));
    }
    else
    {
      qWarning() << i.key() + " Should be converted but no conversion found";
    }
  }

  return Directory.absolutePath() + "/" + ConvertedFormat + "/" + fileInfo.fileName();
}


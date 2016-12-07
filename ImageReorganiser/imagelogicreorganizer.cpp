#include "imagelogicreorganizer.h"
#include <cmath>

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
    Directory.mkpath(Destination.absolutePath());
    if (!QFile::rename(fileInfo.filePath(),Destination.absoluteFilePath()))
    {
      qWarning() << "move failed with error : " << QFile::AbortError << endl;
    }
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
    else if (i.key() == "%M")
    {
      if (image.width() > image.height())
      {
        ConvertedFormat = ConvertedFormat.replace("%M",tr("Paysage"));
      }
      if (image.width() < image.height())
      {
        ConvertedFormat = ConvertedFormat.replace("%M",tr("Portrait"));
      }
      if (image.width() == image.height())
      {
        ConvertedFormat = ConvertedFormat.replace("%M",tr("Carré"));
      }
    }
    else if (i.key() == "%r")
    {
      unsigned int PlusGrandCommunDiviseur = gcd(image.width(),image.height());
      unsigned int XRatio = image.width() / PlusGrandCommunDiviseur;
      unsigned int YRatio = image.height() / PlusGrandCommunDiviseur;

      if (XRatio == 8 && YRatio == 5)
      {
        XRatio *= 2;
        YRatio *= 2;
      }

      ConvertedFormat = ConvertedFormat.replace("%r",QString::number(XRatio)+"-"
                                                + QString::number(YRatio));
    }
    else
    {
      qWarning() << i.key() + " Should be converted but no conversion found";
    }
  }

  QFileInfo FinalDestination = Directory.absolutePath() + "/" + ConvertedFormat + "/" + fileInfo.fileName();

  while (FinalDestination.exists())
  {
    FinalDestination = Directory.absolutePath() +
        "/" + ConvertedFormat +
        "/" + FinalDestination.baseName().append("_more") +
        "." + FinalDestination.completeSuffix();
  }

  return FinalDestination.absoluteFilePath();
}

unsigned int ImageLogicReorganizerThread::gcd (unsigned int n1, unsigned int n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}


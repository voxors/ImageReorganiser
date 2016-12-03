#include "imagelogicreorganizer.h"

void ImageLogicReorganizer::FindAllFile()
{
    QList<QByteArray> FormatListByte = QImageReader::supportedImageFormats();

    QStringList FormatStringList;
    foreach (QByteArray FormatByte, FormatListByte) {
        FormatStringList.append(FormatByte);
    }

    QDirIterator it(Directory, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        it.next();
        ImageListPath.append(it.path());
    }
}

ImageLogicReorganizer::ImageLogicReorganizer(QString Directory)
{
    this->Directory.setPath(Directory);
    this->Directory.setFilter(QDir::Files);
    FindAllFile();
}

void ImageLogicReorganizer::MoveToBackup()
{

}


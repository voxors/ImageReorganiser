#include "imagelogicreorganizer.h"

void ImageLogicReorganizer::FindAllFile()
{
    QList<QByteArray> FormatListByte = QImageReader::supportedImageFormats();

    QStringList FormatStringList;
    foreach (QByteArray FormatByte, FormatListByte) {
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

ImageLogicReorganizer::ImageLogicReorganizer(QString Directory)
{
    this->Directory.setPath(Directory);
    this->Directory.setFilter(QDir::Files);
    FindAllFile();
}

void ImageLogicReorganizer::MoveToBackup()
{
    if (!QDir(Directory.path()+"/Backup").exists())
    {
        QDir(Directory.path()+"/Backup").mkdir(".");
    }
    Directory.cd(Directory.path()+"/Backup");
    unsigned int count = 0;
    foreach (QFileInfo ImagePath, ImageListPath)
    {
        ++count;
        qDebug() << ImagePath.absoluteFilePath();
        qDebug() << Directory.absolutePath()+"/Image_"+QString::number(count)+"."+ImagePath.suffix();
        QFile::rename(ImagePath.absoluteFilePath(),Directory.absolutePath()+"/Image_"+QString::number(count)+"."+ImagePath.suffix());
    }
}


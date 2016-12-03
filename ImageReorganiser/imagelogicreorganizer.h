#ifndef IMAGELOGICREORGANIZER_H
#define IMAGELOGICREORGANIZER_H

#include <QtCore>
#include <QImageReader>

class ImageLogicReorganizer
{
private:
    QDir Directory;
    QList<QString> ImageListPath;

    void FindAllFile();
public:
    ImageLogicReorganizer(QString Directory);
    void MoveToBackup();
};

#endif // IMAGELOGICREORGANIZER_H

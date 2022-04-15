#ifndef UTILS_H
#define UTILS_H
#include <QFile>
#include <QDebug>
#include <QString>

namespace S4{
namespace QT{

inline bool fileCanBeOpened(const QString &path){
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()){
        // qDebug() << "File can't be opened, path: " << path;
        return false;
    }

    return  true;
}

}
}

#endif // UTILS_H

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>

class FileManager
{
public:
    FileManager();
    void openFile(const QString &filePath, QString &uffer);
    void saveFile(const QString &filePath);
    void fileDirectory(const QString &filePath);
    ~FileManager();
};

#endif // FILEMANAGER_H

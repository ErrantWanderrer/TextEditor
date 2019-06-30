#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <QFile>
#include <QTextStream>


class FileEdit
{
public:
    FileEdit();

    QString openFile(const QString &filepath);
    void saveFile(const QString &filepath, QString &text);

    ~FileEdit();
};

#endif // FILEEDIT_H

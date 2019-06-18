#include "filemanager.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

void FileManager::openFile(const QString &filePath, QString &buffer)
{
    QFile mFile(filePath);
    QTextStream stream(&mFile); // создание потока ввода текста
    buffer = stream.readAll(); //буфер в которой помещается все текстовое значение
    mFile.flush(); // метод позволяет считывать информацию без ожидания кэша с жесткого диска
    mFile.close();
}

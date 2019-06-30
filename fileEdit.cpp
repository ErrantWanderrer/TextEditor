#include "fileEdit.h"
#include "QInputDialog"
FileEdit::FileEdit()
{

}

FileEdit::~FileEdit()
{

}

QString FileEdit::openFile(const QString &filepath)
{
    QFile file(filepath);
    QTextStream fstream(&file); // создание потока ввода текста
    file.open(QFile::ReadOnly);
    QString text = fstream.readAll(); // считываем в поток все текстовое значение
    file.flush(); // метод позволяет считывать информацию без ожидания кэша с жесткого диска
    file.close();

    return text;
}

void FileEdit::saveFile(const QString &filepath, QString &text)
{
    QFile file (filepath);
    QTextStream fstream(&file);
    file.open(QFile::WriteOnly);
    fstream << text;
    file.flush();
    file.close();
}

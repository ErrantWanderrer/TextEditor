#ifndef FILE_H
#define FILE_H

#include <QDialog>

namespace Ui {
class File;
}

class File : public QDialog
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();

private:
    Ui::File *ui;
signals:
    void filePath(const QString  &str); // Сигнал для генерации строки пути к файлу
private slots:
    void okClicked(); // Слот для генерации сигнала filePath через emit
};

#endif // FILE_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "edit.h"
#include "fileEdit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void fileDirectory(const QString &filePath);
    void actionFileDirectory();
    void Copy();
    void Paste();
    void Cut();
    void setTextSize();
    void setTextColor();
    void setTextFont();
    void setTextCodec();
    void setTextBackgroundColor();
    void setBackgroundColor();

private:
    Ui::MainWindow *ui;
    FileEdit *file;
    EditVisual *editor;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "edit.h"

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
    void openFile(const QString &filePath);
    void saveFile(const QString &filePath);
    void fileDirectory(const QString &filePath);
    void on_actionOpen_file_triggered();
    void on_actionSave_file_triggered();
    void on_actionFile_directory_triggered();
    void Copy();
    void Paste();
    void Cut();
    void setTextSize();
    void setTextColor();
    void setTextFont();
    void setTextBackgroundColor();
    void setBackgroundColor();


private:
    Ui::MainWindow *ui;
    EditVisual *editor;
};

#endif // MAINWINDOW_H

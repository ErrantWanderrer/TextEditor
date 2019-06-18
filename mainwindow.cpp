#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include "edit.h"
#include <QMessageBox> // отображение ошибок
#include <QTextStream> // позволяет вводить и выводить текстовые значения
#include <QFile>
#include <QString>
#include <QColorDialog>
#include <QInputDialog>
#include <QDir> // позволяет работать с директориями


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    editor = new EditVisual(ui->textEdit);
    ui->actionOpen_file->setIcon(QIcon(":/Icon/icons/open.png"));
    ui->actionSave_file->setIcon(QIcon(":/Icon/icons/save.png"));
    ui->actionFile_directory->setIcon(QIcon(":/Icon/icons/file.png"));
    connect(ui->actionCopy,&QAction::triggered,this,&MainWindow::Copy);
    connect(ui->actionPaste,&QAction::triggered,this,&MainWindow::Paste);
    connect(ui->actionCut,&QAction::triggered,this,&MainWindow::Cut);
    connect(ui->actionSet_Text_Size,&QAction::triggered,this,&MainWindow::setTextSize);
    connect(ui->actionSet_Text_Color,&QAction::triggered,this,&MainWindow::setTextColor);
    connect(ui->actionSet_Text_Font,&QAction::triggered,this,&MainWindow::setTextFont);
    connect(ui->actionSet_Text_Background_Color,&QAction::triggered,this,&MainWindow::setTextBackgroundColor);
    connect(ui->actionSet_Background_Color,&QAction::triggered,this,&MainWindow::setBackgroundColor);

    ui->statusBar->showMessage("OK");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_file_triggered()
{
    File *wnd = new File(this); // Создаем окно динамически, которое потом откроем на главном окне
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(openFile(QString))); // при открытии окна, генерируется сигнал Path со значением QString, который передается в слот openFile со значением QString
}


void MainWindow::on_actionSave_file_triggered()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(saveFile(QString)));
}

void MainWindow::on_actionFile_directory_triggered()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(fileDirectory(QString)));

}

void MainWindow::fileDirectory(const QString &filePath)
{
    QDir mDir(filePath);
    QString buffer;

    for (QFileInfo temp : mDir.entryInfoList()){ // выдает информацию о директориях
        buffer += temp.absoluteFilePath() + '\n';
    }

    ui->textEdit->setText(buffer); // Передаем буфер в textedit
}

void MainWindow::openFile(const QString &filePath) // реализация слота openFile
{
    //a.func();
    QFile mFile(filePath);
    if (!mFile.open(QFile::ReadOnly | QFile::Text)){ //проверка читаемости файла и того, что файл содержит текстовое значение(+того, что файл вообще открыт)
        QMessageBox::information(this, "Error", "Error open file"); // отображение месадж бокса
        ui->statusBar->showMessage("Error open file"); // в statusBar будет отображаться полученное значение
        return;
    }
    QTextStream stream(&mFile); // создание потока ввода текста
    QString buffer = stream.readAll(); //буфер в которой помещается все текстовое значение
    ui->textEdit->setText(buffer); // из буфера считываем значение
    ui->statusBar->showMessage("Read to file: " + filePath); // означает, что программа считала файл
    mFile.flush(); // метод позволяет считывать информацию без ожидания кэша с жесткого диска
    mFile.close();
}

void MainWindow::saveFile(const QString &filePath) // реализация слота saveFile
{
    QFile mFile(filePath);
    if (!mFile.open(QFile::WriteOnly | QFile::Text)){ //проверка читаемости файла и того, что файл содержит текстовое значение(+того, что файл вообще открыт), отличается тем, что если не сможет открыть, то создаст
        QMessageBox::information(this, "Error", "Error save file"); // отображение месадж бокса
        ui->statusBar->showMessage("Error save file"); // в statusBar будет отображаться полученное значение
        return;
    }
    QTextStream stream(&mFile); // создание потока ввода текста
    stream << ui-> textEdit->toPlainText(); // сбрасываем всю информацию в поток
    ui->statusBar->showMessage("Write to file: " + filePath); // означает, что программа считала файл
    mFile.close();
}

void MainWindow::Copy()
{
    ui->textEdit->copy();
}

void MainWindow::Paste()
{
    ui->textEdit->paste();
}

void MainWindow::Cut()
{
    ui->textEdit->cut();
}

void MainWindow::setTextSize()
{
    editor->changeTextSize(QInputDialog::getInt(this,tr("Size of font"),nullptr,100,1));
}

void MainWindow::setTextColor()
{
    editor->changeTextColor(QColorDialog::getColor(editor->textColor,this));
}

void MainWindow::setTextFont()
{
    QStringList styles;
    styles<<tr("TimesNewRoman")<<tr("Calibri")<<tr("Arial");
    const QString text_style = QInputDialog::getItem(this,tr("Set Font style"),tr("font list"),styles,0,false);
    editor->changeTextFont(text_style);
}

void MainWindow::setTextBackgroundColor()
{
    editor->changeTextBackgroundColor(QColorDialog::getColor(editor->textBgColor,this));
}

void MainWindow::setBackgroundColor()
{
    editor->changeBackgroundColor(QColorDialog::getColor(editor->bgColor,this));
}




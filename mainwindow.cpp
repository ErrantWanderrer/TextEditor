#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include <QMessageBox> // отображение ошибок
#include <QTextStream> // позволяет вводить и выводить текстовые значения
#include <QFile>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextCodec>
#include <QDir> // позволяет работать с директориями


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    editor = new EditVisual(ui->textEdit);
    file = new FileEdit();
    ui->actionOpenFile->setIcon(QIcon(":/Icon/icons/open.png"));
    ui->actionSaveFile->setIcon(QIcon(":/Icon/icons/save.png"));
    ui->actionFileDirectory->setIcon(QIcon(":/Icon/icons/file.png"));
    connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionFileDirectory, &QAction::triggered, this, &MainWindow::actionFileDirectory);
    connect(ui->actionSaveFile, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::Copy);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::Paste);
    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::Cut);
    connect(ui->actionSetTextSize, &QAction::triggered, this, &MainWindow::setTextSize);
    connect(ui->actionSetTextColor, &QAction::triggered, this, &MainWindow::setTextColor);
    connect(ui->actionSetTextFont, &QAction::triggered, this, &MainWindow::setTextFont);
    connect(ui->actionSetTextCodec, &QAction::triggered, this, &MainWindow::setTextCodec);
    connect(ui->actionSetTextBackgroundColor, &QAction::triggered, this, &MainWindow::setTextBackgroundColor);
    connect(ui->actionSetBackgroundColor, &QAction::triggered, this, &MainWindow::setBackgroundColor);
    ui->statusBar->showMessage("OK");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editor;
    delete file;
}

void MainWindow::actionFileDirectory()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(fileDirectory(QString)));

}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, ("Open file"));
    if(filePath!="")
    {
        QString text = file->openFile(filePath);
        ui->textEdit->setPlainText(text);
        ui->statusBar->showMessage("Read to file: " + filePath);
    }
}

void MainWindow::saveFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, ("Save file"));
    if(filePath!="")
    {
        QString text = ui->textEdit->toPlainText();
        file->saveFile(filePath, text);
        ui->statusBar->showMessage("Write to file: " + filePath);
    }
}

void MainWindow::fileDirectory(const QString &filePath)
{
    QDir mDir(filePath);
    QString buffer;

    for (QFileInfo temp : mDir.entryInfoList()){ // выдает информацию о директориях
        buffer += temp.absoluteFilePath() + '\n';
    }

    ui->textEdit->setText(buffer);
    ui->statusBar->showMessage("Directory information loaded: " + filePath);
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
    editor->changeTextSize(QInputDialog::getInt(this, ("Font size"), nullptr, 12, 1));
}

void MainWindow::setTextColor()
{
    editor->changeTextColor(QColorDialog::getColor(editor->textColor, this));
}

void MainWindow::setTextFont()
{
    QStringList styles;
    styles<<("TimesNewRoman")<<("Calibri")<<("Impact");
    const QString textStyle = QInputDialog::getItem(this, ("Set the font type"), ("Font types"), styles, 0, false);
    editor->changeTextFont(textStyle);
}

void MainWindow::setTextBackgroundColor()
{
    editor->changeTextBackgroundColor(QColorDialog::getColor(editor->textBgColor, this));
}

void MainWindow::setBackgroundColor()
{
    editor->changeBackgroundColor(QColorDialog::getColor(editor->bgColor, this));
}

void MainWindow::setTextCodec()
{
    QStringList Codec;
    Codec<<("Win-1251")<<("UTF-8")<<("UTF-16")<<("UTF-32");
    QString fileCodec = QInputDialog::getItem(this, ("Select the codec: "), ("Encoding format"), Codec, 0, false);
    QTextCodec *textCodec = QTextCodec::codecForName(fileCodec.toStdString().c_str());
    QString text = ui->textEdit->toPlainText();
    QTextStream fstream(&text);
    fstream.setCodec(textCodec);
    ui->textEdit->setPlainText(text);
}

#include "file.h"
#include "ui_file.h"
#include <QPushButton>

File::File(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(okClicked())); // подключаем сигнал к кнопке OK
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close())); // подключаем сигнал к кнопке отмена
}

void File::okClicked(){ // указываем путь к файлу
    emit filePath(ui->lineEdit->text()); // генерируем сигнал
    close();
}

File::~File()
{
    delete ui;
}

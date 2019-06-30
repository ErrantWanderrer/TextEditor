#include "edit.h"
#include <QPalette>

EditVisual::EditVisual(QTextEdit *text)
{
   editor = text;
   textSize = 12;
   bgColor = Qt::white;
   textColor = Qt::black;
}

void EditVisual::changeTextSize(int size)
{
   this->textSize = size;
   editor->setFontPointSize(this->textSize);
}

void EditVisual::changeTextColor(const QColor color)
{
   this->textColor=color;
   editor->setTextColor(this->textColor);
}

void EditVisual::changeTextFont(const QString type)
{
   this->textStyle = type;
   editor->setFontFamily(this->textStyle);
}

void EditVisual::changeTextBackgroundColor(const QColor txtBgColor)
{
   this->textBgColor = txtBgColor;
   editor->setTextBackgroundColor(this->textBgColor);
}

void EditVisual::changeBackgroundColor(const QColor bgColor)
{
   QPalette color = editor->palette();
   color.setColor(QPalette::Base, bgColor);
   editor->setPalette(color);
}

EditVisual::~EditVisual()
{
    delete editor;
}

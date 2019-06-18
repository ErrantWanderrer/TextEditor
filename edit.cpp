#include "edit.h"
#include <QPalette>
#define DEFAULT_SIZE 12
#define DEFAULT_TEXT_COLOR black
#define DEFAULT_BG_COLOR white


EditVisual::EditVisual(QTextEdit *text)
{
   editor = text;
   textSize = DEFAULT_SIZE;
   bgColor = Qt::DEFAULT_BG_COLOR;
   textColor = Qt::DEFAULT_TEXT_COLOR;
}


void EditVisual::changeTextSize(int text_size)
{
   this->textSize = text_size;
   editor->setFontPointSize(this->textSize);
}

void EditVisual::changeTextColor(const QColor color)
{
   this->textColor=color;
   editor->setTextColor(this->textColor);
}

void EditVisual::changeTextFont(const QString style)
{
   this->textStyle = style;
   editor->setFontFamily(this->textStyle);
}

void EditVisual::changeTextBackgroundColor(const QColor text_bg_color)
{
   this->textBgColor = text_bg_color;
   editor->setTextBackgroundColor(this->textBgColor);
}

void EditVisual::changeBackgroundColor(const QColor bg_color)
{
   QPalette col = editor->palette();
   col.setColor(QPalette::Base,bg_color);
   editor->setPalette(col);
}

EditVisual::~EditVisual()
{

}

#ifndef EDIT_H
#define EDIT_H

#include <QTextEdit>
#include <QColor>

class EditVisual
{
public:
    EditVisual(QTextEdit *text);

    int textSize;
    QColor textColor;
    QString textStyle;
    QColor textBgColor;
    QColor bgColor;
    void changeTextSize(int size);
    void changeTextColor(const QColor textColor);
    void changeTextFont(const QString textStyle);
    void changeTextBackgroundColor(const QColor);
    void changeBackgroundColor(const QColor bgColor);

    ~EditVisual();
private:
    QTextEdit *editor;

};

#endif // EDIT_H

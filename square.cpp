#include "square.h"

void Square::set_attributes(int rank, File file) {
    rank_ = rank;
    file_ = file;
    set_code();
}

void Square::set_code()
{
    char code[2];
    sprintf(code, "%c%d", 'A' + file_, rank_);
    code_.append(code);
}

void Square::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void Square::enterEvent(QEnterEvent *event)
{
    emit hovered();
}

void Square::highlight(const QString &color)
{
    QString style = "QLabel {background-color : ";
    style.append(color);
    style.append('}');
    setStyleSheet(style);
    qDebug() << "Clicked";
}

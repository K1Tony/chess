#include "square.h"

Square::Square(QWidget *parent) : QLabel(parent)
{
    background_change_notifier_ = background_color_.addNotifier([this] () {
        QString name = this->background_color().name();
        this->setStyleSheet("QLabel { background-color : " + name + " }");
    });
}

void Square::set_attributes(int rank, File file) {
    rank_ = rank;
    file_ = file;
    set_code();
}

MColor Square::background_color() const
{
    return background_color_.value();
}

void Square::set_background_color(const MColor &new_background_color)
{
    background_color_.setValue(new_background_color);
}

void Square::set_code()
{
    char code[2];
    sprintf(code, "%c%d", 'A' + file_, rank_);
    code_.append(code);
}

void Square::mousePressEvent([[maybe_unused]] QMouseEvent *event)
{
    emit clicked();
}

void Square::enterEvent([[maybe_unused]] QEnterEvent *event)
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

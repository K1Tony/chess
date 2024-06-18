#include "square.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>

Square::Square(QWidget *parent) : QLabel(parent)
{
    background_change_notifier_ = background_color_.addNotifier([this] () {
        QString name = this->background_color().name();
        this->setStyleSheet("QLabel { background-color : " + name + " }");
    });
    drag = new QDrag(parent);
    mime_data = new QMimeData;
    drag->setMimeData(mime_data);

    setAcceptDrops(true);
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

void Square::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;
    drag_start = event->pos();
    emit clicked();
}

void Square::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if ((event->pos() - drag_start).manhattanLength() < QApplication::startDragDistance())
        return;

    QPixmap pm = pixmap().scaled(size(), Qt::KeepAspectRatio);
    drag->setPixmap(pm);
    drag->exec();
}

void Square::enterEvent([[maybe_unused]] QEnterEvent *event)
{
    emit hovered();
}

void Square::dragEnterEvent(QDragEnterEvent *event)
{
    if (is_highlighted())
        event->acceptProposedAction();
}

void Square::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();
    emit clicked();
}

void Square::highlight(const QString &color)
{
    QString style = "QLabel {background-color : ";
    style.append(color);
    style.append('}');
    setStyleSheet(style);
    qDebug() << "Clicked";
}

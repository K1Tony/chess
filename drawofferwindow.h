#ifndef DRAWOFFERWINDOW_H
#define DRAWOFFERWINDOW_H

#include <QWidget>
#include <properties.h>
#include <QProperty>

namespace Ui {
class DrawOfferWindow;
}

class DrawOfferWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DrawOfferWindow(QWidget *parent = nullptr);
    ~DrawOfferWindow();

    [[nodiscard]] QProperty<bool> &action_taken() {return action_taken_;}

    void reset();

private:
    Ui::DrawOfferWindow *ui;

    QProperty<bool> action_taken_;
    DrawOffer offer_ = IGNORED;
};

#endif // DRAWOFFERWINDOW_H

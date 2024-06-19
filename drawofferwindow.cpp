#include "drawofferwindow.h"
#include "ui_drawofferwindow.h"

DrawOfferWindow::DrawOfferWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawOfferWindow)
{
    ui->setupUi(this);

    connect(ui->accept, &QPushButton::clicked, this, [this] () {
        this->action_taken_.setValue(true);
        this->offer_ = ACCEPTED;
    });

    connect(ui->decline, &QPushButton::clicked, this, [this] () {
        this->action_taken_.setValue(true);
        this->offer_ = DECLINED;
    });

    connect(ui->ignore, &QPushButton::clicked, this, [this] () {
        this->action_taken_.setValue(true);
        this->offer_ = IGNORED;
    });
}

DrawOfferWindow::~DrawOfferWindow()
{
    delete ui;
}

void DrawOfferWindow::reset()
{
    action_taken_.setValue(false);
    offer_ = IGNORED;
}

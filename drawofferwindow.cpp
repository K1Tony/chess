#include "drawofferwindow.h"
#include "ui_drawofferwindow.h"

DrawOfferWindow::DrawOfferWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawOfferWindow)
{
    ui->setupUi(this);

    connect(ui->accept, &QPushButton::clicked, this, [this] () {
        this->offer_ = ACCEPTED;
        this->action_taken_.setValue(true);
    });

    connect(ui->decline, &QPushButton::clicked, this, [this] () {
        this->offer_ = DECLINED;
        this->action_taken_.setValue(true);
    });

    connect(ui->ignore, &QPushButton::clicked, this, [this] () {
        this->offer_ = IGNORED;
        this->action_taken_.setValue(true);
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

void DrawOfferWindow::show_offer(PieceColor color)
{
    ui->proposal->setText(QString(color == WHITE ? "White" : "Black") + " has offered a draw.");
    show();
}

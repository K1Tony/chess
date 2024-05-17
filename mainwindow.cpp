#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qlabel.h>

void fill_chessboard(Chessboard &chessboard, Ui::MainWindow *ui);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Chessboard chessboard;
    for (int rank = 0; rank < 8; rank++) {
        for (int field = 0; field < 8; field++) {
            auto *label = new QLabel(ui->centralwidget);
            chessboard[rank][field].set_attributes(rank + 1, (Field) field, label);
            label->setText(chessboard[rank][field].code().c_str());
            ui->gridLayout->addWidget(label, 7 - rank, field);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void fill_chessboard(Chessboard &chessboard, Ui::MainWindow *ui) {
    for (int rank = 0; rank < 8; rank++) {
        for (int field = 0; field < 8; field++) {
            auto *label = new QLabel();
            ui->gridLayout->addWidget(label, 7 - rank, field);
            chessboard[rank][field] = Square(rank + 1, (Field) field, label);
        }
    }
}

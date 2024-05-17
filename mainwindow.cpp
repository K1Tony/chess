#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Chessboard chessboard;
    int playing_area = this->width() * 0.8;
    int square_length = playing_area / 8;
    for (int rank = 0; rank < 8; rank++) {
        for (int field = 0; field < 8; field++) {
            auto *label = new QLabel(ui->centralwidget);
            label->setAutoFillBackground(true);
            label->setMinimumSize(square_length, square_length);
            label->setMaximumSize(square_length, square_length);
            if ((rank + field) % 2 == 0) {
                label->setStyleSheet("QLabel {background-color : #B56F07}");
            } else {
                label->setStyleSheet("QLabel {background-color : #FFEED4}");
            }
            chessboard[rank][field].set_attributes(rank + 1, (Field) field, label);
            ui->gridLayout->addWidget(label, 7 - rank, field);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <piece.h>
#include <pawn.h>

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
        for (int file = 0; file < 8; file++) {
            auto *label = new QLabel(ui->centralwidget);
            label->setAutoFillBackground(true);
            label->setMinimumSize(square_length, square_length);
            label->setMaximumSize(square_length, square_length);
            if ((rank + file) % 2 == 0) {
                label->setStyleSheet("QLabel {background-color : #B56F07}");
            } else {
                label->setStyleSheet("QLabel {background-color : #FFEED4}");
            }
            chessboard[rank][file].set_attributes(rank + 1, (File) file, label);
            ui->gridLayout->addWidget(label, 7 - rank, file);
        }
    }
    setFixedSize(width(), square_length * 9);
    std::set<Position> white_positions, black_positions;
    std::vector< std::unique_ptr<Pawn> > white_pawns, black_pawns;
    white_pawns.reserve(8);
    black_pawns.reserve(8);

    for (int i = 0; i < 8; i++) {
        white_pawns.push_back(std::make_unique<Pawn>(Position(i, 2), WHITE));
        black_pawns.push_back(std::make_unique<Pawn>(Position(i, 7), BLACK));
        white_positions.insert(Position(i, 1));
        white_positions.insert(Position(i, 2));
        black_positions.insert(Position(i, 7));
        black_positions.insert(Position(i, 8));
    }

    for (std::unique_ptr<Pawn> &p : white_pawns) {
        QLabel *label = chessboard[p->position().rank_ - 1][p->position().file_].label();
        label->setText("WP");
    }
    for (std::unique_ptr<Pawn> &p : black_pawns) {
        chessboard[p->position().rank_ - 1][p->position().file_].label()->setText("BP");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <piece.h>
#include <pawn.h>
#include <king.h>
#include <queen.h>

#include <qlabel.h>
#include <iostream>

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
    auto white_king = std::make_unique<King>(Position(E, 1), WHITE),
        black_king = std::make_unique<King>(Position(E, 8), BLACK);
    white_pawns.reserve(8);
    black_pawns.reserve(8);

    auto white_queen = std::make_unique<Queen>(Position(A, 3), WHITE),
        black_queen = std::make_unique<Queen>(Position(D, 6), BLACK);
    black_positions.insert(black_queen->position());
    chessboard[white_queen->position().rank_ - 1][white_queen->position().file_].label()->setStyleSheet("QLabel {background-color : cyan}");

    for (int i = 0; i < 8; i++) {
        white_pawns.push_back(std::make_unique<Pawn>(Position(i, 2), WHITE));
        black_pawns.push_back(std::make_unique<Pawn>(Position(i, 7), BLACK));
        white_positions.insert(Position(i, 1));
        white_positions.insert(Position(i, 2));
        black_positions.insert(Position(i, 7));
        black_positions.insert(Position(i, 8));
    }

    auto v = white_queen->legal_moves(white_positions, black_positions);
    for (Position &p : v) {
        chessboard[p.rank_ - 1][p.file_].label()->setStyleSheet("QLabel {background-color : red}");
    }

    for (std::unique_ptr<Pawn> &p : white_pawns) {
        QLabel *label = chessboard[p->position().rank_ - 1][p->position().file_].label();
        label->setText("WP");
    }
    for (std::unique_ptr<Pawn> &p : black_pawns) {
        chessboard[p->position().rank_ - 1][p->position().file_].label()->setText("BP");
    }
    for (Position &p : white_king->legal_moves(white_positions, black_positions)) {
        chessboard[p.rank_ - 1][p.file_].label()->setStyleSheet("QLabel {background-color : red}");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

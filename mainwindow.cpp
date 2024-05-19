#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <piece.h>
#include <pawn.h>
#include <king.h>
#include <queen.h>
#include <rook.h>
#include <bishop.h>
#include <knight.h>

#include <qlabel.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int playing_area = this->width() * 0.8;
    int square_length = playing_area / 8;
    Chessboard chessboard(square_length, ui->centralwidget);

    // light square: #FFEED4
    // dark square: #B56F07

    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            ui->gridLayout->addWidget(chessboard[rank][file].get(), 7 - rank, file);
            // auto *label = new QLabel(ui->centralwidget);
            // label->setAutoFillBackground(true);
            // label->setMinimumSize(square_length, square_length);
            // label->setMaximumSize(square_length, square_length);
            // if ((rank + file) % 2 == 0) {
            //     label->setStyleSheet("QLabel {background-color : #B56F07}");
            // } else {
            //     label->setStyleSheet("QLabel {background-color : #FFEED4}");
            // }
            // chessboard[rank][file].set_attributes(rank + 1, (File) file, label);
            // ui->gridLayout->addWidget(label, 7 - rank, file);
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << (char)('A' + chessboard[i][j]->file()) << chessboard[i][j]->rank() <<
                chessboard[i][j]->width() << '\n';
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

    auto bishop = std::make_unique<Knight>(Position(F, 5), BLACK);
    for (int i = 0; i < 8; i++) {
        white_pawns.push_back(std::make_unique<Pawn>(Position(i, 2), WHITE));
        black_pawns.push_back(std::make_unique<Pawn>(Position(i, 7), BLACK));
        white_positions.insert(Position(i, 1));
        white_positions.insert(Position(i, 2));
        black_positions.insert(Position(i, 7));
        black_positions.insert(Position(i, 8));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
#include <QPair>

#include <QPushButton>
#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int playing_area = this->width() * 0.8;
    int square_length = playing_area / 8;

    // Chessboard init
    chessboard_.reset(new Chessboard(square_length, ui->gridLayout, ui->centralwidget));

    setFixedSize(width(), square_length * 9);

    for (int rank = 1; rank <= 8; rank++) {
        for (int file = 0; file < 8; file++) {
            connect(chessboard_->at(file, rank).get(), &Square::clicked, this, [this, file, rank] () {
                Position pos(file, rank);
                if (this->chessboard_->white_pieces()->count(pos) > 0) {

                    this->chessboard_->select_piece(pos, WHITE);

                } else if (this->chessboard_->black_pieces()->count(pos) > 0) {

                    this->chessboard_->select_piece(pos, BLACK);

                } else {

                    this->chessboard_->reset_move_highlights();

                }
            });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    // Adding pieces
    white_pieces_.reset(new std::map<Position, std::unique_ptr<Piece> >);
    black_pieces_.reset(new std::map<Position, std::unique_ptr<Piece> >);
    for (int i = 0; i < 8; i++) {
        Position white_pawn(i, 2), black_pawn(i, 7), white_piece(i, 1), black_piece(i, 8);
        white_pieces_->insert({white_pawn, std::make_unique<Pawn>(white_pawn, WHITE)});
        black_pieces_->insert({black_pawn, std::make_unique<Pawn>(black_pawn, BLACK)});
        if (i == A || i == H) {
            white_pieces_->insert({white_piece, std::make_unique<Rook>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Rook>(black_piece, BLACK)});
        } else if (i == B || i == G) {
            white_pieces_->insert({white_piece, std::make_unique<Knight>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Knight>(black_piece, BLACK)});
        } else if (i == C || i == F) {
            white_pieces_->insert({white_piece, std::make_unique<Bishop>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Bishop>(black_piece, BLACK)});
        } else if (i == D) {
            white_pieces_->insert({white_piece, std::make_unique<Queen>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Queen>(black_piece, BLACK)});
        } else {
            white_pieces_->insert({white_piece, std::make_unique<King>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<King>(black_piece, BLACK)});
        }
    }

    for (auto &pair : *white_pieces_) {
        (*chessboard_)[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }
    for (auto &pair : *black_pieces_) {
        (*chessboard_)[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

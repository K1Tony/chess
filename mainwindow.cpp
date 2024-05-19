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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int playing_area = this->width() * 0.8;
    int square_length = playing_area / 8;
    Chessboard chessboard(square_length, ui->gridLayout, ui->centralwidget);

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
    QPixmap white_pawn_pm(":/graphics/resources/white-pawn.png"),
        black_pawn_pm(":/graphics/resources/black-pawn.png"),
        white_knight_pm(":/graphics/resources/white-knight.png"),
        black_knight_pm(":/graphics/resources/black-knight.png"),
        white_bishop_pm(":/graphics/resources/white-bishop.png"),
        black_bishop_pm(":/graphics/resources/black-bishop.png"),
        white_rook_pm(":/graphics/resources/white-rook.png"),
        black_rook_pm(":/graphics/resources/black-rook.png"),
        white_queen_pm(":/graphics/resources/white-queen.png"),
        black_queen_pm(":/graphics/resources/black-queen.png"),
        white_king_pm(":/graphics/resources/white-king.png"),
        black_king_pm(":/graphics/resources/black-king.png");

    for (int i = 0; i < 8; i++) {
        white_pawns.push_back(std::make_unique<Pawn>(Position(i, 2), WHITE));
        black_pawns.push_back(std::make_unique<Pawn>(Position(i, 7), BLACK));
        chessboard[1][i]->setPixmap(white_pawn_pm);
        chessboard[6][i]->setPixmap(black_pawn_pm);
        white_positions.insert(Position(i, 1));
        white_positions.insert(Position(i, 2));
        black_positions.insert(Position(i, 7));
        black_positions.insert(Position(i, 8));
    }

    // Rooks
    chessboard[0][A]->setPixmap(white_rook_pm);
    chessboard[0][H]->setPixmap(white_rook_pm);
    chessboard[7][A]->setPixmap(black_rook_pm);
    chessboard[7][H]->setPixmap(black_rook_pm);

    // Bishops
    chessboard[0][C]->setPixmap(white_bishop_pm);
    chessboard[0][F]->setPixmap(white_bishop_pm);
    chessboard[7][C]->setPixmap(black_bishop_pm);
    chessboard[7][F]->setPixmap(black_bishop_pm);

    // Knights
    chessboard[0][B]->setPixmap(white_knight_pm);
    chessboard[0][G]->setPixmap(white_knight_pm);
    chessboard[7][B]->setPixmap(black_knight_pm);
    chessboard[7][G]->setPixmap(black_knight_pm);

    // Queens
    chessboard[0][D]->setPixmap(white_queen_pm);
    chessboard[7][D]->setPixmap(black_queen_pm);

    // Kings
    chessboard[0][E]->setPixmap(white_king_pm);
    chessboard[7][E]->setPixmap(black_king_pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "promotiondialog.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"

// PAWN 0, KNIGHT 1, BISHOP 2, ROOK 3, QUEEN 4, KING

PromotionDialog::PromotionDialog(QWidget *parent) {
    for (int i = 1; i <= 4; i++) {
        squares_.insert({(PieceTag) i, std::make_unique<Square>(parent)});
        squares_.at((PieceTag) i)->setAutoFillBackground(true);
        squares_.at((PieceTag) i)->setScaledContents(true);
    }
}

void PromotionDialog::init_promotions(const Position &promotion_square, std::shared_ptr<Piece> &pawn)
{
    pawn_ = pawn;

    PieceColor color;
    switch (promotion_square.rank_) {
    case 1:
        color = BLACK;
        break;
    case 8:
        color = WHITE;
        break;
    default:
        return;
    }
    pieces_.insert({QUEEN, std::make_shared<Queen>(promotion_square, color)});
    pieces_.insert({ROOK, std::make_shared<Rook>(promotion_square, color)});
    pieces_.insert({BISHOP, std::make_shared<Bishop>(promotion_square, color)});
    pieces_.insert({KNIGHT, std::make_shared<Knight>(promotion_square, color)});

    for (auto &pair : pieces_) {
        PieceTag tag = pair.first;
        squares_.at(tag)->setPixmap(*pair.second->pixmap());
        squares_.at(tag)->setStyleSheet("QLabel {background-color : cyan}");
    }
}

void PromotionDialog::list_promotions(const Position &promotion_square, QGridLayout *layout)
{
    int offset = 0;
    switch (promotion_square.rank_) {
    case 1:
        offset++;
        break;
    case 8:
        offset--;
        break;
    default:
        return;
    }
    int file = promotion_square.file_ + 1, rank = 10 - promotion_square.rank_;

    layout->addWidget(squares_.at(QUEEN).get(), rank + offset, file);
    layout->addWidget(squares_.at(ROOK).get(), rank + offset + offset, file);
    layout->addWidget(squares_.at(BISHOP).get(), rank + offset, file - 1);
    layout->addWidget(squares_.at(KNIGHT).get(), rank + offset, file + 1);
}

void PromotionDialog::collapse()
{
    pieces_.clear();
    QWidget *parent = squares_.at(QUEEN)->parentWidget();
    int square_size = squares_.at(QUEEN)->width();
    squares_.clear();
    for (int i = 1; i <= 4; i++) {
        squares_.insert({(PieceTag) i, std::make_unique<Square>(parent)});
        squares_.at((PieceTag) i)->setAutoFillBackground(true);
        squares_.at((PieceTag) i)->setScaledContents(true);
    }
    for (auto &pair : squares_) {
        pair.second->setMinimumSize(square_size, square_size);
        pair.second->setMaximumSize(square_size, square_size);
    }
}


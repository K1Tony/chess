#include "queen.h"

Queen::Queen(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-queen.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-queen.png"));
    tag_ = QUEEN;
    code_ = 'Q';
    value_ = 9;
}

void Queen::available_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
{
    if (color_ == WHITE) {
        fill_rook_moves(position_, white_positions, black_positions, legal_moves_);
        fill_diagonals(position_, white_positions, black_positions, legal_moves_);
    } else {
        fill_rook_moves(position_, black_positions, white_positions, legal_moves_);
        fill_diagonals(position_, black_positions, white_positions, legal_moves_);
    }
}

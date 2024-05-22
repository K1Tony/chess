#include "queen.h"

Queen::Queen(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-queen.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-queen.png"));
    tag_ = QUEEN;
}

std::vector<Position> Queen::legal_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
{
    std::vector<Position> result;
    result.reserve(28);
    if (color_ == WHITE) {
        fill_rook_moves(position_, white_positions, black_positions, result);
        fill_diagonals(position_, white_positions, black_positions, result);
    } else {
        fill_rook_moves(position_, black_positions, white_positions, result);
        fill_diagonals(position_, black_positions, white_positions, result);
    }

    return result;
}

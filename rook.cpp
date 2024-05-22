#include "rook.h"

Rook::Rook(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-rook.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-rook.png"));
    tag_ = ROOK;
}

std::vector<Position> Rook::legal_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
{
    std::vector<Position> result;
    result.reserve(14);
    if (color_ == WHITE) {
        fill_rook_moves(position_, white_positions, black_positions, result);
    } else {
        fill_rook_moves(position_, black_positions, white_positions, result);
    }
    return result;
}

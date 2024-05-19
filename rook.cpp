#include "rook.h"

Rook::Rook(Position position, PieceColor color)
{
    position_ = position;
    color_ = color;
}

std::vector<Position> Rook::legal_moves(const std::set<Position> &white_positions, const std::set<Position> &black_positions)
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

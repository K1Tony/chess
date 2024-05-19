#include "bishop.h"

Bishop::Bishop(Position position, PieceColor color)
{
    position_ = position;
    color_ = color;
}

std::vector<Position> Bishop::legal_moves(const std::set<Position> &white_positions, const std::set<Position> &black_positions)
{
    std::vector<Position> result;
    result.reserve(13);

    if (color_ == WHITE) {
        fill_diagonals(position_, white_positions, black_positions, result);
    } else {
        fill_diagonals(position_, black_positions, white_positions, result);
    }

    return result;
}

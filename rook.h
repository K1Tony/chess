#ifndef ROOK_H
#define ROOK_H

#include <piece.h>

class Rook : public Piece
{
public:
    Rook(Position position, PieceColor color);
    std::vector<Position> legal_moves(const std::set<Position> &white_positions, const std::set<Position> &black_positions);
};

#endif // ROOK_H

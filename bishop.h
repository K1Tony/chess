#ifndef BISHOP_H
#define BISHOP_H

#include <piece.h>

class Bishop : public Piece
{
public:
    Bishop(Position position, PieceColor color);

    std::vector<Position> legal_moves(const std::set<Position> &white_positions, const std::set<Position> &black_positions);
};

#endif // BISHOP_H

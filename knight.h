#ifndef KNIGHT_H
#define KNIGHT_H

#include <piece.h>

class Knight : public Piece
{
public:
    Knight(Position position, PieceColor color);

    std::vector<Position> legal_moves(const std::set<Position> &white_positions, const std::set<Position> &black_positions);
};

#endif // KNIGHT_H

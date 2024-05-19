#ifndef KING_H
#define KING_H

#include <piece.h>

class King : public Piece
{
public:
    King(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::set<Position> &white_positions,
        const std::set<Position> &black_positions) override;
};

#endif // KING_H

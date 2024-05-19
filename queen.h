#ifndef QUEEN_H
#define QUEEN_H

#include <piece.h>

class Queen : public Piece
{
public:
    Queen(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::set<Position> &white_positions,
        const std::set<Position> &black_positions) override;
};

#endif // QUEEN_H

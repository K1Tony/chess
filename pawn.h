#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(Position position, PieceColor color);

    std::vector<Position> legal_moves(const std::set<Position> &white_positions,
                                      const std::set<Position> &black_pieces) override;
};

#endif // PAWN_H

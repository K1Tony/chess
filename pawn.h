#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_pieces)
        override;
};

#endif // PAWN_H

#ifndef ROOK_H
#define ROOK_H

#include <piece.h>

class Rook : public Piece
{
public:
    Rook(Position position, PieceColor color);
    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
        override;
};

#endif // ROOK_H

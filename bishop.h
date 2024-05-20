#ifndef BISHOP_H
#define BISHOP_H

#include <piece.h>

class Bishop : public Piece
{
public:
    Bishop(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
        override;
};

#endif // BISHOP_H

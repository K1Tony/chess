#ifndef KNIGHT_H
#define KNIGHT_H

#include <piece.h>

class Knight : public Piece
{
public:
    Knight(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
        override;
};

#endif // KNIGHT_H

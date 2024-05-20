#ifndef KING_H
#define KING_H

#include <piece.h>

class King : public Piece
{
public:
    King(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
        override;
};

#endif // KING_H

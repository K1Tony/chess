#ifndef KNIGHT_H
#define KNIGHT_H

#include <piece.h>

class Knight : public Piece
{
public:
    Knight(Position position, PieceColor color);

    void available_moves(
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
        override;
};

#endif // KNIGHT_H

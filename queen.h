#ifndef QUEEN_H
#define QUEEN_H

#include <piece.h>

class Queen : public Piece
{
public:
    Queen(Position position, PieceColor color);

    void available_moves(
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
        override;
};

#endif // QUEEN_H

#ifndef QUEEN_H
#define QUEEN_H

#include <piece.h>

class Queen : public Piece
{
public:
    Queen(Position position, PieceColor color);

    std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
        override;
};

#endif // QUEEN_H

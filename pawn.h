#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(Position position, PieceColor color);

    void available_moves(
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_pieces)
        override;

    static bool check_en_passant(const LastMove &last_move,
                                 std::shared_ptr<Piece> &pawn);

};

#endif // PAWN_H

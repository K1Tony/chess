#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "properties.h"
#include <chessboard.h>
#include <set>

enum PieceColor{
    WHITE, BLACK
};

class Piece
{
public:
    Piece() = default;

    Piece(Position position, PieceColor color);

    [[nodiscard]] Position position() const {return position_;}

    [[nodiscard]] int color() const {return color_;}

    void set_color(int color) {color_ = (PieceColor) color;}

    void set_color(PieceColor color) {color_ = color;}

    virtual ~Piece() = default;

    virtual std::vector<Position> legal_moves(
        const std::set<Position> &white_positions,
        const std::set<Position> &black_positions) = 0;


protected:
    Position position_;

    PieceColor color_;
};

#endif // PIECE_H

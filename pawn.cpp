#include "pawn.h"
#include "iostream"
#include "map"

Pawn::Pawn(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-pawn.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-pawn.png"));

}

std::vector<Position> Pawn::legal_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
{
    std::vector<Position> result;
    result.reserve(4);
    File file = position().file_;
    int rank = position().rank_;

    if (color_ == WHITE) {
        Position up(file, rank + 1);
        Position left_up(file - 1, rank + 1);
        Position right_up(file + 1, rank + 1);
        if (white_positions->count(up) == 0 && black_positions->count(up) == 0) {
            result.push_back(up);
            Position up2(file, rank + 2);
            if (rank == 2 && white_positions->count(up2) == 0 && black_positions->count(up2) == 0) {
                result.push_back(up2);
            }
        }
        if (black_positions->count(left_up) > 0) {
            result.push_back(left_up);
        }
        if (black_positions->count(right_up) > 0) {
            result.push_back(right_up);
        }
    } else {
        Position down(file, rank - 1);
        Position down_left(file - 1, rank - 1);
        Position down_right(file + 1, rank - 1);
        if (white_positions->count(down) == 0 && black_positions->count(down) == 0) {
            result.push_back(down);
            Position down2(file, rank - 2);
            if (rank == 7 && white_positions->count(down2) == 0 && black_positions->count(down2) == 0) {
                result.push_back(down2);
            }
        }
        if (white_positions->count(down_left) > 0) {
            result.push_back(down_left);
        }
        if (white_positions->count(down_right) > 0) {
            result.push_back(down_right);
        }
    }

    return result;
}



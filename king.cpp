#include "king.h"

King::King(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-king.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-king.png"));
}

std::vector<Position> King::legal_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions) {
    File f = position().file_;
    int r = position().rank_;

    std::vector<Position> result;
    result.reserve(8);

    Position possibilities[] = {Position(f, r + 1), Position(f + 1, r + 1), Position(f + 1, r), Position(f + 1, r - 1),
                                Position(f, r - 1), Position(f - 1, r - 1), Position(f - 1, r), Position(f - 1, r + 1)};

    for (Position &p : possibilities) {
        if (p.in_bounds()) {
            if (color_ == WHITE && white_positions->count(p) == 0) {
                result.push_back(p);
            } else if (color_ == BLACK && black_positions->count(p) == 0) {
                result.push_back(p);
            }
        }
    }

    return result;
}

#include "knight.h"


Knight::Knight(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-knight.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-knight.png"));
}

std::vector<Position> Knight::legal_moves(
    const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::unique_ptr<Piece> > > &black_positions)
{
    std::vector<Position> result;
    result.reserve(8);
    File file = position_.file_;
    int rank = position_.rank_;
    Position moves[] = {Position(file + 1, rank + 2), Position(file + 2, rank + 1),
                         Position(file + 2, rank - 1), Position(file + 1, rank - 2),
                         Position(file - 1, rank - 2), Position(file - 2, rank - 1),
                        Position(file - 2, rank + 1), Position(file - 1, rank + 2)};

    for (Position &p : moves) {
        if (!p.in_bounds()) continue;
        if (color_ == WHITE && white_positions->count(p) == 0) {
            result.push_back(p);
        } else if (color_ == BLACK && black_positions->count(p) == 0) {
            result.push_back(p);
        }
    }

    return result;
}

#include "bishop.h"

Bishop::Bishop(Position position, PieceColor color) : Piece(position, color)
{
    if (color == WHITE)
        pixmap_.reset(new QPixmap(":/graphics/resources/white-bishop.png"));
    else
        pixmap_.reset(new QPixmap(":/graphics/resources/black-bishop.png"));
}

std::vector<Position> Bishop::legal_moves(
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions)
{
    std::vector<Position> result;
    result.reserve(13);

    if (color_ == WHITE) {
        fill_diagonals(position_, white_positions, black_positions, result);
    } else {
        fill_diagonals(position_, black_positions, white_positions, result);
    }

    return result;
}

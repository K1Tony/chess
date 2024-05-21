#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "properties.h"
#include <map>
#include <QPixmap>

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

    [[nodiscard]] std::unique_ptr<QPixmap> &pixmap() {return pixmap_;}

    void set_color(int color) {color_ = (PieceColor) color;}

    void set_color(PieceColor color) {color_ = color;}

    virtual ~Piece() = default;

    virtual std::vector<Position> legal_moves(
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions) = 0;


protected:
    Position position_;

    PieceColor color_;

    std::unique_ptr<QPixmap> pixmap_;
};

void fill_rook_moves(const Position &position,
                     const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsA,
                     const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsB,
                     std::vector<Position> &result);

void fill_diagonals(const Position &position,
                    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsA,
                    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsB,
                    std::vector<Position> &result);

#endif // PIECE_H

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "properties.h"
#include <map>
#include <QPixmap>

class Piece
{
public:
    Piece() = default;

    Piece(Position position, PieceColor color);

    [[nodiscard]] Position position() const {return position_;}

    [[nodiscard]] int color() const {return color_;}

    [[nodiscard]] std::unique_ptr<QPixmap> &pixmap() {return pixmap_;}

    [[nodiscard]] PieceTag tag() const {return tag_;}

    [[nodiscard]] bool moved() const {return moved_;}

    [[nodiscard]] std::vector<Position> legal_moves() const {return legal_moves_;}

    [[nodiscard]] std::vector<Position> &__legal_moves() {return legal_moves_;}

    [[nodiscard]] QChar code() const {return code_;}

    void __set_legal_moves(std::vector<Position> &moves) {legal_moves_ = moves;}

    void set_color(int color) {color_ = (PieceColor) color;}

    void set_color(PieceColor color) {color_ = color;}

    void set_position(const Position position) {position_ = position;}

    void set_moved() {moved_ = true;}

    virtual ~Piece() = default;

    virtual void available_moves(
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_positions,
        const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_positions) = 0;


protected:
    Position position_;

    PieceColor color_;

    std::unique_ptr<QPixmap> pixmap_;

    PieceTag tag_;

    bool moved_ = false;

    std::vector<Position> legal_moves_;

    QChar code_;

};

void fill_rook_moves(const Position &position,
                     const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsA,
                     const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsB,
                     std::vector<Position> &result);

void fill_diagonals(const Position &position,
                    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsA,
                    const std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &positionsB,
                    std::vector<Position> &result);

typedef struct LastMove{
    Position old_;
    Position new_;
    std::shared_ptr<Piece> moved_piece_;
} LastMove;

#endif // PIECE_H

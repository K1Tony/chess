#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <Square.h>
#include <QGridLayout>
#include <pawn.h>
#include <knight.h>
#include <bishop.h>
#include <rook.h>
#include <queen.h>
#include <king.h>


class Chessboard
{

public:
    Chessboard(int suqare_size, QGridLayout *layout, QWidget *parent = Q_NULLPTR);

    std::array<std::unique_ptr<Square>, 8> &operator[](int rank);

    std::unique_ptr<Square> &at(int file, int rank);

    std::unique_ptr<Square> &at(File file, int rank);

    std::unique_ptr<Square> &at(const Position &position);

    [[nodiscard]] std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &white_pieces() {return white_pieces_;}

    [[nodiscard]] std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > &black_pieces() {return black_pieces_;}

    [[nodiscard]] std::shared_ptr<Piece> &selected_piece() {return selected_piece_;}

    [[nodiscard]] std::vector<Position> &highlighted_moves() {return highlighted_moves_;}

    [[nodiscard]] PieceColor turn() {return turn_;}

    [[nodiscard]] LastMove last_move() const {return last_move_;}

    void reset_move_highlights();

    void select_piece(Position &position, PieceColor color);

    void move(std::shared_ptr<Piece> &piece, const Position destination);

    void move(const Position destination);

// members
private:
    std::array< std::array< std::unique_ptr<Square>, 8>, 8 > squares_;

    std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > white_pieces_, black_pieces_;

    PieceColor turn_ = WHITE;

    std::shared_ptr<Piece> selected_piece_;

    std::vector<Position> highlighted_moves_;

    QString base_light_color_ = "QLabel {background-color : #FFEED4}",
        base_dark_color_ = "QLabel {background-color : #B56F07}";

    QPixmap blank_ = QPixmap();

    LastMove last_move_;

    std::map<SpecialMoveTag, Position> special_moves_;
};

#endif // CHESSBOARD_H

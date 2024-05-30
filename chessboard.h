#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "movedialog.h"

#include <Square.h>
#include <QGridLayout>
#include <pawn.h>
#include <knight.h>
#include <bishop.h>
#include <rook.h>
#include <queen.h>
#include <king.h>

#include <promotiondialog.h>


class Chessboard
{

private:
    void check_castling(SpecialMoveTag castling_style, PieceColor color);

    void castle(SpecialMoveTag castling_style, PieceColor color);

    bool is_attacked(const Position &position);

    void list_promotions();

    void promote(PieceTag tag);

// public methods
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

    void __set_turn(PieceColor __turn) {turn_ = __turn;}

    [[nodiscard]] LastMove last_move() const {return last_move_;}

    [[nodiscard]] QPixmap &blank() {return blank_;}

    [[nodiscard]] std::map<SpecialMoveTag, Position> &special_moves() {return special_moves_;}

    [[nodiscard]] std::unique_ptr<PromotionDialog> &promotion_dialog() {return promotion_dialog_;}

    void reset_move_highlights();

    void select_piece(Position &position, PieceColor color);

    void move(std::shared_ptr<Piece> &piece, const Position destination);

    void move(const Position destination);

    std::shared_ptr<Piece> piece_at(const Position &position);

    bool check_promotion();

    void set_available_moves();

    void set_available_moves(PieceColor color);

    bool scan_checks();

    void trim_legal_moves();

    void register_move(Move &move);

// private members
private:
    std::unique_ptr<QWidget> parent_;

    std::unique_ptr<QGridLayout> layout_;

    std::array< std::array< std::unique_ptr<Square>, 8>, 8 > squares_;

    std::unique_ptr< std::map<Position, std::shared_ptr<Piece> > > white_pieces_, black_pieces_;

    std::shared_ptr<Piece> white_king_, black_king_;

    std::unique_ptr<PromotionDialog> promotion_dialog_;

    PieceColor turn_ = WHITE;

    std::shared_ptr<Piece> selected_piece_;

    std::vector<Position> highlighted_moves_;

    QString base_light_color_ = "QLabel {background-color : #FFEED4}",
        base_dark_color_ = "QLabel {background-color : #B56F07}";

    QPixmap blank_ = QPixmap();

    LastMove last_move_;

    std::map<SpecialMoveTag, Position> special_moves_;

    int legal_moves_count_;
};

#endif // CHESSBOARD_H

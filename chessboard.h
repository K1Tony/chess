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

#include <colordialog.h>

#include <FEN.h>
#include <promotiondialog.h>


class Chessboard
{

private:
    using piece_map = std::map< Position, std::shared_ptr<Piece> >;


    void check_castling(SpecialMoveTag castling_style, PieceColor color);

    void castle(SpecialMoveTag castling_style, PieceColor color);

    bool is_attacked(const Position &position);

    void list_promotions();

    void promote(PieceTag tag);

    void reset_square_colors();

    void set_pieces_on_squares();

// public methods
public:
    Chessboard(int suqare_size, QGridLayout *layout, QWidget *parent = Q_NULLPTR);

    std::array<std::unique_ptr<Square>, 8> &operator[](int rank);

    std::unique_ptr<Square> &at(int file, int rank);

    std::unique_ptr<Square> &at(File file, int rank);

    std::unique_ptr<Square> &at(const Position &position);

    [[nodiscard]] std::unique_ptr<piece_map> &white_pieces() {return white_pieces_;}

    [[nodiscard]] std::unique_ptr<piece_map> &black_pieces() {return black_pieces_;}

    [[nodiscard]] std::shared_ptr<Piece> &selected_piece() {return selected_piece_;}

    [[nodiscard]] std::vector<Position> &highlighted_moves() {return highlighted_moves_;}

    [[nodiscard]] PieceColor turn() {return turn_;}

    void __set_turn(PieceColor __turn) {turn_ = __turn;}

    [[nodiscard]] Move last_move() const {return last_move_;}

    [[nodiscard]] QPixmap &blank() {return blank_;}

    [[nodiscard]] std::map<SpecialMoveTag, Position> &special_moves() {return special_moves_;}

    [[nodiscard]] std::unique_ptr<PromotionDialog> &promotion_dialog() {return promotion_dialog_;}

    [[nodiscard]] bool flips_after_move() const {return flip_after_move_;}

    void set_move_flip(bool flip) {flip_after_move_ = flip;}

    std::vector< std::shared_ptr<Piece> > get_attackers(File file, int rank, PieceColor color);

    std::vector< std::shared_ptr<Piece> > get_attackers(const Position &position, PieceColor color);

    std::vector< std::shared_ptr<Piece> > get_attackers(int file, int rank, PieceColor color);

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

    bool check_for_mate();

    bool check_for_draw();

    void set_board();

    void flip_chessboard();

    int moves_count() const;

    std::shared_ptr<QProperty<bool> > mate_property() const;

    std::shared_ptr<QProperty<bool> > draw_property() const;

    ChessboardColorDialog &color_dialog() {return color_dialog_;}

    std::shared_ptr<MoveDialog> move_dialog() {return move_dialog_;}

    void undo();

    void readFEN(const QString &fen);

    void readFEN(const FEN &fen);

    FEN writeFEN();

    void set_basic_board();

    void register_position();


private:
    std::unique_ptr<QWidget> parent_;

    std::unique_ptr<QGridLayout> layout_;

    std::array< std::array< std::unique_ptr<Square>, 8>, 8 > squares_;

    std::unique_ptr<piece_map> white_pieces_ =
        std::make_unique<piece_map>(),
        black_pieces_ = std::make_unique<piece_map>();

    std::shared_ptr<Piece> white_king_, black_king_;

    std::unique_ptr<PromotionDialog> promotion_dialog_;

    PieceColor turn_ = WHITE;

    std::shared_ptr<Piece> selected_piece_;

    std::vector<Position> highlighted_moves_;

    QPixmap blank_ = QPixmap();

    Move last_move_;

    std::shared_ptr<MoveDialog> move_dialog_;

    std::map<SpecialMoveTag, Position> special_moves_;

    int legal_moves_count_;

    int moves_count_ = 0;

    ChessboardColorDialog color_dialog_;

    QPropertyNotifier light_square_change_, dark_square_change_, legal_move_change_, last_move_change_, promotion_change_;

    QPropertyNotifier color_change_notifier_;

    std::shared_ptr< QProperty<bool> > mate_property_;

    std::shared_ptr< QProperty<bool> > draw_property_;

    bool white_up = true;

    int max_undos_ = 5;

    bool flip_after_move_ = true;
};

#endif // CHESSBOARD_H

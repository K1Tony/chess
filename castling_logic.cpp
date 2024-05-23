#include "castling_logic.h"


void castle(Chessboard *chessboard, SpecialMoveTag castling_style, PieceColor color)
{
    Position rook_initial(castling_style == LONG_CASTLING ? A : H, color == WHITE ? 1 : 8),
        rook_destination(castling_style == LONG_CASTLING ? C : F, color == WHITE ? 1 : 8);
    chessboard->at(rook_destination)->setPixmap(chessboard->at(rook_initial)->pixmap());
    chessboard->at(rook_initial)->setPixmap(chessboard->blank());
    std::unique_ptr< std::map< Position, std::shared_ptr<Piece> > > &pieces =
        color == WHITE ? chessboard->white_pieces() : chessboard->black_pieces();
    pieces->insert({rook_destination, pieces->at(rook_initial)});
    pieces->erase(rook_initial);
    pieces->at(rook_destination)->set_position(rook_destination);
}

void check_castling(Chessboard *chessboard, SpecialMoveTag castling_style, PieceColor color)
{
    if (chessboard->selected_piece()->tag() != KING || chessboard->selected_piece()->moved()) return;
    int rank = color == WHITE ? 1 : 8;
    File file = castling_style == LONG_CASTLING ? C : G;
    Position rook_pos(castling_style == LONG_CASTLING ? A : H, rank);
    if (chessboard->piece_at(rook_pos)->moved()) return;
    int begin_iteration = castling_style == LONG_CASTLING ? B : F;
    int end_iteration = castling_style == LONG_CASTLING ? E : H;

    for (; begin_iteration < end_iteration; begin_iteration++) {
        Position p(begin_iteration, rank);
        if (chessboard->piece_at(p).get() != nullptr) {
            return;
        }
    }
    chessboard->highlighted_moves().push_back(Position(file, rank));
    chessboard->special_moves().insert({castling_style, Position(file, rank)});
}

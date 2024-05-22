#ifndef CASTLING_LOGIC_H
#define CASTLING_LOGIC_H

#include "chessboard.h"

void castle(Chessboard *chessboard, SpecialMoveTag castling_style, PieceColor color);

void check_castling(Chessboard *chessboard, SpecialMoveTag castling_style, PieceColor color);

#endif // CASTLING_LOGIC_H

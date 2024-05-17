#include "chessboard.h"

Chessboard::Chessboard()
{

}

std::array<Square, 8>& Chessboard::operator[](int rank)
{
    return squares_[rank];
}

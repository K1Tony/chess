#include "piece.h"

Piece::Piece() {}

Piece &Piece::operator=(Piece &&piece) noexcept
{
    return *this;
}

Piece &Piece::operator=(const Piece& piece) {
    return *this;
}



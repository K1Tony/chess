#ifndef PIECE_H
#define PIECE_H

class Piece
{
public:
    Piece();

    Piece &operator=(const Piece &piece);

    Piece &operator=(Piece &&piece) noexcept;
};

#endif // PIECE_H

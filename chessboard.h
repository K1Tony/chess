#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <Square.h>
#include <array>


class Chessboard
{
public:
    Chessboard();

    std::array<Square, 8>& operator[](int rank);

private:
    std::array<std::array<Square, 8>, 8> squares_;
};

#endif // CHESSBOARD_H

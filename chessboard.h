#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <Square.h>
#include <QGridLayout>


class Chessboard
{
public:
    Chessboard(int suqare_size, QGridLayout *layout, QWidget *parent = Q_NULLPTR);

    std::array<std::unique_ptr<Square>, 8> &operator[](int rank);


private:
    std::array< std::array< std::unique_ptr<Square>, 8>, 8 > squares_;

};

#endif // CHESSBOARD_H

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <Square.h>


class Chessboard
{
public:
    Chessboard(int suqare_size, QWidget *parent = Q_NULLPTR);

    std::vector< std::unique_ptr<Square> >& operator[](int rank);


private:
    std::vector< std::vector< std::unique_ptr<Square> > > squares_;

};

#endif // CHESSBOARD_H

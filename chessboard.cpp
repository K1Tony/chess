#include "chessboard.h"

Chessboard::Chessboard(int square_size, QWidget *parent)
{
    squares_.reserve(8);
    for (int i = 0; i < 8; i++) {
        squares_.push_back(std::vector< std::unique_ptr<Square> >());
        squares_[i].reserve(8);
        for (int j = 0; j < 8; j++) {
            squares_[i].push_back(std::make_unique<Square> (parent));
            squares_[i].back()->set_attributes(i + 1, (File) j);
            squares_[i].back()->setAutoFillBackground(true);
            squares_[i].back()->setMinimumSize(square_size, square_size);
            squares_[i].back()->setMaximumSize(square_size, square_size);
            if ((i + j) % 2 == 0) {
                squares_[i].back()->setStyleSheet("QLabel {background-color : #B56F07}");
            } else {
                squares_[i].back()->setStyleSheet("QLabel {background-color : #FFEED4}");
            }
        }
    }
}

std::vector< std::unique_ptr<Square> >& Chessboard::operator[](int rank)
{
    return squares_[rank];
}

#include "chessboard.h"

Chessboard::Chessboard(int square_size, QGridLayout *layout, QWidget *parent)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto *square = new Square(parent);
            square->set_attributes(i + 1, (File) j);
            square->setAutoFillBackground(true);
            square->setScaledContents(true);
            square->setMinimumSize(square_size, square_size);
            square->setMaximumSize(square_size, square_size);
            if ((i + j) % 2 == 0) {
                square->setStyleSheet("QLabel {background-color : #B56F07}");
            } else {
                square->setStyleSheet("QLabel {background-color : #FFEED4}");
            }
            squares_[i][j].reset(square);
            layout->addWidget(square, 7 - i, j);
        }
    }
}

std::array< std::unique_ptr<Square>, 8 >& Chessboard::operator[](int rank)
{
    return squares_[rank];
}

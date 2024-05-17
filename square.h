#ifndef SQUARE_H
#define SQUARE_H

#include "properties.h"

#include <Piece.h>
#include <qlabel.h>
#include <algorithm>
#include "iostream"

class Square
{
public:
    Square();

    Square(int rank, int field, QLabel *label);

    Square(int rank, Field field, QLabel *label);

    void set_attributes(int rank, Field field, QLabel *label);

    [[nodiscard]] int rank() const {return rank_;}

    [[nodiscard]] Field field() const {return field_;}

    [[nodiscard]] std::string code() {return code_;}

    [[nodiscard]] Piece &piece() {return piece_;}

    [[nodiscard]] QLabel *label() {return label_;}

    void setPiece(const Piece &piece) {piece_ = piece;}

private:
    int rank_;
    Field field_;

    std::string code_;

    Piece piece_;

    QLabel *label_;

    void set_code();
};

#endif // SQUARE_H

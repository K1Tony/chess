#include "square.h"


Square::Square() {}

Square::Square(int rank, int field, QLabel *label) :
    rank_(rank),
    field_((Field) field),
    label_(label)
{
    set_code();
}

Square::Square(int rank, Field field, QLabel *label) :
    rank_(rank),
    field_(field),
    label_(label)
{
    set_code();
}

void Square::set_attributes(int rank, Field field, QLabel *label) {
    rank_ = rank;
    field_ = field;
    label_ = label;
    set_code();
}

void Square::set_code()
{
    char code[2];
    sprintf(code, "%c%d", 'A' + field_, rank_);
    code_.append(code);
}

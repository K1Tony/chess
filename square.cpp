#include "square.h"


Square::Square() {}

Square::Square(int rank, int file, QLabel *label) :
    rank_(rank),
    file_((File) file),
    label_(label)
{
    set_code();
}

Square::Square(int rank, File file, QLabel *label) :
    rank_(rank),
    file_(file),
    label_(label)
{
    set_code();
}

void Square::set_attributes(int rank, File file, QLabel *label) {
    rank_ = rank;
    file_ = file;
    label_ = label;
    set_code();
}

void Square::set_code()
{
    char code[2];
    sprintf(code, "%c%d", 'A' + file_, rank_);
    code_.append(code);
}

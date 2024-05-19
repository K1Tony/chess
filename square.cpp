#include "square.h"

void Square::set_attributes(int rank, File file) {
    rank_ = rank;
    file_ = file;
    set_code();
}

void Square::set_code()
{
    char code[2];
    sprintf(code, "%c%d", 'A' + file_, rank_);
    code_.append(code);
}

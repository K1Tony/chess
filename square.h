#ifndef SQUARE_H
#define SQUARE_H

#include "properties.h"

#include <qlabel.h>

class Square
{
public:
    Square();

    Square(int rank, int file, QLabel *label);

    Square(int rank, File file, QLabel *label);

    void set_attributes(int rank, File field, QLabel *label);

    [[nodiscard]] int rank() const {return rank_;}

    [[nodiscard]] File file() const {return file_;}

    [[nodiscard]] std::string code() {return code_;}

    [[nodiscard]] QLabel *label() {return label_;}

private:
    std::string code_;
    int rank_;
    File file_;
    QLabel *label_;
    void set_code();

signals:

    void clicked();
};

#endif // SQUARE_H

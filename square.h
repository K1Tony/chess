#ifndef SQUARE_H
#define SQUARE_H

#include "properties.h"

#include <qlabel.h>

class Square : public QLabel
{
    Q_OBJECT
public:
    Square(QWidget *parent = Q_NULLPTR) : QLabel(parent) {}

    void set_attributes(int rank, File field);

    [[nodiscard]] int rank() const {return rank_;}

    [[nodiscard]] File file() const {return file_;}

    [[nodiscard]] std::string code() {return code_;}

private:
    std::string code_;
    int rank_;
    File file_;
    void set_code();

signals:

    void clicked();

protected:

    void mousePressEvent(QMouseEvent *event);

public slots:

    void highlight(const QString &color);
};

#endif // SQUARE_H

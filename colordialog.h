#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QColor>


class MColor : public QColor {
public:
    MColor(int red, int green, int blue, int alpha = 255) : QColor(red, green, blue, alpha) {}

    MColor(const QColor &color) : QColor(color) {}

    MColor(QColor &&color) noexcept : QColor(color) {}

    MColor &operator+(const QColor &other);
};

class ChessboardColorDialog
{
public:
    ChessboardColorDialog();

    MColor light_square() const;
    void setLight_square(const MColor &newLight_square);

    MColor dark_square() const;
    void setDark_square(const MColor &newDark_square);

    MColor legal_move() const;
    void setLegal_move(const MColor &newLegal_move);

    MColor last_move() const;
    void setLast_move(const MColor &newLast_move);

    MColor promotion() const;
    void setPromotion(const MColor &newPromotion);

private:
    MColor light_square_, dark_square_, legal_move_, last_move_, promotion_;

};

#endif // COLORDIALOG_H

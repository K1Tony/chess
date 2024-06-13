#include "colordialog.h"

MColor &MColor::operator+(const QColor &other)
{
    if (&other == this) return *this;
    this->setRed((red() + 2 * other.red()) / 3);
    this->setGreen((green() + 2 * other.green()) / 3);
    this->setBlue((blue() + 2 * other.blue()) / 3);
    this->setAlpha((alpha() + 2 * other.alpha()) / 3);
    return *this;
}

ChessboardColorDialog::ChessboardColorDialog()
{
    light_square_.setValue(MColor(QColor(0xFFEED4)));
    dark_square_.setValue(MColor(QColor(0xB56F07)));
    legal_move_.setValue(MColor(255, 0, 0));
    last_move_.setValue(MColor(255, 255, 0));
    promotion_.setValue(MColor(0, 255, 255));
}

MColor ChessboardColorDialog::light_square() const
{
    return light_square_;
}

void ChessboardColorDialog::setLight_square(const MColor &newLight_square)
{
    light_square_.setValue(newLight_square);
}

MColor ChessboardColorDialog::dark_square() const
{
    return dark_square_;
}

void ChessboardColorDialog::setDark_square(const MColor &newDark_square)
{
    dark_square_.setValue(newDark_square);
}

MColor ChessboardColorDialog::legal_move() const
{
    return legal_move_;
}

void ChessboardColorDialog::setLegal_move(const MColor &newLegal_move)
{
    legal_move_.setValue(newLegal_move);
}

MColor ChessboardColorDialog::last_move() const
{
    return last_move_;
}

void ChessboardColorDialog::setLast_move(const MColor &newLast_move)
{
    last_move_.setValue(newLast_move);
}

MColor ChessboardColorDialog::promotion() const
{
    return promotion_;
}

void ChessboardColorDialog::setPromotion(const MColor &newPromotion)
{
    promotion_.setValue(newPromotion);
}


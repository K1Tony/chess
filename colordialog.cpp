#include "colordialog.h"

MColor &MColor::operator+(const QColor &other)
{
    if (&other == this) return *this;
    this->setRed((red() + other.red()) / 2);
    this->setGreen((green() + other.green()) / 2);
    this->setBlue((blue() + other.blue()) / 2);
    this->setAlpha((alpha() + other.alpha()) / 2);
    return *this;
}

ChessboardColorDialog::ChessboardColorDialog() :
    light_square_(QColor(0xFFEED4)),
    dark_square_(QColor(0xB56F07)),
    legal_move_(QColor("red")),
    last_move_(QColor("yellow")),
    promotion_(QColor("cyan"))
{

}

MColor ChessboardColorDialog::light_square() const
{
    return light_square_;
}

void ChessboardColorDialog::setLight_square(const MColor &newLight_square)
{
    light_square_ = newLight_square;
}

MColor ChessboardColorDialog::dark_square() const
{
    return dark_square_;
}

void ChessboardColorDialog::setDark_square(const MColor &newDark_square)
{
    dark_square_ = newDark_square;
}

MColor ChessboardColorDialog::legal_move() const
{
    return legal_move_;
}

void ChessboardColorDialog::setLegal_move(const MColor &newLegal_move)
{
    legal_move_ = newLegal_move;
}

MColor ChessboardColorDialog::last_move() const
{
    return last_move_;
}

void ChessboardColorDialog::setLast_move(const MColor &newLast_move)
{
    last_move_ = newLast_move;
}

MColor ChessboardColorDialog::promotion() const
{
    return promotion_;
}

void ChessboardColorDialog::setPromotion(const MColor &newPromotion)
{
    promotion_ = newPromotion;
}

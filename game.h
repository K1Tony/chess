#ifndef GAME_H
#define GAME_H

#include "FEN.h"

#include <QMouseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

class Game : public QGroupBox
{
public:
    Game();

    FEN &fen() {return fen_;}

    void setFEN(const FEN &fen) {fen_ = fen;}

    QString name() const {return name_;}

    void set_name(const QString &name);

    std::unique_ptr<QPushButton> &action_button() {return action_;}

private:
    std::unique_ptr<QLabel> name_label_;
    std::unique_ptr<QPushButton> action_;
    FEN fen_;
    QString name_;
};

#endif // GAME_H

#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

#include "piece.h"
#include "QScrollArea"

#include <QGroupBox>
#include <qlabel.h>

struct Move {
    Position old_, new_;
    std::shared_ptr<Piece> piece_, promotion_into_;
    bool take_, check_, mate_;
    SpecialMoveTag special_;

    Move() = default;
    Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece);
};

class MoveBox : public QGroupBox {
    Q_OBJECT

public:
    MoveBox(QWidget *parent = Q_NULLPTR) : QGroupBox(parent) {}

    void set_move(const Move &move);

private:
    std::unique_ptr<QLabel> white_move_, black_move_;
};

class MoveDialog
{
public:
    MoveDialog();

    [[nodiscard]] int move_count() {return move_count_;}

    void write_move(const Move &move, QScrollArea *scroll_area);

    void undo();

private:
    int move_count_;
    std::vector< std::shared_ptr<MoveBox> > moves_;
};

#endif // MOVEDIALOG_H

#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

#include "piece.h"
#include "QScrollArea"

#include <QGroupBox>
#include <QStandardItem>
#include <qlabel.h>

struct Move {
    Position old_, new_;
    std::shared_ptr<Piece> piece_, promotion_into_;
    bool take_, check_, mate_;
    SpecialMoveTag special_;

    Move() = default;
    Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece);
};

class MoveBox : public QStandardItem {
public:
    MoveBox() : QStandardItem() {}
    MoveBox(const Move &move);
};

class MoveDialog
{
public:
    MoveDialog();

    [[nodiscard]] int move_count() {return move_count_;}

    void write_move(const Move &move);

    void undo();

private:
    int move_count_;
    std::vector< Move > moves_;

};

#endif // MOVEDIALOG_H

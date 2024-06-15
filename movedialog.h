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
    int special_ = -1;

    Move() = default;
    Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece);
};

class MoveBox : public QStandardItem {
public:
    MoveBox() : QStandardItem() {}
    MoveBox(const Move &move, bool has_twin_controller = false);
};

class MoveDialog : public QStandardItemModel
{
public:
    MoveDialog();

    [[nodiscard]] int move_count() {return move_count_;}

    void append_move(const Move &move, bool twin);

    void undo();

    void clear_moves();

private:
    int move_count_;
    std::vector< Move > white_moves_, black_moves_;

    void init();

};

#endif // MOVEDIALOG_H

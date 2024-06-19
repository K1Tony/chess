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

    [[nodiscard]] int max_undo() {return max_undo_;}

    void set_max_undo(int max_undo) {
        if (max_undo < 0)
            max_undo_ = 0;
        else
            max_undo_ = max_undo;
    }

    void append_move(const Move &move, bool twin);

    bool undo();

    void clear_moves();

private:
    int move_count_;
    std::vector< Move > white_moves_, black_moves_;
    int undo_count_ = 0;

    int max_undo_ = 5;

    void init();

};

#endif // MOVEDIALOG_H

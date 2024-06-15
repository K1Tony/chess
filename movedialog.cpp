#include "movedialog.h"

Move::Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece) :
    old_(old_pos), new_(new_pos), piece_(piece)
{
    special_ = (SpecialMoveTag) -1;
}

MoveDialog::MoveDialog() {
    moves_.reserve(100);
}

void MoveDialog::write_move(const Move &move)
{
    if (move.piece_->color() == BLACK) {
        move_count_++;
    }
    moves_.push_back(move);
}

MoveBox::MoveBox(const Move &move) : QStandardItem()
{
    QString text;

    if (move.special_ == LONG_CASTLING){
        text = "O-O-O";
    } else if (move.special_ == SHORT_CASTLING) {
        text = "O-O";
    }
    else {
        text.append(move.piece_->code());
        if (move.take_)
            text.append('x');
        text.append(move.new_.to_string(true));
        if (move.check_)
            text.append('+');
        else if (move.mate_)
            text.append('#');
        if (move.special_ == EN_PASSANT)
            text.append('~');
        else if (move.promotion_into_.get() != nullptr)
            text.append(QString('=').append(move.promotion_into_->code()));
    }
    setText(text);
}

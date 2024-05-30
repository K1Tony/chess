#include "movedialog.h"

Move::Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece) :
    old_(old_pos), new_(new_pos), piece_(piece)
{
    special_ = (SpecialMoveTag) -1;
}

void MoveBox::set_move(const Move &move)
{
    std::unique_ptr<QLabel> &label = move.piece_->color() == WHITE ? white_move_ : black_move_;
    QString text(move.piece_->code());
    if (move.special_ == LONG_CASTLING) {
        text = QString("O-O-O");
    } else if (move.special_ == SHORT_CASTLING) {
        text = QString("O-O");
    } else {
        if (move.take_){
            if (move.piece_->tag() == PAWN)
                text.append(move.old_.to_string(true).at(0));
            text.append('x');
            if (move.special_ == EN_PASSANT)
                text.append('~');
        }
        text.append(move.new_.to_string(true));
        if (move.promotion_into_.get())
            text.append('=').append(move.promotion_into_->code());
    }
    if (move.check_)
        text.append('+');
    else if (move.mate_)
        text.append('#');

    label->setText(text);
}

MoveDialog::MoveDialog() {}

void MoveDialog::write_move(const Move &move, QScrollArea *scroll_area)
{
    if (move.piece_->color() == BLACK) {
        move_count_++;
        moves_.back()->set_move(move);
    } else {
        auto move_box = std::make_shared<MoveBox>();
        move_box->set_move(move);
        moves_.push_back(move_box);
        scroll_area->addScrollBarWidget(move_box.get(), Qt::AlignCenter);
    }
}

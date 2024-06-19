#include "movedialog.h"

Move::Move(const Position &old_pos, const Position &new_pos, std::shared_ptr<Piece> &piece) :
    old_(old_pos), new_(new_pos), piece_(piece), take_(false), check_(false), mate_(false), special_(-1)
{
}


MoveBox::MoveBox(const Move &move, bool has_twin_controller) : QStandardItem()
{
    QString text;
    setFlags(flags() & ~Qt::ItemIsEditable);
    setTextAlignment(Qt::AlignCenter);
    if (move.special_ == LONG_CASTLING){
        text = "O-O-O";
    } else if (move.special_ == SHORT_CASTLING) {
        text = "O-O";
    }
    else {
        if (move.piece_->tag() != PAWN)
            text.append(move.piece_->code());
        if (has_twin_controller)
            text.append((QChar) ('a' + move.old_.file_));
        if (move.take_){
            if (move.piece_->tag() == PAWN)
                text.append((QChar) ('a' + move.old_.file_));
            text.append('x');
        }
        text.append(move.new_.to_string(true));
        if (move.special_ == EN_PASSANT)
            text.append('~');
        else if (move.promotion_into_.get() != nullptr)
            text.append(QString('=').append(move.promotion_into_->code()));
    }
    if (move.mate_)
        text.append('#');
    else if (move.check_)
        text.append('+');
    setText(text);
}

MoveDialog::MoveDialog() : QStandardItemModel()
{
    init();
}

void MoveDialog::append_move(const Move &move, bool twin)
{
    std::vector<Move> &moves = move.piece_->color() == WHITE ? white_moves_ : black_moves_;

    // white: 0, black: 1
    int col = move.piece_->color();
    moves.push_back(move);
    setItem(move_count_, col, new MoveBox(move, twin));
    move_count_ += col;
}

bool MoveDialog::undo()
{
    if (undo_count_ == max_undo_ || move_count_ == 0)
        return false;
    move_count_--;
    undo_count_++;
    white_moves_.pop_back();
    black_moves_.pop_back();

    setItem(black_moves_.size(), 1, nullptr);
    removeRow((int) white_moves_.size());

    return true;
}

void MoveDialog::clear_moves()
{
    clear();
    init();
}

void MoveDialog::init()
{
    move_count_ = 0;
    undo_count_ = 0;
    auto white = new QStandardItem(QObject::tr("White"));
    auto black = new QStandardItem(QObject::tr("Black"));
    setHorizontalHeaderItem(0, white);
    setHorizontalHeaderItem(1, black);
    setColumnCount(2);
}

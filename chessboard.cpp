#include "chessboard.h"

bool Chessboard::is_attacked(const Position &position)
{
    std::unique_ptr< std::map< Position, std::shared_ptr<Piece> > > &attacking_pieces =
        turn_ == WHITE ? black_pieces_ : white_pieces_;

    for (auto &pair : *attacking_pieces) {
        std::vector<Position> moves = pair.second->legal_moves();
        for (auto &move : moves) {
            if (move == position) return true;
        }
    }
    return false;
}

void Chessboard::reset_square_colors()
{
    for (int i = 0; i < 64; i++) {
        std::unique_ptr<Square> &square = squares_[i / 8][i % 8];
        MColor basic_bg = (i / 8 + i % 8) % 2 == 1 ? color_dialog_.light_square() : color_dialog_.dark_square();

        if (square->is_highlighted()) {
            square->set_background_color(basic_bg + color_dialog_.legal_move());
        } else if (Position(i % 8, i / 8 + 1) == last_move_.old_ || Position(i % 8, i / 8 + 1) == last_move_.new_) {
            square->set_background_color(basic_bg + color_dialog_.last_move());
        } else {
            square->set_background_color(basic_bg);
        }
    }
}

void Chessboard::set_available_moves()
{
    for (auto &pair : *white_pieces_) {
        pair.second->__legal_moves().clear();
        pair.second->available_moves(white_pieces_, black_pieces_);
    }
    for (auto &pair : *black_pieces_) {
        pair.second->__legal_moves().clear();
        pair.second->available_moves(white_pieces_, black_pieces_);
    }
}

void Chessboard::set_available_moves(PieceColor color)
{
    auto &pieces = color == WHITE ? white_pieces_ : black_pieces_;
    for (auto &pair : *pieces) {
        pair.second->__legal_moves().clear();
        pair.second->available_moves(white_pieces_, black_pieces_);
    }
}

bool Chessboard::scan_checks()
{
    auto &king = turn_ == WHITE ? white_king_ : black_king_;
    return is_attacked(king->position());
}

void Chessboard::trim_legal_moves()
{
    auto &pieces = turn_ == WHITE ? white_pieces_ : black_pieces_;
    auto &enemies = turn_ == WHITE ? black_pieces_ : white_pieces_;

    // COPY MUST STAY!
    std::map< Position, std::shared_ptr<Piece> > piece_copy(*pieces);
    PieceColor opposite = turn_ == WHITE ? BLACK : WHITE;
    legal_moves_count_ = 0;

    for (auto &pair : piece_copy) {
        pieces->erase(pair.first);
        std::vector<Position> moves;
        moves.reserve(28);
        for (Position &p : pair.second->legal_moves()) {
            bool take = false;
            pair.second->set_position(p);
            pieces->insert({p, pair.second});
            std::shared_ptr<Piece> enemy;
            if (enemies->count(p) > 0) {
                enemy = enemies->at(p);
                enemies->erase(p);
                take = true;
            }
            set_available_moves(opposite);
            if (!scan_checks()){
                moves.push_back(p);
                legal_moves_count_++;
            }
            pieces->erase(p);
            if (take) {
                enemies->insert({p, enemy});
            }
        }
        pair.second->set_position(pair.first);
        pair.second->__set_legal_moves(moves);
        pieces->insert(pair);
        set_available_moves(opposite);
    }

}

void Chessboard::check_for_mate()
{
    mate_property_->setValue(scan_checks() && legal_moves_count_ == 0);
}

void Chessboard::check_for_draw()
{
    if (legal_moves_count_ == 0 && !scan_checks()) {
        draw_property_->setValue(true);
        return;
    }
    typedef std::unique_ptr< std::map< Position, std::shared_ptr<Piece> > > piece_map;

    auto check = [] (piece_map &pieces) -> bool {

        int bishop_count = 0;
        for (auto &pair : *pieces) {
            PieceTag tag = pair.second->tag();
            if (tag == PAWN || tag == QUEEN || tag == ROOK)
                return false;
            if (tag == BISHOP) {
                bishop_count++;
            } else if (tag == KNIGHT && bishop_count >= 1) {
                return false;
            }
        }
        return bishop_count <= 1;
    };

    piece_map &white = white_pieces_, &black = black_pieces_;
    draw_property_->setValue(check(white) && check(black));
}

void Chessboard::set_board()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares_[i][j]->setPixmap(blank_);
            squares_[i][j]->set_background_color((i + j) % 2 == 0 ? color_dialog_.dark_square() : color_dialog_.light_square());
        }
    }
    white_pieces_->clear();
    black_pieces_->clear();
    for (int i = 0; i < 8; i++) {
        Position white_pawn(i, 2), black_pawn(i, 7), white_piece(i, 1), black_piece(i, 8);
        white_pieces_->insert({white_pawn, std::make_shared<Pawn>(white_pawn, WHITE)});
        black_pieces_->insert({black_pawn, std::make_shared<Pawn>(black_pawn, BLACK)});
        if (i == A || i == H) {
            white_pieces_->insert({white_piece, std::make_shared<Rook>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_shared<Rook>(black_piece, BLACK)});
        } else if (i == B || i == G) {
            white_pieces_->insert({white_piece, std::make_shared<Knight>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_shared<Knight>(black_piece, BLACK)});
        } else if (i == C || i == F) {
            white_pieces_->insert({white_piece, std::make_shared<Bishop>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_shared<Bishop>(black_piece, BLACK)});
        } else if (i == D) {
            white_pieces_->insert({white_piece, std::make_shared<Queen>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_shared<Queen>(black_piece, BLACK)});
        } else {
            white_king_ = std::make_shared<King>(white_piece, WHITE);
            black_king_ = std::make_shared<King>(black_piece, BLACK);
            white_pieces_->insert({white_piece, white_king_});
            black_pieces_->insert({black_piece, black_king_});
        }
    }

    for (auto &pair : *white_pieces_) {
        squares_[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }
    for (auto &pair : *black_pieces_) {
        squares_[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }
    turn_ = WHITE;
    if (!white_up)
        flip_chessboard();
    last_move_ = Move();
    moves_count_ = 0;
    set_available_moves();
}

void Chessboard::flip_chessboard()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (white_up) {
                layout_->addWidget(squares_[i][j].get(), i + 2, 8 - j);
            } else {
                layout_->addWidget(squares_[i][j].get(), 9 - i, j + 1);
            }
        }
    }
    white_up = !white_up;
}

int Chessboard::moves_count() const
{
    return moves_count_;
}

std::shared_ptr<QProperty<bool> > Chessboard::mate_property() const
{
    return mate_property_;
}

std::shared_ptr<QProperty<bool> > Chessboard::draw_property() const
{
    return draw_property_;
}

bool Chessboard::check_promotion()
{
    return (selected_piece_->tag() == PAWN &&
            (selected_piece_->position().rank_ == 1 || selected_piece_->position().rank_ == 8));
}


void Chessboard::check_castling(SpecialMoveTag castling_style, PieceColor color)
{
    if (selected_piece_->tag() != KING || selected_piece_->moved()) return;
    int rank = color == WHITE ? 1 : 8;
    File file = castling_style == LONG_CASTLING ? C : G;
    Position rook_pos(castling_style == LONG_CASTLING ? A : H, rank);
    std::shared_ptr<Piece> rook = piece_at(rook_pos);
    if (rook.get() == nullptr || rook->tag() != ROOK || rook->color() != color || rook->moved()) return;
    int begin_iteration = castling_style == LONG_CASTLING ? B : F;
    int end_iteration = castling_style == LONG_CASTLING ? E : H;
    if (scan_checks() || is_attacked(rook_pos)) return;

    for (; begin_iteration < end_iteration; begin_iteration++) {
        Position p(begin_iteration, rank);
        if (piece_at(p).get() != nullptr || is_attacked(p)) {
            return;
        }
    }
    highlighted_moves().push_back(Position(file, rank));
    special_moves().insert({castling_style, Position(file, rank)});
}

void Chessboard::castle(SpecialMoveTag castling_style, PieceColor color)
{
    Position rook_initial(castling_style == LONG_CASTLING ? A : H, color == WHITE ? 1 : 8),
        rook_destination(castling_style == LONG_CASTLING ? D : F, color == WHITE ? 1 : 8);
    at(rook_destination)->setPixmap(at(rook_initial)->pixmap());
    at(rook_initial)->setPixmap(blank());
    std::unique_ptr< std::map< Position, std::shared_ptr<Piece> > > &pieces =
        color == WHITE ? white_pieces_ : black_pieces();
    pieces->insert({rook_destination, pieces->at(rook_initial)});
    pieces->erase(rook_initial);
    pieces->at(rook_destination)->set_position(rook_destination);
}

Chessboard::Chessboard(int square_size, QGridLayout *layout, QWidget *parent)
{
    parent_.reset(parent);
    layout_.reset(layout);

    promotion_dialog_.reset(new PromotionDialog());

    mate_property_.reset(new QProperty<bool>());
    draw_property_.reset(new QProperty<bool>());

    light_square_change_ = color_dialog_.light_square().addNotifier([this] () {this->reset_square_colors();});
    dark_square_change_ = color_dialog_.dark_square().addNotifier([this] () {this->reset_square_colors();});
    legal_move_change_ = color_dialog_.legal_move().addNotifier([this] () {this->reset_square_colors();});
    last_move_change_ = color_dialog_.last_move().addNotifier([this] () {this->reset_square_colors();});
    promotion_change_ = color_dialog_.promotion().addNotifier([this] () {this->reset_square_colors();});

    for (auto &pair : promotion_dialog_->squares()) {
        pair.second->setMinimumSize(square_size, square_size);
        pair.second->setMaximumSize(square_size, square_size);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto *square = new Square(parent);
            square->set_attributes(i + 1, (File) j);
            square->setAutoFillBackground(true);
            square->setScaledContents(true);
            square->setMinimumSize(square_size, square_size);
            square->setMaximumSize(square_size, square_size);
            if ((i + j) % 2 == 0) {
                square->set_background_color(color_dialog_.dark_square());
            } else {
                square->set_background_color(color_dialog_.light_square());
            }
            squares_[i][j].reset(square);
            layout->addWidget(square, 9 - i, j + 1);
        }
    }

    set_board();

    highlighted_moves_.reserve(28);
    set_available_moves();
}

std::array< std::unique_ptr<Square>, 8 >& Chessboard::operator[](int rank)
{
    return squares_[rank];
}

std::unique_ptr<Square> &Chessboard::at(int file, int rank)
{
    return squares_[rank - 1][file];
}

std::unique_ptr<Square> &Chessboard::at(File file, int rank)
{
    return squares_[rank - 1][file];
}

std::unique_ptr<Square> &Chessboard::at(const Position &position)
{
    return at(position.file_, position.rank_);
}

void Chessboard::reset_move_highlights()
{
    for (Position &p : highlighted_moves_) {
        at(p)->set_highlight(false);
        MColor color = (p.file_ + p.rank_) % 2 == 0 ? color_dialog_.light_square() : color_dialog_.dark_square();

        if (last_move_.old_ == p || last_move_.new_ == p) {
            at(p)->set_background_color(color + color_dialog_.last_move());
        }
        else {
            at(p)->set_background_color(color);
        }
        // at(p)->disconnect(at(selected_piece_->position()).get());
    }
    selected_piece_.reset();
}

void Chessboard::select_piece(Position &position, PieceColor color)
{
    reset_move_highlights();
    std::shared_ptr<Piece> &piece = color == WHITE ? white_pieces_->at(position) : black_pieces_->at(position);
    selected_piece_ = piece;
    highlighted_moves_ = piece->legal_moves();
    auto &pieces = turn_ == WHITE ? white_pieces_ : black_pieces_;

    // Check for en passant
    if (last_move_.piece_.get() != nullptr && piece->tag() == PAWN &&
        Pawn::check_en_passant(last_move_, piece)) {
        int available_rank = piece->color() == WHITE ? 6 : 3;
        Position pos(last_move().old_.file_, available_rank), initial = piece->position();
        piece->set_position(pos);
        pieces->erase(initial);
        pieces->insert({pos, piece});
        set_available_moves((PieceColor) ((turn_ + 1) % 2));
        if (!scan_checks()){
            special_moves_.insert({EN_PASSANT, pos});
            highlighted_moves_.push_back(pos);
        }
        piece->set_position(initial);
        pieces->erase(pos);
        pieces->insert({initial, piece});
        set_available_moves((PieceColor) ((turn_ + 1) % 2));
    }

    // Check for castling
    if (piece->color() == WHITE){
        check_castling(LONG_CASTLING, WHITE);
        check_castling(SHORT_CASTLING, WHITE);
    } else {
        check_castling(LONG_CASTLING, BLACK);
        check_castling(SHORT_CASTLING, BLACK);
    }

    // Check for promotions
    // #TODO
    for (auto &p : highlighted_moves_) {
        MColor color = (p.file_ + p.rank_) % 2 == 0 ? color_dialog_.light_square() : color_dialog_.dark_square();
        at(p)->set_background_color(color + color_dialog_.legal_move());
        at(p)->set_highlight(true);
        // at(p)->connect(at(p).get(), &Square::clicked, at(p).get(), [this, p] () {
        //     this->move(this->selected_piece(), p);
        // });
    }
}

void Chessboard::move(std::shared_ptr<Piece> &piece, const Position destination)
{
    if (moves_count_ > 0) {
        at(last_move_.old_)->set_background_color(
            (last_move_.old_.rank_ + last_move_.old_.file_) % 2 == 0 ? color_dialog_.light_square() : color_dialog_.dark_square());
        at(last_move_.new_)->set_background_color(
            (last_move_.new_.rank_ + last_move_.new_.file_) % 2 == 0 ? color_dialog_.light_square() : color_dialog_.dark_square());
    }

    last_move_.old_ = piece->position();
    last_move_.new_ = destination;
    last_move_.piece_ = piece;

    piece->set_moved();

    auto &ally_pieces = piece->color() == WHITE ? white_pieces_ : black_pieces_;
    auto &enemy_pieces = piece->color() == WHITE ? black_pieces_ : white_pieces_;

    PieceColor opposite = turn_ % 2 == 0 ? BLACK : WHITE;

    at(piece->position())->setPixmap(blank_);
    at(destination)->setPixmap(*piece->pixmap());
    ally_pieces->erase(piece->position());
    ally_pieces->insert({destination, piece});
    piece->set_position(destination);
    if (enemy_pieces->count(destination) > 0) {
        enemy_pieces->erase(destination);
    } else if (special_moves_.count(EN_PASSANT) > 0 && destination == special_moves_.at(EN_PASSANT)) {
        Position ep(destination.file_, 5);
        at(ep)->setPixmap(blank_);
        enemy_pieces->erase(ep);
    } else if (special_moves_.count(SHORT_CASTLING) > 0 && destination == special_moves_.at(SHORT_CASTLING)) {
        castle(SHORT_CASTLING, turn());
    } else if (special_moves_.count(LONG_CASTLING) > 0 && destination == special_moves_.at(LONG_CASTLING)) {
        castle(LONG_CASTLING, turn());
    }
    turn_ = opposite;

    piece->set_position(destination);
    special_moves_.clear();
    set_available_moves();
    trim_legal_moves();

    at(last_move_.old_)->set_background_color(at(last_move_.old_)->background_color() + color_dialog_.last_move());
    at(last_move_.new_)->set_background_color(at(last_move_.new_)->background_color() + color_dialog_.last_move());

    moves_count_++;

    flip_chessboard();
}

void Chessboard::move(const Position destination)
{
    move(selected_piece_, destination);
}

std::shared_ptr<Piece> Chessboard::piece_at(const Position &position)
{
    if (white_pieces_->count(position) > 0) {
        return white_pieces_->at(position);
    } else if (black_pieces_->count(position) > 0) {
        return black_pieces_->at(position);
    }
    Piece *piece = nullptr;
    std::shared_ptr<Piece> nptr(piece);
    return nptr;
}

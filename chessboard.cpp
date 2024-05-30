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
    std::map< Position, std::shared_ptr<Piece> > piece_copy(*pieces);
    PieceColor opposite = turn_ == WHITE ? BLACK : WHITE;

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
    if (piece_at(rook_pos)->moved()) return;
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
                square->setStyleSheet(base_dark_color_);
            } else {
                square->setStyleSheet(base_light_color_);
            }
            squares_[i][j].reset(square);
            layout->addWidget(square, 9 - i, j + 1);
        }
    }

    white_pieces_.reset(new std::map<Position, std::shared_ptr<Piece> >);
    black_pieces_.reset(new std::map<Position, std::shared_ptr<Piece> >);

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
    for (auto &p : highlighted_moves_) {
        if ((p.rank_ + p.file_) % 2 == 1) {
            at(p)->setStyleSheet(base_dark_color_);
        } else {
            at(p)->setStyleSheet(base_light_color_);
        }
        at(p)->set_highlight(false);
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
    if (last_move_.moved_piece_.get() != nullptr && piece->tag() == PAWN &&
        Pawn::check_en_passant(last_move_, piece)) {
        int available_rank = piece->color() == WHITE ? 6 : 3;
        Position pos(last_move_.old_.file_, available_rank), initial = piece->position();
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
        at(p)->setStyleSheet("QLabel {background-color : red}");
        at(p)->set_highlight(true);
        // at(p)->connect(at(p).get(), &Square::clicked, at(p).get(), [this, p] () {
        //     this->move(this->selected_piece(), p);
        // });
    }
}

void Chessboard::move(std::shared_ptr<Piece> &piece, const Position destination)
{
    last_move_.old_ = piece->position();
    last_move_.new_ = destination;
    last_move_.moved_piece_ = piece;
    piece->set_moved();
    if (piece->color() == WHITE) {
        at(piece->position())->setPixmap(blank_);
        at(destination)->setPixmap(*piece->pixmap());
        white_pieces_->erase(piece->position());
        white_pieces_->insert({destination, piece});
        piece->set_position(destination);
        if (black_pieces_->count(destination) > 0) {
            black_pieces_->erase(destination);
        } else if (special_moves_.count(EN_PASSANT) > 0 && destination == special_moves_.at(EN_PASSANT)) {
            Position ep(destination.file_, 5);
            at(ep)->setPixmap(blank_);
            black_pieces_->erase(ep);
        } else if (special_moves_.count(SHORT_CASTLING) > 0 && destination == special_moves_.at(SHORT_CASTLING)) {
            castle(SHORT_CASTLING, WHITE);
        } else if (special_moves_.count(LONG_CASTLING) > 0 && destination == special_moves_.at(LONG_CASTLING)) {
            castle(LONG_CASTLING, WHITE);
        }
        // if (check_promotion()) {
        //     promotion_dialog_->init_promotions(piece->position(), piece);
        //     promotion_dialog_->list_promotions(piece->position(), layout_.get());
        // }
        turn_ = BLACK;
    } else {
        at(piece->position())->setPixmap(blank_);
        at(destination)->setPixmap(*piece->pixmap());
        black_pieces_->erase(piece->position());
        black_pieces_->insert({destination, piece});
        piece->set_position(destination);
        if (white_pieces_->count(destination) > 0) {
            white_pieces_->erase(destination);
        } else if (special_moves_.count(EN_PASSANT) > 0 && destination == special_moves_.at(EN_PASSANT)) {
            Position ep(destination.file_, 4);
            at(ep)->setPixmap(blank_);
            white_pieces_->erase(ep);
        } else if (special_moves_.count(SHORT_CASTLING) > 0 && destination == special_moves_.at(SHORT_CASTLING)) {
            castle(SHORT_CASTLING, BLACK);
        } else if (special_moves_.count(LONG_CASTLING) > 0 && destination == special_moves_.at(LONG_CASTLING)) {
            castle(LONG_CASTLING, BLACK);
        }
        // if (check_promotion()) {
        //     promotion_dialog_->init_promotions(piece->position(), piece);
        //     promotion_dialog_->list_promotions(piece->position(), layout_.get());
        // }
        turn_ = WHITE;
    }
    piece->set_position(destination);
    special_moves_.clear();
    set_available_moves();
    trim_legal_moves();
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

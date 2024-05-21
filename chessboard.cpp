#include "chessboard.h"

Chessboard::Chessboard(int square_size, QGridLayout *layout, QWidget *parent)
{
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
            layout->addWidget(square, 7 - i, j);
        }
    }

    white_pieces_.reset(new std::map<Position, std::shared_ptr<Piece> >);
    black_pieces_.reset(new std::map<Position, std::shared_ptr<Piece> >);
    for (int i = 0; i < 8; i++) {
        Position white_pawn(i, 2), black_pawn(i, 7), white_piece(i, 1), black_piece(i, 8);
        white_pieces_->insert({white_pawn, std::make_unique<Pawn>(white_pawn, WHITE)});
        black_pieces_->insert({black_pawn, std::make_unique<Pawn>(black_pawn, BLACK)});
        if (i == A || i == H) {
            white_pieces_->insert({white_piece, std::make_unique<Rook>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Rook>(black_piece, BLACK)});
        } else if (i == B || i == G) {
            white_pieces_->insert({white_piece, std::make_unique<Knight>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Knight>(black_piece, BLACK)});
        } else if (i == C || i == F) {
            white_pieces_->insert({white_piece, std::make_unique<Bishop>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Bishop>(black_piece, BLACK)});
        } else if (i == D) {
            white_pieces_->insert({white_piece, std::make_unique<Queen>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<Queen>(black_piece, BLACK)});
        } else {
            white_pieces_->insert({white_piece, std::make_unique<King>(white_piece, WHITE)});
            black_pieces_->insert({black_piece, std::make_unique<King>(black_piece, BLACK)});
        }
    }

    for (auto &pair : *white_pieces_) {
        squares_[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }
    for (auto &pair : *black_pieces_) {
        squares_[pair.first.rank_ - 1][pair.first.file_]->setPixmap(*pair.second->pixmap());
    }

    highlighted_moves_.reserve(28);
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
    }
}

void Chessboard::select_piece(Position &position, PieceColor color)
{
    std::shared_ptr<Piece> &piece = color == WHITE ? white_pieces_->at(position) : black_pieces_->at(position);
    selected_piece_ = piece;
    reset_move_highlights();
    highlighted_moves_ = piece->legal_moves(white_pieces_, black_pieces_);
    for (auto &p : highlighted_moves_) {
        at(p)->setStyleSheet("QLabel {background-color : red}");
    }
}

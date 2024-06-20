#include "fen.h"

#include <Bishop.h>
#include <King.h>
#include <Knight.h>
#include <Pawn.h>
#include <Queen.h>
#include <Rook.h>

FEN::FEN() {
    piece_placement_.resize(8);
}


// Assumes fen is written correctly. If it isn't the chessboard will ignore impropper
// codes
FEN::FEN(QString fen)
{
    QList params = fen.split(' ');
    if (params.size() != 6)
        return;
    piece_placement_ = params[0].split('/');
    turn_ = params[1];
    castling_rights_ = params[3];
    halfmoves_ = params[4];
    fullmoves_ = params[5];
}

QString FEN::to_string()
{
    QString result;
    std::for_each(piece_placement_.begin(), piece_placement_.end(),
                  [&result] (const QString &str) -> void {result.append(str).append('/');});
    result.removeLast().append(' ').append(turn_);
    result.append(' ').append(castling_rights_);
    result.append(' ').append(en_passant_);
    result.append(' ').append(halfmoves_);
    result.append(' ').append(fullmoves_);
    return result;
}

FEN FEN::update(const Position &_old, const Position &_new)
{
    return FEN(FEN::basic_fen);
}

void FEN::write(std::unique_ptr<piece_map> &white_pieces, std::unique_ptr<piece_map> &black_pieces)
const
{
    int rank = 8;
    int file = A;
    for (const QString &str : piece_placement_) {
        for (const QChar &c : str) {
            Position p(file, rank);
            if (c.isDigit()) {
                file += c.unicode() - '0';
                continue;
            }
            PieceColor color = c.isLower() ? BLACK : WHITE;
            std::unique_ptr<piece_map> &pieces = color == WHITE ? white_pieces : black_pieces;
            switch (c.toUpper().unicode()) {
            case 'P':
                pieces->insert({p, std::make_shared<Pawn>(p, color)});
                break;
            case 'N':
                pieces->insert({p, std::make_shared<Knight>(p, color)});
                break;
            case 'B':
                pieces->insert({p, std::make_shared<Bishop>(p, color)});
                break;
            case 'R':
                pieces->insert({p, std::make_shared<Rook>(p, color)});
                break;
            case 'Q':
                pieces->insert({p, std::make_shared<Queen>(p, color)});
                break;
            case 'K':
                pieces->insert({p, std::make_shared<King>(p, color)});
            default:
                break;
            }
            file++;
        }
        rank--;
        file = A;
    }
}

FEN &FEN::read(std::unique_ptr<piece_map> &white_pieces, std::unique_ptr<piece_map> &black_pieces)
{

    int skip = 0;
    Position prev(A, 8);
    for (int rank = 8; rank > 0; rank--) {
        for (int file = A; file <= H; file++) {
            Position p(file, rank);
            if (white_pieces->count(p) > 0) {
                if (skip > 0) {
                    piece_placement_[8 - rank].append((QChar) ('0' + skip));
                    skip = 0;
                }
                piece_placement_[8 - rank].append(white_pieces->at(p)->code());
            } else if (black_pieces->count(p) > 0) {
                if (skip > 0) {
                    piece_placement_[8 - rank].append((QChar) ('0' + skip));
                    skip = 0;
                }
                piece_placement_[8 - rank].append(black_pieces->at(p)->code().toLower());
            } else {
                skip++;
            }
        }
        if (skip > 0) {
            piece_placement_[8 - rank].append((QChar) ('0' + skip));
            skip = 0;
        }
    }
    return *this;
}

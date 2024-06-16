#ifndef FEN_H
#define FEN_H

#include <QString>
#include "QList"
#include "properties.h"
#include "piece.h"


class FEN
{
    typedef std::map<Position, std::shared_ptr<Piece> > piece_map;
public:
    const static inline QString basic_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 0";

    FEN();
    FEN(QString fen);

    QString to_string();

    FEN update(const Position &_old, const Position &_new);

    FEN &set_en_passant(const QString &eps);

    FEN &update_castling_rights(SpecialMoveTag style, PieceColor color);

    FEN &write(std::unique_ptr<piece_map> &white_pieces, std::unique_ptr<piece_map> &black_pieces);

    FEN &read(std::unique_ptr<piece_map> &white_pieces, std::unique_ptr<piece_map> &black_pieces);

private:
    QStringList piece_placement_;
    QString turn_ = "w", castling_rights_ = "QKqk", en_passant_ = "-",
        halfmoves_ = "0", fullmoves_ = "0";
};

#endif // FEN_H

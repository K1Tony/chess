#ifndef PROPERTIES_H
#define PROPERTIES_H

enum File{
    A, B, C, D, E, F, G, H
};

enum PieceColor{
    WHITE, BLACK
};

enum PieceTag{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum SpecialMoveTag{
    EN_PASSANT, CASTLING, PROMOTION
};

typedef struct Position{
    File file_;
    int rank_;

    Position() = default;
    Position(int file, int rank) : file_((File) file), rank_(rank) {}
    Position(File file, int rank) : file_(file), rank_(rank) {}

    bool operator<(const Position &other) const {
        return file_ == other.file_ ? rank_ < other.rank_ : file_ < other.file_;
    }

    bool operator==(const Position &other) const {
        return file_ == other.file_ && rank_ == other.rank_;
    }

    bool in_bounds() const {return 0 <= file_ && file_ <= 7 && 0 < rank_ && rank_ <= 8;}
} Position;

#endif // PROPERTIES_H

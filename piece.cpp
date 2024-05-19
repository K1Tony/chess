#include "piece.h"

/*
 * Function checks if a position is taken by another piece, and if that piece can be taken
 *
 * @param position: position to be analysed;
 * @param positionsA: set of positions of ally pieces
 * @param positionsB: set of positions of enemy pieces
 * @param result: vector of legal moves
 *
 * @return: true - signal that you can't move further, false - you can
 *
 * If an ally is occupying the position - you can't move there, whereas
 * if an enemy is there - you can, however you can't move further.
*/
bool check_placement(const Position &position, const std::set<Position> &positionsA, const std::set<Position> &positionsB, std::vector<Position> &result) {
    if (positionsA.count(position) > 0) return true;
    result.push_back(position);
    if (positionsB.count(position) > 0) return true;
    return false;
}

void fill_rook_moves(const Position &position, const std::set<Position> &positionsA, const std::set<Position> &positionsB, std::vector<Position> &result)
{
    File file = position.file_;
    int rank = position.rank_;

    // Check the squares above
    for (int i = rank + 1; i <= 8; i++) {
        Position up(file, i);
        if (check_placement(up, positionsA, positionsB, result)) break;
    }

    // Check the squares below
    for (int i = rank - 1; i >= 0; i--) {
        Position down(file, i);
        if (check_placement(down, positionsA, positionsB, result)) break;
    }

    // Check the squares to the right
    for (int i = file + 1; i < 8; i++) {
        Position right(i, rank);
        if (check_placement(right, positionsA, positionsB, result)) break;
    }

    // Check the squares to the left
    for (int i = file - 1; i >= 0; i--) {
        Position left(i, rank);
        if (check_placement(left, positionsA, positionsB, result)) break;
    }
}

void fill_diagonals(const Position &position, const std::set<Position> &positionsA, const std::set<Position> &positionsB, std::vector<Position> &result)
{
    File file = position.file_;
    int rank = position.rank_;

    // Check north-east direction
    for (int i = 1; i <= std::min(8 - rank, 7 - file); i++) {
        Position north_east(file + i, rank + i);
        if (check_placement(north_east, positionsA, positionsB, result)) break;
    }

    // Check south-east direction
    for (int i = 1; i <= std::min(rank - 1, 7 - file); i++) {
        Position south_east(file + i, rank - i);
        if (check_placement(south_east, positionsA, positionsB, result)) break;
    }

    // Check south-west direction
    for (int i = 1; i <= std::min(rank - 1, file + 0); i++) {
        Position south_west(file - i, rank - i);
        if (check_placement(south_west, positionsA, positionsB, result)) break;
    }

    // Check north-west direction
    for (int i = 1; i <= std::min(8 - rank, file + 0); i++) {
        Position north_west(file - i, rank + i);
        if (check_placement(north_west, positionsA, positionsB, result)) break;
    }

}

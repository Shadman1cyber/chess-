#include "pawn.hpp"
#include <cmath>

Pawn::Pawn(bool is_white, std::string name)
    : Piece(is_white, name) {}

bool Pawn::canMove(const Board& board, std::string destination) const {

    std::string start = board.find_by_piece(symbol());
    if (start.empty())
        return false;

    int direction = getColor() ? 1 : -1;

    int dc = destination[0] - start[0];
    int dr = destination[1] - start[1];

    Piece* target = board.get_piece(destination);

    // Move forward
    if (dc == 0 && dr == direction && !target)
        return true;

    // Double move
    if (dc == 0 && dr == 2 * direction) {
        if ((getColor() && start[1] == '2') || (!getColor() && start[1] == '7')) {

            std::string mid;
            mid += start[0];
            mid += start[1] + direction;

            if (!board.get_piece(mid) && !target)
                return true;
        }
    }

    // Capture
    if (abs(dc) == 1 && dr == direction && target &&
        target->getColor() != getColor())
        return true;

    return false;
}

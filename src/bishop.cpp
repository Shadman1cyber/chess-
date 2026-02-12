#include "bishop.hpp"
#include <cmath>

Bishop::Bishop(bool is_white, std::string name): Piece(is_white, name) {}

bool Bishop::canMove(const Board& board, std::string destination) const {

    std::string start = board.find_by_piece(symbol());
    if (start.empty())
        return false;

    int dc = abs(destination[0] - start[0]);
    int dr = abs(destination[1] - start[1]);

    if (dc == dr) {
        Piece* target = board.get_piece(destination);
        if (!target || target->getColor() != getColor())
            return true;
    }

    return false;
}

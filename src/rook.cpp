#include "rook.hpp"
#include <cmath>


Rook::Rook(bool is_white,std::string name) : Piece(is_white,name) {}

bool Rook::canMove(const Board& board, std::string destination) const {

    std::string start = board.find_by_piece(symbol());
    if (start.empty())
        return false;

    if (start[0] == destination[0] || start[1] == destination[1]) {

        Piece* target = board.get_piece(destination);
        if (!target || target->getColor() != getColor())
            return true;
    }

    return false;
}
